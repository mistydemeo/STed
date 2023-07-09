/*
  dos.c

  functions for compatibility to doslib

  ( mainly contains file-oriented functions )

  Made by Studio Breeze. 1998

 */

#include "sted.h"

/* variables */

char fnc_func[10][32];
char fnc_sfunc[10][32];
char fnc_key[12][6];
/* ROLL UP, ROLL DOWN, INS, DEL,
   UP, LEFT, RIGHT, DOWN,
   CLR, HELP, HOME, UNDO */

/* local functions */

static char *name_conv( char *, const char * );

static char Name[1024];           /* convert buffer */
static DIR *_dos_dir=NULL;        /* dirent:handle */
static char _dos_node[1024];      /* dirent:directory */


/* console-oriented functions */

int _dos_c_cls_al ( void ) {

  _iocs_b_clr_al();
  return 0;
}

int _dos_c_cls_ed( void ) {

 _iocs_b_clr_ed();
 return 0;
}

int _dos_c_curoff( void ) {

  if ( isconsole ) {
    curses_curoff();

  } else if ( isxwin ) {
    XSTed_curoff();
  }
  return 0;
}
int _dos_c_curon( void ) {

  if ( iswindowopened ) {
    if ( isconsole ) {
      curses_curon();
      
    } else if (isxwin ) {
      XSTed_curon();
    }
  }
  return 0;
}
int _dos_c_fnkmod( int mode ) {

  /* not implemented */
  return 0;
}
int _dos_c_window( int x, int y ) {

  if ( isconsole ) {
    curses_tlocate( 0, 0 );

  } else if ( isxwin ) {
    XSTed_tlocate( 0, 0 );
  }
  return 0;
}

int _dos_fnckeygt( int fno, char *buff ) {

  /* not implemented */
  return 0;
}

int _dos_fnckeyst( int fno, const char *buff ) {

  int i,j;
  const char *p;

  p=buff;

  if (fno==0) {
    for ( i=0 ; i<10 ; i++ ) {
      for ( j=0 ; j<32 ; j++ ) {
	fnc_func[i][j]=*p++;
      }
    }
    for ( i=0 ; i<10 ; i++ ) {
      for ( j=0 ; j<32 ; j++ ) {
	fnc_sfunc[i][j]=*p++;
      }
    }
    for ( i=0 ; i<12 ; i++ ) {
      for ( j=0 ; j<6 ; j++ ) {
	fnc_key[i][j]=*p++;
      }
    }
  } else if ( fno<=10 ) {
    for ( j=0 ; j<32 ; j++ ) {
      fnc_func[fno-1][j]=*p++;
    }
  } else if ( fno<=20 ) {
    for ( j=0 ; j<32 ; j++ ) {
      fnc_sfunc[fno-11][j]=*p++;
    }
  } else if ( fno<=32 ) {
    for ( j=0 ; j<6 ; j++ ) {
      fnc_key[fno-21][j]=*p++;
    }
  }
  return 0;
}

int _dos_inpout( int code ) {

  int i,ret;

  ret=0;

  if ( (code==0xfe) || (code==0xff) ) {

    if ( isconsole ) {
      ret=curses_keyin(code);

    } else if ( isxwin ) {
      ret=XSTed_keyin(code);
    }

  }

  return ret;
}

/* functions */

void *_dos_malloc(int i) {

  void *tmp;

  tmp = (void *)malloc(i);
  if ( tmp == NULL ) tmp = (void *)0x82000000;

  return tmp;
  
}

dosmode_t _dos_chmod( const char *name, dosmode_t atr ) {

  /* returns only one flag : is the file "name" directory? */

  int ret_code=0;

  if (atr == -1) {
    struct stat *stt,tmp;

    name_conv(Name, name);
    stt=&tmp;
    if (stat( Name, stt )) ret_code=-1;
    else ret_code = S_ISDIR(stt->st_mode)?0x10:0;
  }
  return ret_code;
}

int _dos_chdir( const char *name ) {

  name_conv( Name, name );
  return chdir( Name );
}

