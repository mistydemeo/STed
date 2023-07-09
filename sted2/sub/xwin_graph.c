/*
  xwin_graph.c

  xwin: drawing oriented functions

  Made by Studio Breeze. 1998

 */

#include "sted.h"
#include "xwin.h"

int isgscrchanged;
int istscrchanged;

int tpage ( int v ){
  int ret=0;

  switch ( v ) {
  case 0:
    ret=1;
    break;
  case 1:
    ret=2;
    break;
  default:
    ret=3;
    break;
  }

  return ret;
}

void XSTed_txbox( short x0, short y0, short x1, short y1, unsigned short p ) {

  int sx,sy,lx,ly;
  int c;

  c = tpage(p);

  sx = W_Width  * x0       / X68_GWidth;
  lx = W_Width  * (x1-x0)  / X68_GWidth;
  sy = (W_Height * y0      / X68_GHeight)%W_Height;
  ly = (W_Height * (y1-y0) / X68_GHeight) %W_Height;

  XSTed_SetTColor( c );
  XDrawRectangle( XSTed_d, XSTed_w, XSTed_tgc,
		  sx, sy, lx, ly );
  XDrawRectangle( XSTed_d, XSTed_tscr, XSTed_tgc,
		  sx, sy, lx, ly );
  XSTed_SetTColor( TCurrentCol );

  istscrchanged=1;
  return;
}

void XSTed_txxline( unsigned short v, short x0, short y0, short x1, unsigned short ls ) {

  int sx,sy,lx;
  int c;

  c = (ls!=0)?tpage(v):0;

  sx = W_Width  * x0  / X68_GWidth;
  lx = W_Width  * x1  / X68_GWidth;
  sy = (W_Height * y0 / X68_GHeight) % W_Height;

  if ( c!=0 ) {
    XSTed_SetTColor( c );
    XDrawLine( XSTed_d, XSTed_w, XSTed_tgc,
	       sx, sy, sx+lx, sy );
    XDrawLine( XSTed_d, XSTed_tscr, XSTed_tgc,
	       sx, sy, sx+lx, sy );
    XSTed_SetTColor( TCurrentCol );
  } else {
    XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc,
	       sx, sy, lx, 1, sx, sy );
    XDrawLine( XSTed_d, XSTed_tscr, XSTed_egc,
	       sx, sy, sx+lx, sy );
  }
  istscrchanged=1;
  return;
}

void XSTed_txyline( unsigned short v, short x0, short y0, short y1, unsigned short ls ) {

  int sx,sy,ey;
  int c;

  c = (ls!=0)?tpage(v):0;

  sx = W_Width  * x0       / X68_GWidth;
  sy = (W_Height * y0      / X68_GHeight) % W_Height;
  ey = (W_Height * (y0+y1) / X68_GHeight) % W_Height;

  if ( c!=0 ) {
    XSTed_SetTColor( c );
    XDrawLine( XSTed_d, XSTed_w, XSTed_tgc,
	       sx, sy, sx, ey-1 );
    XDrawLine( XSTed_d, XSTed_tscr, XSTed_tgc,
	       sx, sy, sx, ey-1 );
    XSTed_SetTColor( TCurrentCol );
  } else {
    XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc,
	       sx, sy, 1, ey-sy, sx, sy );
    XDrawLine( XSTed_d, XSTed_tscr, XSTed_egc,
	       sx, sy, sx, ey-1 );
  }

  istscrchanged=1;
  return;
}

void XSTed_trev( int x0, int y0, int l0, int col ) {

  int x1,y1,y2,l1;

  /*
  static const int r[4][4] = {
    {3,2,1,0},
    {1,0,3,2},
    {2,3,0,1},
    {3,2,1,0}
  };
  */

  x1 = W_Width * x0 / X68_TWidth;
  l1 = W_Width * l0 / X68_TWidth;
  y1 = W_Height* y0 / X68_THeight;
  y2 = W_Height* (y0+1) / X68_THeight;

  XSetForeground( XSTed_d, XSTed_wgc, WhitePixel(XSTed_d, XSTed_sc) );
  /*XSetForeground( XSTed_d, XSTed_wgc, (1<<XSTed_depth)-1 );*/
  XFillRectangle( XSTed_d, XSTed_vscr, XSTed_wgc,
		  0, 0, l1, y2-y1 );
  XSetForeground( XSTed_d, XSTed_wgc, 1 );
  XSetFunction( XSTed_d, XSTed_wgc, GXxor );
  XCopyArea( XSTed_d, XSTed_vscr, XSTed_w, XSTed_wgc,
	     0, 0, l1, y2-y1, x1, y1 );
  XCopyArea( XSTed_d, XSTed_vscr, XSTed_tscr, XSTed_wgc,
	     0, 0, l1, y2-y1, x1, y1 );
  XSetFunction( XSTed_d, XSTed_wgc, GXcopy );

  istscrchanged = 1;
  return;
}

