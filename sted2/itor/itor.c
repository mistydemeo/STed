/*************************************/
/* STD MIDI file converter / player  */
/*************************************/

/*
  This code is brought from Takayuki Toda's 'rc_converters'.

  Modified 2000 by Daisuke Nagano <breeze.nagano@nifty.ne.jp>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rcpfile.h"
#include "rcpdef.h"
#include "rcddef.h"

#if STDC_HEADERS
# include <string.h>
#else
# ifndef HAVE_MEMCPY
#  define memcpy(d, s, n) bcopy ((s), (d), (n))
#  define memmove(d, s, n) bcopy ((s), (d), (n))
# endif
#endif

#define TRACK_LEN 65536

static struct head {
  char chunk[4];
  long length;
  short format;
  short ntrks;
  short division;
} std_head;

static struct track {
  char chunk[4];
  long length;
} std_trk;

static int opt, comment;
static int sameflag;

static unsigned char *rcpptr, *lastptr;
static unsigned char *inptr, *buf;
static unsigned char *note, *note_data;
static int incount;
static int tc;
static int fmt;
static int pt;
static int midi_ch;
static int tb_mode,tb_max, ratio,rcp_base;
static int step, stepx;
static int barlen, barunit, stepsum;
static int fixflag;
static char std_name[256];

static const char memoinit[] = "                                    ";
static const char ttlinit[] = "                                                                ";
static int memoflag;
static int beatflag;
static int tempoflag;
static int chfixflag,chbport;

static int tempofix;
static int exc_no,exc_id,barno,devno_fix,notoff,chport;

static int trk;
static int len;
static int cmd;
static int d_byte;

static int nbuf[16], vbuf[16], gbuf[16], cbuf[16];

const static int beat[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
static int	barlenb[2048];

static char	rc_path[256];
static char	exc_buf[32*1024+4];

static int tai_compres(int);
static int same_compres(int);
static int add_set(int, int *);
static int meas_len(int, int);

static unsigned char * strncpy0( unsigned char *dst, unsigned char *src, int n )
{
  int i;

  for( i = 0; i < n; i++ ) {
    dst[i] = src[i];
  }
  dst[n] = 0;
  return( dst );
}

static int alloc_mem( void )
{
  void *work;

  if( ( work = (void *)malloc( TRACK_LEN * 8 ) ) < 0 ) {
    fprintf( stderr, "Memory exhausted\n" );
    return 1;
  }

  note_data = ( unsigned char * )work;
  buf = ( unsigned char * )( work + TRACK_LEN * 4 );

  return 0;
}

static void destroy_mem( void )
{
  if ( note_data != NULL )
    free(note_data);

  return;
}

static void get_data( unsigned char *s, int bc )
{
  memmove( ( char * )s, ( char *)( inptr + incount ), bc );
  incount += bc;

  return;
}

static void put_data( unsigned char *s, int bc )
{
  if( lastptr <= rcpptr + bc ) {
    fprintf( stderr, "Buffer exhausted\n" );
    return;
  }
  memmove( ( char * )rcpptr, ( char * )s, bc );
  rcpptr += bc;

  return;
}

static void strpaste( unsigned char *dst, unsigned char *src )
{
  while( *src ) {
    *dst++ = *src++;
  }
}

static void strnpaste( unsigned char *dst, unsigned char *src, int n )
{
  while( n-- ) {
    *dst++ = *src++;
  }
}

static void ctrlcut( char *s )
{
  while(*s) {
    if( *s == 13 ) { *s = 32; }
    if( *s == 27 ) { *s = 32; }
    s++;
  }
}

/**/

static int get_delta( int p )
{
  register int val, i, d;
  
  val = 0;
  d_byte = 0;
  
  for( i = 0; i < 4; i++ ) {
    d = buf[p++];
    d_byte++;
    val = ( val << 7 ) + ( d & 0x7f );
    if( d < 0x80 ) {
      return( val );
    }
  }
  
  fprintf( stderr, "Invalid delta time.\n" );
  return(0); /**//*warning*//**/
}
/**/

static void proc_beat( int high, int low )
{
  /*
    if( beatflag ) {
    return;
    }
    */
  if( !beatflag ) {
    RCP_HEAD.Beathigh = high;
    RCP_HEAD.Beatlow = low;
  }

  barlen = (RCP_HEAD.Timebase+RCP_HEAD.Timebaseh*256) * 4 * high / low;
  if(trk==0 && barno<2048){barlenb[barno]=barlen;}
}

