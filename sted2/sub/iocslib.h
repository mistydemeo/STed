/* iocslib.h

   dummy header file for X680x0 compatible

   Made by Studio Breeze. 1998

*/

#ifndef _X68_IOCSLIB_H_
#define _X68_IOCSLIB_H_

/* structs */

struct _x68_fntbuf {
  short x1;                  /* dots of x-dir */
  short y1;                  /* dots of y-dir */
  unsigned char buffer[72];  /* reading buffer */
};

#define X68_FNTBUF _x68_fntbuf

struct _x68_txfillptr {
  unsigned short vram_page;  /* text page */
  short x;                   /* x position of start point */
  short y;                   /* y position of start point */
  short x1;                  /* x position of end point */
  short y1;                  /* y position of end point */
  unsigned short fill_patn;  /* pattern of filling */
};

#define X68_TXFILLPTR _x68_txfillptr
#define X68_TXBOXPTR  _x68_txfillptr

struct _x68_xlineptr {
  unsigned short vram_page;  /* text page */
  short x;                   /* x position of start point */
  short y;                   /* y position of start point */
  short x1;                  /* x length to end point */
  unsigned short line_style; /* pattern of filling */
};

#define X68_XLINEPTR _x68_xlineptr

struct _x68_ylineptr {
  unsigned short vram_page;  /* text page */
  short x;                   /* x position of start point */
  short y;                   /* y position of start point */
  short y1;                  /* y length to end point */
  unsigned short line_style; /* pattern of filling */
};

#define X68_YLINEPTR _x68_ylineptr


/* defines for upper-cased-name functions */

#define READCAP		_readcap
#define INQUIRY		_inquiry

