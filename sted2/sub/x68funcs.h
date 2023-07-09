/*
  x68funcs.h

  prototype dec.s for functions compatible to X680x0

  Made by Studio Breeze. 1998

 */

#ifndef _X68FUNCS_H_
#define _X68FUNCS_H_

/* variables */

extern int iswindowopened;
extern int iocs_graph_home; /* 0 or 1 */

extern char fnc_func[10][32];
extern char fnc_sfunc[10][32];
extern char fnc_key[12][6];
/* ROLL UP, ROLL DOWN, INS, DEL,
   UP, LEFT, RIGHT, DOWN,
   CLR, HELP, HOME, UNDO */

/* misc functions */

extern void strmfe( char *, const char *, const char * );
extern void b_striS( char *, int, int );
extern void KNJCTRL( int, int );

/* X-BASIC compatible functions */

extern double val( char * );
extern int child( char * );
extern int dskf( char );
extern int mspos( int *, int * );
extern char *dtasc( unsigned int );
extern char *tmasc( unsigned int );


extern void fill( int, int, int, int, unsigned int );
extern void box( int, int, int, int, unsigned int, unsigned int );
extern int  point( int, int );
extern void line( int, int, int, int, int, int );
extern void symbol( int, int, char *, char, char, char, int, char );

/* original functions */

extern FILE *fopen2( char *, char * );
extern void STed_system_initialize( int *, char *** );

#endif /* _X68FUNCS_H_ */
