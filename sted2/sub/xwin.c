/*
  xwin.c

  Widgets on X Window System

  Made by Studio Breeze. 1998

 */

#include "sted.h"
#include "xwin.h"

int IsWindowOpened=0;
int IsVisualRW ;         /* is current visual capable Read and Write? */

int W_Width=768;
int W_Height=512;

Display *XSTed_d;                       /* Display ID */
Pixmap XSTed_tscr;                      /* text screen */
Pixmap XSTed_gscr[2];                   /* graphic screen */
Pixmap XSTed_vscr;                      /* temporary screen */
XImage *XSTed_pscr;                     /* for text drawing buffer */

Window XSTed_rw,XSTed_w;                /* Window ID */
int XSTed_sc;                           /* Screen ID */

XSetWindowAttributes XSTed_attr;        /* Screen Attributes */
GC XSTed_tgc;                           /* GC for text */
GC XSTed_ggc;                           /* GC for graphics */
GC XSTed_wgc;                           /* GC for copy */
GC XSTed_egc;                           /* GC for erase */

Atom XSTed_atom;                        /* Atom */
Atom XSTed_prop;                        /* Atom */

XFontSet XSTed_fs;                      /* font set */
int XSTed_fs_max_width;                 /* max width of fontset */
int XSTed_fs_max_height;                /* max height of fontset */ 

long STed_col[XSTed_max_palletes];      /* allocated pixel number */
int XSTed_depth;                        /* Screen depth */
Colormap XSTed_cmap;                    /* Colormap */

char *XSTed_Window_Title;               /* Window name */
char *RES_NAME;                         /* Resource name */
char *Displayname;                      /* Display name */
char *Geometryname;                     /* Geometry name */

static void Parse_X_Resources(void);
static int  Setup_ColorMap(void);
static int  Setup_FontSet(void);
static int  Setup_Pixmaps(void);

char last_file_name[512];
char font_name[1024];


/* Initialize Screen */

int Init_STed_Window( void ) {

  int i,x,y;

  int gflag;
  int mx,my,msx,msy;

  XEvent XSTed_ev;
  XGCValues gcv;
  long gvmask;

  XSizeHints hint;
  XClassHint chint;

  XTextProperty ct;
  char *namlist[2];

  Atom a1,a2;

  Parse_X_Resources();

  /* setup locale */

  /*if (setlocale( LC_ALL, "" )==NULL) return -1;*/
  setlocale( LC_ALL, "" );
  /*XtSetLanguageProc( NULL, NULL, NULL );*/
  

  if ((XSTed_d = XOpenDisplay ( Displayname ))==NULL)
    return -1;/* error("Cannot open display"); */

  /* Setup FontSet */

  if ( Setup_FontSet() ) return -1;

  /* setup from resources */

  hint.flags = USSize | PMinSize | PMaxSize ;
  hint.width = hint.min_width = hint.max_width = W_Width;
  hint.height = hint.min_height = hint.max_height = W_Height;

  if ( Geometryname != NULL ) {
    gflag = XParseGeometry( Geometryname, &mx, &my, &msx, &msy );

    if ( gflag & XNegative )
      mx = DisplayWidth( XSTed_d, DefaultScreen(XSTed_d)) -1 + mx - W_Width;
    if ( gflag & YNegative )
      my = DisplayHeight( XSTed_d, DefaultScreen(XSTed_d)) -1 + my - W_Height;
    hint.x = mx;
    hint.y = my;
    hint.flags |= USPosition;
  } else {
    mx = 0;
    my = 0;
    /*hint.flags |= PPosition;*/
    hint.x = mx;
    hint.y = my;
    hint.flags |= USPosition;
  }

  /* setup window */

  XSTed_sc = DefaultScreen(XSTed_d);
  XSTed_rw = XDefaultRootWindow ( XSTed_d ) ;

  XSTed_w = XCreateSimpleWindow ( XSTed_d, XSTed_rw, mx, my,
				  W_Width, W_Height, 2,
				  WhitePixel ( XSTed_d, XSTed_sc ),
				  BlackPixel ( XSTed_d, XSTed_sc ));

  XSTed_attr.backing_store = True;
  XChangeWindowAttributes( XSTed_d, XSTed_w, CWBackingStore, &XSTed_attr );

  namlist[0] = (char *)malloc(strlen(XSTed_Window_Title)+1);
  strcpy( namlist[0], XSTed_Window_Title );
  XmbTextListToTextProperty( XSTed_d, namlist, 1, XCompoundTextStyle, &ct );

  XSetWMName ( XSTed_d, XSTed_w, &ct );
  XSetWMIconName ( XSTed_d, XSTed_w, &ct );
  free(namlist[0]);
  strncpy( last_file_name, rcp_file, sizeof(last_file_name) );

  XSetNormalHints( XSTed_d, XSTed_w, &hint );

  chint.res_name = RES_NAME ;
  chint.res_class = RES_CLASS ;
  XSetClassHint( XSTed_d, XSTed_w, &chint );

  a1 = XInternAtom( XSTed_d, "WM_PROTOCOLS", False );
  a2 = XInternAtom( XSTed_d, "WM_DELETE_WINDOW", False );
  XSetWMProtocols ( XSTed_d, XSTed_w, &a2, 1 );

  XSTed_atom = XInternAtom( XSTed_d, "COMPOUND_TEXT", False );
  XSTed_prop = XInternAtom( XSTed_d, "__COPY_TEXT", False );


  /* Setup GC */

  gcv.background = 0;
  gcv.function   = GXcopy;
  gcv.line_width = 0;
  gcv.line_style = LineSolid;
  gcv.cap_style  = CapButt;
  gcv.join_style = JoinMiter;
  gcv.graphics_exposures = False;
  gvmask = GCFunction | GCBackground | GCLineWidth | GCLineStyle | GCCapStyle | GCJoinStyle | GCGraphicsExposures;

  XSTed_tgc = XCreateGC( XSTed_d, XSTed_rw, gvmask, &gcv );
  XSTed_wgc = XCreateGC( XSTed_d, XSTed_rw, gvmask, &gcv );
  XSTed_egc = XCreateGC( XSTed_d, XSTed_rw, gvmask, &gcv );
  gcv.background = BlackPixel( XSTed_d, XSTed_sc );
  XSTed_ggc = XCreateGC( XSTed_d, XSTed_rw, gvmask, &gcv );

  /* Setup Key valuables */

  XSTed_key_init();

   /* Setup ColorMap */

  if ( Setup_ColorMap() ) return -1;

  /* Setup text / graphics screen */

  if ( Setup_Pixmaps() ) return -1;

  /* wait for mapping window */

  XClearWindow( XSTed_d, XSTed_w );
  XRaiseWindow( XSTed_d, XSTed_w );
  XMapWindow( XSTed_d, XSTed_w );

  XSelectInput ( XSTed_d, XSTed_w,
                 ExposureMask|KeyReleaseMask|KeyPressMask|ButtonPressMask );

  while(1) {
    XNextEvent ( XSTed_d, &XSTed_ev ) ;
    if (XSTed_ev.type == Expose ) break;
  }

  current_gwindow=0;
  IsWindowOpened = 1;
  return 0;
}


