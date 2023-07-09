/*
  hprint.c

  functions for compatibility in hprint.s
  "extremely fast print functions"

  H_INIT , H_PRINT , H_PRINT2

  Made by Studio Breeze. 1998

 */

#include "sted.h"

void H_INIT ( void ) {

  /* not implemented */
  return;
}

void H_PRINT ( char * s1, char *s2, char *s3 ) {

  int x,y;
  int l=0;

  x=B_LOCATE(-1,0);
  y=x&0xffff;
  x=x>>16;

  if ( isconsole ) {
    curses_tlocate(0,y);
    curses_cls_eol();

    curses_tlocate(x,y);
    if (s1!="") {
      curses_tputs(s1);
      l=strlen(s1);
    }

    if (s2!="") {
      curses_tputs(s2);
      l+=strlen(s2);
    }

    if (s3!="") {
      curses_tputs(s3);
      l+=strlen(s3);
    }

    B_LOCATE(x+l,y);

  } else if ( isxwin ) {
    int c;
    XSTed_tlocate(0,y);
    XSTed_cls_eol();

    XSTed_tlocate(x,y);
    if (s1!="") {
      c=XSTed_tcolor(3);
      XSTed_tputs(s1);
      XSTed_tcolor(c);
      l=strlen(s1);
    }

    if (s2!="") {
      c=XSTed_tcolor(2);
      XSTed_tputs(s2);
      XSTed_tcolor(c);
      l+=strlen(s2);
    }

    if (s3!="") {
      c=XSTed_tcolor(1);
      XSTed_tputs(s3);
      XSTed_tcolor(c);
      l+=strlen(s3);
    }

    B_LOCATE(x+l,y);
  }

  return;
}

void H_PRINT2 ( char *s1, char *s2, char *s3 ) {

  int x,y;
  int l=0;

  x=B_LOCATE(-1,0);
  y=x&0xffff;
  x=x>>16;

  if ( isconsole ) {
    curses_tlocate(x,y);
    if (s1!="") {
      curses_tputs(s1);
      l=strlen(s1);
    }

    if (s2!="") {
      curses_tputs(s2);
      l+=strlen(s2);
    }

    if (s3!="") {
      curses_tputs(s3);
      l+=strlen(s3);
    }

    B_LOCATE(x+l,y);

  } else if ( isxwin ) {

    int c;
    XSTed_tlocate(x,y);
    if (s1!="") {
      c=XSTed_tcolor(3);
      XSTed_tputs(s1);
      XSTed_tcolor(c);
      l=strlen(s1);
    }

    if (s2!="") {
      c=XSTed_tcolor(2);
      XSTed_tputs(s2);
      XSTed_tcolor(c);
      l+=strlen(s2);
    }

    if (s3!="") {
      c=XSTed_tcolor(1);
      XSTed_tputs(s3);
      XSTed_tcolor(c);
      l+=strlen(s3);
    }

    B_LOCATE(x+l,y);
  }
  return;
}
