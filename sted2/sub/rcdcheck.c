/* rcdcheck.c

   RCD stay check functions
   compatible to rcdcheck.s

   Made by Studio Breeze. 1998

*/

#include "sted.h"
#include <signal.h>

#ifndef NO_SHM
# include <sys/ipc.h>
# include <sys/shm.h>
#endif /* NO_SHM */

/*extern int rcptomid( char *, int, char ** );*/
#include "rcpconv.h"

extern int open_midi_port( char * );
extern int get_midi_data( void );

#define MAX_BAR      2048            /* max size of measure is 2048 */
int STed_InitMeasureConversion( void );
int STed_MeasureConversion( int track );
static int bar_st[TRK_NUM][MAX_BAR];

void rcd_check( void );
struct RCD_HEAD *rcd;
char rcd_version[5];

char player_name[1024];          /* midi player name */
char midi_port_name[1024];       /* midi_port device name */
int player_flag=0;               /* bit0 : rcp_capable
				    bit1 : sted controllable
				    bit2 : data from shared memory */

#define RCP_CAPABLE (player_flag&(1<<0))
#define STED_CONTROLLABLE (player_flag&(1<<1))
#define DATA_FROM_FILE (player_flag&(1<<2))
#define B_DATA_FROM_FILE (1<<2)
#define CONTROL_FROM_PIPE (player_flag&(1<<3))

static char *_data_adr, *_tone_adr, *_word_adr, *_gsd_adr, *_smf_adr;
static char tmp_file_name[1024];

static int pipe_in_fd, pipe_out_fd, shmid=0;

char *zero_ptr="\0";

static void _play_external_player( void );
static void _stop_external_player( void );
static void _exit_external_player( int );
static void request_midi_data( char * );

static void install_sighandler( void );
static void release_sighandler( void );

static pid_t player_pid=0;

static void null_func ( void ) {};
static void null_func_char ( char a) {};

void rcd_check( void ) {

  int i;
  int alloc_size;

  /* memory allocation */

  alloc_size =
    sizeof(struct RCD_HEAD)+
    sizeof(char)*
    (DATA_ADR_SIZE +
     SMF_ADR_SIZE +
     TONE_ADR_SIZE +
     WORD_ADR_SIZE +
     GSD_ADR_SIZE);

#ifndef NO_SHM
  shmid = shmget( IPC_PRIVATE, alloc_size, IPC_CREAT|0600 );
  if (shmid<0) {
    fprintf(stderr, "sted: cannot allocate shared memory\n");
    exit(1);
  }
  rcd = (struct RCD_HEAD *)shmat(shmid, 0, 0);
#else /* NO_SHM */
  shmid=-1;
  rcd = (struct RCD_HEAD *)malloc( alloc_size );
  if ( rcd == NULL ) {
    fprintf(stderr, "sted: cannot allocate shared memory\n");
    exit(1);
  }
#endif /* NO_SHM */
  _data_adr = (char *)rcd + sizeof(struct RCD_HEAD);
  _smf_adr  = _data_adr + DATA_ADR_SIZE;
  _tone_adr = _smf_adr  + SMF_ADR_SIZE;
  _word_adr = _tone_adr + TONE_ADR_SIZE;
  _gsd_adr  = _word_adr + WORD_ADR_SIZE;


  install_sighandler();

  rcd_version[0] = '3';
  rcd_version[1] = '.';
  rcd_version[2] = '0';
  rcd_version[3] = '1';

  rcd->title[0] = 'R';
  rcd->title[1] = 'C';
  rcd->title[2] = 'D';
  rcd->title[3] = ' ';

  rcd->version[0] = '3';
  rcd->version[1] = '.';
  rcd->version[2] = '0';
  rcd->version[3] = '1';

  rcd->staymark = 0;

  rcd->data_valid = 1;
  rcd->tone_valid = 0;
  rcd->word_valid = 0;
  rcd->gsd_valid = 0;
  rcd->fmt = 1;

  rcd->data_adr = _data_adr;
  rcd->tone_adr = _tone_adr;
  rcd->word_adr = _word_adr;
  rcd->gsd_adr  = _gsd_adr;
  rcd->smf_adr  = _smf_adr;

  rcd->init  = null_func;              /* RCD initialize ? */
  rcd->setup = null_func;              /* RCD setup routine ? */
  rcd->begin = _play_external_player;  /* start playing RCP data */
  rcd->end = _stop_external_player;    /* stop playing RCP data */

  rcd->md_put = put_midi_data;
  rcd->md_get = get_midi_data;
  rcd->md_put2 = null_func_char;
  rcd->mix_out = request_midi_data;

  rcd->act = 0;
  rcd->sts = 1;
  rcd->tar_trk = 0;
  rcd->tar_bar = 0;

  rcd->dummy1[0] = 0;

  rcd->tempo = 64;
  rcd->basetempo = 64;

  rcd->totalcount = 0;
  rcd->filename[0] = 0;
  rcd->tonename[0] = 0;

  rcd->dummy2[0] = 0;

  rcd->bufcap = DATA_ADR_SIZE;

  rcd->MIDI_avl = 0;
  rcd->MIDI_req[0] = 0;

  for( i=0;i<TRK_NUM;i++ ) {
    rcd->active[i]=1;
    rcd->bar[i]=0;
    rcd->step[i]=0;
  }
  rcd->stepcount = 0;
}

