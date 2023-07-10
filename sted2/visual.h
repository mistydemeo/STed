/*
 * STed: visual.h  (controller visal edit)
 */

#ifndef _VISUAL_H_
#define _VISUAL_H_

int vis_edit(int po,int ln,int ssh);
int vis_bufset(int po,int co,int *para,int *step,int vmo,int bf);
int b2_set(int ad,int ln);
int vis_ext_mix(int po,int co,int *para,int *step,int vmo,int ost);
int vis_a_in(int po,int ln,int *para,int *step,int vmo);
int vis_a_in_co(int po,int ln,int vmo);
int vis_a_in_st(int po,int ln);
void    vis_a_out(int po,int ln,int *para,int *step,int vmo);
void    vis_disp(int co,int cx,int ccx,int *para,int *step,int mo,int c,int vmo);
void    vis_wave(int st,int co,int cx,int ccx,int *para,int *step,int md,int vmo);
void    bunkatsu(int st,int co,int *da);
int vis_cut(int co,int st,int *para,int *step);
int vis_lnk(int co,int *para,int *step);
void    vis_zom(int co,int in_step,int out_step,int *step,int *step2);

#endif
