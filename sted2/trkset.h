/*
 * STed: trkset.h (track set subroutine)
 */

#ifndef _TRKSET_H_
#define _TRKSET_H_

int trk_sel(int cx);
void    trk_no_cur(int i,int m);
void    trk_no_dis();
void    trk_set(int md);
void    trmod_set(int tr,int md,int sh);
void    trk_lin(int i,int cx,int m);
void    ts_swap(int a,int b);
void    ts_ins(int a,int b);
void    ts_sort(int a,int b);
void    ts_copy(int a,int b);
void    ts_clear(int a);
void    ts_mix(int tr1,int tr2,int tr3);
void    ts_measend(int tr1,int sh);
void    ts_ext(int i);
void    trksize(int tr);
void    trksize_c();

#endif
