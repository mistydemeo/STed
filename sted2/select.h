/*
 * STed: select.h (selecter)
 */

#ifndef _SELECT_H_
#define _SELECT_H_

typedef struct {
  char      name[23];
  unsigned char far;
  unsigned int  fln;
  unsigned int  ftm;
  unsigned int  fdt;
} X68_DIR;

int timsel(int bmode,int bank,int gx,int prog);
int timsel2(int ch,int bank,int gx,int prog);
void    stest_para_disp(int x);
void    stest_para_edit(int x,int a);
int varia(char *pname,int bank,int prg,int md);
void    s_test(int ch,int bank,int prg,int note,int velo);
int spc_select();
int repl_select(int md);
void fsel(char *fna,char *pth,int w);
void    str_change(char *s);
void    path_cut(char *fpath,char *fname);
void    path_down(char *pth);
void    path_set(char *pth);
int file_check(char *fna,int cc);
void    file_back(char *fna);
int drvchk(char *pth);
int drvchk2(char *pth);
int drv_code(char *st);
void    frees(char *pth,int cx);
void    dir_disp(X68_DIR *dir,int nm,int p,int cx,int sp,int ln);
int fdir(char *pth,char *exts,X68_DIR *dir,int w);
void    memo_disp();
void    memo_load(char *pth,char *fna);

#endif
