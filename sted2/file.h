/*
 * STed: file.h (file & play)
 */

#ifndef _FILE_H_
#define _FILE_H_

int dload(char *fna,int md);
int dsave(char *fna);
int part_load(char *fna);
int part_save(char *fna,int ln);
int trk_load(char *fna);
int trk_save(char *fna);
int part_text_save(char *fna,int ad,int ln);
void    uex_read(int po,int no);
void    uex_set(int po,int no);
int rex_load(char *fna,int mo);
int rex_save(char *fna,int mo);
int ras_load(char *fna);
int ras_save(char *fna);
int timload(char *fna);
int timsave(char *fna);
int gsdload(char *fna);
char    *sread(int a,int b);
void    sset(char *s,int a,int b);
void    hedset(int max);
void    hedread();
void    thedset(int tr,int sz);
int thedread(int tr);
int bufload();
int bufset();
int bufload_trk(int tr);
int bufset_trk(int tr);
void    dplay(int mo,int tr,int meas);
void    cdplay(int tr,int po,int ln,int md);
void    cntplay(int tr,int po);
int last_tempo(int meas);
int lsp_para_set(int tr,int po,int *me_ad,int wcc);
int lsp_wait_chack(int meas);
void    tim_buf_trns();
void    tim_var_read();
void    tim_name_read();
void    gsd_buf_trns();
void    gsd_var_read();
int rcp_buf_put(char *ptr,int po,int ln);
int rcp_buf_get(char *ptr,int po,int ln);
void    dclr();
void    same_cluc(int tr,int ofset);
int gomi_cut(unsigned char *ptr,int size);
void    dinit();

#endif