/* Close Screen */

void Close_STed_Window ( void ) {
  int i;

  if (IsWindowOpened==0) return;
  IsWindowOpened =0 ;
  /*
  if ( IsVisualRW ) {
    if ( XSTed_cmap != DefaultColormap( XSTed_d, XSTed_sc ) )
      XFreeColormap( XSTed_d, XSTed_cmap );
    else
      XFreeColors ( XSTed_d, XSTed_cmap, STed_col, XSTed_max_palletes, 0 );
  }
  */
  XFreeGC( XSTed_d, XSTed_tgc );
  XFreeGC( XSTed_d, XSTed_ggc );
  XFreeGC( XSTed_d, XSTed_wgc );
  XFreeGC( XSTed_d, XSTed_egc );

  XFreeFontSet( XSTed_d, XSTed_fs );

  XDestroyImage( XSTed_pscr );
  XFreePixmap( XSTed_d, XSTed_gscr[1] );
  XFreePixmap( XSTed_d, XSTed_gscr[0] );
  XFreePixmap( XSTed_d, XSTed_tscr );
  XFreePixmap( XSTed_d, XSTed_vscr );

  XDestroyWindow( XSTed_d, XSTed_w );

  XCloseDisplay ( XSTed_d ) ;

  return;
}

void XSTed_init_window( void ) {

  if ( iswindowopened ) return;
  if ( Init_STed_Window() ) {
    B_PRINT("Cannot open display. Aborting.");
    exit(-1);
  }
  iswindowopened=1;
  return;
}

void XSTed_close_window( void ) {
  
  if ( iswindowopened ) Close_STed_Window();
  iswindowopened=0;

  return;
}

void XSTed_rwindow( void ) {

  XSTed_overlap();
  return;
}

void Parse_X_Resources(void) {

  Displayname = NULL;
  Geometryname = NULL;

  XSTed_Window_Title = "STed";

  return;
}

