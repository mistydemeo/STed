/*
 * MIDI Music Composer STed v2.07j : sted.h (header) 1997-07-20 by TURBO
 */

#ifndef _STED_H_
#define _STED_H_

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include <sys/stat.h>

#ifdef HAVE_STRING_H
#  include <string.h>
#endif /* HAVE_STRING_H */

#ifndef STDC_HEADERS
#  ifndef HAVE_STRCHR
#    define strchr index
#    define strrchr rindex
#  endif /* HAVE_STRCHR */
   char *strchr(), *strrchr();
#  ifndef HAVE_MEMCPY
#    define memcpy(d, s, n) bcopy((s), (d), (n))
#    define memmove(d, s, n) bcopy((s), (d), (n))
#  endif
#endif

#ifdef HAVE_FCNTL_H
#  include <fcntl.h>
#endif /* HAVE_FCNTL_H */

#ifdef HAVE_UNISTD_H
#  include <sys/types.h>
#  include <unistd.h>
#endif /* HAVE_UNISTD_H */

#ifndef HAVE_SYS_TIME_H
#  include <time.h>
#else /* HAVE_SYS_TIME */
#  ifdef TIME_WITH_SYS_TIME
#    include <time.h>
#  endif /* TIME_WITH_SYS_TIME */
#  include <sys/time.h>
#endif

#include <sys/types.h>
#ifdef HAVE_SYS_WAIT_H
#  include <sys/wait.h>
#endif /* HAVE_SYS_WAIT_H */
#ifndef WEXITSTATUS
#  define WEXITSTATUS(stat_val) ((unsigned)(stat_val) >> 8)
#endif /* WEXITSTATUS */
#ifndef WIFEXITED
#  define WIFEXITED(stat_val) (((stat_val) & 255) == 0)
#endif /* WIFEXITED */

#ifdef HAVE_DIRENT_H
#  include <dirent.h>
#  define NAMLEN(dirent) strlen((dirent)->d_name)
#else
#  define dirent direct
#  define NAMLEN(dirent) (dirent)->d_namlen
#  ifdef HAVE_SYS_NDIR_H
#    include <sys/ndir.h>
#  endif
#  ifdef HAVE_SYS_DIR_H
#    include <sys/dir.h>
#  endif
#  ifdef HAVE_NDIR_H
#    include <ndir.h>
#  endif
#endif /* HAVE_DIRENT_H */


#include "version.h"

#include "iocslib.h"
#include "doslib.h"
#include "graph.h"
#include "rcddef.h"
#include "sub/x68funcs.h"
#include "sub/midi_in.h"

#ifdef HAVE_SUPPORT_STED3
# include "sted3.h"
#endif

extern void rcd_check( void );
extern void rcd_open_device( void );
extern struct RCD_HEAD	*rcd;
extern char rcd_version[];

/* etc */
char	hlp_path[128];			/* help file path & name	*/
char	fon_path[128];			/* font file path & name	*/

char	def_path[128];			/* .def path name		*/
char	rcp_path[128];			/* .rcp path name		*/
char	prt_path[128];			/* .prt path name		*/
char	trk_path[128];			/* .trk path name		*/

char	def_file[128];			/* .def file name		*/
char	rcp_file[128];			/* .rcp file name		*/
char	prt_file[128];			/* .prt file name		*/
char	trk_file[128];			/* .trk file name		*/

char	repl[128];			/* replace string		*/
char	delt[128];			/* delete string		*/
char	srch[128];			/* find string			*/

char	repl_t[26*6][40];
char	repl_d[26*6][50];

int	tr_step[36];			/* track total step temp	*/
int	tr_alc[36];			/* track aloc size		*/
int	tr_len[36];			/* track used size		*/
int	tr_pos[36][2][4];		/* track cursor position	*/
int	tag[26+2][4];			/* tag jamp list buffer		*/

int	es,ecode,scyp;			/* input subroutine exit code	*/

int	btrack;				/* track set top track		*/
int	track,track1,track2;		/* edit track no.		*/
int	edit_scr;			/* 0=l_track 1=r_track 2=rhythm	*/
int	cmdflag,cnfflag,mdlflag;	/* STed2 system flag		*/
int	poft;

int	TRACK_SIZE,work_size;		/* buffer size			*/
int	buff_size,buff_free,buff_max;
int	cpcy,cpadd,cplen;
int	cpleng,rcpf,rcplen;		/* copy flag			*/

void	*ErrorTrap_Old;			/* err trap vecter/flag		*/
int	ErrFlag;

/* cnf */
char	comment[64];			/* comment			*/

int	tm_lag;				/* graphic rewrite time lag	*/
char	inpmode;			/* editor input mode		*/
char	grpmode;			/* editor graphic mode		*/
char	thrumode;			/* edit midi in thru mode	*/
int	rec_getch,rec_putmd;		/* recoding ch./put mode	*/

