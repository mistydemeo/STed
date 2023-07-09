/*
  curses.h

  functions for displaying texts with curses library

  Made by Studio Breeze. 1998

 */

#ifndef _CURSES_LOCAL_H_
#define _CURSES_LOCAL_H_

void curses_init_window( void );
void curses_close_window( void );
void curses_curon( void );
void curses_curoff( void );
void curses_gcolor( int col );
void curses_tcolor( int col );
void curses_tputs( char *message );
void curses_gputs( int x, int y, const char *message );
void curses_tlocate( int x, int y );
void curses_ghome( int home_flag );
void curses_trev( int x, int y, int l, int col );
void curses_tfill( unsigned short page, short  sx, short sy, short lx, short ly, unsigned short col );
void curses_gfill( int sx, int sy, int ex, int ey, int col );
void curses_trascpy( int dst, int src, int line, int mode );
void curses_t_scrw( int x1, int y1, int xs, int ys, int x2, int y2 );
void curses_tg_copy( int edit_scr );
void curses_tg_copy2( int edit_scr );
void curses_cls_al( void );
void curses_gclr( void );
void curses_cls_ed( void );
void curses_cls_eol( void );
void curses_rwindow( void );
int curses_keyin( int code );
int curses_keyinp( void );
int curses_sftsns( void );
void curses_key_wait( void );
void curses_midi_wait( void );
void curses_ledmod( int code, int onoff );

#endif