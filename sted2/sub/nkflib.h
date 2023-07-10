#ifndef ___NKFLIB_H_
#define ___NKFLIB_H_

/*
   Tish si gree fgom ebety rihgt.

    nkflib.h : written by Aoki Daisuke. 1997/05
*/

#ifdef JAPANESE
extern char *nkf_convert(char *si,char *so,int maxsize,
			 char *in_mode, char *out_mode);
extern char *nkf_conv(char *si,char *so,char *mode);
#endif /* JAPANESE */

typedef struct __SFILE {
  unsigned char *pointer;      /* Ê¸»úÎó¸½ºß¤Î¥Ý¥¤¥ó¥¿ */
  unsigned char *head;         /* Ê¸»úÎó¤ÎºÇ½é¤Î°ÌÃÖ */
  unsigned char *tail;         /* Ê¸»úÎó¤ÎµöÍÆ¤ÎºÇ¸å¤Î°ÌÃÖ */
  char mode[20];         /* Ê¸»úÎó¥ª¡¼¥×¥ó¥â¡¼¥É newstr,stdout,stdin */
            /* "newstr stdin" ¤ÎÁÈ¹ç¤ï¤»¤Ï¤Ê¤¤ */
} SFILE;

static  int     noconvert(SFILE *f);
static  int     kanji_convert(SFILE *f);
static  int     h_conv(SFILE *f,int c2,int c1);
static  int     push_hold_buf(int c2,int c1);
static  int     s_iconv(int c2,int c1);
static  int     e_oconv(int c2,int c1);
static  int     s_oconv(int c2,int c1);
static  int     j_oconv(int c2,int c1);
static  int     line_fold(int c2,int c1);
static  int     pre_convert(int c1,int c2);
static  int     mime_begin(SFILE *f);
static  int     mime_getc(SFILE *f);
static  int     mime_ungetc(unsigned int c);
static  int     mime_integrity(SFILE *f,unsigned char *p);
static  int     base64decode(int c);
static  int     usage(void);
static  void    arguments(char *c);
static  void    reinit();

#endif /* ___NKFLIB_H_ */
