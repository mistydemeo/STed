/*
 * STed: cm6con.h (cm-64 controler)
 */

#ifndef _CM6CON_H_
#define _CM6CON_H_

void    cm64_con();
void    pfil();
void    keyd();
void    keyd_inp(int a);
void    pch_fld(int m);
void    card_sel();
void    card_name_get();
int sys_mode();
int tone_patch(int mo);
void    pat_para_set(int mo,int ad,int i);
void    pat_para_dis(int m,int ad);
int rhy_patch();
int user_tone_list();
int cm6_tonesel(int slmd);
void    cminit();
void    cm6_write(int ad,int ad2,int ln);
void    cm6_tone_write(int i);
void    cm6_la_write(int i);
void    cm6_pcm_write(int i);
void    trns_check(void);
void    timtra();
void    all_note_off(int m);
void    temporary_set();
char    *cm6_tone_name(int mo,int i);
void    twait(int ti);
void    gsd_con();
void    gsinit();

#endif
