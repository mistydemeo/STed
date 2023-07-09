/*
  xwin_col.c

  xwin: color oriented functions

  Made by Studio Breeze. 1998

 */

#include "sted.h"
#include "xwin.h"

int GCurrentCol=15;
int TCurrentCol=3;
int TCurrentBackCol=0;

static void XSTed_GetColor( int, int );


int XSTed_gpalet( int pal, int col ) {

  XSTed_GetColor( pal+XSTed_t_palletes, col );

  return 0;
}

int XSTed_tpalet( int pal, int col ) {

  if ( col > 0 )
    XSTed_GetColor( pal, col );

  return 0;
}

int XSTed_tcolor( int col ) {

  int b,c;

  b=0;
  if ( col&8 ) { /* reverse */
    b=col&3;
    col=0;
  }
  col &= 3;
  c = TCurrentCol;
  TCurrentCol=col;
  TCurrentBackCol = b;

  /*XSTed_SetTColor( col );
  XSetBackground( XSTed_d, XSTed_tgc, STed_col[b] );*/

  return c;
}

int XSTed_gcolor( int col ) {

  int c;

  c = GCurrentCol;
  GCurrentCol = col;
  /*XSTed_SetGColor( col );*/

  return c;
}

int XSTed_SetTColor( int col ) {

  int c;

  c = STed_col[col];
  XSetForeground( XSTed_d, XSTed_tgc, c );
  return c;
}

int XSTed_SetGColor( int col ) {

  GCurrentCol = col;
  XSetForeground( XSTed_d, XSTed_ggc, STed_col[col+XSTed_t_palletes] );

  return STed_col[col+XSTed_t_palletes];
}

void XSTed_GetColor( int  i, int pal ) {

  XColor C;
  int r,g,b;

  b=((pal>>1)&0x001f)<<11;
  r=((pal>>6)&0x001f)<<11;
  g=((pal>>11)&0x001f)<<11;

  C.red   = r;
  C.green = g;
  C.blue  = b;
  C.flags = DoRed | DoGreen | DoBlue ;
  C.pixel = STed_col[i];

  if ( IsVisualRW ) {
    XStoreColor( XSTed_d, XSTed_cmap, &C );
  } else {
    XAllocColor( XSTed_d, XSTed_cmap, &C );
    STed_col[i]=C.pixel;
  }

  return;
}