static int proc_header( void )
{
  int	i;
  unsigned char b[14];
  
  get_data( b, 14 );
  
  if( strncmp( b, "MThd", 4 ) ) {
    unsigned char tmp[128];
    get_data( tmp, 128-14 ); /* Mac binary */
    
    get_data( b, 14 );
    
    if( strncmp( b, "MThd", 4 ) ) {
      /*fprintf( stderr, "This file is not SMF file (MThd).\n" );*/
      return 1;
    }
  }
  
  std_head.length = b[4]*256*256*256 + b[5]*65536 + b[6]*256 + b[7];
  std_head.format = b[8]*256 + b[9];
  std_head.ntrks  = b[10]*256 + b[11];
  std_head.division = b[12]*256 + b[13];

  if( !comment ) {
    printf( "format =%3d    ntrk =%3d    division =%4d\n",
	    std_head.format, std_head.ntrks, std_head.division );
  }
  
  if( ( fmt = std_head.format ) != 0 && fmt != 1 ) {
    fprintf( stderr, "Cannot treat format %d.\n", fmt );
    return 1;
  }
  
  if(std_head.ntrks>18){
    RCP_HEAD.trkmax = 36;
  }else{
    RCP_HEAD.trkmax = 18;
  }
  
  /*
  strpaste( RCP_HEAD.memo +  28, ( unsigned char * )"  このデータは、" );
  strpaste( RCP_HEAD.memo +  84, ( unsigned char * )"  標準MIDIフォーマットから" );
  strpaste( RCP_HEAD.memo + 140, ( unsigned char * )"  ItoR.x (v1.00)により" );
  strpaste( RCP_HEAD.memo + 151, ( unsigned char * )version );
  strpaste( RCP_HEAD.memo + 196, ( unsigned char * )"  変換されました。" );
  strpaste( RCP_HEAD.memo + 252, ( unsigned char * )"  Copyright 1990-97" );
  strpaste( RCP_HEAD.memo + 280, ( unsigned char * )"           HARPOON,TURBO" );
  */
  
  if( !tb_mode || std_head.division > tb_max ) {
    rcp_base=48;if( tb_mode ) {rcp_base=tb_max;}
    
    RCP_HEAD.Timebase = rcp_base;
    RCP_HEAD.Timebaseh = rcp_base>>8;
    tb_mode = 0;
    ratio = std_head.division;
    
    if( !comment ) {
      if( std_head.division > tb_max ) {
	printf( "タイムベースを%dに変更します。\n\n",tb_max );
      }
    }
    
  } else {
    RCP_HEAD.Timebase = std_head.division;
    RCP_HEAD.Timebaseh = std_head.division>>8;
    
    if( !comment ) {
      printf( "タイムベースを変更しません。\n\n" );
    }
    
  }
  
  RCP_HEAD.Tempo = 120;
  beatflag = 0;
  proc_beat( 4, 4 );
  RCP_HEAD.Key = 0;
  RCP_HEAD.Playbias = 0;
  
  tempoflag = 0;
  
  tc = 0x0586;
  
  for(i=0;i<2048;i++){barlenb[i]=0;}
  
  return 0;
}

static void entry( int d0, int d1, int d2, int d3 )
{

  /*if(len && d0==0xe6 && note[len-4]==0xe6){len-=4;d1=note[len+1];}*//**/

  note[ len++ ] = d0;
  note[ len++ ] = d1;
  note[ len++ ] = d2;
  note[ len++ ] = d3;
  
  if( len >= 65492+65536*3 ) {
    fprintf( stderr, "Track buffer overflow\n" );
    len-=4;
    return;
  }

  return;
}

static void flash( int dt )
{
  int dx, i, j;
  
  while( dt > 0 ) {
    
    if( dt <= 0xf0 ) {
      dx = dt;
    } else {
      dx = 0xf0;
    }
    
    if( dx + barunit > barlen ) {
      dx = barlen - barunit;
    }
    
    for( i = 0; i < 16; i++ ) {
      if( gbuf[i] ) {
	
	if(fmt!=0 && !chfixflag && midi_ch!=cbuf[i]){
	  if( midi_ch == -1 ) {
	    TRACK.MIDI_CH = cbuf[i];
	  }else{
	    entry( 0xe6, 0x00, cbuf[i]+1, 0x00 );
	  }
	  midi_ch=cbuf[i];
	}
	
	/*if( gbuf[i] <= dx ) {*/
	if( gbuf[i] <= 0xf0 ) {/**/
	  entry( nbuf[i], 0, gbuf[i], vbuf[i] );
	  for( j = i; j < 15; j++ ) {
	    nbuf[j] = nbuf[j+1];
	    vbuf[j] = vbuf[j+1];
	    gbuf[j] = gbuf[j+1];
	    cbuf[j] = cbuf[j+1];
	  }
	  nbuf[15] = vbuf[15] = gbuf[15] = cbuf[15] = 0;
	  i--;
	} else {
	  entry( nbuf[i], 0, dx + 1, vbuf[i] );
	  gbuf[i] -= dx;
	}
      } else {
	break;
      }
    }
    
    if( note[ len - 4 ] !=0xde &&
	note[ len - 4 ] < 0xf0 && ( note[ len - 3 ] + dx ) <= 0xf0 ) {
      note[ len - 3 ] += dx ;
    } else {
      if(note[len-4]==0xf7){
	int ll=len-4;
	while(note[ll]==0xf7){ll-=4;}
	if(note[ll]==0x98 && ( note[ ll + 1 ] + dx ) <= 0xf0 ) {
	  note[ ll + 1 ] += dx ;
	} else {
	  entry( 0x00, dx, 0, 0 );
	}
      }else{
	entry( 0x00, dx, 0, 0 );
      }
    }
    
    dt -= dx;
    
    if( ( barunit += dx ) == barlen ) {
      entry( 0xfd, 0x00, 0x00, 0x00 );
      barunit = 0;
      if(barlenb[barno]>0 && trk>0){barlen=barlenb[barno];}
      barno++;
    }
    
  }
  
  stepsum = 0;
}