int _dos_curdir( int drive, char *buff ) {

  char *tmp;

  /* buff : max 128 bytes */

  if ( (tmp=getcwd(NULL, 128)) == NULL ) return -1;
  strcpy( buff, tmp+1 ); /* delete first '/' */
  free(tmp);

  return 0;
}

int _dos_curdrv( void ) {

  return 0; /* always drive A: */
}

int _dos_delete( const char *name ) {

  name_conv( Name, name );
  return unlink( Name );
}

int _dos_drvctrl( int mode, int drive ) {

  return 2; /* media inserted, ready, not protected, enable eject by user,
	       no buffer, enable eject, not blink LED */
}

int _dos_rename( const char *name, const char *nname ) {

  char nName[1024];

  name_conv( Name, name );
  name_conv( nName, nname );

  return rename( Name, nName );
}

int _dos_super( int stack ) {

  return 1; /* ignore */
}

int _dos_files (struct _x68_filbuf *buff, const char *name, int atr ) {

  struct dirent *d;
  char *a,filename[1100];
  struct stat *stt,tmp;
  struct tm *asc;

  stt=&tmp;

  if ( _dos_dir != NULL ) closedir(_dos_dir);

  name_conv( Name, name );
  a=strrchr( Name,'/' );
  *(a+1)=0;                          /* ignore filename */
  strcpy( _dos_node, Name );
  _dos_dir = opendir( _dos_node );

  if ( _dos_dir == NULL ) return -3; /* error */

  d = readdir( _dos_dir );
  if ( d == NULL ) {
    closedir(_dos_dir);
    _dos_dir=NULL;
    return -3;
  }

  strcpy( filename, _dos_node );
  strcat( filename, d->d_name );

  if (stat(filename, stt)) return -3;
  
  asc=localtime(&(stt->st_mtime));

  buff->atr     = (unsigned char)(S_ISDIR(stt->st_mode)?0x10:1);
  buff->filelen = (unsigned int)stt->st_size;
  buff->date    = (unsigned short)(asc->tm_year<<9 | asc->tm_mon<<5 | asc->tm_mday);
  buff->time    = (unsigned short)(asc->tm_hour<<11 | asc->tm_min<<5 | (asc->tm_sec/2));
  strncpy( buff->name, d->d_name, 22 );
  buff->name[22]=0;

  return 0;
}

int _dos_nfiles( struct _x68_filbuf *buff ) {

  struct dirent *d;
  char filename[1024];
  struct stat *stt,tmp;
  struct tm *asc;

  stt=&tmp;

  if ( _dos_dir==NULL ) return -3;

  d = readdir( _dos_dir );
  if ( d == NULL ) {
    closedir( _dos_dir );
    _dos_dir = NULL;
    return -3;
  }

  strcpy( filename, _dos_node );
  strcat( filename, d->d_name );

  if (stat(filename, stt)){
    if ( errno != ENOENT ) return -3;  /* ??? Jul.04.1998 by Daisuke Nagano */
  }
  
  asc=localtime(&(stt->st_mtime));
  buff->atr     = (unsigned char)(S_ISDIR(stt->st_mode)?0x10:0x21);
  buff->filelen = (unsigned int)stt->st_size;
  buff->date    = (unsigned short)(asc->tm_year<<9 | asc->tm_mon<<5 | asc->tm_mday);
  buff->time    = (unsigned short)(asc->tm_hour<<11 | asc->tm_min<<5 | (asc->tm_sec/2));
  strncpy( buff->name, d->d_name, 22 );
  buff->name[22]=0;

  return 0;
}

int _dos_setblock( void *memptr, int newsize ) {

  /* not implemented */
  return -1;
  
}

int dskf( char drive_number ) {

  /* max 8 keta */
  return 58371500;
}

FILE *fopen2( char *name, char *mode) {

  name_conv( Name, name );
  return fopen( Name, mode );
}

/* local use functions */

/* converts HUMAN file name to unix file name */

static char *name_conv ( char *dest, const char *name ) { 

  char *a;

  a=strchr(name, ':');  /* ignore drive letter */
  if ( a==NULL ) strcpy( dest, name );
  else strcpy( dest, a+1 );

  return dest;
}

