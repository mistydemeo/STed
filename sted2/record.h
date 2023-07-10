/*************************************/
/* real time recording subroutine    */
/*************************************/

#ifndef _RECORD_H_
#define _RECORD_H_

int real_record();
void    mix_one(int c,int a);
void mix_two(int c,int a,int b);
void    rec_ch_disp();
void    rec_ch_change(int pm);
void    rec_md_change();
void    rec_mt_change(int md);
void    rec_sy_change();
void    rec_meas_change(void);
int countstart(int md,int smeas);
unsigned char   *strncpy0( unsigned char *dst, unsigned char *src, int n );
int get_delta( int p );
void put_delta( int p ,int val);
void entry( int d0, int d1, int d2, int d3 );
void record_flash( int dt );
void proc_dummy( int dt );
void check( int data );
int search( int pp );
void ent_dat( int nt, int vl, int gt );
void note_off( int p );
void note_on( int p );
void ctl_chg( int p );
void prg_chg( int p );
void aft_tch( int p );
void pt_bend( int p );
void run_sts( int p );
int num_check( int num, int limit );
void proc_excl( unsigned char *text , int length,int code);
void proc_next( void );
void track_end( void );
void rec_conv( int mm );
int rec_ext(int i);
int meas_adjust(int i,int topm);
int meas_adj_sub(int ln,int st);

#endif