void rcd_open_device( void ) {
  open_midi_port( midi_port_name );
  return;
}

void _play_external_player( void ) {

  /* play with external midi player */
  /* the data located from _data_adr to _data_adr+rcd->totalcound */

  int fd = -1;
  int i=0;
  pid_t p;

  int argc;
  char *argv[128];
  char name[1024];
  char buf[256];
  char *a,*a0;
  int cont_inter[2], inter_cont[2];

  if ( STed_InitMeasureConversion() !=0 ) return;

  /* create temporary file name */

  if ( tmp_file_name[0] == '\0' ) {
    if ( !STED_CONTROLLABLE ) {
      player_flag |= B_DATA_FROM_FILE;
    }
    strcpy(tmp_file_name, "/tmp/_sted2_file_XXXXXX");
  }

  /* write out the data file if required */
  /* ( !DATA_FROM_FILE not requires ) */

  if ( DATA_FROM_FILE ) {
    if ( !RCP_CAPABLE ) {
      int smfsize;
      unsigned char *smfdata;

      smfsize = rcpconv( _data_adr, (long)rcd->totalcount, &smfdata, NULL );
      if ( smfsize < -1 ) return;

      fd = mkstemp(tmp_file_name);
      if (fd<0) {
	tmp_file_name[0] = '\0';
	return;
      }
      i = write(fd, smfdata, smfsize);
      close(fd);
      free(smfdata);
      if ( i!=smfsize ) {
	unlink(tmp_file_name);
	tmp_file_name[0] = '\0';
	return;
      }
      strncpy(name, tmp_file_name, 1024);
      strncat(name, ".mid", 1024);
      if (access(name, W_OK)==0) {
	unlink(tmp_file_name);
	tmp_file_name[0] = '\0';
	return;
      }
      if (rename(tmp_file_name, name)) {
	unlink(tmp_file_name);
	tmp_file_name[0] = '\0';
	return;
      }
      strncpy(tmp_file_name, name, 1024);

    } else {  /* RCP_CAPABLE */
      fd = mkstemp(tmp_file_name);
      if (fd<0) {
	tmp_file_name[0] = '\0';
	return;
      }
      i = write(fd, _data_adr, rcd->totalcount);
      close(fd);
      if ( i!=rcd->totalcount ) {
	unlink(tmp_file_name);
	tmp_file_name[0] = '\0';
	return;
      }
      strncpy(name, tmp_file_name, 1024);
      strncat(name, ".r36", 1024);
      if (access(name, W_OK)==0) {
	unlink(tmp_file_name);
	tmp_file_name[0] = '\0';
	return;
      }
      if (rename(tmp_file_name, name)) {
	unlink(tmp_file_name);
	tmp_file_name[0] = '\0';
	return;
      }
      strncpy(tmp_file_name, name, 1024);
    }

  } else { /* !DATA_FROM_FILE */
    if ( !RCP_CAPABLE ) {
      int smfsize;
      unsigned char *smfdata;

      /*smfsize = rcptomid( _data_adr, rcd->totalcount, &smfdata );*/
      smfsize = rcpconv( _data_adr, (long)rcd->totalcount, &smfdata, NULL );
      rcd->totalcount = smfsize;
      if ( smfsize < 0 ) return;
      if ( smfsize>rcd->bufcap ) return;
      memcpy( _smf_adr, smfdata, smfsize );
      free(smfdata);
    }
  }

  /* execute external player */

  if (player_pid==0) {
    if ( STED_CONTROLLABLE&&CONTROL_FROM_PIPE ) {
      if ( pipe(cont_inter)<0 || pipe(inter_cont)<0 ) {
	fprintf(stderr,"sted: cannot create pipe\n");
	exit(1);
      }
    }
    player_pid=fork();
    if ( player_pid!=0 ) {
      signal( SIGCHLD, _exit_external_player );
      rcd->act = 1; /* play */
      rcd->sts = 0; /* run */
      if ( STED_CONTROLLABLE&&CONTROL_FROM_PIPE ) {
	close(cont_inter[0]);
	close(inter_cont[1]);
	pipe_in_fd=inter_cont[0];
	pipe_out_fd=cont_inter[1];
      }
      return;
    }

  } else if ( STED_CONTROLLABLE ) {  /* player_pid != 0 */
    int time=0;
    while( rcd->act==2 ) {
      usleep(1000);
      if ( time++ > 2000 ) { /* time-out after 2 seconts */
	_stop_external_player();
	return;
      }
    }
    rcd->act=0;	/* stop */
    usleep(10000);
    rcd->act=1;	/* play */
    rcd->sts=0;	/* run */
    if ( CONTROL_FROM_PIPE ) {
      int r;
      r=snprintf(name,1024,"PLAY %s\n",tmp_file_name);
      if ( r < 0 ) {
	name[0]='\0';
      }
    }
    return;
  }

  release_sighandler();

  strcpy(name,player_name);
  a0=a=name;
  argc=0;

  while(1) {
    argv[argc++]=a0;
    while(!(*a==' ' || *a==0)) {a++;}
    if ( *a==0 ) {
      argv[argc++]=tmp_file_name;
      argv[argc]=(char *)NULL;
      break;
    }
    *a++=0;
    a0=a;
  }
  if( snprintf(buf,256,"STED_RCD_SHMID=%d",shmid) > 0 ) {
    putenv(buf);
  }
  if ( STED_CONTROLLABLE&&CONTROL_FROM_PIPE ) {
    close(inter_cont[0]);
    close(cont_inter[1]);
    close(0);
    dup(cont_inter[0]);
    close(1);
    dup(inter_cont[1]);
  } else {
    freopen("/dev/null","r",stdin);
    freopen("/dev/null","a",stdout);
    freopen("/dev/null","a",stderr);
  }
  freopen("/dev/null","a",stderr);
  i=execvp(argv[0], argv);
  exit(0);
}