static void proc_dummy( int dt )
  {
    if( !tb_mode ) {
      step += dt;
      dt = ( step * rcp_base / ratio ) - stepx;
      stepx += dt;
    }

    if( fmt == 0 ) {
      stepsum += dt;
    } else {
      flash( dt );
    }
  }

static void check( int data )
  {
    cmd = data & 0xf0;

    /*	if(cmd==0x80){return;}*/

    if( !fixflag ) {
      data &= 0x0f;data+=chport;
      if( midi_ch != data ) {
	if( fmt == 1 ) {
	  flash(stepsum);/**/
	  if( midi_ch == -1 ) {
	    TRACK.MIDI_CH = data;
	  }else{
	    if(!chfixflag){
	      entry( 0xe6, 0x00, data+1, 0x00 );
	    }
	  }
	}
	midi_ch = data;
      }
    }
  }

static int search( int pp )
  {
    /*	int n, dt, cc, ch, ccmd, last, i,ocmd;*/
    int dt, last, i;
    short n,cc, ch, ccmd,ocmd;

    n = buf[pp];
    ccmd = cmd;
    ocmd = cmd;
    last = std_trk.length;
    pp += 2;
    dt = 0;
    ch = midi_ch&15;/**/

    while( pp < last ) {
      if(notoff!=0 && dt>255){return( 1 );}

      dt += get_delta( pp );
      pp += d_byte;
      if( ( cc = buf[pp] ) < 0x80 ) {
	if( ccmd == 0x80 && cc == n && ( fixflag || ch+chport == midi_ch ) ) {
	  return( dt );
	} else {
	  if( ccmd == 0x90 && cc == n &&
	      buf[pp+1] == 0x00 && ( fixflag || ch+chport == midi_ch ) ) {
	    return( dt );
	  } else {
	    pp += 2;
	    if(ccmd>=0xc0 && ccmd<=0xdf){pp--;}
	  }
	}
      } else {
	ocmd=cc;
	switch( cc & 0xf0 ) {
	case 0x80 :
	  if( buf[pp+1] == n &&
	      ( fixflag || cc == ( 0x80 + (midi_ch&15) ) ) ) {
	    return( dt );
	  }
	  pp += 3;
	  ch = cc & 0x0f;
	  break;
	case 0x90 :
	  if( buf[pp+1] == n && buf[pp+2] == 0x00 &&
	      ( fixflag || cc == ( 0x90 + (midi_ch&15) ) ) ) { 
	    return( dt );
	  }
	  pp += 3;
	  ch = cc & 0x0f;
	  break;
	case 0xa0 :
	case 0xb0 :
	case 0xe0 :
	  pp += 3;
	  ch = cc & 0x0f;
	  break;
	case 0xc0 :
	case 0xd0 :
	  pp += 2;
	  ch = cc & 0x0f;
	  break;
	case 0xf0 :
	  switch( cc ) {
	  case 0xf0 :
	  case 0xf7 :
	    pp += 1;
	    i = get_delta( pp );
	    pp += d_byte;
	    pp += i;
	    break;
	  case 0xff :
	    pp += 2;
	    i = get_delta( pp );
	    pp += d_byte;
	    pp += i;
	    break;
	  default :
	    fprintf( stderr, "Invalid format\n" );
	    /*exit(18);*/
	    return 1;
	    break;
	  }
	  break;
	}
	ccmd = cc & 0xf0;
      }
    }
    notoff=1;
    return( 1 );
  }

static void ent_buf( int nt, int vl, int gt )
  {
    int i;

    /*
      if( !comment ) {
      printf( "<nt=%d vl=%d gt=%d>\n", nt, vl, gt );
      }
      */

    if( gt <= 0xf0 ) {
      entry( nt, 0, gt,vl );return;
    } else {
      entry( nt, 0, 255,vl );
    }

    for( i = 0; i < 16; i++ ) {
      if( !gbuf[i] || (nbuf[i] == nt && cbuf[i] == midi_ch) ) {
	nbuf[i] = nt;
	vbuf[i] = vl;
	gbuf[i] = gt;
	cbuf[i] = midi_ch;
	return;
      }
    }

    for( i = 0; i < 15; i++ ) {
      nbuf[i] = nbuf[i+1];
      vbuf[i] = vbuf[i+1];
      gbuf[i] = gbuf[i+1];
      cbuf[i] = cbuf[i+1];
    }

    nbuf[15] = nt;
    vbuf[15] = vl;
    gbuf[15] = gt;
    cbuf[15] = midi_ch;

    /*
      fprintf( stderr, "ノートオーバフロー\n" );	exit(18);
      */
  }

