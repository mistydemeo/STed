/*--------------------------------------------------------------*/
/* rcddef.h							*/
/*--------------------------------------------------------------*/
/* RCD ƒhƒ‰ƒCƒoEƒAƒNƒZƒX—p\‘¢‘Ì’è‹`   RCD v3.01 ˆÈ~—p	*/
/*--------------------------------------------------------------*/
/*								*/
/* RCD ‚ğ—˜—p‚·‚éƒvƒƒOƒ‰ƒ€‚ÍA					*/
/* 								*/
/* –{ƒtƒ@ƒCƒ‹‚ğƒCƒ“ƒNƒ‹[ƒh‚µ‚Ä‰º‚³‚¢B				*/
/* 								*/
/* extern struct RCD_HEAD *rcd;   <--- ƒ|ƒCƒ“ƒ^‚ÌŠO•”’è‹`‚ğ‚µA	*/
/* 								*/
/* rcdcheck ‚ğƒR[ƒ‹‚µ‚Ä\‘¢‘Ì‚ÌƒAƒhƒŒƒX‚ğ‹‚ß‚½Œã‚ÉA		*/
/* 								*/
/* rcd->fmt ‚È‚Ç‚Ì‚æ‚¤‚ÉƒAƒNƒZƒX‚·‚éB				*/
/* 								*/
/* ƒ‹[ƒ`ƒ“ƒR[ƒ‹‚ÍA(*rcd->begin)() ‚Ì‚æ‚¤‚É‚·‚éB		*/
/*								*/
/*--------------------------------------------------------------*/

#define	TRK_NUM	36			/* ƒgƒ‰ƒbƒN”		*/
#define	CHL_NUM	34 			/* ƒ`ƒƒƒlƒ‹”		*/
					/*  32/33 ‚Í–¢g—p	*/

#define DATA_ADR_SIZE 512 *1024          /* KB */
#define TONE_ADR_SIZE 64  *1024
#define WORD_ADR_SIZE 64  *1024
#define GSD_ADR_SIZE  64  *1024
#define SMF_ADR_SIZE  512 *1024          /* Dec.18.1998 Daisuke Nagano */


struct RCD_HEAD {
  char	title[4];		/* "RCD "		*/
  char	version[4];		/* "N.NN"		*/
  int	staymark;

  char	data_valid;		/* RCP/MCP —LŒø 1	*/
  char	tone_valid;		/* CM6/MTD —LŒø 1	*/
  char	word_valid;		/* WRD —LŒø 1		*/
  char	fmt;			/* MCP:0 RCP:1 R36:2	*/

  char	*data_adr;		/* MCP/RCP address	*/
  char	*tone_adr;		/* MTD/CM6 address	*/
  char	*word_adr;		/* WRD address		*/
  char	*gsd_adr;		/* GSD address		*/ /*(v2.92)*/
  char	*smf_adr;		/* SMF address		*/ /* Dec.11.1998*/

  void	(*init)( void );	/* ƒpƒ‰ƒ[ƒ^‰Šú‰»	*/ /* void (v2.70)*/
  void	(*setup)( void );	/* ‰¹Fƒf[ƒ^‘‚«‚İ	*/ /* void (v2.70)*/
  void	(*begin)( void );	/* ‰‰‘tŠJn		*/ /* void (v2.70)*/
  void	(*end)( void );		/* ‰‰‘tI—¹		*/ /* void (v2.70)*/

  void	(*md_put)( char );	/* MIDI 1 byte o—Í	*/ /* void (v2.70)*/
  int	(*md_get)( void );	/* MIDI 1 byte “ü—Í@(-1)“ü—Í‚È‚µ*/ /*(v2.70)*/
  void	(*md_put2)( char );	/* MIDI 1 byte o—Í(dual)*/ /* void (v2.92)*/
  void	(*mix_out)( char * );	/* MIX OUT(buff adrs)end=$ff*/ /*(v3.01)*/

