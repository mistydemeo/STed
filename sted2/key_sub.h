/*
 * STed2.x:key_sub.h midi in & chord & key name
 */

#ifndef _KEY_SUB_H_
#define _KEY_SUB_H_

void    inpmon();
void    midi_change(int md);
int midi_inout();
void    midi_chout(int a);
int midi_in();
int midi_in_fk();
void    midi_clr();
int polykey(int cde);
int onekey(int imd,int cde);
int ret_midi(int cde,int imd,int ad,int cy);
int ret_chord(int ad);
int chord_sel(int key,int ad);
int chord_ten(int key,int no);
int chord_ins(int ad,int co);
void    chord_dis(int n);
int ctc(int da,char *s,int skey);
char    *keystr(int da);
char    *keystr1(int da,int skey);
char    *keystr2(int da,int skey);
char    *chstr(int ex);
int strch(int och,char *tmp0);
int key_shift(int skey,int *f,int *a);
void    key_shift_sub(int no,int *f,int *a);
char    *scale_str(int da);
int scale_no(int j);
int scale_sel(int x,int y,int skey);
char    *prog_name(int ch,int bank,int prog,int h);
char    *tim_names(int no);
int mml_inp(int ad);

#endif
