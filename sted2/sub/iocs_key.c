/*
  iocs_key.c

  functions for compatibility to iocslib
  ( containing mainly key oriented functions )

  Made by Studio Breeze. 1998

 */

#include "sted.h"

/* key input */

void _iocs_ledmod( int code, int onoff ) {

  if ( isconsole ) {
    curses_ledmod( code, onoff );
  } else if ( isxwin ) {
    XSTed_ledmod( code, onoff );
  }

  return;
}

int _iocs_b_keyinp( void ) {

  int ret;

  ret=0;
  if ( isconsole ) {
    ret=curses_keyinp();
  } else if ( isxwin ) {
    ret=XSTed_keyinp();
  }

  return ret;
}

int _iocs_b_keysns( void ) {

  int ret;

  ret=0;
  if ( isconsole ) {
    ret=(curses_keyin(0xfe)==0)?0:1;
  } else if ( isxwin ) {
    ret=XSTed_keysns();
  }

  return ret;
}

int _iocs_b_sftsns( void ) {

  int ret=0;

  if ( isconsole ) {
    ret=curses_sftsns();
  } else if ( isxwin ) {
    ret=XSTed_sftsns();
  }
  return ret;
}

int _iocs_bitsns( int group ) {

  int ret=0;

  if ( isxwin ) {
    ret = XSTed_bitsns( group );
  }
  return ret;
}
