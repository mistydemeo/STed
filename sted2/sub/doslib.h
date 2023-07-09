/* doslib.h

   dummy header file for X680x0 compatible

   Made by Studio Breeze. 1998

*/

#ifndef _X68_DOSLIB_H_
#define _X68_DOSLIB_H_

/* structs */

#ifndef __dosmode_t_defined__
#define __dosmode_t_defined__
typedef int dosmode_t;
#endif

struct _x68_filbuf {
  unsigned char searchatr; /* attributes for searching files */
  unsigned char driveno;   /* drive number */
  unsigned short dircls;   /* claster number */
  unsigned short dirfat;   /* FAT number of file */
  unsigned short dirsec;   /* sector number of directory */
  unsigned short dirpos;   /* position in directory */
  char filename[8];        /* filename of file */
  char ext[3];             /* extension of file */
  unsigned char atr;       /* attributes of file */
  unsigned short time;     /* time of file */
  unsigned short date;     /* date of file */
  unsigned int filelen;    /* length of file */
  char name[23];           /* long-filename( Human68k format ) */
};

#define X68_FILBUF _x68_filbuf

/* defines for upper-cased-name functions */

#define COMLINE		_comline
#define DPBPTR		_dpbptr
#define DREGS		_dregs
#define FREEINF		_freeinf
#define INPPTR		_inpptr
#define INQUIERY	_inquiry
#define NAMECKBUF	_nameckbuf
#define NAMESTBUF	_namestbuf
#define PRCCTRL		_prcctrl
#define PRCPTR		_prcptr
#define READCAP		_readcap

