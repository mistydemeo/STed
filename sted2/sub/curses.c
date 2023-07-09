/*
  curses.c

  functions for displaying texts with curses library

  Made by Studio Breeze. 1998

 */

int x68_scancode[]={
  0x35, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x09, 0x0a, 0x28, 0x27, 0x31, 0x0c, 0x32, 0x33,
  0x0b, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
  0x09, 0x0a, 0x28, 0x27, 0x31, 0x0c, 0x32, 0x33,
  0x1b, 0x1e, 0x2e, 0x2c, 0x20, 0x13, 0x21, 0x22,
  0x23, 0x18, 0x24, 0x25, 0x26, 0x30, 0x2f, 0x19,
  0x1a, 0x11, 0x14, 0x1f, 0x15, 0x17, 0x2d, 0x12,
  0x2b, 0x16, 0x2a, 0x1c, 0x0e, 0x29, 0x0d, 0x34,
  0x1b, 0x1e, 0x2e, 0x2c, 0x20, 0x13, 0x21, 0x22,
  0x23, 0x18, 0x24, 0x25, 0x26, 0x30, 0x2f, 0x19,
  0x1a, 0x11, 0x14, 0x1f, 0x15, 0x17, 0x2d, 0x12,
  0x2b, 0x16, 0x2a, 0x1c, 0x0e, 0x29, 0x0d
};

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */

#if defined(USE_CURSES) && defined(HAS_CURSES)

#if defined(USE_NCURSES) && !defined(RENAMED_NCURSES)
# include <ncurses.h>
#else
# include <curses.h>
#endif /* USE_NCURSES && ! RENAMED_NCURSES */

#include "x68defines.h"

extern char *nkf_conv( const char *, char *, char * );

extern int iswindowopened;
extern int iocs_graph_home; /* 0 or 1 */

extern char fnc_func[10][32];
extern char fnc_sfunc[10][32];
extern char fnc_key[12][6];
/* ROLL UP, ROLL DOWN, INS, DEL,
   UP, LEFT, RIGHT, DOWN,
   CLR, HELP, HOME, UNDO */

extern int iocs_current_console_width, iocs_current_console_height;
extern int iocs_console_xtop, iocs_console_ytop;
extern int iocs_current_text_x, iocs_current_text_y;
extern int iocs_current_color;

/* static function */

static void curses_rwindow( void );


/* the following functions are based on curses */

static iscursesinited=0;
static WINDOW *curses_twindow, *curses_gwindow[2], *w;
static WINDOW *curses_awindow;
static int current_gwindow=-1;
static int current_tcolor, current_gcolor;
static int current_tx, current_ty;
static int current_gx, current_gy;
static int iscursoron;

static int last_key;
static int insert_flag;

#ifndef HAVE_MVWCHGAT
static void mvwchgat( WINDOW *win, int ty, int tx, int l, int attr, int color, char *dummy ) {} 
/* void function that forces to through linker. (by zinnia@jan.ne.jp) */
#endif /* HAVE_MVWCHGAT */

#endif /* USE_CURSES */

void curses_init_window( void ) {

#ifdef USE_CURSES
  if ( iscursesinited ) return;

  initscr();
 
  w                 = newwin(0,0,0,0);
  curses_twindow    = newwin(0,0,0,0);
  curses_awindow    = newwin(0,0,0,0);
  curses_gwindow[0] = newwin(0,0,0,0);
  curses_gwindow[1] = newwin(0,0,0,0);

  cbreak();
  noecho();
  keypad   ( stdscr, TRUE );
  nodelay  ( stdscr, TRUE );
  leaveok  ( stdscr, TRUE );
/*  notimeout( stdscr, TRUE );*/

  nonl();

  current_gwindow=0;
  current_tcolor=0;
  current_gcolor=0;

  current_tx=0;
  current_ty=0;

  iscursoron=0;

  iswindowopened=1;
  iscursesinited=1;

#endif /* USE_CURSES */
  return;
}