#define ABORTJOB	_iocs_abortjob
#define ABORTRST	_iocs_abortrst
#define ADPCMINP	_iocs_adpcminp
#define ADPCMMOD	_iocs_adpcmmod
#define ADPCMOUT	_iocs_adpcmout
#define ADPCMSNS	_iocs_adpcmsns
#define AKCONV		_iocs_akconv
#define ALARMGET	_iocs_alarmget
#define ALARMMOD	_iocs_alarmmod
#define ALARMSET	_iocs_alarmset
#define APAGE		_iocs_apage
#define BGCTRLGT	_iocs_bgctrlgt
#define BGCTRLST	_iocs_bgctrlst
#define BGSCRLGT	_iocs_bgscrlgt
#define BGSCRLST	_iocs_bgscrlst
#define BGTEXTCL	_iocs_bgtextcl
#define BGTEXTGT	_iocs_bgtextgt
#define BGTEXTST	_iocs_bgtextst
#define BINDATEBCD	_iocs_bindatebcd
#define BINDATEGET	_iocs_bindateget
#define BINDATESET	_iocs_bindateset
#define BITSNS		_iocs_bitsns
#define BOOTINF		_iocs_bootinf
#define BOX		_iocs_box
#define B_ASSIGN	_iocs_b_assign
#define B_BADFMT	_iocs_b_badfmt
#define B_BPEEK		_iocs_b_bpeek
#define B_BPOKE		_iocs_b_bpoke
#define B_CLR_AL	_iocs_b_clr_al
#define B_CLR_ED	_iocs_b_clr_ed
#define B_CLR_ST	_iocs_b_clr_st
#define B_COLOR		_iocs_b_color
#define B_CONSOL	_iocs_b_consol
#define B_CUROFF	_iocs_b_curoff
#define B_CURON		_iocs_b_curon
#define B_DEL		_iocs_b_del
#define B_DOWN		_iocs_b_down
#define B_DOWN_S	_iocs_b_down_s
#define B_DRVCHK	_iocs_b_drvchk
#define B_DRVSNS	_iocs_b_drvsns
#define B_DSKINI	_iocs_b_dskini
#define B_EJECT		_iocs_b_eject
#define B_ERA_AL	_iocs_b_era_al
#define B_ERA_ED	_iocs_b_era_ed
#define B_ERA_ST	_iocs_b_era_st
#define B_FORMAT	_iocs_b_format
#define B_INS		_iocs_b_ins
#define B_INTVCS	_iocs_b_intvcs
#define B_KEYINP	_iocs_b_keyinp
#define B_KEYSNS	_iocs_b_keysns
#define B_LEFT		_iocs_b_left
#define B_LOCATE	_iocs_b_locate
#define B_LPEEK		_iocs_b_lpeek
#define B_LPOKE		_iocs_b_lpoke
#define B_MEMSET	_iocs_b_memset
#define B_MEMSTR	_iocs_b_memstr
#define B_PRINT		_iocs_b_print
#define B_PUTC		_iocs_b_putc
#define B_PUTMES	_iocs_b_putmes
#define B_READ		_iocs_b_read
#define B_READDI	_iocs_b_readdi
#define B_READDL	_iocs_b_readdl
#define B_READID	_iocs_b_readid
#define B_RECALI	_iocs_b_recali
#define B_RIGHT		_iocs_b_right
#define B_SEEK		_iocs_b_seek
#define B_SFTSNS	_iocs_b_sftsns
#define B_SUPER		_iocs_b_super
#define B_UP		_iocs_b_up
#define B_UP_S		_iocs_b_up_s
#define B_VERIFY	_iocs_b_verify
#define B_WPEEK		_iocs_b_wpeek
#define B_WPOKE		_iocs_b_wpoke
#define B_WRITE		_iocs_b_write
#define B_WRITED	_iocs_b_writed
#define CIRCLE		_iocs_circle
#define CLIPPUT		_iocs_clipput
#define CONTRAST	_iocs_contrast
#define CRTCRAS		_iocs_crtcras
#define CRTMOD		_iocs_crtmod
#define DAKJOB		_iocs_dakjob
#define DATEASC		_iocs_dateasc
#define DATEBIN		_iocs_datebin
#define DATECNV		_iocs_datecnv
#define DAYASC		_iocs_dayasc
#define DEFCHR		_iocs_defchr
#define DENSNS		_iocs_densns
#define DMAMODE		_iocs_dmamode
#define DMAMOVE		_iocs_dmamove
#define FILL		_iocs_fill
#define FNTGET		_iocs_fntget
#define GPALET		_iocs_gpalet
#define G_CLR_ON	_iocs_g_clr_on
#define HANJOB		_iocs_hanjob
#define HOME		_iocs_home
#define HSVTORGB	_iocs_hsvtorgb
#define HSYNCST		_iocs_hsyncst
#define INIT_PRN	_iocs_init_prn
#define INP232C		_iocs_inp232c
#define IPLERR		_iocs_iplerr
#define ISNS232C	_iocs_isns232c
#define JISSFT		_iocs_jissft
#define JOYGET		_iocs_joyget
#define LEDMOD		_iocs_ledmod
#define LINE		_iocs_line
#define LOF232C		_iocs_lof232c
#define MS_CURGT	_iocs_ms_curgt
#define MS_CUROF	_iocs_ms_curof
#define MS_CURON	_iocs_ms_curon
#define MS_CURST	_iocs_ms_curst
#define MS_GETDT	_iocs_ms_getdt
#define MS_INIT		_iocs_ms_init
#define MS_LIMIT	_iocs_ms_limit
#define MS_OFFTM	_iocs_ms_offtm
#define MS_ONTM		_iocs_ms_ontm
#define MS_PATST	_iocs_ms_patst
#define MS_SEL		_iocs_ms_sel
#define MS_SEL2		_iocs_ms_sel2
#define MS_STAT		_iocs_ms_stat
#define ONTIME		_iocs_ontime
#define OPMINTST	_iocs_opmintst
#define OPMSET		_iocs_opmset
#define OPMSNS		_iocs_opmsns
#define OSNS232C	_iocs_osns232c
#define OS_CUROF	_iocs_os_curof
#define OS_CURON	_iocs_os_curon
#define OUT232C		_iocs_out232c
#define OUTLPT		_iocs_outlpt
#define OUTPRN		_iocs_outprn
#define POINT		_iocs_point
#define PRNINTST	_iocs_prnintst
#define PSET		_iocs_pset
#define RMACNV		_iocs_rmacnv
#define ROMVER		_iocs_romver
#define SCROLL		_iocs_scroll
#define SET232C		_iocs_set232c
#define SFTJIS		_iocs_sftjis
#define SKEYSET		_iocs_skeyset
#define SKEY_MOD	_iocs_skey_mod
#define SNSPRN		_iocs_snsprn
#define SPALET		_iocs_spalet
#define SP_CGCLR	_iocs_sp_cgclr
#define SP_DEFCG	_iocs_sp_defcg
#define SP_GTPCG	_iocs_sp_gtpcg
#define SP_INIT		_iocs_sp_init
#define SP_OFF		_iocs_sp_off
#define SP_ON		_iocs_sp_on
#define SP_REGGT	_iocs_sp_reggt
#define SP_REGST	_iocs_sp_regst
#define SYMBOL		_iocs_symbol
#define TCOLOR		_iocs_tcolor
#define TEXTGET		_iocs_textget
#define TEXTPUT		_iocs_textput
#define TGUSEMD		_iocs_tgusemd
#define TIMEASC		_iocs_timeasc
#define TIMEBCD		_iocs_timebcd
#define TIMEBIN		_iocs_timebin
#define TIMECNV		_iocs_timecnv
#define TIMEGET		_iocs_timeget
#define TIMERDST	_iocs_timerdst
#define TIMESET		_iocs_timeset
#define TPALET		_iocs_tpalet
#define TPALET2		_iocs_tpalet2
#define TRAP15		_iocs_trap15
#define TVCTRL		_iocs_tvctrl
#define TXBOX		_iocs_txbox
#define TXFILL		_iocs_txfill
#define TXRASCPY	_iocs_txrascpy
#define TXREV		_iocs_txrev
#define TXXLINE		_iocs_txxline
#define TXYLINE		_iocs_txyline
#define VDISPST		_iocs_vdispst
#define VPAGE		_iocs_vpage
#define WINDOW		_iocs_window
#define WIPE		_iocs_wipe