  int	act;			/* 1:‰‰‘t’†		*/
  int	sts;			/* 0:RUN 1:STOP 2:SEARCH 3:CUE	*/ /*(v2.70)*/
  int	tar_trk;		/* TARGET TRACK		*/
  int	tar_bar;		/* TARGET BAR		*/

  char	dummy1[ 18 ];

  int	tempo;			/* Œ»İ‚Ìƒeƒ“ƒ|		*/
  int	basetempo;		/* Œ³‚Ìƒeƒ“ƒ|		*/

  int	totalcount;		/* ‰¹•„ƒtƒ@ƒCƒ‹’·	*/
  char	filename[30];		/* ‰¹•„ƒtƒ@ƒCƒ‹–¼	*/
  char	tonename[30];		/* ‰¹Fƒtƒ@ƒCƒ‹–¼	*/

  char	dummy2[ 72 ];

  int	bufcap;			/* ƒoƒbƒtƒ@—e—Ê		*/  /*(v2.70)*/

  int	MIDI_avl;		/* MIDI o—Í—LŒø(trk.no)*/  /*(v2.80)*/
  unsigned char MIDI_req[16];	/* MIDI o—Í—v‹ƒoƒbƒtƒ@*/  /*(v2.80)*/
	  /* (80) (ch) ...	:ƒ`ƒƒƒlƒ‹ƒ`ƒFƒ“ƒW	*/
	  /* (90) (ke) (ve)	:ƒm[ƒgƒIƒ“		*/  /*(v2.92)*/
	  /* (b0) (xx) (xx)	:ƒRƒ“ƒgƒ[ƒ‹ƒ`ƒFƒ“ƒW	*/
	  /* (c0) (xx) ...	:ƒvƒƒOƒ‰ƒ€ƒ`ƒFƒ“ƒW	*/
	  /* (e0) (xx) (xx)	:ƒsƒbƒ`ƒxƒ“ƒ_		*/
	  /* (f0) (hh) (mm) (ll) (xx) :ƒƒ‚ƒŠƒ‰ƒCƒg	*/
	  /* (f1) (hh) (mm) (ll) (xx) (id):ƒƒ‚ƒŠƒ‰ƒCƒg	*/  /*(v2.92)*/

#if 1
  char	LA_VOL;			/* LA part master vol   */ /*(v2.80)*/
  char	LA_RVB_Mode;		/* LA part reverb Mode  */ /*(v2.80)*/
  char	LA_RVB_Time;		/* LA part reverb Time  */ /*(v2.80)*/
  char	LA_RVB_Level;		/* LA part reverb Level */ /*(v2.80)*/

  char	PCM_VOL;		/* PCM part master vol  */ /*(v2.80)*/
  char	PCM_RVB_Mode;		/* PCM part reverb Mode */ /*(v2.80)*/
  char	PCM_RVB_Time;		/* PCM part reverb Time */ /*(v2.80)*/
  char	PCM_RVB_Level;		/* PCM part reverb Level*/ /*(v2.80)*/

  int	filter_mode;		/* 0:–³Œø 1:PRG‚Ì‚İ 2:LA/PCM‚ ‚è */ /*(v2.90)*/
  char	*filter_data;		/* Filter DataƒAƒhƒŒƒX	*/ /*(v2.90)*/

  int	play_mode;	/* 0:normal 1:slow 2:fast 3:slow2 4:fast2 */ /*(v2.92)*/
#endif
  int	mute_mode;	/* 0:off 1:cm64 2:sc55	*/ /*(v2.92)*/
  int	init_mode;	/* 0:off 1:cm64 2:sc55 3:cm+sc */ /*(v2.92)*/
#if 1
  char	scan_mode;	/* key scan flag 0:off 1:on */
  char	rsmd_mode;	/* midi port flag 0:midi 1:midi+rs/sb 2:rs/sb */
  short	fade_time;	/* fade out speed	*/
  char	fade_count;	/* fade out start flag 128:start 0:end */
#endif
  char	moduletype;	/* panel display 0:cm64 1:sc55 2:cm+sc */
#if 1
  char	fade_mode;	/* fade out mode 0:exclusive a:volume 2:expres*/
  char	timer_mode;	/* RS-MIDI timer mode 0:OPM Timer-A 1:OPM Timer-B */
  char	midi_clock;	/* MIDI clock out 0:disable 1:enable */
#endif
  char	put_mode;	/* md_put port mode 0:normal 1:midi 2:rs */
#if 1
  char	rcd_type;	/* 0:midi+rs-232c 1:midi+polyphon 3:polyphon only */
  char	sc55_fix;	/* 0:off 1:sc55 capi.down emulate */ /*(v3.01)*/