void curses_close_window( void ) {

#ifdef USE_CURSES

  if ( iscursesinited ) {

    delwin(w);
    delwin(curses_twindow);
    delwin(curses_awindow);
    delwin(curses_gwindow[0]);
    delwin(curses_gwindow[1]);

    clear();
    refresh();
    endwin();
    fflush(stdout);
    fflush(stderr);
  }
#endif /* USE_CURSES */
  return;
}

void curses_curon( void ) {

#ifdef USE_CURSES
  if ( !iscursoron ) {
    leaveok( stdscr, FALSE );
    iscursoron=1;
  }
#endif /* USE_CURSES */
  return;
}

void curses_curoff( void ) {

#ifdef USE_CURSES
  if ( iscursoron ) {
    leaveok( stdscr, TRUE );
    iscursoron=0;
  }
#endif /* USE_CURSES */
  return;
}

void curses_gcolor( int col ) {

#ifdef USE_CURSES
  if ((col==15)||(col==3)||(col==2)||(col==1)||(col==6)) {
    current_gcolor=0;
  } else {
    current_gcolor=1;
  }

#endif /* USE_CURSES */
  return;
}

void curses_tcolor( int col ) {

#ifdef USE_CURSES
  switch( col ) {
  case 11:
    wattroff( curses_twindow, A_NORMAL );
    wattroff( curses_twindow, A_STANDOUT );
    wattron ( curses_twindow, A_REVERSE );
    break;

  case 3:
    wattroff( curses_twindow, A_NORMAL );
    wattron ( curses_twindow, A_STANDOUT );
    wattroff( curses_twindow, A_REVERSE );
    break;

  default:
    wattron ( curses_twindow, A_NORMAL );
    wattroff( curses_twindow, A_STANDOUT );
    wattroff( curses_twindow, A_REVERSE );
    break;
  }

  current_tcolor=col;

#endif /* USE_CURSES */
  return;
}

void curses_tputs( char *message ) {

#ifdef USE_CURSES
  chtype t;
  int l,i;
  char s[128];
  
  l=strlen( message );
  if ( message[0]=='\r' ) {
    l-=2;
    message+=2;
    current_tx=0;
    if (current_ty<X68_THeight-1) current_ty++;
    wmove( curses_twindow, current_ty, current_tx );
  }

  for ( i=0 ; i<l ; i++ ) s[i]=' ';
  s[i]=0;
  waddstr( curses_twindow, s );

  wmove( curses_twindow, current_ty, current_tx );
  waddstr( curses_twindow, message );

  t = mvwinch( curses_twindow,
	       current_ty, current_tx ) & A_ATTRIBUTES;
  if ( t&A_REVERSE ) {
    mvwchgat( curses_gwindow[current_gwindow],
	      current_ty, current_tx ,l,
	      A_REVERSE, COLOR_WHITE, NULL );
  } else {
    mvwchgat( curses_gwindow[current_gwindow],
	      current_ty, current_tx ,l,
	      A_NORMAL, COLOR_WHITE, NULL );
  }

  current_tx+=l;
  wmove( curses_twindow, current_ty, current_tx );
  wmove( curses_gwindow[current_gwindow], current_gy, current_gx );

#endif /* USE_CURSES */
  return;
}

void curses_gputs( int x, int y, const char *message ) {

#ifdef USE_CURSES
  int c;
  chtype t;
  int flg;
  int l;

  current_gx = X68_TWidth * x / X68_GWidth;
  current_gy = (X68_THeight * y / X68_GHeight) % X68_THeight;

  c = (y>=X68_GHeight) ? 1:0;

  t=mvwinch( curses_gwindow[c],
	    current_gy, current_gx )&A_ATTRIBUTES;
  flg=((t&A_REVERSE)!=0)||(current_gcolor!=0)?1:0;

  mvwaddstr( curses_gwindow[c],
	    current_gy, current_gx, message );
  l=strlen(message);

  if ( flg ) 
      mvwchgat( curses_gwindow[c], current_gy, current_gx,
	       l, A_REVERSE, COLOR_WHITE, NULL );
  else
      mvwchgat( curses_gwindow[c], current_gy, current_gx,
	       l, A_NORMAL, COLOR_WHITE, NULL );

#endif /* USE_CURSES */
  return;
}