static void note_off( int p )
  {
    /* do nothing */
  }

static void note_on( int p )
  {
    int gt;

    if( fmt == 0  ) {
      if( midi_ch != TRACK.MIDI_CH  ) {
	return;
      }
      flash( stepsum );
    }

    if( buf[p+1] ) {
      if( !( gt = search( p ) ) ) {
	return;
      }
      if( !tb_mode ) {
	if( !( gt = gt * rcp_base / ratio ) ) {
	  /*			if( !( gt = (gt * rcp_base+(ratio>>1)) / ratio ) ) {*/
	  gt = 1;
	}
      }
      ent_buf( buf[p], buf[p+1], gt );
    }
  }

static void aft_key( int p )
  {
    if( fmt == 0  ) {
      if( midi_ch != TRACK.MIDI_CH  ) {
	return;
      }
      flash( stepsum );
    }

    entry( 0xed, 0x00, buf[p], buf[p+1] );
  }

static void ctl_chg( int p )
  {
    if( fmt == 0  ) {
      if( midi_ch != TRACK.MIDI_CH  ) {
	return;
      }
      flash( stepsum );
    }

    entry( 0xeb, 0x00, buf[p], buf[p+1] );
  }

static void prg_chg( int p )
  {
    if( fmt == 0  ) {
      if( midi_ch != TRACK.MIDI_CH  ) {
	return;
      }
      flash( stepsum );
    }

    entry( 0xec, 0x00, buf[p], 0x00 );
  }

static void aft_tch( int p )
  {
    if( fmt == 0  ) {
      if( midi_ch != TRACK.MIDI_CH  ) {
	return;
      }
      flash( stepsum );
    }

    entry( 0xea, 0x00, buf[p], 0x00 );
  }

static void pt_bend( int p )
  {
    if( fmt == 0  ) {
      if( midi_ch != TRACK.MIDI_CH  ) {
	return;
      }
      flash( stepsum );
    }

    entry( 0xee, 0x00, buf[p], buf[p+1] );
  }

static void run_sts( int p )
  {
    if( fmt == 0  ) {
      if( midi_ch != TRACK.MIDI_CH  ) {
	return;
      }
      flash( stepsum );
    }

    switch( cmd ) {
    case 0x80 : note_off(p); break;
    case 0x90 : note_on(p);  break;
    case 0xa0 : aft_key(p);  break;
    case 0xb0 : ctl_chg(p);  break;
    case 0xc0 : prg_chg(p);  break;
    case 0xd0 : aft_tch(p);  break;
    case 0xe0 : pt_bend(p);  break;
    }
  }

static int num_check( int num, int limit )
  {
    if( num > limit ) {
      return( limit );
    } else {
      return( num );
    }
  }

static void clr_ttl( void )
  {
    strpaste( ( unsigned char * )RCP_HEAD.title, ( unsigned char * )ttlinit );
  }

