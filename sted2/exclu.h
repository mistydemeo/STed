/*
 * STed: exclu.h (selecter)
 */

#ifndef _EXCLU_H_
#define _EXCLU_H_

void    user_exc_as(int no);
void    user_exc_dis(int no);
void    exc_edit(int ad,int cy,int sw);
void    excsum(unsigned char *da,int nn);
void    excins(unsigned char *da,int co,int nn);
void    excdel(unsigned char *da,int co,int nn);
void    exc_dis(int no,int cx,int co,int m);
int exc_load(char *fna);
int exc_save(char *fna,int co);
void prn_gspanel( int cx );
int dot_ed(int dx,int co);
void    dot_ctrl(int m);
void    dot_dis(int cx);
void    dattopat(void);
void    pattodat(void);
void    exc_view(int ad);
void    exc_dis2(int cx,int co);

#endif
