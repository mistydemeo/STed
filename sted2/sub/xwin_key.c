/*
  xwin_key.c

  xwin: key in functions

  Made by Studio Breeze. 1998

 */

#include "sted.h"
#include "xwin.h"

char KEY_XF1[128];               /* keysym names */
char KEY_XF2[128];
char KEY_XF3[128];
char KEY_XF4[128];
char KEY_XF5[128];
char KEY_KANA[128];
char KEY_KIGO[128];
char KEY_TOROKU[128];
char KEY_INS[128];
char KEY_DEL[128];
char KEY_HOME[128];
char KEY_UNDO[128];
char KEY_RUP[128];
char KEY_RDOWN[128];
char KEY_OPT1[128];
char KEY_OPT2[128];

static KeyCode k_xf1, k_xf2, k_xf3, k_xf4, k_xf5;
static KeyCode k_kana, k_kigo, k_toroku;
static KeyCode k_ins, k_del, k_home, k_undo, k_rup, k_rdown;
static KeyCode k_opt1, k_opt2;

extern int x68_scancode[];
extern int isinputmode;

static Bool shift_flag, ctrl_flag, alt_flag;
static Bool insert_flag=False;
static Bool kana_flag=False;
static Bool opt1_flag=False, opt2_flag=False;
static XEvent last_event;
static char last_code[256];

static unsigned char selection_buffer[1024];
static int sbp=0;
static int sbp_len=0;

static KeySym Get_Key( void );
static int KeySymToAsc( KeySym );
static void check_selection( char *, int *, int * );


static KeyCode querykey( char *str ) {
  KeyCode ret;
  KeySym ks=XK_VoidSymbol;

  while ( *str==' ' || *str==8 ) str++;

  if ( *str != 0 ) {
    ks = XStringToKeysym(str);
    if ( ks==NoSymbol ) {
      fprintf(stderr, "sted: No keysym entry : %s\n", str );
      ks = XK_VoidSymbol;
    }
  }

  ret = XKeysymToKeycode( XSTed_d, ks );

  return ret;
}

int XSTed_key_init( void ) {

  k_xf1 = querykey(KEY_XF1);
  k_xf2 = querykey(KEY_XF2);
  k_xf3 = querykey(KEY_XF3);
  k_xf4 = querykey(KEY_XF4);
  k_xf5 = querykey(KEY_XF5);

  k_kana = querykey(KEY_KANA);
  k_kigo = querykey(KEY_KIGO);
  k_toroku = querykey(KEY_TOROKU);

  k_ins   = querykey(KEY_INS);
  k_del   = querykey(KEY_DEL);
  k_home  = querykey(KEY_HOME);
  k_undo  = querykey(KEY_UNDO);
  k_rup   = querykey(KEY_RUP);
  k_rdown = querykey(KEY_RDOWN);

  k_opt1  = querykey(KEY_OPT1);
  k_opt2  = querykey(KEY_OPT2);

  return;
}


int XSTed_keyin( int code ) {

  KeySym ks;
  KeyCode kc;
  int ret=0;

  if ( isinputmode==0 ) {
    sbp=sbp_len=0;
    selection_buffer[sbp]=0;
  } else {
    check_selection( selection_buffer, &sbp, &sbp_len );
    if ( sbp<sbp_len ) return selection_buffer[sbp++];
  }

  ks=Get_Key();
  kc=XKeysymToKeycode( XSTed_d, ks ); 

  switch (ks) {
  case XK_Up:
    ret=fnc_key[4][0];
    break;
      
  case XK_Left:
    ret=fnc_key[5][0];
    break;
    
  case XK_Right:
    ret=fnc_key[6][0];
    break;
    
  case XK_Down:
    ret=fnc_key[7][0];
    break;
    
  case XK_BackSpace:
    ret=0x08;
    break;
    
  case NoSymbol:
    ret=0;
    break;
    
  default:
    if ( kc == k_home ) {
      ret=fnc_key[10][0];
    } else if ( kc == k_undo ) {
      ret=fnc_key[11][0];
    } else if ( kc == k_del ) {
      ret=fnc_key[3][0];
    } else if ( kc == k_ins ) {
      ret=fnc_key[2][0];
    } else if ( kc == k_rdown ) {
      ret=fnc_key[0][0];
    } else if ( kc == k_rup ) {
      ret=fnc_key[1][0];
    } else {
      ret=KeySymToAsc(ks);
      if ( ret==0 ) ks=NoSymbol;
    }
    break;
  }

  if ((code==0xfe)&&(ks!=NoSymbol)) XPutBackEvent( XSTed_d, &last_event );
  if (code!=0xfe) {XSTed_rwindow();}
  return ret;
}