int Setup_ColorMap( void ) {

  int i;
  Visual *vis;

  /* Visuals */

  vis   = DefaultVisual( XSTed_d, DefaultScreen( XSTed_d ) );
  XSTed_cmap  = DefaultColormap ( XSTed_d, XSTed_sc );
  XSTed_depth = DefaultDepth( XSTed_d, XSTed_sc );

  switch ( vis->class ) {
    
  case GrayScale:
  case PseudoColor:
    IsVisualRW = 1;
    break;
    
  case StaticGray:
  case StaticColor:
  case TrueColor:
    IsVisualRW = 0;
      break;
      
  default:
    return -1; /* error("Current visual type is not supported."); */
  }

  
  /* colors */

  if ( IsVisualRW ) {
    if ( !XAllocColorCells( XSTed_d, XSTed_cmap, False,
			    NULL, 0, STed_col, XSTed_max_palletes ) ) {
      XSTed_cmap = XCreateColormap( XSTed_d, XSTed_w, vis, AllocAll );
      XInstallColormap( XSTed_d, XSTed_cmap );
      XSetWindowColormap( XSTed_d, XSTed_w, XSTed_cmap );
      for ( i=0 ; i<XSTed_max_palletes ; i++ ) STed_col[i]=i+1;
    }
    
  } else {      /* Current Visual is now Read-Only */
    for ( i=0 ; i<XSTed_max_palletes ; i++ ) {
      STed_col[i] = i+1;
    }
  }
  for ( i=0 ; i<16 ; i++ ) {
    XSTed_gpalet(i,0);
    XSTed_tpalet(i,0);
  }

  STed_col[0]=0;
  XSTed_tpalet(3, WhitePixel(XSTed_d, XSTed_sc));
  XSTed_tcolor(3);
  return 0;
}

int Setup_FontSet( void ) {

  XFontSetExtents *e;
  char **miss, *def;
  int n_miss;
  XRectangle i_ret, l_ret;


  if ( font_name[0]==0 ) strcpy( font_name, XSTed_Default_Font );
  XSTed_fs = XCreateFontSet ( XSTed_d, font_name,
                              &miss, &n_miss, &def);

  if ( n_miss > 0 ) return -1;

  e = XExtentsOfFontSet( XSTed_fs );
  XmbTextExtents( XSTed_fs, "A", 1, &i_ret, &l_ret ); 

  XSTed_fs_max_width  = e->max_logical_extent.width;
  XSTed_fs_max_height = e->max_logical_extent.height;

  /*W_Width  = X68_TWidth/2  * XSTed_fs_max_width;*/
  W_Width  = X68_TWidth  * l_ret.width;
  W_Height = X68_THeight * XSTed_fs_max_height;

  return 0;
}

int Setup_Pixmaps( void ) {

  Visual *vis;
  int pad;
  int x,y,c;
  int i;

  vis = DefaultVisual( XSTed_d, DefaultScreen( XSTed_d ) );
  if ( XSTed_depth == 8 ) pad=8;
  else pad=32;
  
  XSTed_tscr   =XCreatePixmap( XSTed_d, XSTed_w,
			       W_Width, W_Height, XSTed_depth );
  XSTed_vscr   =XCreatePixmap( XSTed_d, XSTed_w,
			       W_Width, W_Height, XSTed_depth );
  XSTed_gscr[0]=XCreatePixmap( XSTed_d, XSTed_w,
			       W_Width, W_Height, XSTed_depth );
  XSTed_gscr[1]=XCreatePixmap( XSTed_d, XSTed_w,
			       W_Width, W_Height, XSTed_depth );

  XSTed_pscr = XCreateImage ( XSTed_d, vis, XSTed_depth,
			      ZPixmap, 0, 0,
			      W_Width, XSTed_fs_max_height*2, pad, 0 );
  XSTed_pscr->data =
    (char *)malloc(XSTed_pscr->bytes_per_line * XSTed_fs_max_height*2);

  XSetForeground( XSTed_d, XSTed_wgc, 1 );
  XSetForeground( XSTed_d, XSTed_egc, 0 );
  XSetBackground( XSTed_d, XSTed_egc, 0 );

  XFillRectangle( XSTed_d, XSTed_tscr,    XSTed_egc, 0,0,W_Width,W_Height );
  XFillRectangle( XSTed_d, XSTed_gscr[0], XSTed_egc, 0,0,W_Width,W_Height );
  XFillRectangle( XSTed_d, XSTed_gscr[1], XSTed_egc, 0,0,W_Width,W_Height );
  XFillRectangle( XSTed_d, XSTed_vscr,    XSTed_egc, 0,0,W_Width,W_Height );

  istscrchanged = 1;
  isgscrchanged = 1;
  return 0;
}
