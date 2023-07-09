/*
  mcpy.c

  functions for compatibility to mcpy.s
  ( some memory-oriented functions )

  Made by Studio Breeze. 1998

 */

#include "sted.h"


/*
  void memcpy_l( unsigned char *dest, unsigned char *src , int len )

   copies len bytes from src to dest

   I guess that original programmer want to make fast copy function
   by coding long-word copy routine.
 */

void memcpy_l( unsigned char *dest, unsigned char *src, int len ) {

  memmove( (void *)dest, (void *)src, (size_t)len );
  return;

#if 0
  int d1,d2;

  if ( !len ) return;
  if ( dest=src ) return;

  len/=4;
  d2=len;
  len--;
  d1=d0;

  if ( dest > src ) {
    d2*=4;
    dest+=d2;
    src+=d2;
  }

  while ( len ) {
    while ( d1 ) {
      *(--dest) == *(--src);
    }
  }
  return;
#endif

}

/*
  void keyclr( void )

   clear key buffer

 */

void keyclr( void ) {

  /* not implemented */
  return ;
}