int XSTed_keyinp( void ) {

  KeySym ks;
  KeyCode kc;
  int ret=0;
  int ascii, code;

  ks = Get_Key();
  kc = XKeysymToKeycode( XSTed_d, ks );

  switch(ks) {
  case XK_Up:
    ascii=0;code=0x3c;break;
  case XK_Left:
    ascii=0;code=0x3b;break;
  case XK_Down:
    ascii=0;code=0x3e;break;
  case XK_Right:
    ascii=0;code=0x3d;break;
  case XK_BackSpace:
    ascii=0;code=0x0f;break;
  case XK_Return:
    ascii=0x0d;code=0x1d;break;
  case XK_Escape:
    ascii=0x1b;code=0x01;break;
  case XK_Tab:
    ascii=0x09;code=0x10;break;

  case XK_Shift_L:
  case XK_Shift_R:
    ascii=0;code=(shift_flag)?0x70:0xf0;break;

  case XK_Control_L:
  case XK_Control_R:
    ascii=0;code=(ctrl_flag)?0x71:0xf1;break;

  case XK_F1:
    ascii=0;code=0x63;break;
  case XK_F2:
    ascii=0;code=0x64;break;
  case XK_F3:
    ascii=0;code=0x65;break;
  case XK_F4:
    ascii=0;code=0x66;break;
  case XK_F5:
    ascii=0;code=0x67;break;
  case XK_F6:
    ascii=0;code=0x68;break;
  case XK_F7:
    ascii=0;code=0x69;break;
  case XK_F8:
    ascii=0;code=0x6a;break;
  case XK_F9:
    ascii=0;code=0x6b;break;
  case XK_F10:
    ascii=0;code=0x6c;break;

  case XK_KP_0:
    ascii='0';code=0x4f;break;
  case XK_KP_1:
    ascii='1';code=0x4b;break;
  case XK_KP_2:
    ascii='2';code=0x4c;break;
  case XK_KP_3:
    ascii='3';code=0x4d;break;
  case XK_KP_4:
    ascii='4';code=0x47;break;
  case XK_KP_5:
    ascii='5';code=0x48;break;
  case XK_KP_6:
    ascii='6';code=0x49;break;
  case XK_KP_7:
    ascii='7';code=0x43;break;
  case XK_KP_8:
    ascii='8';code=0x44;break;
  case XK_KP_9:
    ascii='9';code=0x45;break;
  case XK_KP_Decimal:
    ascii='.';code=0x51;break;
  case XK_KP_Divide:
    ascii='/';code=0x40;break;
  case XK_KP_Multiply:
    ascii='*';code=0x41;break;
  case XK_KP_Subtract:
    ascii='-';code=0x42;break;
  case XK_KP_Add:
    ascii='+';code=0x46;break;
  case XK_KP_Enter:
    ascii=0x0d;code=0x4e;break;

  default:

    if ( kc == k_kigo ) {
      ascii=0;code=0x52;              /* 'KIGOU' */
    } else if ( kc == k_toroku ) {
      ascii=0;code=0x53;              /* 'TOUROKU' */
    } else if ( kc == k_xf1 ) {
      ascii=0;code=0x55;              /* XF1 */
    } else if ( kc == k_xf2 ) {
      ascii=0;code=0x56;              /* XF2 */
    } else if ( kc == k_xf3 ) {
      ascii=0;code=0x57;              /* XF3 */
    } else if ( kc == k_xf4 ) {
      ascii=0;code=0x58;              /* XF4 */
    } else if ( kc == k_xf5 ) {
      ascii=0;code=0x59;              /* XF5 */

    } else if ( kc == k_home ) {
      ascii=0;code=0x36;              /* HOME */
    } else if ( kc == k_del ) {
      ascii=0;code=0x37;              /* DEL */
    } else if ( kc == k_ins ) {
      ascii=0;code=0x5e;              /* INS */
    } else if ( kc == k_rdown ) {
      ascii=0;code=0x38;              /* ROLL DOWN */
    } else if ( kc == k_rup ) {
      ascii=0;code=0x39;              /* ROLL UP */
    } else if ( kc == k_undo ) {
      ascii=0;code=0x3a;              /* UNDO */
    } else if ( kc == k_opt1 ) {
      ascii=0;code=(opt1_flag)?0x72:0xf2; /* OPT1 */
    } else if ( kc == k_opt2 ) {
      ascii=0;code=(opt2_flag)?0x73:0xf3; /* OPT2 */

    } else if ( (ks>=0x20)&&(ks<0x7f) ) {
      ascii=KeySymToAsc(ks);
      code=x68_scancode[ks-0x20];
    } else {
      ascii=0;code=0;
    }
    break;

  }

  ret = ascii | code<<8;
  /*fprintf(stderr,"%0x\r  ",ks);*/
  XSTed_rwindow();
  return ret;
}

