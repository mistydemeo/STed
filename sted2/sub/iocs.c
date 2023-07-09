/*
  iocs.c

  functions for compatibility to iocslib
  ( containing misc functions )

  Made by Studio Breeze. 1998

 */

#include "sted.h"

/* etc */

int _iocs_b_wpeek( const void *adr ) {

  return 0; /* ignore */
}

void _iocs_b_wpoke( void *adr, int val ) {

  return; /* ignore */
}

int _iocs_ontime ( void ) {

  static struct timeval st;
  long i;

  gettimeofday( &st, NULL );
  i = st.tv_usec/10000 + st.tv_sec*100;

  return ((unsigned int)i%863999);
}