void XSTed_rev_area( int r_ad, int r_ln, int edit_scr ) {

  /* if your system has capable enough to draw rev_area
     uncomment the following codes.

  int x0, y0, xl, yl;

  x0 = (edit_scr==0)? 2 : 56 ;
  y0 = 6+r_ad;
  xl=36 ; yl=r_ln;

  x0 = W_Width * x0 / X68_TWidth;
  y0 = W_Height* y0 / X68_THeight;
  xl = W_Width * xl / X68_TWidth;
  yl = W_Height* yl / X68_THeight;

  XSetForeground( XSTed_d, XSTed_wgc, WhitePixel(XSTed_d, XSTed_sc) );
  XFillRectangle( XSTed_d, XSTed_vscr, XSTed_wgc,
		  0, 0, xl, yl );
  XSetForeground( XSTed_d, XSTed_wgc, 1 );
  XSetFunction( XSTed_d, XSTed_wgc, GXxor );
  XCopyArea( XSTed_d, XSTed_vscr, XSTed_w, XSTed_wgc,
	     0, 0, xl, yl, x0, y0 );
  XCopyArea( XSTed_d, XSTed_vscr, XSTed_tscr, XSTed_wgc,
	     0, 0, xl, yl, x0, y0 );
  XSetFunction( XSTed_d, XSTed_wgc, GXcopy );
  */

  return;
}

void XSTed_tfill( unsigned short p, short x0, short y0, short x1, short y1, unsigned short ls ) {

  int sx,sy,lx,ey;
  int c;

  c = (ls!=0)?tpage(p):0;

  sx = W_Width  * x0       / X68_GWidth;
  lx = W_Width  * x1       / X68_GWidth;
  sy = (W_Height * y0      / X68_GHeight) % W_Height;
  ey = (W_Height * (y0+y1) / X68_GHeight) % W_Height;

  if ( c!=0 ) {
    XSTed_SetTColor( c );
    XFillRectangle( XSTed_d, XSTed_w, XSTed_tgc,
		    sx, sy, lx, ey-sy );
    XFillRectangle( XSTed_d, XSTed_tscr, XSTed_tgc,
		    sx, sy, lx, ey-sy );
    XSTed_SetTColor( TCurrentCol );
  } else {
    XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc,
	       sx, sy, lx, ey-sy, sx, sy );
    XFillRectangle( XSTed_d, XSTed_tscr, XSTed_egc,
		    sx, sy, lx, ey-sy );
  }

  istscrchanged=1;
  return;
}

void XSTed_gbox( int x1, int y1, int x2, int y2, unsigned int col, unsigned int ls) {

  int sx,sy,ex,ey;
  int x,y;
  int d;

  sx = W_Width  * x1 / X68_GWidth;
  ex = W_Width  * x2 / X68_GWidth;
  sy = (W_Height * y1 / X68_GHeight) % W_Height;
  ey = (W_Height * y2 / X68_GHeight) % W_Height;
  d  = ( y1 >= X68_GHeight )?1:0;
  if ( sx>ex ) { x=ex;ex=sx;sx=x; }
  if ( sy>ey ) { y=ey;ey=sy;sy=y; }

  XSTed_SetGColor( col );
  if ( d==current_gwindow )
    XDrawRectangle( XSTed_d, XSTed_w, XSTed_ggc,
		    sx, sy, ex-sx+1, ey-sy+1 );
  XDrawRectangle( XSTed_d, XSTed_gscr[d], XSTed_ggc,
		  sx, sy, ex-sx+1, ey-sy+1 );

  isgscrchanged=1;
  return;
}

