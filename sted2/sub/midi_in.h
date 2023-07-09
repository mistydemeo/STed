/*
  midi_in.h

  prototype dec.s for functions midi port access

  Made by Studio Breeze. 1998

 */

#ifndef _MIDI_IN_H_
#define _MIDI_IN_H_

int open_midi_port( char * );
void close_midi_port( void );
int get_midi_data( void );
int is_midi_in( void );
void put_midi_data( char );

#endif /* _MIDI_IN_H */
