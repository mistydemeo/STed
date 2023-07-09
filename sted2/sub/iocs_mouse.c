/*
  iocs_mouse.c.c

  functions for compatibility to iocslib
  ( containing mouse oriented functions )

  Made by Studio Breeze. 1998

 */

#include "sted.h"

/* functions */

void _iocs_ms_curof( void ) {

  if ( isxwin ) {
    XSTed_ms_curof();
  }
  return;
}

void _iocs_ms_curon( void ) {

  if ( isxwin ) {
    XSTed_ms_curon();
  }
  return;
}

int _iocs_ms_getdt( void ) {

  int ret=0;

  if ( isxwin ) {
    ret=XSTed_ms_getdt();
  }
  return ret;
}

void _iocs_ms_init( void ) { 

  if ( isxwin ) {
    XSTed_ms_init();
  }
  return;
}

int _iocs_ms_limit( int xs, int ys, int xe, int ye ) {

  int ret=0;

  if ( isxwin ) {
    XSTed_ms_limit( xs, ys, xe, ye );
  }

  return ret;
}