static void proc_meta( int meta, unsigned char *text, int length )
  {
    int i;
    unsigned char work[128];

    if( fmt == 0 /*&& trk*/ ) {
      flash( stepsum );
    }

    switch( meta ) {
    case 0x03:
      if( !memoflag ) {
	ctrlcut(text);
	memoflag = 1;
	if(trk){
	  if((127<text[35] && 161>text[35]) || 224<text[35]){
	    text[35]=0;}
	  strnpaste( TRACK.Memo, text, num_check( length, 36 ) );
	  if(strncmp(text,"PartA",5)==0){chport=0;}
	  if(strncmp(text,"PartB",5)==0){chport=16;}
	}
	if( trk == 0 ) {
	  clr_ttl();
	  if((127<text[63] && 161>text[63]) || 224<text[63]){
	    text[63]=0;}
	  strnpaste( RCP_HEAD.title, text, num_check( length, 64 ) );
	}
      }
      break;
    case 0x01:
      /*if( !step ) {*/
      if( step<barlen ) {
	if( !memoflag ) {
	  ctrlcut(text);
	  memoflag = 1;
	  if(trk){
	    if((127<text[35] && 161>text[35]) || 224<text[35]){
	      text[35]=0;}
	    strnpaste( TRACK.Memo, text, num_check( length, 36 ) );
	    if(strncmp(text,"PartA",5)==0){chport=0;}
	    if(strncmp(text,"PartB",5)==0){chport=16;}
	  }
	  if( trk == 0 ) {
	    clr_ttl();
	    if((127<text[63] && 161>text[63]) || 224<text[63]){
	      text[63]=0;}
	    strnpaste( RCP_HEAD.title, text, num_check( length, 64 ) );
	  }
	  if(!step){break;}
	}
      }	/* no break */
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07:
    case 0x02:/*turbo*/
      ctrlcut(text);
    next:
      strcpy( ( char * )work, ( char * )memoinit );
      strnpaste( work, text, num_check( length, 64 ) );
      if(length<20){length=20;}
      entry( 0xf6, 0x00, work[0], work[1] );
      for( i = 2; i < 20; i += 2 ) {
	entry( 0xf7, 0x00, work[i], work[i+1] );
      }
      if(length>20){strcpy(text,&text[20]);length-=20;goto next;}

      /*		for( i = 2; i < length; i += 2 ) {
			entry( 0xf7, 0x00, work[i], work[i+1] );
			}
			*/
      break;
    case 0x20:
      midi_ch = 0;
      /*fixflag = 1;*/
      if(!chfixflag || fmt==0){entry( 0xe6, 0x00, (text[0]+1)+chport, 0x00 );}
      break;
    case 0x51:
      if( !tempoflag && trk == 0 && tempofix==0) {
	i = 60000000 / ( ( text[0] << 16 ) + ( text[1] << 8 ) + text[2] );
	/*
	  if( i > 255 ) {
	  i = 255;
	  } else */{
	  if( i == 0 ) {
	    i = 1;
	  }
	}

	  RCP_HEAD.Tempo = i;
	  tempoflag = 1;

	  if( i > 255 ) {
	    RCP_HEAD.Tempo = 255;goto skip;}

      } else {
      skip:
	if( !tempoflag && trk == 0 ) {
	  i = 60000000 / ( ( text[0] << 16 ) + ( text[1] << 8 ) + text[2] );
	  RCP_HEAD.Tempo = i>>1;
	  tempoflag = 1;
	}

	i = 60000000 / ( ( text[0] << 16 ) + ( text[1] << 8 ) + text[2] );
	i = 64 * i / RCP_HEAD.Tempo;
	/*設定したいテンポ÷初期設定テンポ×64*/
	if( i > 255 ) {
	  i = 255;
	} else {
	  if( i == 0 ) {
	    i = 1;
	  }
	}
	entry( 0xe7, 0x00, i, 0x00 );
	tempoflag = 1;
      }
      break;
    case 0x58:
      proc_beat( text[0], beat[ text[1] ] );
      beatflag = 1;
      break;
    case 0x21:
      if((text[0])==1){chport=16;}else{chport=0;}
      /*entry( 0xe6, 0x00, (midi_ch+1)+chport, 0x00 );*/
      break;
    case 0x00:
      /*	case 0x02:*/
    case 0x2f:
    case 0x54:
    case 0x59:
    case 0x7f:
      break;
    default :
      if( !comment ) {
	printf( "FF %02X (Unknown meta event)\n", meta );
      }
      break;
    }
  }

static void proc_excl( unsigned char *text, int length ,int code)
  {
    int h, m, l;
    int hh, mm, ll;
    int i;

    if( fmt == 0 /*&& trk*/ ) {
      flash( stepsum );
    }

    text[ length ] = 0xf7 ;

    if( devno_fix !=0 && text[0] == 0x41 && text[3] == 0x12){
      text[1]=0x10;}

    if( length < 9 || length > 15 ||
	text[0] != 0x41 || text[3] != 0x12 ||
	text[ length-1 ] != 0xf7 ) {

      if( text[0] == 0x41 && text[3] == 0x12 && length<9 ){return;}

      if(code==0xf0){
      nor:
	i=0;
	entry( 0x98, 0, 0, 0 );
	while(i<length){
	  entry( 0xf7, 0, text[i], text[i+1] );
	  if( text[i] == 0xf7 || text[ i+1 ] == 0xf7 ) {break;}
	  i=i+2;
	}
      }else{
	if(len==0 || note[len-4]!=0xf7){goto nor;}
	i=0;

	if(note[len-2]==0xf7){note[len-2]=text[i++];}
	if(note[len-1]==0xf7){note[len-1]=text[i++];}

	while(i<length){
	  entry( 0xf7, 0, text[i], text[i+1] );
	  if( text[i] == 0xf7 || text[ i+1 ] == 0xf7 ) {break;}
	  i=i+2;
	}
      }

      /*fprintf( stderr, "不正EXCLUSIVEメッセージ \n" );
	exit(18);*/

      return;
    }

    if( exc_no != text[1] || exc_id != text[2] ) {
      exc_no = text[1];exc_id = text[2];
      entry( 0xdf, 0, exc_no, exc_id );
    }

    h = text[4]; m = text[5]; l = text[6];
    hh = mm = ll = -1;

    for( i = 7; i < length - 2; i++ ) {
      if( hh != h || mm != m  ) {
	entry( 0xdd, 0x00, h, m );
	hh = h; mm = m; ll = l;
      }
      entry( 0xde, 0x00, l, text[i] );
      if( l++ == 0x7f ) {
	l = 0;
	m++;
      }
    }
  }