  char	dummyA[19];		/* Šg’£—pƒŠƒU[ƒu	*/

  char	mt32_mode;		/* mt-32 mode		*/
  int	exc_wait;		/* exclusive send wait	*/
  char	tim_all;		/* timbre trans mode	*/
#endif

  char	gsd_valid;		/* GSD —LŒø 1		*/  /*(v2.92)*/
  char	gsdname[30];		/* GSDƒtƒ@ƒCƒ‹–¼	*/

  int	wordcap;		/* word ƒoƒbƒtƒ@—e—Ê	*/  /*(v2.92)*/

#if 1
  char	dummyC[10];		/* Šg’£—pƒŠƒU[ƒu	*/

  char	GS_VOL;			/* GS part master vol   */ /*(v2.93)*/
  char	GS_PAN;			/* GS part master pan   */ /*(v2.93)*/

  char	GS_RVB_Macro;		/* ƒŠƒo[ƒuƒ}ƒNƒ	*/ /*(v2.93)*/
  char	GS_RVB_Char;		/* ƒŠƒo[ƒuEƒLƒƒƒ‰ƒNƒ^[EƒRƒ“ƒgƒ[ƒ‹*/
  char	GS_RVB_Prelpf;		/* ƒŠƒo[ƒuE‚o‚q‚dE‚k‚o‚eEƒRƒ“ƒgƒ[ƒ‹*/
  char	GS_RVB_Level;		/* ƒŠƒo[ƒuEƒŒƒxƒ‹EƒRƒ“ƒgƒ[ƒ‹*/
  char	GS_RVB_Time;		/* ƒŠƒo[ƒuEƒ^ƒCƒ€EƒRƒ“ƒgƒ[ƒ‹*/
  char	GS_RVB_Delay;		/* ƒŠƒo[ƒuEDELAYEFEEDBACKEƒRƒ“ƒgƒ[ƒ‹*/
  char	GS_RVB_Send;		/* REVERB SEND LEVEL TO CHOURUS */
  char	GS_RVB_PreDelay;	/* REVERB PREDLY T. */

  char	GS_CHO_Macro;		/* ƒR[ƒ‰ƒXƒ}ƒNƒ	*/
  char	GS_CHO_Prelpf;		/* ƒR[ƒ‰ƒXE‚o‚q‚dE‚k‚o‚eEƒRƒ“ƒgƒ[ƒ‹*/
  char	GS_CHO_Level;		/* ƒR[ƒ‰ƒXEƒŒƒxƒ‹EƒRƒ“ƒgƒ[ƒ‹*/
  char	GS_CHO_Feed;		/* ƒR[ƒ‰ƒXEƒtƒB[ƒhEƒoƒbƒN*/
  char	GS_CHO_Delay;		/* ƒR[ƒ‰ƒXE‚c‚…‚Œ‚‚™EƒRƒ“ƒgƒ[ƒ‹*/
  char	GS_CHO_Rate;		/* ƒR[ƒ‰ƒXE‚q‚‚”‚…EƒRƒ“ƒgƒ[ƒ‹*/
  char	GS_CHO_Depth;		/* ƒR[ƒ‰ƒXE‚c‚…‚‚”‚ˆEƒRƒ“ƒgƒ[ƒ‹*/
  char	GS_CHO_Send;		/* CHORUS SEND LEVEL TO REVERB */
  char	GS_CHO_Send_Dly;