void _stop_external_player( void ) {

  int time=0;

  if ( player_pid==0 ) return;
  while( rcd->act==2 ) {
    usleep(1000);
    if ( time++ > 2000 ) break;
  }
  rcd->act = 0; /* stop */
  if ( STED_CONTROLLABLE ) {
    if ( CONTROL_FROM_PIPE ) {
      write(pipe_out_fd,"STOP\n",5);
    }
    if ( DATA_FROM_FILE ) {
      unlink( tmp_file_name );
      tmp_file_name[0] = '\0';
    }
    return;
  }
  signal( SIGCHLD, SIG_DFL );
  kill( player_pid, SIGTERM );
  waitpid( player_pid, NULL, 0 );
  if ( DATA_FROM_FILE ) {
    unlink( tmp_file_name );
    tmp_file_name[0]='\0';
  }
  player_pid=0;
  return;
}

void _exit_external_player( int sig ){

  int stt;

  if (player_pid==0) return;
  if ( waitpid( player_pid, &stt, WNOHANG ) > 0 ){
    if (WIFEXITED(stt)){
      if ( DATA_FROM_FILE )
        unlink( tmp_file_name );
      player_pid=0;
      rcd->act=0;
      return;
    }
  }
  signal( SIGCHLD, _exit_external_player );

  return;
}