int	vis_reso;			/**/

unsigned char	rfilt[32][4];		/* record filter */
unsigned char	pfilt[32][4];		/* play   filter */

char	mplay[16][16];
int	palet_dat[16];

unsigned char	keyst_table[2][128];	/* key# -> st/gt convert table	*/
unsigned char	stgt_tbl[60];		/* f.key -> st/gt table		*/

char	rhy_vel[16];

char	chcom_s[26*2][2][50];		/* child command comment	*/
char	chcom_c[26*2][2][16];		/* child command parameter	*/

/* def */
char	module[64];			/* module name			*/

int	lsp_wait;			/* last para. transfer wait	*/
int	bend_range;			/* piche bend range		*/

char	tim_asin[33];			/* tone list channle assign	*/
char	tim_head[400][24];		/* tone list title		*/
char	tim_sym[400][8];		/* tone list symbol		*/
char	tim_name[80*128][15];		/* tone name buffer		*/
short	tim_top[400];			/* tone name buffer address	*/

char	card_name[21][64];		/* pcm card name list		*/
char	card_no[2];			/* used pcm card no.		*/

short	gs_bank[18*128];		/* gs bank part no.(8+1 group)	*/
short	gs_mode[18];			/* gs bank mode    (8+1 group)	*/

char	rhy_stest[8];			/* rhythm sound test ch. & para	*/
char	rec_met[10];			/* recording metoro tone	*/

unsigned char	init_exc_data[258];	/* init exclusive data		*/

/*** rcp format head parameter ***/
char	mtitle[65];			/* music title			*/
char	memo[12][29];			/* memo				*/
int	tbase,mtempo;
int     beat1,beat2,bkey,pbias;		/* common parameter		*/
char	cm6_file[128],gsd_file[128];	/* controol file name		*/

char	rhyna[32][15];			/* rhythm assign name		*/
unsigned char	rhyno[32][2];		/* rhythm assign key & gate	*/

char	user_exc_memo[8][25];		/* user exclusive memo		*/
unsigned char	user_exc_data[8][24];	/* user exclusive data		*/

unsigned char	trno[36];		/* track no.			*/
unsigned char	trmod[36];		/* track play mode		*/
unsigned char	trrhy[36];		/* track rhythm sw.		*/
unsigned char	mch[36];		/* track midi ch.		*/
unsigned char	trkey[36];		/* track key shift		*/
unsigned char	trst[36];		/* track st shift		*/
char	trkmemo[36][37];		/* track comment		*/

/* buffer */
unsigned char	lcbuf[1024*4+4];	/* delete line buffer		*/
unsigned char	rlcbuf[132];		/* delete rhythm line buffer	*/
unsigned char	cm6[22601],gsd[4096];	/* control file buffer		*/
unsigned char	hed[1414];		/* rcp header temporary		*/

unsigned char	*trk[36];		/* track buffer pointer		*/
unsigned char	*cpbuf;			/* track copy buffer		*/
unsigned char	*rcpbuf;		/* rhythm track copy buffer	*/
unsigned char	*dat;			/* temporary & recording buffer	*/
unsigned char	*dat2;			/* temporary			*/

/* the following variables is only PC version available */

extern int issted3;                     /* Am I a new version ? */
extern int isconsole;                   /* is console mode? */
extern int isxwin;                      /* is X mode? */
extern char euc_text[1024];             /* code convert buffer */
extern char player_name[1024];          /* midi player name */
extern char midi_port_name[1024];       /* midi_port device name */
extern char font_name[1024];            /* X font set name */
extern int player_flag;                 /* is player able to play only SMF? */

extern char KEY_XF1[];                  /* keysym names */
extern char KEY_XF2[];
extern char KEY_XF3[];
extern char KEY_XF4[];
extern char KEY_XF5[];
extern char KEY_KANA[];
extern char KEY_KIGO[];
extern char KEY_TOROKU[];
extern char KEY_INS[];
extern char KEY_DEL[];
extern char KEY_HOME[];
extern char KEY_UNDO[];
extern char KEY_RUP[];
extern char KEY_RDOWN[];
extern char KEY_OPT1[];
extern char KEY_OPT2[];

extern int itor( char *, char * );
extern int STed_MeasureConversion( int track );
extern void Exit(int);
#define exit Exit

extern int eucenv;
extern char *nkf_conv(char *, char *, char *);
#define eucconv(a) ((eucenv!=0) ? nkf_conv( a, euc_text, "EUC" ) : a)

#ifdef ENABLE_NLS
# include <locale.h>
# include <libintl.h>
# undef _
# define _(String) gettext(String)
# define N_(String) (String)

#else /* ENABLE_NLS */
# define _(String) (String)
# define N_(String) (String)
#endif /* ENABLE_NLS */

#endif /* _STED_H_ */
