/*
  xwin_print.c

  xwin: printing oriented functions

  Made by Studio Breeze. 1998

 */

#include "sted.h"
#include "xwin.h"

int current_gwindow;

static Bool iscursoron=False;

static int current_tx, current_ty;
static int current_gx, current_gy;

void XSTed_curon( void ) {

  iscursoron=True;
  XSTed_trev( current_tx, current_ty, 1, 3 );

  return;
}

void XSTed_curoff( void ) {

  iscursoron=False;
  return;
}

void XSTed_tlocate( int x, int y ) {

  int lx, ly;

  lx=current_tx;
  ly=current_ty;

  current_tx = x % X68_TWidth;
  current_ty = y % X68_THeight;

  if ( iscursoron ) {
    XSTed_trev( lx, ly, 1, 3 );
    XSTed_trev( current_tx, current_ty, 1, 3 );
  }

  return;
}

void XSTed_tputs( char *message ) {

  int w,h,ht;
  int l;
  int x0,y0,x,y;
  int lx, ly;
  XRectangle ink,log;

  lx = current_tx;
  ly = current_ty;

  l = strlen(message);

  if ( message[0]=='\r' ) {
    l-=2;
    message+=2;
    current_tx=0;
    if (current_ty<X68_THeight-1) current_ty++;
  }

  x0=W_Width * current_tx/X68_TWidth;
  y0=W_Height * current_ty/X68_THeight;

  XmbTextExtents( XSTed_fs, message, l, &ink, &log );
  w = log.width;
  h = XSTed_fs_max_height;
  ht = log.y;

  XSTed_SetTColor( TCurrentCol );
  XSetBackground(XSTed_d, XSTed_tgc, STed_col[TCurrentBackCol] );

  XmbDrawImageString( XSTed_d, XSTed_tscr, XSTed_fs, XSTed_tgc,
		      x0, y0-ht, message, l );

  if ( TCurrentCol != 0 ) {
    XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_vscr, XSTed_wgc,
	       x0, y0, w, h, 0, 0 );
    XmbDrawString( XSTed_d, XSTed_vscr, XSTed_fs, XSTed_tgc,
		   0, -ht, message, l );

    XCopyArea( XSTed_d, XSTed_vscr, XSTed_w, XSTed_wgc,
	       0, 0, w, h, x0, y0 );
  } else {
    XmbDrawImageString( XSTed_d, XSTed_w, XSTed_fs, XSTed_tgc,
			x0, y0-ht, message, l );
  }

  current_tx+=l;
  if ( iscursoron ) {
    XSTed_trev( lx, ly, 1, 3 );
    XSTed_trev( current_tx, current_ty, 1, 3 );
  }
  istscrchanged=1;
  return;
}

void XSTed_gputs( int x0, int y0, const char *message ) {

  int w,l,c;
  int h,ht;
  int x,y,xd,yd;
  XRectangle ink,log;

  current_gx = W_Width * x0 / X68_GWidth;
  current_gy = (W_Height * y0 / X68_GHeight) % W_Height;

  c = (y0>=X68_GHeight) ? 1:0;
  l = strlen(message);

  XmbTextExtents( XSTed_fs, message, l, &ink, &log );
  w = log.width;
  h = XSTed_fs_max_height;
  ht = log.y;

  XSTed_SetGColor( GCurrentCol );
  if ( c==current_gwindow )
    XmbDrawString( XSTed_d, XSTed_w,
		   XSTed_fs, XSTed_ggc, 
		   current_gx, current_gy-ht, message, l );
  XmbDrawString( XSTed_d, XSTed_gscr[c],
		 XSTed_fs, XSTed_ggc, 
		 current_gx, current_gy-ht, message, l );

  isgscrchanged=1;
  return;
}

void XSTed_cls_eol( void ) {

  int sx,sy,ex,ey;

  sx=0;
  ex=W_Width;
  sy=W_Height * current_ty/X68_THeight;
  ey=sy+XSTed_fs_max_height;

  XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc, 
	     sx, sy, ex-sx, ey-sy, sx, sy );

  XFillRectangle( XSTed_d, XSTed_tscr, XSTed_egc,
		  sx, sy, ex-sx, ey-sy );

  istscrchanged=1;
  return;
}

void XSTed_cls_ed( void ) {

  int sx,sy,ex,ey;
  int y;

  sx=0;
  ex=W_Width;
  sy=W_Height * current_ty/X68_THeight;
  ey=W_Height;

  XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc, 
	     sx, sy, ex-sx, ey-sy, sx, sy );
  XFillRectangle( XSTed_d, XSTed_tscr, XSTed_egc,
		  sx, sy, ex-sx, ey-sy );

  istscrchanged=1;
  return;
}