void curses_tlocate( int x, int y ) {

#ifdef USE_CURSES
  wmove( curses_twindow, y%X68_THeight, x );

  current_tx=x;
  current_ty=y%X68_THeight;

#endif /* USE_CURSES */
  return;
}

void curses_ghome( int home_flag ) {

#ifdef USE_CURSES
  current_gwindow = home_flag;
  touchwin( curses_gwindow[current_gwindow] );

#endif /* USE_CURSES */
  return;
}

void curses_trev( int x, int y, int l, int col ) {

#ifdef USE_CURSES
  chtype t;

  t = mvwinch( curses_twindow, y, x ) & A_ATTRIBUTES;
  if ( t&A_REVERSE ) {
    mvwchgat( curses_twindow, y, x ,l,
	     A_NORMAL, COLOR_WHITE, NULL );
    mvwchgat( curses_gwindow[current_gwindow], y, x ,l,
	     A_NORMAL, COLOR_WHITE, NULL );
  } else {
    mvwchgat( curses_twindow, y, x ,l,
	     A_REVERSE, COLOR_WHITE, NULL );
    mvwchgat( curses_gwindow[current_gwindow], y, x ,l,
	     A_REVERSE, COLOR_WHITE, NULL );
  }
  wmove( curses_twindow, current_ty, current_tx );
  wmove( curses_gwindow[current_gwindow], current_gy, current_gx );

#endif /* USE_CURSES */
  return;
}

void curses_tfill( unsigned short page, short  sx, short sy, short lx, short ly, unsigned short col ) {

#ifdef USE_CURSES
  int x,y,i;
  char sp[256];

  sy+=page*X68_GHeight;

  for ( i=0 ; i<lx/8 ; i++ ) sp[i]=' ';
  sp[i]=0;

  for ( y=sy ; y<sy+ly ; y+=16 ) {
    mvwaddstr( curses_twindow, (y/16)%X68_THeight, sx/8, sp );
  }

#endif /* USE_CURSES */
  return;
}

void curses_gfill( int sx, int sy, int ex, int ey, int col ) {

#ifdef USE_CURSES
  int x,y,i;
  int cx,cy,c;
  char sp[256];

  sx++;
  sy++;
  x=(ex-sx)/8;
  for ( i=0 ; i<x ; i++ ) sp[i]=' ';
  sp[i]=0;

  cx = X68_TWidth * sx / X68_GWidth;
  if ( col < 10 ) {
    for ( y=sy ; y<ey ; y+=16 ) {
      cy=(X68_THeight*y/X68_GHeight) % X68_THeight;
      c = (y>=X68_GHeight) ? 1:0;
      
      mvwaddstr( curses_gwindow[c],cy, cx, sp );
      mvwchgat( curses_gwindow[c],cy, cx, x,
	       A_NORMAL, COLOR_WHITE, NULL );
    }
  } else {
    for ( y=sy ; y<ey ; y+=16 ) {
      cy=(X68_THeight*y/X68_GHeight)%X68_GHeight;
      c = (y>=X68_GHeight) ? 1:0;
      
      mvwaddstr( curses_gwindow[c],cy, cx, sp );
      mvwchgat( curses_gwindow[c],cy, cx, x,
	       A_REVERSE, COLOR_WHITE, NULL );
    }
  }
#endif /* USE_CURSES */
  return;
}

void curses_trascpy( int dst, int src, int line, int mode ) {

#ifdef USE_CURSES
  int i,maxx,maxy;

  line/=4;
  getmaxyx( stdscr, maxy, maxx );

  if ( mode >= 0x8000 ) {
    src=(src-3)/4-line+1;
    dst=(dst-3)/4-line+1;

    copywin( curses_twindow, curses_awindow, src, 0,
	     0,0,line-1,maxx-1, FALSE );
    copywin( curses_awindow, curses_twindow, 0,0,
	     dst, 0, dst+line-1, maxx-1, FALSE );
  } else {
    src/=4;
    dst/=4;
    if ( src==63 ) {
      wmove( curses_twindow, dst, 0 );
      wclrtoeol( curses_twindow );
    } else {
      copywin( curses_twindow, curses_twindow, src, 0,
	       dst, 0, dst+line-1, maxx-1, FALSE );
    }
  }

#endif /* USE_CURSES */
  return;
}