  char	GS_DLY_Macro;		/* ƒfƒBƒŒƒCƒ}ƒNƒ	*/ /*(v3.01)*/
  char	GS_DLY_Prelpf;
  char	GS_DLY_Time_C;
  char	GS_DLY_Time_L;
  char	GS_DLY_Time_R;
  char	GS_DLY_Lev_C;
  char	GS_DLY_Lev_L;
  char	GS_DLY_Lev_R;
  char	GS_DLY_Level;
  char	GS_DLY_Feed;
  char	GS_DLY_Send_Rev;

  char	GS_EQ_Low_Freq;
  char	GS_EQ_Low_Gain;
  char	GS_EQ_High_Freq;
  char	GS_EQ_High_Gain;

  char	dummyD[32-16];		/* Šg’£—pƒŠƒU[ƒu	*/
#endif

  char	active[ TRK_NUM ];	/* ƒgƒ‰ƒbƒN—LŒø		*/
  char	trk_mask[ TRK_NUM ];	/* TRACK MASK		*/
#if 1
  char	midich[ TRK_NUM ];	/* MIDI CH		*/

  int	noteptr;		/* ƒm[ƒgƒ‰ƒ“ƒjƒ“ƒOƒ|ƒCƒ“ƒ^	*/
  unsigned char	*note_adr;	/* ƒm[ƒgƒ‰ƒ“ƒjƒ“ƒOƒoƒbƒtƒ@ƒAƒhƒŒƒX	*/
  char	*top[ TRK_NUM ];	/* ƒgƒ‰ƒbƒNƒf[ƒ^æ“ª	*/
  unsigned char *ptr[ TRK_NUM ];	/* ƒJƒŒƒ“ƒgƒgƒ‰ƒbƒNƒ|ƒCƒ“ƒ^	*/

  char	flg_vel[ TRK_NUM ];	/* VELOCITY ON ƒtƒ‰ƒO	*/
  char	flg_off[ TRK_NUM ];	/* VELOCITY OFF ƒtƒ‰ƒO	*/
  char	flg_act;		/* ACTIVE OFF ƒtƒ‰ƒO	*/
  char	flg_bar;		/* BAR •ÏX ƒtƒ‰ƒO	*/
  char	flg_step;		/* STEP •ÏX ƒtƒ‰ƒO	*/
  char	flg_pbend;		/* PITCH BEND •ÏX ƒtƒ‰ƒO	*/
  char	flg_vol;		/* VOLUME •ÏX ƒtƒ‰ƒO	*/
  char	flg_prg;		/* PROGRAM •ÏX@ƒtƒ‰ƒO	*/
  char	flg_panpot;		/* PANPOT •ÏX ƒtƒ‰ƒO	*/
  char	flg_midich;		/* MIDI CH •ÏX ƒtƒ‰ƒO	*/

  char	flg_song;		/* SONG ƒf[ƒ^ ƒtƒ‰ƒO	*/
  char	flg_system;		/* SYSTEM ƒGƒŠƒA•ÏXƒtƒ‰ƒO	*/ /*(v2.80)*/

  char	flg_expres;		/* EXPRESSION •ÏX ƒtƒ‰ƒO	*/
  char	flg_modula;		/* MODULATION •ÏX ƒtƒ‰ƒO	*/
  char	flg_bank;		/* BANK •ÏX ƒtƒ‰ƒO	*/
  char	flg_replay;		/* REPLAY ƒtƒ‰ƒO		*/