static int proc_next( void )
  {
    int meta, code, length,last;
    unsigned char text[4096];

    last = std_trk.length;
    cmd = 0x00;
    step = stepx = 0;

    while(pt<last) {

      proc_dummy( get_delta(pt) );
      pt += d_byte;

      if( ( code = buf[pt] ) == 0xff ) {
	pt++;
	meta = buf[pt++];
	length = get_delta(pt);
	pt += d_byte;
	strncpy0( text, buf + pt, length );
	if( fmt == 1 || trk == 0 ) {
	  proc_meta( meta, text, length );
	}
	pt += length;
	if( meta == 0x2f ) {
	  return 0;
	}
      } else {
	switch( code & 0xf0 ) {
	case 0x80: /*check( buf[pt] ); note_off(pt+1);*/
	  cmd = buf[pt] & 0xf0;
	  pt += 3; break;
	case 0x90: check( buf[pt] ); note_on(pt+1);  pt += 3; break;
	case 0xa0: check( buf[pt] ); aft_key(pt+1);  pt += 3; break;
	case 0xb0: check( buf[pt] ); ctl_chg(pt+1);  pt += 3; break;
	case 0xc0: check( buf[pt] ); prg_chg(pt+1);  pt += 2; break;
	case 0xd0: check( buf[pt] ); aft_tch(pt+1);  pt += 2; break;
	case 0xe0: check( buf[pt] ); pt_bend(pt+1);  pt += 3; break;
	case 0xf0:
	  if( code != 0xf0 && code != 0xf7 ) {
	    fprintf( stderr, "Invalid MIDI message (%02X)\n", code );
	    return 1;
	  }
	  pt++;
	  length = get_delta(pt);
	  pt += d_byte;
	  if( fmt == 1 || trk == 0 ) {
	    if(length<32*1024){
	      strncpy0( exc_buf, buf + pt, length );
	      proc_excl( exc_buf, length ,code);
	    }
	  }
	  pt += length;
	  break;
	default :  run_sts(pt); pt += 2;
	  if(cmd>=0xc0 && cmd<=0xdf){pt--;}
	  break;
	}
      }
    }
  }

static void track_end( void )
{
  if( fmt == 0 ) {
    flash( stepsum );
  }
  
  if(trk){
    while(len>0) {
      if( ( note[ len - 4 ] == 0x00 && note[ len - 2 ] == 0x00 ) ||
	  note[ len - 4 ] == 0xfd ) {
	len -= 4;
      } else {
	break;
      }
    }
  }
  
  entry( 0xfe, 0, 0, 0 );
  len=tai_compres(len);
  if(sameflag){len=same_compres(len);}
  
  if( len > 65488 ) {
    fprintf( stderr, "Track overflow.\n" );
    /*		len=65488-4;
		entry( 0xfe, 0, 0, 0 );*/
  }
  
  TRACK.len_high = ( len + 44 ) >> 8;
  TRACK.len_low = (( len + 44 ) >> 16 ) + ( len + 44 ) & 0xff;
}

static int proc_track( void )
{
  int i;
  unsigned char b[8];
  
  exc_no=0x10;exc_id=0x16;chport=0;
  
  if( fmt == 1 || trk == 0 ) {
    get_data( b, 8 );
    strncpy(std_trk.chunk, b, 4);
    std_trk.length = b[4]*256*256*256 + b[5]*65536 + b[6]*256 + b[7];
    if( strncmp( std_trk.chunk, "MTrk", 4 ) ) {
      fprintf( stderr, "Invalid SMF file (MTrk)\n" );
      return 1;
    }
    get_data( buf, std_trk.length );
  }

  for( i = 0; i < 16; i++ ) {
    nbuf[i] = vbuf[i] = gbuf[i] = cbuf[i] = 0;
  }
  
  pt = 0;
  len = 0;
  
  barunit = 0; stepsum = 0;
  fixflag = 0;
  
  TRACK.track_no = trk;
  TRACK.rhythm_flag = 0x00;
  
  if( fmt == 0 ) {
    TRACK.MIDI_CH = midi_ch = trk ;
  } else {
    TRACK.MIDI_CH = 0 ;
    midi_ch = -1;
  }
  
  TRACK.Play_bias = 0x00;
  TRACK.ST_offset = 0x00;
  TRACK.Mode = 0x00;
  
  strpaste( TRACK.Memo, ( unsigned char * )memoinit );
  memoflag = 0;
  barno=0;
  if(barlenb[0]>0 && trk>0){barlen=barlenb[barno++];}
  
  if( !comment ) {
    printf( "Track= %2d  %04X\n", trk, std_trk.length );
  }
  
  if(chbport!=0 && trk>16 ){chport=16;}
  
  notoff=0;
  if ( proc_next() != 0 ) return 1;

  track_end();
  
  if( trk == 0 ) {
    put_data( RCP_HEAD.mark, 0x0586 );
  }
  
  if(chfixflag){
    if( std_head.format==0 ){
      TRACK.MIDI_CH = trk ;
    }else{
      if(trk){TRACK.MIDI_CH = trk-1 ;}
    }
  }
  
  put_data( ( unsigned char * )&TRACK.len_low, 44 );
  put_data( ( unsigned char * )note, len );
  tc += len + 44;

  return 0;
}

