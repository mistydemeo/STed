/*
 * STed: defload.h (def file)
 */

#ifndef _DEFLOAD_H_
#define _DEFLOAD_H_

void    rhinit();
void    rhinit2(int i);
void    user_exc_init();
void    user_exc_init2(int i);
void    stgt_init();
void    stgt_init2(int i);
void    asin_change();
void    asin_init();
void    cnfinit();
void    definit();
int defload(char *fi,int md);
void    cnf_stgt(char *li,int nn);
void    cnf_rvel(char *li);
void    cnf_prog(char *li,char *li2,int md);
void    cnf_repl(char *li,char *li2,int md);
void    def_init(char *li);
int defsave(char *fi,int md,int mutef,int initf);
char    *exc_str(unsigned char *li,int ln,int md);
int buf_put(char *ptr,int ln);
int def_bsave(char *fi,int last_no,int mutef,int initf);
int def_bload(char *fi,int md);

#endif
