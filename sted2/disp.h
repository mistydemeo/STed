/*
 * STed: disp.h (input and output subroutine)
 */

#ifndef _DISP_H_
#define _DISP_H_

void sinput(char *sb,int ln);
int vinput(int l,int ln);
int inkey2(void);
int inkey3(void);
void snsclr();
void    spcut(char *st);
int knck(unsigned char *st,int p);

int str_search(unsigned char *tmp0,unsigned char *tmp1);
int str_last(unsigned char *tmp0);
unsigned char   *jstrupr(unsigned char *st);
char    *spadd(char *s,int c);
char    *fstr(int v,int c);
char    *nstr(int v);
int str_val(char *s);
char    *hex_s(int a,int c);
void    fnc_dis(int n);
void    home2(int y);
void    edfield(int m);
void    noed_cls();
void    noed_cls_t();
void    cons_md(int x);

void    trk_free(int ad);
void    trk_no();

void    sdis(int x,int y,char *s,int c,int c1,int c2);
void    sdis2(int x,int y,char *s,int c,int c1,int c2);
void    sdis3(int x,int y,char *s,int c,int c1,int c2);
void    vdis(int x,int y,int v,int c,int c1,int c2);
void    vdis2(int x,int y,int v,int c,int c1,int c2);
void    vdis3(int x,int y,int v,int c,int c1,int c2);
void    g_print2(int x,int y,char *s,int c1);
void    tdis(int x,int y,char *s,int c,int c1);

void    msg(char *s);
void    msg_clr();
int help(int md);

#endif