static void dummy_track( void )
  {
    len = 0;

    TRACK.track_no = trk;
    TRACK.rhythm_flag = 0x00;
    TRACK.MIDI_CH = 255;
    TRACK.Play_bias = 0x00;
    TRACK.ST_offset = 0x00;
    TRACK.Mode = 0x00;
    strpaste( TRACK.Memo, ( unsigned char * )memoinit );

    if( !comment ) {
      printf( "Track= %2d  dummy\n", trk );
    }

    track_end();

    put_data( ( unsigned char * )&TRACK.len_low, 44 );
    put_data( ( unsigned char * )note, len );
    tc += len + 44;
  }

#if 0
static void option( char *s )
  {
    char c;

    opt = 0;
    comment = 0;
    tb_mode = 0;
    tb_max = 48;
    sameflag = 0;
    chfixflag = 0;
    tempofix = 0;
    devno_fix = 0;
    chbport=0;

    if( !*s ) {
      usage();
    }

    while( c = *s++ ) {
      switch( c ) {
      case 'C' :
      case 'c' :
	opt = 0;
	break;
      case 'B' :
      case 'b' :
	opt = 1;
	break;
      case 'P' :
      case 'p' :
	opt = 2;
	break;
      case 'K' :
      case 'k'  :
	opt = 2;
	break;
      case 'R' :
      case 'r'  :
	opt = 3;
	break;
      case 'X' :
      case 'x' :
	opt = 4;
	break;
      case 'T' :
      case 't' :
	tb_mode = 1;
	tb_max = 0;
	while(*s>='0' && *s<='9'){
	  tb_max=tb_max*10+((*s++)-'0');
	}
	if(tb_max<48){tb_max=240;}
	break;
      case 'N' :
      case 'n' :
	comment = 1;
	break;
      case ' ' :
	opt = 0;
	break;
      case 'S' :
      case 's' :
	sameflag = 1;
	break;
      case 'F' :
      case 'f' :
	chfixflag = 1;
	break;
      case 'G' :
      case 'g' :
	chbport = 1;
	break;
      case 'E' :
      case 'e' :
	tempofix = 1;
	break;
      case 'D' :
      case 'd' :
	devno_fix = 1;
	break;
      default :
	usage();
	break;
      }
    }

  }
#endif

int itor( unsigned char *smf_data, unsigned char *rcp_buf )
{
  int i;

  /* Initialize all configurable valuables */
  
  opt = 0;
  chfixflag = 0;
  devno_fix = 0;

  tb_mode =  1; /* 0:time base is converted into 48 */
  tb_max = 480; /* Max number of time base */
  chbport =  1; /* translate all tracks > 16 into port B */
  tempofix = 1; /* fixes errors of tempo change */
  sameflag = 1; /* unifies all tracks with SAME MEAS */
  comment  = 1; /* suppress all comments */
  

  /* allocate internal work memory */
  
  note_data = NULL;

  if ( alloc_mem() != 0 ) return 0;
  
  inptr   = smf_data;
  rcpptr  = rcp_buf;
  incount = 0;
  lastptr = rcpptr + 512*1024; /* DATA_ADR_SIZE */
  
  for( i = 0; i < 16; i++ ) {
    note_data[i] = 0xff;
  }
  
  note = note_data + 16;
  

  /* process all tracks */
  
  if ( proc_header() != 0 ) {
    destroy_mem();
    return 0;
  }
  
  if( fmt == 0 ) {
    for( trk = 0; trk < 16; trk++ ) {
      if ( proc_track() != 0 ) {
	destroy_mem();
	return 0;
      }
    }
    
    for( trk = 16; trk < 18; trk++ ) {
      dummy_track();
    }
    
  } else {
    for( trk = 0; trk < std_head.ntrks; trk++ ) {
      if ( proc_track()!= 0 ) {
	destroy_mem();
	return 0;
      }
    }
    
    if( std_head.ntrks>18){
      for( trk = std_head.ntrks; trk < 36; trk++ ) {
	dummy_track();
      }
    }else{
      for( trk = std_head.ntrks; trk < 18; trk++ ) {
	dummy_track();
      }
    }
    
  }
  
  /* free all minternal work memory */

  destroy_mem();
  
  /* all works finished */
  
  return (int)(rcpptr-rcp_buf);
}

/***************************/