void curses_t_scrw( int x1, int y1, int xs, int ys, int x2, int y2 ) {

#ifdef USE_CURSES
  copywin( curses_twindow, curses_awindow, y1/16, x1,
	   0,0, ys/16, xs,
	   FALSE );
  copywin( curses_awindow, curses_twindow, 0, 0,
	   y2/16, x2, (y2+ys-1)/16, x2+xs-1,
	   FALSE );
#endif /* USE_CURSES */
  return;
}

void curses_tg_copy( int edit_scr ) {

#ifdef USE_CURSES 
  int x, xl, y, yl;

  xl=36 ; yl=24;
  if ( !edit_scr ) {
    x= 2 ; y= 6;
  } else {
    x=58 ; y= 6;
  }

  copywin( curses_twindow, curses_gwindow[1],
	   y, x, y, x, y+yl, x+xl, FALSE );
  
#endif /* USE_CURSES */
  return;
}

void curses_tg_copy2( int edit_scr ) {

#ifdef USE_CURSES
  int x, xl, y, yl;

  xl=56 ; yl=24 ;
  if ( !edit_scr ) {
    x= 0 ; y= 6;
  } else {
    x=38 ; y= 6;
  }

  copywin( curses_twindow, curses_gwindow[1],
	   y, x, y, x, y+yl, x+xl, FALSE );

#endif /* USE_CURSES */
  return;
}

void curses_cls_al( void ) {

#ifdef USE_CURSES
  wclear( curses_twindow );
#endif /* USE_CURSES */
  return;
}

void curses_gclr( void ) {

#ifdef USE_CURSES
  wclear( curses_gwindow[0] );
  wclear( curses_gwindow[1] );
#endif /* USE_CURSES */
  return;
}

void curses_cls_ed( void ) {

#ifdef USE_CURSES
  wclrtobot( curses_twindow );
#endif /* USE_CURSES */
  return;
}

void curses_cls_eol( void ){

#ifdef USE_CURSES
  wmove( curses_twindow, current_ty, 0 );
  wclrtoeol( curses_twindow );
#endif /* USE_CURSES */
  return;
}

void curses_rwindow( void ) {

#ifdef USE_CURSES
  overwrite( curses_gwindow[current_gwindow], w );
  overlay( curses_twindow, w );
  if ( iscursoron )
    wmove( w, current_ty, current_tx );
  else
    wmove( w, 0, 0 );

  wrefresh( w );

#endif /* USE_CURSES */
  return;
}

int curses_keyin( int code ) {

  int ret=0;
#ifdef USE_CURSES
  int key,i;

  key = getch();
  /*
  if ( key != ERR ) {
    char t[256];
    snprintf(t, 256, "%3d", key );
    curses_tlocate(0,31);
    curses_tputs(t);
  }
  */
  switch( key ) {
  case KEY_UP:
    ret=fnc_key[4][0];
    break;

  case KEY_LEFT:
    ret=fnc_key[5][0];
    break;

  case KEY_RIGHT:
    ret=fnc_key[6][0];
    break;

  case KEY_DOWN:
    ret=fnc_key[7][0];
    break;

  case KEY_HOME:
    ret=fnc_key[10][0];
    break;

  case KEY_BACKSPACE:
    ret=0x08;
    break;

  case 127:
  case KEY_DC:
  case KEY_SDC:
    ret=fnc_key[3][0];
    break;

  case KEY_IC:
  case KEY_SIC:
    ret=fnc_key[2][0];
    insert_flag = insert_flag?0:1;
    break;

  case KEY_NPAGE:
    ret=fnc_key[0][0];
    break;

  case KEY_PPAGE:
    ret=fnc_key[1][0];
    break;

  case ERR:
    ret=0;
    break;

  default:
    ret=key;
    break;
  }

  if ((code==0xfe)&&(key!=ERR)) ungetch( key );
  else {
    curses_rwindow();
    last_key=key;
  }
#endif /* USE_CURSES */
  return ret;
}

