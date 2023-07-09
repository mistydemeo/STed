/*
  iocs_console.c

  functions for compatibility to iocslib
  ( containing mainly console oriented functions )

  Made by Studio Breeze. 1998

 */

#include "sted.h"

/* local val.s */

unsigned int iocs_current_console_width=96, iocs_current_console_height=32;
unsigned int iocs_console_xtop=0, iocs_console_ytop=0;
unsigned int iocs_current_text_x=0, iocs_current_text_y=0;
unsigned int iocs_current_color=15;

/* functions */

/* console */

int _iocs_b_consol( int xs, int ys, int xl, int yl ) {

  iocs_current_console_width =xl+1;
  iocs_current_console_height=yl+1;

  iocs_console_xtop = xs/8;
  iocs_console_ytop = ys/8;

  iocs_current_text_x = 0;
  iocs_current_text_y = 0;

  return xl*65536+yl;
}

int _iocs_b_color( int color ) {

  int c;
  c=iocs_current_color;
  iocs_current_color = color;
  if ( isconsole ) {
    curses_tcolor( color );
  } else if ( isxwin ) {
    XSTed_tcolor( color );
  }

  return c;
}

int _iocs_b_print( const char *message ) {

  int x,y;

  if ( !iswindowopened ) {
    printf("%s", message );
    return 0;
  }
  if ( isconsole )
    curses_tputs( message );
  else if ( isxwin )
    XSTed_tputs( message );

  x = iocs_current_text_x + strlen(message);
  y = iocs_current_text_y;
  if ( x >= iocs_current_console_width ) {
    x %= iocs_current_console_width;
    x += iocs_console_xtop;
    y ++;
  }
  if ( y >= iocs_current_console_height ) {
    y=iocs_current_console_height-1;
  }

  iocs_current_text_x = x;
  iocs_current_text_y = y;

  return x*65536+y;
}

int _iocs_b_putmes ( int col, int x, int y, int width, const char *str ) {

  int c;

  if ( isconsole ) {
    curses_tcolor(col);
    curses_tlocate( x, y );
    curses_tputs( str );
    curses_tcolor( iocs_current_color );
    curses_tlocate( iocs_current_text_x+iocs_console_xtop,
		    iocs_current_text_y+iocs_console_ytop );
  } else if ( isxwin ) {
    c=XSTed_tcolor( col );
    XSTed_tlocate( x, y );
    XSTed_tputs( str );
    XSTed_tcolor( c );
    XSTed_tlocate( iocs_current_text_x+iocs_console_xtop,
		   iocs_current_text_y+iocs_console_ytop );
  }

  return 0;
}

int _iocs_b_locate( int x0, int y0 ) {

  int old_x, old_y;
  int x,y;

  old_x = iocs_current_text_x;
  old_y = iocs_current_text_y;

  if ( x0 != -1 ) {
    iocs_current_text_x = x0;
    iocs_current_text_y = y0;
    /*
    if ( x0 >= iocs_current_console_width ) return -1;
    else if ( y0 >= iocs_current_console_height ) return -1;
    */
    x = x0+iocs_console_xtop;
    y = y0+iocs_console_ytop;

    if ( isconsole )
      curses_tlocate( x, y );
    else if ( isxwin )
      XSTed_tlocate( x, y );
  }

  return old_x*65536+old_y;
}

void _iocs_b_clr_al( void ) {

  if ( isconsole ) {
    curses_cls_al();
  } else if ( isxwin ) {
    XSTed_cls_al();
  }


  iocs_current_text_x = 0;
  iocs_current_text_y = 0;

  return;
}

void _iocs_b_clr_ed ( void ) {

  if ( isconsole ) {
    curses_cls_ed();
  } else if ( isxwin ) {
    XSTed_cls_ed();
  }
  return;
}

/* fonts */

int _iocs_defchr( int type, int code, const void *buff ) {

  /* not implemented */
  return 0;
}

int _iocs_fntget( int type, int code, struct _x68_fntbuf *fntbuf ) {

  /* not implemented */
  return 0;
}