#define ALLCLOSE	_dos_allclose
#define BINDNO		_dos_bindno
#define BREAKCK		_dos_breakck
#define BUS_ERR		_dos_memcpy
#define CHANGE_PR	_dos_change_pr
#define CHDIR		_dos_chdir
#define CHGDRV		_dos_chgdrv
#define CHMOD		_dos_chmod
#define CINSNS		_dos_cinsns
#define CLOSE		_dos_close
#define COMINP		_dos_cominp
#define COMMON_CK	_dos_common_ck
#define COMMON_DEL	_dos_common_del
#define COMMON_FRE	_dos_common_fre
#define COMMON_LK	_dos_common_lk
#define COMMON_RD	_dos_common_rd
#define COMMON_WT	_dos_common_wt
#define COMOUT		_dos_comout
#define CONSNS		_dos_consns
#define COUTSNS		_dos_coutsns
#define CREATE		_dos_create
#define CTLABORT	_dos_ctlabort
#define CURDIR		_dos_curdir
#define CURDRV		_dos_curdrv
#define C_CLS_AL	_dos_c_cls_al
#define C_CLS_ED	_dos_c_cls_ed
#define C_CLS_ST	_dos_c_cls_st
#define C_COLOR		_dos_c_color
#define C_CUROFF	_dos_c_curoff
#define C_CURON		_dos_c_curon
#define C_DEL		_dos_c_del
#define C_DOWN		_dos_c_down
#define C_DOWN_S	_dos_c_down_s
#define C_ERA_AL	_dos_c_era_al
#define C_ERA_ED	_dos_c_era_ed
#define C_ERA_ST	_dos_c_era_st
#define C_FNKMOD	_dos_c_fnkmod
#define C_INS		_dos_c_ins
#define C_LEFT		_dos_c_left
#define C_LOCATE	_dos_c_locate
#define C_PRINT		_dos_c_print
#define C_PUTC		_dos_c_putc
#define C_RIGHT		_dos_c_right
#define C_UP		_dos_c_up
#define C_UP_S		_dos_c_up_s
#define C_WIDTH		_dos_c_width
#define C_WINDOW	_dos_c_window
#define DELETE		_dos_delete
#define DISKRED		_dos_diskred
#define DISKRED2	_dos_diskred2
#define DISKWRT		_dos_diskwrt
#define DISKWRT2	_dos_diskwrt2
#define DRVCTRL		_dos_drvctrl
#define DRVXCHG		_dos_drvxchg
#define DSKFRE		_dos_dskfre
#define DUP		_dos_dup
#define DUP0		_dos_dup0
#define DUP2		_dos_dup2
#define ERRABORT	_dos_errabort
#define EXEC2		_dos_exec2
#define EXECONLY	_dos_execonly
#define EXIT		_dos_exit
#define EXIT2		_dos_exit2
#define FATCHK		_dos_fatchk
#define FATCHK2		_dos_fatchk2
#define FFLUSH		_dos_fflush
#define FGETC		_dos_fgetc
#define FGETS		_dos_fgets
#define FILEDATE	_dos_filedate
#define FNCKEYGT	_dos_fnckeygt
#define FNCKEYST	_dos_fnckeyst
#define FPUTC		_dos_fputc
#define FPUTS		_dos_fputs
#define GETASSIGN	_dos_getassign
#define GETC		_dos_getc
#define GETCHAR		_dos_getchar
#define GETDATE		_dos_getdate
#define GETDPB		_dos_getdpb
#define GETENV		_dos_getenv
#define GETFCB		_dos_getfcb
#define GETS		_dos_gets
#define GETSS		_dos_getss
#define GETTIM2		_dos_gettim2
#define GETTIME		_dos_gettime
#define GET_FCB_ADR	_dos_getfcb
#define GET_PR		_dos_get_pr
#define HENDSPIC	_dos_hendspic
#define HENDSPIO	_dos_hendspio
#define HENDSPIP	_dos_hendspip
#define HENDSPIR	_dos_hendspir
#define HENDSPMC	_dos_hendspmc
#define HENDSPMO	_dos_hendspmo
#define HENDSPMP	_dos_hendspmp
#define HENDSPMR	_dos_hendspmr
#define HENDSPSC	_dos_hendspsc
#define HENDSPSO	_dos_hendspso
#define HENDSPSP	_dos_hendspsp
#define HENDSPSR	_dos_hendspsr
#define INDOSFLG	_dos_indosflg
#define INKEY		_dos_inkey
#define INPOUT		_dos_inpout
#define INTVCG		_dos_intvcg
#define INTVCS		_dos_intvcs
#define IOCTRLDVCTL	_dos_ioctrldvctl
#define IOCTRLDVGT	_dos_ioctrldvgt
#define IOCTRLFDCTL	_dos_ioctrlfdctl
#define IOCTRLFDGT	_dos_ioctrlfdgt
#define IOCTRLGT	_dos_ioctrlgt
#define IOCTRLIS	_dos_ioctrlis
#define IOCTRLOS	_dos_ioctrlos
#define IOCTRLRD	_dos_ioctrlrd
#define IOCTRLRH	_dos_ioctrlrh
#define IOCTRLRTSET	_dos_ioctrlrtset
#define IOCTRLST	_dos_ioctrlst
#define IOCTRLWD	_dos_ioctrlwd
#define IOCTRLWH	_dos_ioctrlwh
#define KEEPPR		_dos_keeppr
#define KEYSNS		_dos_keysns
#define KFLUSHGC	_dos_kflushgc
#define KFLUSHGP	_dos_kflushgp
#define KFLUSHGS	_dos_kflushgs
#define KFLUSHIN	_dos_kflushin
#define KFLUSHIO	_dos_kflushio
#define KILL_PR		_dos_kill_pr
#define K_INSMOD	_dos_k_insmod
#define K_KEYBIT	_dos_k_keybit
#define K_KEYINP	_dos_k_keyinp
#define K_KEYSNS	_dos_k_keysns
#define K_SFTSNS	_dos_k_sftsns
#define LOAD		_dos_load
#define LOADEXEC	_dos_loadexec
#define LOADONLY	_dos_loadonly
#define LOCK		_dos_lock
#define MAKEASSIGN	_dos_makeassign
#define MAKETMP		_dos_maketmp
#define MALLOC		_dos_malloc
#define MALLOC2		_dos_malloc2
#define MEMCPY		_dos_memcpy
#define MFREE		_dos_mfree
#define MKDIR		_dos_mkdir
#define MOVE		_dos_move
#define NAMECK		_dos_nameck
#define NAMESTS		_dos_namests
#define NEWFILE		_dos_newfile
#define OPEN		_dos_open
#define OPEN_PR		_dos_open_pr
#define PATHCHK		_dos_pathchk
#define PRINT		_dos_print
#define PRNOUT		_dos_prnout
#define PRNSNS		_dos_prnsns
#define PUTCHAR		_dos_putchar
#define RASSIGN		_dos_rassign
#define READ		_dos_read
#define RENAME		_dos_rename
#define RETSHELL	_dos_retshell
#define RMDIR		_dos_rmdir
#define SEEK		_dos_seek
#define SEND_PR		_dos_send_pr
#define SETBLOCK	_dos_setblock
#define SETDATE		_dos_setdate
#define SETENV		_dos_setenv
#define SETTIM2		_dos_settim2
#define SETTIME		_dos_settime
#define SLEEP_PR	_dos_sleep_pr
#define SUPER		_dos_super
#define SUPER_JSR	_dos_super_jsr
#define SUSPEND_PR	_dos_suspend_pr
#define S_MALLOC	_dos_s_malloc
#define S_MFREE		_dos_s_mfree
#define S_PROCESS	_dos_s_process
#define TIME_PR		_dos_time_pr
#define UNLOCK		_dos_unlock
#define VERIFY		_dos_verify
#define VERIFYG		_dos_verifyg
#define VERNUM		_dos_vernum
#define WAIT		_dos_wait
#define WRITE		_dos_write

#define FILES(a,b,c) _dos_files ((struct _x68_filbuf *) (a), (b), (c))
#define NFILES(a) _dos_nfiles ((struct _x68_filbuf *) (a))

/* functions */

extern dosmode_t _dos_chmod( const char *, dosmode_t );
extern void *_dos_malloc( int );
extern int _dos_c_cls_al( void );
extern int _dos_c_cls_ed( void );
extern int _dos_c_curoff( void );
extern int _dos_c_curon( void );
extern int _dos_c_fnkmod( int );
extern int _dos_c_window( int, int );
extern int _dos_chdir( const char * );
extern int _dos_curdir(int, char * );
extern int _dos_curdrv( void );
extern int _dos_delete( const char *);
extern int _dos_drvctrl( int, int );
extern int _dos_files( struct _x68_filbuf *, const char *, int );
extern int _dos_fnckeygt( int, char * );
extern int _dos_fnckeyst( int, const char * );
extern int _dos_inpout( int );
extern int _dos_nfines( struct _x68_filbuf * ) ;
extern int _dos_rename( const char *, const char * );
extern int _dos_setblock( void *, int );
extern int _dos_super( int );

/* -------------- */

#endif /* _X68_DOSLIB_H_ */