void XSTed_gfill( int x1, int y1, int x2, int y2, int col ) {

  int sx,sy,ex,ey;
  int x,y;
  int d;

  sx = W_Width  * x1 / X68_GWidth;
  ex = W_Width  * x2 / X68_GWidth;
  sy = (W_Height * y1 / X68_GHeight) % W_Height;
  ey = (W_Height * y2 / X68_GHeight) % W_Height;
  d  = ( y1 >= X68_GHeight )?1:0;
  if ( sx>ex ) { x=ex;ex=sx;sx=x; }
  if ( sy>ey ) { y=ey;ey=sy;sy=y; }

  XSTed_SetGColor( col );
  if ( d==current_gwindow )
    XFillRectangle( XSTed_d, XSTed_w, XSTed_ggc,
		    sx, sy, ex-sx+1, ey-sy+1 );
  XFillRectangle( XSTed_d, XSTed_gscr[d], XSTed_ggc,
		  sx, sy, ex-sx+1, ey-sy+1 );

  isgscrchanged=1;
  return;
}

int  XSTed_gpoint( int x, int y) {

  int ret=0;

  return ret;
}

void XSTed_gline( int x1, int y1, int x2, int y2, int col, int ls ) {

  int sx,sy,ex,ey;
  int x,y;
  int d;

  sx = W_Width  * x1 / X68_GWidth;
  if ( sx < 0 ) sx=0;
  ex = W_Width  * x2 / X68_GWidth;
  if ( ex >= W_Width ) ex = W_Width-1;
  sy = (W_Height * y1 / X68_GHeight)%W_Height;
  ey = (W_Height * y2 / X68_GHeight)%W_Height;
  d  = ( y1 >= X68_GHeight )?1:0;
  if ( sx>ex ) { x=ex;ex=sx;sx=x; }
  if ( sy>ey ) { y=ey;ey=sy;sy=y; }

  XSTed_SetGColor( col );
  if ( d==current_gwindow )
    XDrawLine( XSTed_d, XSTed_w, XSTed_ggc,
	       sx, sy, ex, ey );
  XDrawLine( XSTed_d, XSTed_gscr[d], XSTed_ggc,
	     sx, sy, ex, ey );

  isgscrchanged=1;
  return;
}

void XSTed_trascpy( int dst, int src, int line, int mode ) {

  int sx, lx;
  int sy,dy,ly;

  ly = W_Height * (line/4-1) / X68_THeight;

  if ((src==63*4)||(src==30*4)) {
    sx=0;
    lx=W_Width;
  } else {
    if ( edit_scr==0 ) {
      sx=W_Width * 2 /X68_TWidth;
      lx=W_Width * 36/X68_TWidth;
    } else {
      sx=W_Width * 58/X68_TWidth;
      lx=W_Width * 36/X68_TWidth;
    }
  }

  if ( mode >= 0x8000 ) {
    sy = W_Height * ((src+1)/4) / X68_THeight;
    dy = W_Height * ((dst+1)/4) / X68_THeight;

    XCopyArea( XSTed_d, XSTed_w, XSTed_w, XSTed_wgc,
	       sx, sy-ly, lx, ly, sx, dy-ly );
    XCopyArea( XSTed_d, XSTed_tscr, XSTed_tscr, XSTed_wgc,
	       sx, sy-ly, lx, ly, sx, dy-ly );
  } else {

    if ( src == 63*4 ) {
      sy=W_Height * dst/4 /X68_THeight;
      dy=sy+XSTed_fs_max_height;
      
      XClearArea( XSTed_d, XSTed_w,
		  sx, sy, lx, dy-sy, False );
      XFillRectangle( XSTed_d, XSTed_tscr, XSTed_egc,
		      sx, sy, lx, dy-sy );
    } else {

      sy = W_Height * (src/4) / X68_THeight;
      dy = W_Height * (dst/4) / X68_THeight;

      XCopyArea( XSTed_d, XSTed_w, XSTed_w, XSTed_wgc,
		 sx, sy, lx, ly, sx, dy );
      XCopyArea( XSTed_d, XSTed_tscr, XSTed_tscr, XSTed_wgc,
		 sx, sy, lx, ly, sx, dy );
    }
  }

  istscrchanged=1;
  return;
}

