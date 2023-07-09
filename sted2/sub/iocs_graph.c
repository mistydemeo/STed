/*
  iocs_graph.c

  functions for compatibility to iocslib
  ( containing mainly graphics oriented functions )

  Made by Studio Breeze. 1998

 */

#include "sted.h"

/* variables */

int iocs_graph_home;

/* functions */

int _iocs_crtmod( int mode ) {

  if ( mode < 0x100 ) {
    if ( mode==17 ) {
      if ( isconsole ){
	curses_close_window();
      } else if ( isxwin ) {
	XSTed_close_window();
      }
    } else {
      if ( isconsole ) {
	curses_init_window();
	curses_cls_al();
      } else if ( isxwin ) {
	XSTed_init_window();
	XSTed_cls_al();
      }
    }
  }

  return 0;
}

void _iocs_g_clr_on( void ) {

  if ( isconsole ) {
    curses_gclr();
  } else if ( isxwin ) {
    XSTed_gclr();
  }

  return;
}

int _iocs_gpalet( int no, int color ) {

  int ret=0;

  if ( isxwin ) {
    ret=XSTed_gpalet( no, color );
  }
  return ret;
}

int _iocs_home( int page, int x, int y ) {

  /* y=0 or 512 ( page select? ) */

  iocs_graph_home = y>511 ? 1:0;
  if ( isconsole )
    curses_ghome(iocs_graph_home);
  else if ( isxwin )
    XSTed_ghome(iocs_graph_home);
  return 0;
}

int _iocs_tgusemd( int text_gr, int mode ) {

  return 0; /* G-RAM is not used */
}

int _iocs_window( int sx, int sy, int ex, int ey ) {

  return 0; /* ignore */
}