int curses_keyinp( void ) {

  int ret=0;
#ifdef USE_CURSES
  int key;
  int ascii, code;


  nodelay( stdscr, FALSE );
  key=wgetch(stdscr);
  nodelay( stdscr, TRUE );

  switch( key ) {
  case KEY_UP:
  case 0x10:           /* ctrl-P */
    ascii=0;code=0x3c;break;
  case KEY_LEFT:
  case 0x02:           /* ctrl-F */
    ascii=0;code=0x3b;break;
  case KEY_DOWN:
  case 0x0e:           /* ctrl-N */
    ascii=0;code=0x3e;break;
  case KEY_RIGHT:
  case 0x06:           /* ctrl-B */
    ascii=0;code=0x3d;break;
  case KEY_HOME:
  case 0x01:           /* ctrl-A */
    ascii=0;code=0x36;break;
  case KEY_BACKSPACE:
  case '\b':
  case 0x7f:
    ascii=0;code=0x0f;break;
  case KEY_DC:
  case KEY_EXIT:
  case KEY_CLOSE:
  case KEY_CANCEL:
  case 0x04:             /* ctrl-D */
    ascii=0;code=0x37;break;
  case KEY_IC:
    insert_flag = insert_flag?0:1;
    ascii=0;code=0x5e;break;
  case KEY_NPAGE:
    ascii=0;code=0x38;break;
  case KEY_PPAGE:
    ascii=0;code=0x39;break;
  case KEY_END:                    /* UNDO ? */
    ascii=0;code=0x3a;break;
  case KEY_ENTER:
    ascii=0x0d;code=0x1d;break;
  case 0x1b:                       /* ESC */
    ascii=0x1b;code=0x01;break;
  case 0x0d:                       /* Return */
    ascii=0x0d;code=0x1d;break;
  case KEY_F(1):
    ascii=0;code=0x63;break;
  case KEY_F(2):
    ascii=0;code=0x64;break;
  case KEY_F(3):
    ascii=0;code=0x65;break;
  case KEY_F(4):
    ascii=0;code=0x66;break;
  case KEY_F(5):
    ascii=0;code=0x67;break;
  case KEY_F(6):
    ascii=0;code=0x68;break;
  case KEY_F(7):
    ascii=0;code=0x69;break;
  case KEY_F(8):
    ascii=0;code=0x6a;break;
  case KEY_F(9):
    ascii=0;code=0x6b;break;
  case KEY_F(10):
    ascii=0;code=0x6c;break;

  case KEY_F(11):
    ascii=0;code=0x52;break; /* 'KIGOU' */
  case KEY_F(12):
    ascii=0;code=0x53;break; /* 'TOUROKU' */

  default:
    if ( (key>=0x20)&&(key<0x7f) ) {
      ascii=key;
      code=x68_scancode[key-0x20];
    } else {
      ascii=0;
      code=0;
    }
    break;
  }

  ret = ascii | code<<8;
  curses_rwindow();
  last_key=key;

#endif /* USE_CURSES */
  return ret;
}

int curses_sftsns( void ) {

  int ret=0;

#ifdef USE_CURSES
  if ( (last_key>='A') && (last_key<='Z') ) ret|=1;
  if ( insert_flag==1 ) ret|=4096;
#endif /* USE_CURSES */

  return ret;
}

void curses_key_wait( void ) {

#ifdef USE_CURSES
  int key;

  curses_rwindow();
  nodelay( stdscr, FALSE );
  key=getch();
  ungetch(key);
  nodelay( stdscr, TRUE );
  curses_rwindow();
#endif /* USE_CURSES */
  return;
}

void curses_midi_wait( void ) {

#ifdef USE_CURSES
  int key;
  int a=1;

  curses_rwindow();
  nodelay( stdscr, TRUE );
  while ( a ) {
    if ( (key=getch()) != ERR ) {
      ungetch(key);
      a=0;
    }
    if ( is_midi_in() ) a=0;
  }

  curses_rwindow();
#endif /* USE_CURSES */
  return;
}

void curses_ledmod( int code, int onoff ) {

#ifdef USE_CURSES
  switch( code ) {
  case 4: /* INS */
    insert_flag = (onoff==1) ? 1:0;
    break;
  default:
    break;
  }
#endif /* USE_CURSES && HAS_CURSES */
  return;
}
