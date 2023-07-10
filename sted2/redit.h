/*
 * STed: redit.h (rhythm track edit)
 */

#ifndef _REDIT_H_
#define _REDIT_H_

void rtrk_ed(int md,int sh);
void    rtrk_dis(int p,int ad,int line);
void    rhed_dis(int p);
void    rhy_step();
void    rtopat(int me);
void    pattor(int me);
void    rsttrc(int *no,int *cx,int flg,int pg);
void    disp_vels();

#endif
