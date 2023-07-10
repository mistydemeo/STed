/*
  hprint.c

  functions for compatibility in hprint.s
  "extremely fast print functions"

  H_INIT , H_PRINT , H_PRINT2

  Made by Studio Breeze. 1998

 */

#ifndef _HPRINT_H_
#define _HPRINT_H_

void H_INIT ( void );
void H_PRINT ( char * s1, char *s2, char *s3 );
void H_PRINT2 ( char *s1, char *s2, char *s3 );

#endif
