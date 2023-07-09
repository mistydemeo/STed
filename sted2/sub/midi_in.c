/* midi_in.c

   midi-port access functions

   Made by Studio Breeze. 1998

*/

#include "sted.h"

static int midi_dev = -1;
static int ismididevopened = 0;

int open_midi_port( char *dev_name ) {

  int ret=1;

  if ( ismididevopened!=0 ) return ret;

  ismididevopened=-1;
  midi_dev=-1;

  if ( dev_name[0] != 0 ) {

    midi_dev = open( dev_name, O_RDWR | O_NDELAY );
    if ( midi_dev != -1 ) {
      ismididevopened=1;
      ret = 0;
    }
  }

  return ret;
}

void close_midi_port( void ) {

  if ( ismididevopened > 0 ) {
    close(midi_dev);
  }

  return;
}

int get_midi_data( void ) {

  int ret=-1;
  static fd_set x;
  static struct timeval tp;

  open_midi_port( midi_port_name );

  if ( ismididevopened > 0 ) {

    FD_ZERO(&x);
    FD_SET( midi_dev, &x );
    tp.tv_sec = 0;
    tp.tv_usec= 0;
    select( midi_dev+1, &x, (fd_set *)NULL, (fd_set *)NULL, &tp );

    if ( FD_ISSET( midi_dev, &x) ) {
      unsigned char buf[16];
      read( midi_dev, buf, 1);
      ret = (int)buf[0];
    }
  }

  return ret;
}

int is_midi_in( void ) {

  int ret=0;
  static fd_set x;
  static struct timeval tp;

  open_midi_port( midi_port_name );

  if ( ismididevopened > 0 ) {

    FD_ZERO(&x);
    FD_SET( midi_dev, &x );
    tp.tv_sec = 0;
    tp.tv_usec= 0;
    select( FD_SETSIZE, &x, (fd_set *)NULL, (fd_set *)NULL, &tp );

    if ( FD_ISSET( midi_dev, &x) ) ret=1;
  }

  return ret;
}

void put_midi_data ( char data ) {

  if ( ismididevopened > 0 ) {
    write( midi_dev, &data, 1 );
  }

  return;
}

/* */

int start_plm_daemon ( char *device_name ) {

  return 0;
}

static void plm_daemon ( void ) {
}
