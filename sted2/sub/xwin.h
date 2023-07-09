/*
  xwin.h

  Widgets on X Window System

  Made by Studio Breeze. 1998

 */

#ifndef _XWIN_H_
#define _XWIN_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#ifdef FORCE_XLOCALE
# define X_LOCALE
# include <X11/Xlocale.h>
#else

# ifndef NO_XLOCALE
#  if (XtSpecificationRelease < 6)
#   define NO_XLOCALE
#  endif
# endif

# ifndef NO_XSETLOCALE
#  define X_LOCALE
#  include <X11/Xlocale.h>
# else
#  ifndef NO_SETLOCALE
#   include <locale.h>
#  endif /* NO_SETLOCALE */
# endif /* NO_XSETLOCALE */

#endif /* FORCE_XLOCALE */

#include "x68defines.h"

/* defines */

#define XSTed_Default_Font "-*-fixed-*-r-normal--16-*-*-*"

#define XSTed_max_palletes 32      /* numbers of palletes */
#define XSTed_t_palletes 16        /* numbers of text palletes */
#define XSTed_g_palletes 16        /* numbers of graphics palletes */

#define RES_CLASS "sted"           /* Resource class */

/* flags */

extern int W_Width;             /* Width of Window */ 
extern int W_Height;            /* Height of Window */

extern int IsVisualRW ;         /* is current visual capable Read and Write? */
extern int IsWindowOpened;      /* is the window opened */

extern int istscrchanged;       /* is the screen touched */
extern int isgscrchanged;       /* is the screen touched */

/* valiables */

extern long STed_col[XSTed_max_palletes]; /* allocated pixel number */

extern long *XSTed_tcol;                   /* text pallete array */
extern long *XSTed_gcol;                   /* graphics pallete array */

extern int TCurrentCol;
extern int TCurrentBackCol;
extern int GCurrentCol;

extern int  current_gwindow;

extern char last_file_name[];

/* X vals. */

extern char *XSTed_Window_Title;          /* Window name */
extern char *RES_NAME;                    /* Resource name */
extern char *Displayname;                 /* Display name */
extern char *Geometryname;                /* Geometry name */

extern Display *XSTed_d;                  /* Display ID */
extern Window   XSTed_w;                  /* WIndow */
extern Pixmap   XSTed_tscr;               /* text screen */
extern Pixmap   XSTed_gscr[];             /* graphic screen */
extern Pixmap   XSTed_vscr;               /* temporary screen */
extern XImage  *XSTed_pscr;               /* text drawing buffer */
extern GC       XSTed_tgc;                /* GC for text */
extern GC       XSTed_ggc;                /* GC for graphics */
extern GC       XSTed_wgc;                /* GC for copy */
extern GC       XSTed_egc;                /* G for erase */

extern Atom     XSTed_atom;               /* Atom */
extern Atom     XSTed_prop;               /* Atom */

extern XFontSet XSTed_fs;                 /* FontSet */
extern int XSTed_fs_max_width;            /* max width of fontset */
extern int XSTed_fs_max_height;           /* max height of fontset */ 

extern int      XSTed_depth;              /* Screen depth */
extern int      XSTed_sc;                 /* Screen ID */
extern Colormap XSTed_cmap;               /* Colormap */

/* functions */

/* xwin.c */

extern int  Init_STed_Window( void );
extern void Close_STed_Window( void );

extern void XSTed_init_window( void );
extern void XSTed_close_window( void );
extern void XSTed_rwindow( void );

/* xwin_misc.c */

extern void XSTed_curon( void );
extern void XSTed_curoff( void );

/* xwin_col.c */

extern int XSTed_gpalet( int , int );
extern int XSTed_tpalet( int , int );
extern int XSTed_tcolor( int );
extern int XSTed_gcolor( int );

extern int XSTed_SetTCol( int );
extern int XSTed_SetGCol( int );

/* xwin_print.c */

extern void XSTed_tlocate( int , int );
extern void XSTed_tputs( char * );
extern void XSTed_gputs( int , int , const char * );
extern void XSTed_cls_eol( void );
extern void XSTed_cls_ed( void );

/* xwin_graph.c */

extern void XSTed_txbox( short, short, short, short, unsigned short );
extern void XSTed_txxline( unsigned short, short, short, short, unsigned short );
extern void XSTed_txyline( unsigned short, short, short, short, unsigned short );
extern void XSTed_trev( int, int, int, int );
extern void XSTed_rev_area( int, int, int );
extern void XSTed_tfill( unsigned short, short, short, short, short, unsigned short );
extern void XSTed_trascpy( int, int, int, int );
extern void XSTed_t_scrw( int, int, int, int, int, int );

extern void XSTed_gbox( int, int, int, int, unsigned int, unsigned int );
extern int  XSTed_gpoint( int , int );
extern void XSTed_gline( int, int, int, int, int, int );
extern void XSTed_gfill( int, int, int, int, int );

extern void XSTed_tg_copy( int );
extern void XSTed_tg_copy2( int );

extern void XSTed_ghome( int );
extern void XSTed_cls_al( void );
extern void XSTed_gclr( void );

extern void XSTed_overlap( void );

/* xwin_key.c */

extern int  XSTed_key_init( void );
extern int  XSTed_keyin( int );
extern int  XSTed_keyinp( void );
extern int  XSTed_sftsns( void );
extern int  XSTed_bitsns( int );
extern int  XSTed_keysns( void );
extern void XSTed_key_wait( void );
extern void XSTed_ledmod( int, int );

/* xwin_mouse.c */

extern void XSTed_ms_curof( void );
extern void XSTed_ms_curon( void );
extern int  XSTed_ms_getdt( void );
extern void XSTed_ms_init( void );
extern int  XSTed_ms_limit( int, int, int, int );
extern int  XSTed_ms_pos( int *, int * ); 

#endif /* _XWIN_H_ */