int XSTed_sftsns( void ) {

  int ret=0;
  Window r_w,ch_w;
  int rx, ry, wx, wy;
  unsigned int mask_r;

  XQueryPointer( XSTed_d, XSTed_w, &r_w, &ch_w,
		 &rx, &ry, &wx, &wy, &mask_r );

  if ( mask_r&ShiftMask )   ret |= 1;
  if ( mask_r&ControlMask ) ret |= 2;
  if ( opt1_flag )          ret |= 4;
  if ( opt2_flag )          ret |= 8;
  if ( kana_flag )          ret |= 16+256;
  if ( insert_flag )        ret |= 4096;    /* ins */

  return ret;
}

/* I suppose that keysyms XK_0 - XK_9 and XK_A - XK_Z are
   contained in all system.
   If any wrong happen, modify the following ad-hoc codes :-<
   */

int XSTed_bitsns( int group ) {

  int ret=0;
  unsigned char key_buffer[32];
  Bool check_keysym( KeySym, char * );
  Bool check_keycode( KeyCode, char * );

  XQueryKeymap( XSTed_d, key_buffer );

  switch ( group ) {
  case 0:  /* 1 - 6 */
    if (check_keysym (XK_1       , key_buffer)) ret|=4;
    if (check_keysym (XK_2       , key_buffer)) ret|=8;
    if (check_keysym (XK_3       , key_buffer)) ret|=16;
    if (check_keysym (XK_4       , key_buffer)) ret|=32;
    if (check_keysym (XK_5       , key_buffer)) ret|=64;
    if (check_keysym (XK_6       , key_buffer)) ret|=128;
    break;

  case 1:
    if (check_keysym (XK_7          , key_buffer)) ret|=1;
    if (check_keysym (XK_8          , key_buffer)) ret|=2;
    if (check_keysym (XK_9          , key_buffer)) ret|=4;
    if (check_keysym (XK_0          , key_buffer)) ret|=8;
#ifdef XK_minus
    if (check_keysym (XK_minus      , key_buffer)) ret|=16;
#endif
#ifdef XK_asciicircum
    if (check_keysym (XK_asciicircum, key_buffer)) ret|=32;
#endif
#ifdef XK_backslash
    if (check_keysym (XK_backslash  , key_buffer)) ret|=64;
#endif
#ifdef XK_BackSpace
    if (check_keysym (XK_BackSpace  , key_buffer)) ret|=128;
#endif
    break;

  case 2:
#ifdef XK_Tab
    if (check_keysym (XK_Tab        , key_buffer)) ret|=1;
#endif
    if (check_keysym (XK_Q          , key_buffer)) ret|=2;
    if (check_keysym (XK_W          , key_buffer)) ret|=4;
    if (check_keysym (XK_E          , key_buffer)) ret|=8;
    if (check_keysym (XK_R          , key_buffer)) ret|=16;
    if (check_keysym (XK_T          , key_buffer)) ret|=32;
    if (check_keysym (XK_Y          , key_buffer)) ret|=64;
    if (check_keysym (XK_U          , key_buffer)) ret|=128;
    break;

  case 3:
    if (check_keysym (XK_I          , key_buffer)) ret|=1;
    if (check_keysym (XK_O          , key_buffer)) ret|=2;
    if (check_keysym (XK_P          , key_buffer)) ret|=4;
#ifdef XK_at
    if (check_keysym (XK_at         , key_buffer)) ret|=8;
#endif
#ifdef XK_bracketleft
    if (check_keysym (XK_bracketleft, key_buffer)) ret|=16;
#endif
#ifdef XK_Return
    if (check_keysym (XK_Return     , key_buffer)) ret|=32;
#endif
    if (check_keysym (XK_A          , key_buffer)) ret|=64;
    if (check_keysym (XK_S          , key_buffer)) ret|=128;
    break;

  case 4:
    if (check_keysym (XK_D          , key_buffer)) ret|=1;
    if (check_keysym (XK_F          , key_buffer)) ret|=2;
    if (check_keysym (XK_G          , key_buffer)) ret|=4;
    if (check_keysym (XK_H          , key_buffer)) ret|=8;
    if (check_keysym (XK_J          , key_buffer)) ret|=16;
    if (check_keysym (XK_K          , key_buffer)) ret|=32;
    if (check_keysym (XK_L          , key_buffer)) ret|=64;
#ifdef XK_semicolon
    if (check_keysym (XK_semicolon  , key_buffer)) ret|=128;
#endif
    break;

  case 5:
#ifdef XK_colon
    if (check_keysym (XK_colon       , key_buffer)) ret|=1;
#endif
#ifdef XK_bracketright
    if (check_keysym (XK_bracketright, key_buffer)) ret|=2;
#endif
    if (check_keysym (XK_Z           , key_buffer)) ret|=4;
    if (check_keysym (XK_X           , key_buffer)) ret|=8;
    if (check_keysym (XK_C           , key_buffer)) ret|=16;
    if (check_keysym (XK_V           , key_buffer)) ret|=32;
    if (check_keysym (XK_B           , key_buffer)) ret|=64;
    if (check_keysym (XK_N           , key_buffer)) ret|=128;
    break;

  case 6:
    if (check_keysym (XK_M           , key_buffer)) ret|=1;
#ifdef XK_comma
    if (check_keysym (XK_comma       , key_buffer)) ret|=2;
#endif
#ifdef XK_period
    if (check_keysym (XK_period      , key_buffer)) ret|=4;
#endif
#ifdef XK_slash
    if (check_keysym (XK_slash       , key_buffer)) ret|=8;
#endif
#ifdef XK_backslash
    if (check_keysym (XK_backslash   , key_buffer)) ret|=16;
#endif
#ifdef XK_Space
    if (check_keysym (XK_Space       , key_buffer)) ret|=32;
#endif
    break;

  case 7: /* R_UP,R_DOWN, Cursors */
    if (check_keycode(k_rup      , key_buffer)) ret|=1;
    if (check_keycode(k_rdown    , key_buffer)) ret|=2;
    if (check_keycode(k_undo     , key_buffer)) ret|=4;
    if (check_keysym (XK_Left    , key_buffer)) ret|=8;
    if (check_keysym (XK_Up      , key_buffer)) ret|=16;
    if (check_keysym (XK_Right   , key_buffer)) ret|=32;
    if (check_keysym (XK_Down    , key_buffer)) ret|=64;
    break;

  case 0x0a: /* XF1-XF3 */
    if (check_keycode(k_xf1      , key_buffer)) ret|=32;
    if (check_keycode(k_xf2      , key_buffer)) ret|=64;
    if (check_keycode(k_xf3      , key_buffer)) ret|=128;
    break;

  case 0x0b: /* XF4-XF5 */
    if (check_keycode(k_xf4      , key_buffer)) ret|=1;
    if (check_keycode(k_xf5      , key_buffer)) ret|=2;
    break;

  case 0x0c: /* F0-F4 */
    if (check_keysym(XK_F1, key_buffer)) ret|=8;
    if (check_keysym(XK_F2, key_buffer)) ret|=16;
    if (check_keysym(XK_F3, key_buffer)) ret|=32;
    if (check_keysym(XK_F4, key_buffer)) ret|=64;
    if (check_keysym(XK_F5, key_buffer)) ret|=128;
    break;

  case 0x0d: /* F5-F9 */
    if (check_keysym(XK_F6 , key_buffer)) ret|=1;
    if (check_keysym(XK_F7 , key_buffer)) ret|=2;
    if (check_keysym(XK_F8 , key_buffer)) ret|=4;
    if (check_keysym(XK_F9 , key_buffer)) ret|=8;
    if (check_keysym(XK_F10, key_buffer)) ret|=16;
    break;

  case 0x0e: /* OPT.1-OPT.2 */
    if (check_keycode(k_opt1     , key_buffer)) ret|=4;
    if (check_keycode(k_opt2     , key_buffer)) ret|=8;
    break;

  default:
    break;
  }

  return ret;
}

