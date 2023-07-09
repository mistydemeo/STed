
/*
  iocs_tgraph.c

  functions for compatibility to iocslib
  ( containing mainly text-graphics oriented functions )

  Made by Studio Breeze. 1998

 */

#include "sted.h"

int _iocs_tpalet( int no, int code ) {

  int ret=0;

  if ( isxwin ) {
   ret=XSTed_tpalet( no, code ); 
  }
  return ret;
}

void _iocs_txbox( const struct _x68_txfillptr *ptr ) {

  if ( isxwin ) {
    XSTed_txbox( ptr->x, ptr->y, ptr->x1, ptr->y1, ptr->vram_page );
  }
  return;
}

void _iocs_txfill ( const struct _x68_txfillptr *ptr ) {

  if ( isconsole ) {
    curses_tfill( ptr->vram_page, ptr->x, ptr->y, ptr->x1, ptr->y1, ptr->fill_patn );
  } else if ( isxwin ) {
    XSTed_tfill( ptr->vram_page, ptr->x, ptr->y, ptr->x1, ptr->y1, ptr->fill_patn );
  }

  return;
}

void _iocs_txrascpy ( int sr_dst, int copy, int mode ) {

  if ( isconsole ) {
    curses_trascpy( sr_dst&0xff, sr_dst>>8, copy, mode );
  } else if ( isxwin ) {
    XSTed_trascpy( sr_dst&0xff, sr_dst>>8, copy, mode );
  }
  return;
}

void _iocs_txxline ( const struct _x68_xlineptr *ptr ) {

  if ( isxwin ) {
    XSTed_txxline( ptr->vram_page, ptr->x, ptr->y, ptr->x1, ptr->line_style );
  }
  return;
}

void _iocs_txyline ( const struct _x68_ylineptr *ptr ) {

  if ( isxwin ) {
    XSTed_txyline( ptr->vram_page, ptr->x, ptr->y, ptr->y1, ptr->line_style );
  }
  return;
}