  char	flg_gssys;		/* GS SYSTEM ƒGƒŠƒA•ÏXƒtƒ‰ƒO /*(v2.93)*/
  char	flg_gsrev;		/* GSREV •ÏX ƒtƒ‰ƒO	*/ /*(v2.93)*/
  char	flg_gscho;		/* GSCHO •ÏX ƒtƒ‰ƒO	*/ /*(v2.93)*/
#endif
  char	flg_gsinfo;		/* GS info •ÏX ƒtƒ‰ƒO	*/ /*(v2.93l)*/
  char	flg_gsinst;		/* GS inst •ÏX ƒtƒ‰ƒO	*/ /*(v2.93l)*/
  char	flg_gspanel;		/* GS panel •ÏX ƒtƒ‰ƒO	*/ /*(v2.93l)*/

#if 1
  char	flg_hold1;		/* HOLD1 •ÏX ƒtƒ‰ƒO	*/
  char	flg_gsdly;		/* GSDLY •ÏX ƒtƒ‰ƒO	*/ /*(v3.00q)*/
  char	flg_bankl;		/* BANK L•ÏX ƒtƒ‰ƒO	*/ /*(v3.01n)*/

  char	dummyE[9];		/* Šg’£—pƒŠƒU[ƒu	*/
#endif

  int	panel_tempo;		/* ƒpƒlƒ‹ã‚Ìƒeƒ“ƒ|’l	*/
  int	bar[ TRK_NUM ];		/* ¬ß”Ô†		*/
  int	step[ TRK_NUM ];	/* ƒXƒeƒbƒv”Ô†		*/
#if 1
  char	vel[ TRK_NUM ];		/* ƒxƒƒVƒeƒB’l		*/
#endif

  int	stepcount;		/* ‰‰‘tŠJn‚©‚ç‚ÌSTEP COUNT	*/ /*(v2.92)*/
#if 1
  short	loopcount;		/* 255/256‰ñƒŠƒs[ƒg‚ÌCOUNT	*/ /*(v3.00f)*/

  char	dummyF[12-2];		/* Šg’£—pƒŠƒU[ƒu	*/

  char	song[20];		/* SONGƒf[ƒ^(ƒRƒƒ“ƒg)	*/

  char	dummyG[60];		/* Šg’£—pƒŠƒU[ƒu	*/
#endif

  char	gs_info[18];		/* gs patch name	*/ /*v2.93l*/
  char	gs_inst[34];		/* gs comment		*/ /*v2.93l*/
  char	gs_panel[64];		/* gs panel		*/ /*v2.93l*/

  char	ch_port[ CHL_NUM ];/* ƒ`ƒƒƒlƒ‹–ˆ‚Ìi.f.í—Ş 1:MIDI 2:RS-232C/POLYPHON */
#if 1
  char	ch_part[ CHL_NUM ];/* ƒ`ƒƒƒlƒ‹–ˆ‚Ì‰¹Œ¹í—Ş 0:LA 1:PCM 2:‘¼(RHYTHM) */
  int	ch_pbend[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌPITCH BEND’l	*/
  char	ch_vol[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌVOLUME’l	*/
  char	ch_panpot[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌPANPOT’l	*/
  char	flg_ch_prg[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌPROG.CHGƒtƒ‰ƒO*/ /*v2.93j*/
  unsigned char ch_prg[ CHL_NUM ];/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌPROGRAM”Ô†	*/
  char	ch_reverb[ CHL_NUM ];	/* ƒŠƒo[ƒu OFF/ON	*/ /*(v2.80)*/
  char	ch_expr[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌEXPRSSION’l	*/ /*v2.92*/
  char	ch_modu[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌMODULATION’l	*/ /*v2.92*/
  char	ch_bank[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌBANK’l	*/ /*v2.92*/
  char	ch_gsrev[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌGS REVERB’l	*/ /*v2.93*/
  char	ch_gscho[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌGS CHORUS’l	*/ /*v2.93*/
  char	ch_hold1[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌHOLD1’l	*/ /*v2.93*/
  char	ch_gsdly[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌGS DELAY’l	*/ /*v3.00q*/
  char	ch_bankl[ CHL_NUM ];	/* ƒ`ƒƒƒlƒ‹–ˆ‚ÌGS BANK L.’l	*/ /*v3.01n*/

  char	dummyH[34*1];		/* Šg’£—pƒŠƒU[ƒu	*/
#endif
};