static int tai_compres(int ln)
  {
    int	i,ad,ch,rbh=-1,rbm=-1;
    unsigned char	a,b,c,d;
    /*base dd dev df*/
    ch=(TRACK.MIDI_CH+1)&0xff;
    ad=0;

    for(i=0;i<ln;i+=4){
      a=note[i];b=note[i+1];c=note[i+2];d=note[i+3];

      if(a<128 && c>b && d>0){
	int cc=ch,ad2,sum;
	ad2=i;sum=0;

	while(ad2<ln){
	  unsigned char	da=note[ad2];
	  if(da==0xe6){cc=note[ad2+2];}

	  if(ad2>i && cc==ch && a==da && note[ad2+2]!=0 && note[ad2+3]!=0 ){
	    if(sum+note[ad2+2]<=255){
	      c=note[ad2+2]+sum;
	      note[i+2]=c;
	      note[ad2+2]=0;
	      note[ad2+3]=0;
	    }else{
	      break;
	    }
	  }

	  if(da<0xf0){sum+=note[ad2+1];if(sum>255 || sum>=c){break;}}

	  if(da>=0xfc||da==0xf8||da==0xf9||da==0xe2||da==0xec){break;}
	  ad2+=4;
	}
      }

      /*		if(note[i]>=0xfc){ch=-1;}*/

      if(note[i]>=0xfc){rbh=-1;rbm=-1;}

      if(note[i]==0xdd){
	if(note[i+2]==rbh && note[i+3]==rbm){
	  note[i]=0;note[i+2]=0;note[i+3]=0;
	}else{
	  rbh=note[i+2];
	  rbm=note[i+3];

	  if(ad && note[ad-4]==0xdd){
	    note[ad-2]=note[i+2];
	    note[ad-1]=note[i+3];
	    note[i]=0;note[i+2]=0;note[i+3]=0;
	  }
	}
      }

      /*		if(note[i]==0xe6){
			if(note[i+2]==ch){
			note[i]=0;note[i+2]=0;note[i+3]=0;
			}else{
			ch=note[i+2];

			if(ad && note[ad-4]==0xe6){
			note[ad-2]=note[i+2];
			note[i]=0;note[i+2]=0;note[i+3]=0;
			}
			}
			}
			*/
      /*
	if(note[i]==0xee){
	if(ad && note[ad-4]==note[i] && note[ad-3]==0){
	note[ad-2]=note[i+2];
	note[i]=0;note[i+2]=0;note[i+3]=0;
	}
	}
	*/
      if((note[i]<0x80 &&(note[i+2]==0||note[i+3]==0))&&
	 ad>0 && note[ad-4]<0xf0 && note[ad-3]+note[i+1]<=240){
	note[ad-3]+=note[i+1];
      }else{
	note[ad++]=note[i];note[ad++]=note[i+1];
	note[ad++]=note[i+2];note[ad++]=note[i+3];
      }
    }

    return ad;
  }

/***************************/
static int same_compres(int size)
  {
    int	i,j=0,k,match,count=0;
    int	po=0,m_max,ln,co=0,me=0,ad;
    int	add[1024],add2[1024],leng[1024];

    m_max=add_set(size,add);if(m_max<2 || m_max>1024){return(size);}

    for(i=0;i<m_max;i++){
      po=add[i];ln=meas_len(size,po);match=0;
      if(ln>4 && note[po+ln-4]==0xfc){ln=ln-4;}

      if(note[po]<0xfc && me>0){
	j=0;while(j<me ){
	  if(ln==leng[j] && note[add2[j]]<0xfc){
	    match=1;ad=add2[j];
	    k=0;while(k<ln){
	      if(note[po+k]!=note[ad]){match=0;break;}
	      k++;ad++;
	    }
	  }
	  if(match!=0){break;}
	  j++;
	}
      }

      if(match!=0 && j<1024 && add2[j]<65536-44){
	int ad=add2[j]+44;
	if(me<1024){add2[me]=co;leng[me]=4;me++;}
	note[co]=0xfc;
	note[co+1]=j&0xff;note[co+2]=(j>>8)+(ad&0xfc);note[co+3]=ad>>8;
	co=co+4;count++;
      }else{
	if(me<1024){add2[me]=co;leng[me]=ln;me++;}
	for(k=0;k<ln;k++){note[co]=note[po];po++;co++;}
      }
    }
    note[co]=0xfe;co=co+4;
    return(co);
  }

static int add_set(int size,int *add)
  {
    int	co=0,i=0;

    add[0]=0;
    while(i<size){
      if(note[i]>=0xfc||note[i+4]==0xfc){
	co++;if(co<1024){add[co]=i+4;}
      }

      if(note[i]<128){
	if(note[i+2]==0 || note[i+3]==0){note[i]=0;note[i+2]=0;note[i+3]=0;}
      }
      i=i+4;
    }

    return(co);
  }

static int meas_len(int size,int j)
  {
    int	co=0,d;

    while(j<size ){
      d=note[j];
      if( d==0xfe ){break;}
      co++;
      if( d>0xfb ){break;}
      j=j+4;
    }
    return(co*4);
  }

/***************************/
