/*
 * STed: track.h (track subroutine)
 */

#ifndef _TRACK_H_
#define _TRACK_H_

int trk_mix_sub(unsigned char *in1,unsigned char *in2);
int trk_ext_sub(int tr,char *exbuf);

int repeat_comp(int tr);
int repeat_ext(unsigned char *obuf,int ln);
int same_meas_conv(int tr);
int same_ext_sub(int tr,int p1,int p2,int md);
void    trk_opt_sub(int tr,int po1,int po2);
int tai_compres(int tr,int po1,int po2);
void    trk_quan(int tr,int po1,int po2);
void    note_ctrl(int po1,int po2);
int velo_ctrl(int ad,int ln,int vmo);

int trk_check(int ln);
int trk_shift(int ad,int ln);
void    trk_delete(int ad,int ln);
int size_change(int tr,int ln);
int size_max(int tr);
int size_add(int tr,int size);
void    size_ref();

#endif
