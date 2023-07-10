/*
 * STed: edit.h (edit mainroutine)
 */

#ifndef _EDIT_H_
#define _EDIT_H_

int channele_no();
void ed_ch_stgt(int, int, int, int, int);

void trk_ed();
void trk_ed_end(int po,int cx,int cy);
void trk_pos_set(int po,int cx,int cy);
void val_add(int ad,int cx,int kc);
void val_sub(int ad,int cx,int kc);
void val_rev(int ad,int cx);
void ed_ch_stgt(int ad,int cx,int cy,int ke,int sh);
int retkey(int ecode);
int retkey2(int ecode);
void inmd_disp();
void cur_up(int *po,int *cy);
void cur_down(int *po,int *cy);
void roll_up(int *po,int *cy);
void roll_down(int *po,int *cy);

void line_del(int po,int cy);
void line_ins(int po,int cy);
void line_ins_aft(int ad);

void ret(int ad,int cx,int cy,int kc);

int comment_inp(int ad,int cy,int sh);

void spcon(int ad,int cy);

char *trk_dis(int y,int ad,int line);

#endif
