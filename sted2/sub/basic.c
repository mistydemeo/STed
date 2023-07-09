/* basic.c

   some of X-BASIC compatible functions

   Made by Studio Breeze. 1998

*/

#include "sted.h"


/* graphic functions */

void fill( int x1, int y1, int x2, int y2, unsigned int col ) {

  if ( isconsole ) {
    curses_gfill( x1, y1, x2, y2, col );

  } else if ( isxwin ) {
    XSTed_gfill( x1, y1, x2, y2, col );
  }
  return;
}

void box( int x1, int y1, int x2, int y2, unsigned int col, unsigned int ls ) {

  if ( isxwin ) {
    XSTed_gbox( x1, y1, x2, y2, col, ls );
  }
  return;
}

int point( int x, int y ) {

  int ret=0;
  if ( isxwin ) {
    ret = XSTed_gpoint( x, y );
  }
  return ret;
}

void line( int x1, int y1, int x2, int y2, int col, int ls ) {

  if ( isxwin ) {
    XSTed_gline( x1, y1, x2, y2, col ,ls );
  }
  return;
}

void symbol( int x, int y, char *st, char h,
	     char v, char mo, int p, char an ) {

  if ( isconsole ) {
    curses_gcolor( p );
    curses_gputs( x, y, st );

  } else if ( isxwin ) {
    XSTed_gcolor( p );
    XSTed_gputs( x, y, st );
  }
  return;
}


/* other functions */

/* returns string describing current day(?) */
char *dtasc( unsigned int j ) {

  static char dtasc_name[10];
  int y,a,b;

  a=(j>>9)&0x7f;
  b=a%10;
  a=a%100-b;
  y=a+b;
  
  snprintf(dtasc_name, 10, "%02d-%02d-%02d", y, ((j>>5)&0x0f)+1, j&0x1f );

  return dtasc_name;
}

/* returns string describing current time(?) */
char *tmasc( unsigned int j ) {

  static char tmasc_name[10];

  snprintf(tmasc_name, 10, "%02d:%02d:%02d", (j>>11)&0x1f, (j>>5)&0x3f, (j&0x1f)*2 );
  return tmasc_name;
}

/* returns mouse positions */
int mspos( int *x, int *y ) {

  int ret=0;

  if ( isxwin ) {
    XSTed_ms_pos( x, y );
  }

  return ret;
}

/* returns someting B-) */
void b_striS ( char * buf, int bufSize, int num ) {
  int r;

  r=snprintf( buf, bufSize, "%d", num );
  if ( r < 0 ) {
    buf[0]='\0';
  }
  return;
}

/* set current Kanji mode */
void KNJCTRL( int i, int j ) {

  /* not implemented */
  return;
}