/* functions */

extern void _iocs_b_clr_al (void);
extern void _iocs_b_clr_ed (void);
extern int  _iocs_b_color (int);
extern int  _iocs_b_consol (int, int, int, int);
extern int  _iocs_b_keyinp (void);
extern int  _iocs_b_keysns (void);
extern int  _iocs_b_locate (int, int);
extern int  _iocs_b_putmes (int, int, int, int, const char *);
extern int  _iocs_b_print (const char *);
extern int  _iocs_b_sftsns (void);
extern int  _iocs_b_wpeek (const void *);
extern void _iocs_b_wpoke (void *, int);
extern int  _iocs_bitsns (int);
extern int  _iocs_crtmod (int);
extern int  _iocs_defchr (int, int, const void *);
extern int  _iocs_fntget (int, int, struct _x68_fntbuf *);
extern void _iocs_g_clr_on (void);
extern int  _iocs_gpalet (int, int);
extern int  _iocs_home (int, int, int);
extern void _iocs_ledmod (int, int);
extern void _iocs_ms_curof (void);
extern void _iocs_ms_curon (void);
extern int  _iocs_ms_getdt (void);
extern void _iocs_ms_init (void);
extern int  _iocs_ms_limit (int, int, int, int);
extern int  _iocs_ontime (void);
extern int  _iocs_tgusemd (int, int);
extern int  _iocs_tpalet (int, int);
extern void _iocs_txbox (const struct _x68_txfillptr *);
extern void _iocs_txfill (const struct _x68_txfillptr *);
extern void _iocs_txrascpy (int, int, int);
extern void _iocs_txxline (const struct _x68_xlineptr *);
extern void _iocs_txyline (const struct _x68_ylineptr *);
extern int  _iocs_window (int, int, int, int);

/* -------------- */

#endif /* _X68_IOCSLIB_H_ */
