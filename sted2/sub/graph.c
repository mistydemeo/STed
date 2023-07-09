/*
  graph.c

  functions for compatibility in graph.s

  g_print rev_area tg_copy tg_copy2 t_scrw txcur

  Made by Studio Breeze. 1998

 */

#include "sted.h"

void g_print( int x, int y, char *str, int col ) {

  if ( isconsole ) {
    curses_gcolor( col );
    curses_gputs( x, y, str );
  } else if ( isxwin ) {
    XSTed_gcolor( col );
    XSTed_gputs( x, y, str );
  }
  return;
}

void rev_area( int r_ad, int r_ln, int edit_scr ) {

  if ( isxwin ) {
    XSTed_rev_area( r_ad, r_ln, edit_scr );
  }

  return;
}

void tg_copy( int edit_scr ) {

  /* T_VRAM to G_VRAM */
  /* edit_scr=0 : left, edit_scr=1 : right  */
  /* (2,4)-(19,31)      (58, 4)-(75,31)     */

  if ( isconsole ) {
    curses_tg_copy( edit_scr );
  } else if ( isxwin ) {
    XSTed_tg_copy( edit_scr );
  }
  return;
}

void tg_copy2( int edit_scr ) {

  /* T_VRAM to G_VRAM */
  /* edit_scr=0 : left, edit_scr=1 : right  */
  /* (0,6)-(27,29)         (38,6)-(65,29) */

  if ( isconsole ) {
    curses_tg_copy2( edit_scr );
  } else  if ( isxwin ) {
    XSTed_tg_copy2( edit_scr );
  }


  return;
}

void t_scrw( int x1, int y1, int xs, int ys, int x2, int y2 ) {

  if ( isconsole ) {
    curses_t_scrw( x1, y1, xs, ys, x2, y2 );
  } else if ( isxwin ) {
    XSTed_t_scrw( x1, y1, xs, ys, x2, y2 );
  }

  return;
}

void txcur( int a, int b, int c1, int c2, int cs ) {

  int i;

  if ( edit_scr ) a+=56;
  if ( isconsole ) {
    for ( i=0 ; i<c2 ; i++ )
      curses_trev( a, b+i, c1, cs );
  } else if ( isxwin ) {
    for ( i=0 ; i<c2 ; i++ )
      XSTed_trev( a, b+i, c1, cs );
  }

  return;
}