void XSTed_t_scrw( int x1, int y1, int xs, int ys, int x2, int y2 ) {

  x1 = W_Width * x1 / X68_TWidth;
  x2 = W_Width * x2 / X68_TWidth;
  xs = W_Width * xs / X68_TWidth;
  y1 = W_Height* y1 / X68_GHeight;
  y2 = W_Height* y2 / X68_GHeight;
  ys = W_Height* ys / X68_GHeight;

  XCopyArea( XSTed_d, XSTed_w, XSTed_w, XSTed_wgc,
	     x1, y1, xs, ys, x2, y2 );
  XCopyArea( XSTed_d, XSTed_tscr, XSTed_tscr, XSTed_wgc,
	     x1, y1, xs, ys, x2, y2 );

  istscrchanged=1;
  return;
}

void XSTed_tg_copy( int edit_scr ) {

  int x1, y1, x2, y2;
  int xt, xl, yt, yl;

  xl=36 ; yl=24;
  if ( edit_scr==0 ) {
    xt= 2 ; yt= 6;
  } else {
    xt=58 ; yt= 6;
  }
  x1 = W_Width * xt      / X68_TWidth;
  x2 = W_Width * xl      / X68_TWidth;
  y1 = W_Height * yt     / X68_THeight;
  y2 = W_Height * (yt+yl)/ X68_THeight;

  XCopyArea( XSTed_d, XSTed_tscr, XSTed_gscr[1], XSTed_wgc,
	     x1, y1, x2, y2-y1, x1, y1 );

  isgscrchanged=1;
  return;
}

void XSTed_tg_copy2( int edit_scr ) {

  int x1, y1, x2, y2;
  int xt, xl, yt, yl;

  xl=56 ; yl=24;
  if ( edit_scr==0 ) {
    xt= 0 ; yt= 6;
  } else {
    xt=38 ; yt= 6;
  }
  x1 = W_Width * xt      / X68_TWidth;
  x2 = W_Width * xl      / X68_TWidth;
  y1 = W_Height * yt     / X68_THeight;
  y2 = W_Height * (yt+yl)/ X68_THeight;

  XCopyArea( XSTed_d, XSTed_tscr, XSTed_gscr[1], XSTed_wgc,
	     x1, y1, x2, y2-y1, x1, y1 );

  isgscrchanged=1;
  return;
}

void XSTed_ghome( int home_flag ){

  current_gwindow=home_flag;

  XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc,
	     0, 0, W_Width, W_Height, 0, 0 );

  isgscrchanged=1;
  return;
}

void XSTed_gclr( void ) {

  XFillRectangle( XSTed_d, XSTed_gscr[current_gwindow], XSTed_egc,
		  0, 0, W_Width, W_Height );
  XClearArea( XSTed_d, XSTed_w, 0, 0, W_Width, W_Height, False );

  isgscrchanged=1;
  return;
}

void XSTed_cls_al( void ) {

  XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc, 
	     0, 0, W_Width, W_Height, 0, 0 );
  XFillRectangle( XSTed_d, XSTed_tscr, XSTed_egc,
		  0, 0, W_Width, W_Height );

  istscrchanged=1;
  return;
}

void XSTed_overlap( void ) {

  static char *namlist[2];
  int l,r;
  XTextProperty ct;

  if ( strcmp( last_file_name, rcp_file ) != 0 ) {
    strncpy( last_file_name, rcp_file, 512 );
    l =strlen( XSTed_Window_Title );
    l+=strlen( (char *)eucconv(mtitle) );
    l+=strlen( rcp_file );
    l+=10;
    namlist[0] = (char *)malloc(sizeof(char)*l);

    if ( rcp_file[0] != 0 )
      r=snprintf( namlist[0], l, "%s : [ %s ] %s",
	       XSTed_Window_Title, rcp_file, eucconv(mtitle) );
    else
      r=snprintf( namlist[0], l, "%s", XSTed_Window_Title );
    if ( r > 0 ) {
      XmbTextListToTextProperty( XSTed_d, namlist, 1, XCompoundTextStyle, &ct );
    
      XSetWMName ( XSTed_d, XSTed_w, &ct );
    }
    free(namlist[0]);
  }

  XSync(XSTed_d, False);

  istscrchanged=0;
  isgscrchanged=0;
  return;
}