Bool check_keysym( KeySym ks, char *table ) {

  int kc = (int)XKeysymToKeycode( XSTed_d, ks );
  if ( kc == 0 ) return False;
  return ((table[kc/8]>>(kc%8))&1!=0)?True:False;
}

Bool check_keycode( KeyCode kc, char *table ) {

  if ( kc==0 ) return False;
  return ((table[kc/8]>>(kc%8))&1!=0)?True:False;
}

void XSTed_key_wait( void ) {

  XEvent e;
  Bool a=True;

  if ( isinputmode !=0 &&  sbp<sbp_len ) return;

  XSTed_rwindow();
  while ( a ) {
    XPeekEvent( XSTed_d, &e );

    switch ( e.type ) {
      
    case Expose:
      XNextEvent( XSTed_d, &e );
      XSTed_rwindow();
      break;
      
    case KeyRelease:
    case KeyPress:
      a=False;
      break;
      
    case ButtonPress:
    case SelectionNotify:
      if (isinputmode!=0) a=False;
      else XNextEvent( XSTed_d, &e );
      break;

    default:
      XNextEvent( XSTed_d, &e );
      break;
    }
  }

  return;
}

void XSTed_midi_wait( void ) {

  XEvent e;
  Bool a=True;

  XSTed_rwindow();
  while ( a ) {
    usleep(1000);

    XCheckMaskEvent( XSTed_d, Expose|KeyRelease|KeyPress, &e );
    switch ( e.type ) {
    case KeyRelease:
    case KeyPress:
      XPutBackEvent( XSTed_d, &e );
      a=False;
      break;

    default:
      break;
    }

    if ( is_midi_in() ) a=False;
  }

  return;
}