void request_midi_data( char *p ){
  int i;

  if ( !STED_CONTROLLABLE ) return;
  if ( player_pid==0 ){
    rcd->totalcount = 0;
    _play_external_player();
  }
  for( i=0;i<500;i++ ){
    usleep(100);
    if( rcd->MIDI_avl==0 ) break;
  }
  if( i==500 ){ /* time out */
    rcd->MIDI_avl=0;
    return;
  }
  for( i=0;i<16;i++,p++ ){
    if( (rcd->MIDI_req[i]=(unsigned char)*p)==0xff ){
      break;
    }
  }
  rcd->MIDI_avl=1;
  return;
}

static const int signals[]={SIGHUP,SIGINT,SIGQUIT,SIGILL,SIGABRT,SIGFPE,
                            SIGBUS,SIGSEGV,SIGPIPE,SIGALRM,SIGTERM,0};

static void install_sighandler( void ) {
  int i;

  for ( i=0 ; signals[i]!=0 ; i++ ) {
    signal( signals[i], Exit );
  }
  return;
}

static void release_sighandler( void ) {
  int i;

  for ( i=0 ; signals[i]!=0 ; i++ ) {
    signal( signals[i], SIG_DFL );
  }
  return;
}

int STed_InitMeasureConversion() {

  int i,j;
  int *measure;
  int m;

  for( i=0;i<TRK_NUM;i++ ) {
    rcd->active[i]=1;
    rcd->bar[i]=0;
    rcd->step[i]=0;
  }
  rcd->stepcount = 0;

  measure = (int *)malloc(sizeof(int)*MAX_BAR);
  for ( i=0 ; i<TRK_NUM ; i++ ) {
    m=add_set( i, measure );
    for ( j=0 ; j<m ; j++ ) {
      bar_st[i][j] = step_cluc2( i, 0, measure[j] );
    }
    bar_st[i][m]=-1;
  }
  free(measure);

  return 0;
}

/* converts from total step to measure & relative step */
static int stp_ad( int tr, int meas, int step );
int STed_MeasureConversion( int tr ) {

  int i;
  int c=rcd->stepcount;

  if ( rcd->bar[tr]>=0 || rcd->step[tr]>=0 ) return 0;

#if 0
  if ( (poft&0xffff)==0 ) {
    c-=99;
  } else {
    c+=16;  /* too ad hoc... */
  }
#endif
  i=0;
  while (i<MAX_BAR) {
    if ( bar_st[tr][i]>c ) break;
    if ( bar_st[tr][i]<0 ) i=MAX_BAR;
    i++;
  }
  i--;
  
  if ( i==MAX_BAR-1 ) {   /* measures ended */
    rcd->bar[tr]=0;
    rcd->step[tr]=0;
    rcd->active[tr]=0;
  } else {
    rcd->active[tr]=1;
    rcd->bar[tr] = i;
    rcd->step[tr] = stp_ad(tr, i, c-bar_st[tr][i]);
  }

  return 0;
}

static int stp_ad( int t, int measure, int step ) {

  unsigned char a;
  int po;
  int tr;
  int s;
  unsigned char *bp=trk[t];

  measure+=(poft&0xffff);
  if (( poft&0xffff)==0 ) measure++;
  tr=track;
  track=t;
  po = meas_add(measure);
  track=tr;

  s=1;
  while (step>0) {
  redis:
    a=bp[po];
    if(a==0xf7){po+=4;goto redis;}
    if(a>=0xfc ) break;

    if ( a<0xf0 ) {
      step-=bp[po+1];
      if (step<0) break;
    }
    s++;
    po=po+4;
  }

  return s;
}

#undef exit

void Exit( int sig ) {

  if ( rcd != NULL ) {
#ifndef NO_SHM
    shmdt( (char *)rcd );
    shmctl( shmid, IPC_RMID, 0 );
#else /* NO_SHM */
    free(rcd);
#endif /* NO_SHM */
  }
  if ( access( tmp_file_name, R_OK )==0 ) {
    unlink(tmp_file_name);
  }
  if ( player_pid==0 ) exit(sig);

  signal( SIGCHLD, SIG_DFL );
  kill( player_pid, SIGTERM );
  waitpid( player_pid, NULL, 0 );
  exit(sig);
}
