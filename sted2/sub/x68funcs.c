/*
  x68funcs.c

  functions for compatibility to X680x0

  Made by Studio Breeze. 1998

 */

#include "sted.h"

/* global variables */

int iswindowopened = 0;
int isxwin         = 0;
int isconsole      = 0;

char euc_text[1024];
int eucenv         = 0;

int issted3        = 0;

/*
  void strmfe( char dest, *char *node , char *extention )

   destination = node.ext
 */

void strmfe( char *dest, const char *node, const char *ext ) {

  char *last,*temp;

  temp = (char *)malloc( sizeof(char) * 1024 );

  if ( ((last=strrchr(node, (int)'.')) != NULL) &&
      (((int)*(last-1)!='.') && ((int)*(last+1)!='/'))) {
    strncpy( temp, node, (size_t)(last-node+1));
    strcat( temp, ext );
  } else {
    strcpy( temp, node );
    strcat( temp, "." );
    strcat( temp, ext );
  }

  strcpy( dest, temp );
  free(temp);
  return;
}

/*
  double val( char *st )

   converts numeric strings to floating pointted number
 */

double val( char *st ) {

/* original "val" function allows following expressions:
    &Hxx
    &Oxx
    &Boo
 */

  return(atof(st));
}

/*
  child ( char *cl )

   execute specified commands in child process
 */

int child( char *cl ) {

  int ret;
  int l;
  char tmp[1024];

  strcpy( tmp, cl );
  l=strlen( tmp );
  for ( ;l>=2;l-- ) {
    if ( tmp[l]==':'  && isalpha(tmp[l-1]) && (tmp[l-2]==' ' || l==0) ) {
      tmp[l--]=' ';
      tmp[l--]=' ';
    }
  }

  ret=system( tmp );
  return ret;
}

/*
 */

void key_wait( void ){

  if ( isconsole ) {
    curses_key_wait();
  } else if ( isxwin ) {
    XSTed_key_wait();
  }

  return;
}

void key_midi_wait( void ){

  if ( isconsole ) {
    curses_midi_wait();
  } else if ( isxwin ) {
    XSTed_midi_wait();
  }
  return;
}

void key_mouse_wait( void ) {

  if ( isconsole ) {
    curses_key_wait();
  } else if ( isxwin ) {
    XSTed_key_wait();
  }
  return;
}

/* system initialize */

void STed_system_initialize( int *argc, char ***argv ) {

  char *p, *buf;
  static char *euc_lang_str[] = { "ujis", "euc", "EUC",
#ifndef _HPUX_SOURCE
				  "japanese",
#endif
				  NULL };
  int i;

  /* init parameters */

  rcd = NULL;
  /* May.06.2001 NAGANO Daisuke <breeze.nagano@nifty.ne.jp> */
  issted3 = 1;

  if ( getenv("DISPLAY")==NULL ) {
#ifdef USE_CURSES
    isconsole = 1;
    isxwin = 0;
#else /* USE_CURSES */
    exit(-1);
#endif /* USE_CURSES */
  } else {
    isconsole = 0;
    isxwin = 1;
  }

  /* get message catalogues */

#ifdef ENABLE_NLS
# ifdef STED_DEFAULT_PATH
  if ( buf!=NULL ) {
    int l;
    if ( (p=getenv("NLSPATH")) == NULL ) {
      l = strlen(STED_DEFAULT_PATH "/nls/%L/%N.cat")+9;
      buf = (char *)malloc(sizeof(char)*l);
      if( snprintf(buf, l, "NLSPATH=%s", STED_DEFAULT_PATH "/nls/%L/%N.cat") > 0 )
	putenv(buf);
    } else {
      if ( strstr(p, STED_DEFAULT_PATH "/nls/%L/%N.cat") == NULL ) {
	l = strlen(p)+strlen(STED_DEFAULT_PATH "/nls/%L/%N.cat")+10;
	buf = (char *)malloc(sizeof(char)*l);
	if ( snprintf(buf, l, "NLSPATH=%s:%s",p, STED_DEFAULT_PATH "/nls/%L/%N.cat") > 0 )
	  putenv(buf);
      }
    }
  }
# endif /* STED_DEFAULT_PATH */

  setlocale(LC_ALL, "");
  bindtextdomain("sted2", STED_LOCALE_DIR);
  textdomain("sted2");

#endif /* HAVE_NLS */

  /* set code conversion */

  if ( (p=getenv("LANG")) != NULL ) {
    for ( i=0; euc_lang_str[i] != NULL  ; i++ ) {
      if ( strstr(p, euc_lang_str[i]) != NULL ) {
	eucenv=1;
        break;
      }
    }
  }

  return;
}