void XSTed_ledmod( int code, int onoff ) {

  switch( code ) {
  case 4: /* INS */
    insert_flag = (onoff==1) ? True:False;
    break;
  case 0: /* KANA */
    kana_flag = (onoff==1) ? True:False;
  default:
    break;
  }

}

int XSTed_keysns( void ) {

  XEvent e;
  KeySym ks;
  int ret=0;

  if ( !XCheckMaskEvent(XSTed_d, KeyPressMask| KeyReleaseMask, &e) )
    return ret;

  XPutBackEvent( XSTed_d, &e );
  switch ( e.type ) {
    
  case KeyRelease:
    ks = XKeycodeToKeysym( XSTed_d, e.xkey.keycode, 0 );
    switch ( ks ) {
    case XK_Shift_L:
    case XK_Shift_R:
    case XK_Control_L:
    case XK_Control_R:
      ret=1;
      break;
    default:
      if ( e.xkey.keycode == k_opt1  ||
	   e.xkey.keycode == k_opt2 ) ret=1;
      else
	XCheckMaskEvent( XSTed_d, KeyReleaseMask, &e );
      break;
    }
    break;
  default:
    ret=1;
    break;
  }

  return ret;
}

KeySym Get_Key( void ) {

  XEvent e,eo;
  KeySym ret=NoSymbol;
  KeyCode kc;
  Bool i=True;
  int j;

  eo=last_event;
  while ( XCheckMaskEvent( XSTed_d, ButtonPressMask|KeyPressMask|KeyReleaseMask, &e ) && i ) {
    
    switch ( e.type ) {
    case ButtonPress:
      if ( e.xbutton.button == Button2 ) {
	if ( isinputmode!=0 ) {
	  XConvertSelection( XSTed_d, XA_PRIMARY, XSTed_atom,
			     XSTed_prop, XSTed_w, e.xbutton.time );
	  i=False;
	}
      }
      last_event=eo;
      break;

    case  KeyRelease:
      ret = XKeycodeToKeysym( XSTed_d, e.xkey.keycode, 0 );
      last_event=e;
      i=False;
      switch ( ret ) {
      case XK_Shift_L:
      case XK_Shift_R:
	shift_flag=False;break;
      case XK_Control_L:
      case XK_Control_R:
	ctrl_flag=False;break;
      default:
	if (e.xkey.keycode == k_opt1 ) {
	  opt1_flag=False;
	} else if (e.xkey.keycode == k_opt2 ) {
	  opt2_flag=False;
	} else {
	  i=True;
	  last_event=eo;
	  ret=NoSymbol;
	}
	break;
      }
      break;

    case  KeyPress:
      j=XLookupString( &(e.xkey), last_code, sizeof(last_code), &ret, NULL );
      if ( j==0 ) last_code[0]=0;
      i=False;
      last_event=e;
      switch ( ret ) {

      case XK_Shift_L:
      case XK_Shift_R:
	shift_flag=True;break;

      case XK_Control_L:
      case XK_Control_R:
	ctrl_flag=True;break;

      default:
	kc = XKeysymToKeycode( XSTed_d, ret );
	if ( kc == k_kana ) {
	  kana_flag = kana_flag ? False : True;
	} else if ( kc == k_opt1 ) {
	  opt1_flag = True;
	} else if ( kc == k_opt1 ) {
	  opt2_flag = True;
	} else if ( kc == k_ins ) {
	  insert_flag = insert_flag ? False : True;
	}
	break;
      }
      break;

    default:
      break;
    }
  }

  return ret;
}

