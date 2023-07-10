/*
  dos.h

  functions for compatibility to doslib

  ( mainly contains file-oriented functions )

  Made by Studio Breeze. 1998

 */

#ifndef _DOS_H_
#define _DOS_H_

#include <stdio.h>

#include "doslib.h"

/* console-oriented functions */
int _dos_c_cls_al ( void );
int _dos_c_cls_ed( void );
int _dos_c_curoff( void );
int _dos_c_curon( void );
int _dos_c_fnkmod( int mode );
int _dos_c_window( int x, int y );
int _dos_fnckeygt( int fno, char *buff );
int _dos_fnckeyst( int fno, const char *buff );
int _dos_inpout( int code );

/* functions */
void *_dos_malloc(int i);
dosmode_t _dos_chmod( const char *name, dosmode_t atr );
int _dos_chdir( const char *name );
int _dos_curdir( int drive, char *buff );
int _dos_curdrv( void );
int _dos_delete( const char *name );
int _dos_drvctrl( int mode, int drive );
int _dos_rename( const char *name, const char *nname );
int _dos_super( int stack );
int _dos_files (struct _x68_filbuf *buff, const char *name, int atr );
int _dos_nfiles( struct _x68_filbuf *buff );
int _dos_setblock( void *memptr, int newsize );
int dskf( char drive_number );
FILE *fopen2( char *name, char *mode);

/* local use functions */
/* converts HUMAN file name to unix file name */
static char *name_conv ( char *dest, const char *name );

#endif
