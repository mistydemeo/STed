/*
  xwin_mouse.c

  Made by Studio Breeze. 1998
 */

#include "sted.h"
#include "xwin.h"

static int max_msx=767, max_msy=511;
static int min_msx=0, min_msy=0;

void XSTed_ms_curof( void ) {

  return;
}

void XSTed_ms_curon( void ) {

  return;
}

int  XSTed_ms_getdt( void ) {

  int ret=0;
  Window r_w,ch_w;
  int rx, ry, wx, wy;
  unsigned int mask_r;

  XQueryPointer( XSTed_d, XSTed_w, &r_w, &ch_w,
		 &rx, &ry, &wx, &wy, &mask_r );

  if ( mask_r&Button1Mask ) ret|=0xff00;
  if ( mask_r&Button3Mask ) ret|=0x00ff;

  return ret;
}

void XSTed_ms_init( void ) {

  return;
}

int  XSTed_ms_limit( int xs, int ys, int xe, int ye ) {

  min_msx = xs;
  min_msy = ys;
  max_msx = xe;
  max_msy = ye;

  return 0;
}

int  XSTed_ms_pos( int *x, int *y ) {

  int ret=0;
  Window r_w,ch_w;
  int rx, ry, wx, wy;
  unsigned int mask_r;

  XQueryPointer( XSTed_d, XSTed_w, &r_w, &ch_w,
		 &rx, &ry, &wx, &wy, &mask_r );

  if ( wx<min_msx ) wx=min_msx;
  else if ( wx>max_msx ) wx=max_msx;
  if ( wy<min_msy ) wy=min_msy;
  else if ( wy>max_msy ) wy=max_msy;

  *x = wx;
  *y = wy;

  return ret;
}