int KeySymToAsc( KeySym ks ) {

  int ret=0;

  if ( ks<=0x7e ) {
    ret = last_code[0] & 0x7f;
  } else if ( IsKeypadKey(ks) ) {
    ret = last_code[0] & 0x7f;
  } else {
    switch (ks) {
    case XK_Escape:
      ret=0x1b;
      break;
    case XK_Tab:
      ret=0x09;
      break;
    case XK_Return:
      ret=0x0d;
      break;
    default:
      ret=0;
      break;
    }
  }
 
  return ret;
}

void check_selection( char *buf, int *ptr, int *len ) {

  XEvent e;
  XTextProperty ct;
  Atom type;
  char **cl;
  unsigned char *buff;
  int fmt,count_return;
  unsigned long nitems, left;

  if ( !XCheckTypedEvent( XSTed_d, SelectionNotify, &e ) ) return;

  if ( e.xselection.selection == XA_PRIMARY
       && e.xselection.property == XSTed_prop ) {
    if ( XGetWindowProperty( XSTed_d, XSTed_w, XSTed_prop, 0, 1024,
			     False, XSTed_atom,
			     &type, &fmt, &nitems, &left, &buff ) == Success
	 && type == XSTed_atom
	 && nitems>0 ) {

      ct.value=buff;
      ct.encoding=XSTed_atom;
      ct.format=fmt;
      ct.nitems=nitems;
      XmbTextPropertyToTextList( XSTed_d, &ct, &cl, &count_return );

      *len=strlen(cl[0]);
      *ptr=0;
      if ( eucenv ) {
	nkf_conv( cl[0], buf, "SJIS" );
      } else {
	strcpy( buf, cl[0] );
      }
      XFree(buff);
      XFree(cl);
    }
  }

  return;
}
