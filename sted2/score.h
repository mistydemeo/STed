/*
 * STed: score.h  (fumen & data draw subroutine)
 */

#ifndef _SCORE_H_
#define _SCORE_H_

void    gra(int po,int sh);
void    gra_c(int po);
void    gra_gakufu(int po,int md);
void    gra_special(int po,int md);
int gra_add(int ad,int md);
int st_cv(int st);
void    put_sharp(int skey,int x,int y);
void    dat_info(int po,int sh);

#endif
