/*--------------------------------------------------------------*/
/* rcddef.h							*/
/*--------------------------------------------------------------*/
/* RCD �ɥ饤�С����������ѹ�¤�����   RCD v3.01 �ʹ���	*/
/*--------------------------------------------------------------*/
/*								*/
/* RCD �����Ѥ���ץ����ϡ�					*/
/* 								*/
/* �ܥե�����򥤥󥯥롼�ɤ��Ʋ�������				*/
/* 								*/
/* extern struct RCD_HEAD *rcd;   <--- �ݥ��󥿤γ�������򤷡�	*/
/* 								*/
/* rcdcheck �򥳡��뤷�ƹ�¤�ΤΥ��ɥ쥹���᤿��ˡ�		*/
/* 								*/
/* rcd->fmt �ʤɤΤ褦�˥����������롣				*/
/* 								*/
/* �롼���󥳡���ϡ�(*rcd->begin)() �Τ褦�ˤ��롣		*/
/*								*/
/*--------------------------------------------------------------*/

#define	TRK_NUM	36			/* �ȥ�å���		*/
#define	CHL_NUM	34 			/* ����ͥ��		*/
					/*  32/33 ��̤����	*/

struct RCD_HEAD {
	char	title[4];		/* "RCD "		*/
	char	version[4];		/* "N.NN"		*/
	int	staymark;

	char	data_valid;		/* RCP/MCP ͭ���� 1	*/
	char	tone_valid;		/* CM6/MTD ͭ���� 1	*/
	char	word_valid;		/* WRD ͭ���� 1		*/
	char	fmt;			/* MCP:0 RCP:1 R36:2	*/

	char	*data_adr;		/* MCP/RCP address	*/
	char	*tone_adr;		/* MTD/CM6 address	*/
	char	*word_adr;		/* WRD address		*/
	char	*gsd_adr;		/* GSD address		*/ /*(v2.92)*/

	void	(*init)( void );	/* �ѥ�᡼�������	*/ /* void (v2.70)*/
	void	(*setup)( void );	/* �����ǡ����񤭹���	*/ /* void (v2.70)*/
	void	(*begin)( void );	/* ���ճ���		*/ /* void (v2.70)*/
	void	(*end)( void );		/* ���ս�λ		*/ /* void (v2.70)*/

	void	(*md_put)( char );	/* MIDI 1 byte ����	*/ /* void (v2.70)*/
	int	(*md_get)( void );	/* MIDI 1 byte ���ϡ�(-1)���Ϥʤ�*/ /*(v2.70)*/
	void	(*md_put2)( char );	/* MIDI 1 byte ����(dual)*/ /* void (v2.92)*/
	void	(*mix_out)( char * );	/* MIX OUT(buff adrs)end=$ff*/ /*(v3.01)*/

	int	act;			/* 1:������		*/
	int	sts;			/* 0:RUN 1:STOP 2:SEARCH 3:CUE	*/ /*(v2.70)*/
	int	tar_trk;		/* TARGET TRACK		*/
	int	tar_bar;		/* TARGET BAR		*/

	char	dummy1[ 18 ];

	int	tempo;			/* ���ߤΥƥ��		*/
	int	basetempo;		/* ���Υƥ��		*/

	int	totalcount;		/* ����ե�����Ĺ	*/
	char	filename[30];		/* ����ե�����̾	*/
	char	tonename[30];		/* �����ե�����̾	*/

	char	dummy2[ 72 ];

	int	bufcap;			/* �Хåե�����		*/  /*(v2.70)*/

	int	MIDI_avl;		/* MIDI ����ͭ��(trk.no)*/  /*(v2.80)*/
	unsigned char MIDI_req[16];	/* MIDI �����׵�Хåե�*/  /*(v2.80)*/
		/* (80) (ch) ...	:������ݼ*/
		/* (90) (ke) (ve)	:ɰĵ	*/  /*(v2.92)*/
		/* (b0) (xx) (xx)	:���۰���ݼ*/
		/* (c0) (xx) ...	:��۸�����ݼ�	*/
		/* (e0) (xx) (xx)	:�߯�����ް	*/
		/* (f0) (hh) (mm) (ll) (xx) :���ײ�	*/
		/* (f1) (hh) (mm) (ll) (xx) (id):���ײ�	*/  /*(v2.92)*/

	char	LA_VOL;			/* LA part master vol   */ /*(v2.80)*/
	char	LA_RVB_Mode;		/* LA part reverb Mode  */ /*(v2.80)*/
	char	LA_RVB_Time;		/* LA part reverb Time  */ /*(v2.80)*/
	char	LA_RVB_Level;		/* LA part reverb Level */ /*(v2.80)*/

	char	PCM_VOL;		/* PCM part master vol  */ /*(v2.80)*/
	char	PCM_RVB_Mode;		/* PCM part reverb Mode */ /*(v2.80)*/
	char	PCM_RVB_Time;		/* PCM part reverb Time */ /*(v2.80)*/
	char	PCM_RVB_Level;		/* PCM part reverb Level*/ /*(v2.80)*/

	int	filter_mode;		/* 0:̵�� 1:PRG�Τ� 2:LA/PCM���� */ /*(v2.90)*/
	char	*filter_data;		/* Filter Data���ɥ쥹	*/ /*(v2.90)*/

	int	play_mode;		/* 0:normal 1:slow 2:fast 3:slow2 4:fast2 */ /*(v2.92)*/
	int	mute_mode;		/* 0:off 1:cm64 2:sc55	*/ /*(v2.92)*/
	int	init_mode;		/* 0:off 1:cm64 2:sc55 3:cm+sc */ /*(v2.92)*/
	char	scan_mode;		/* key scan flag 0:off 1:on */
	char	rsmd_mode;		/* midi port flag 0:midi 1:midi+rs/sb 2:rs/sb */
	short	fade_time;		/* fade out speed	*/
	char	fade_count;		/* fade out start flag 128:start 0:end */
	char	moduletype;		/* panel display 0:cm64 1:sc55 2:cm+sc */
	char	fade_mode;		/* fade out mode 0:exclusive a:volume 2:expres*/
	char	timer_mode;		/* RS-MIDI timer mode 0:OPM Timer-A 1:OPM Timer-B */
	char	midi_clock;		/* MIDI clock out 0:disable 1:enable */
	char	put_mode;		/* md_put port mode 0:normal 1:midi 2:rs */
	char	rcd_type;		/* 0:midi+rs-232c 1:midi+polyphon 3:polyphon only */
	char	sc55_fix;		/* 0:off 1:sc55 capi.down emulate */ /*(v3.01)*/

	char	dummyA[19];		/* ��ĥ�ѥꥶ����	*/

	char	mt32_mode;		/* mt-32 mode		*/
	int	exc_wait;		/* exclusive send wait	*/
	char	tim_all;		/* timbre trans mode	*/

	char	gsd_valid;		/* GSD ͭ���� 1		*/  /*(v2.92)*/
	char	gsdname[30];		/* GSD�ե�����̾	*/

	int	wordcap;		/* word �Хåե�����	*/  /*(v2.92)*/

	char	dummyC[10];		/* ��ĥ�ѥꥶ����	*/

	char	GS_VOL;			/* GS part master vol   */ /*(v2.93)*/
	char	GS_PAN;			/* GS part master pan   */ /*(v2.93)*/

	char	GS_RVB_Macro;		/* ��С��֥ޥ���	*/ /*(v2.93)*/
	char	GS_RVB_Char;		/* ��С��֡�����饯����������ȥ���*/
	char	GS_RVB_Prelpf;		/* ��С��֡��Уңš��̣Уơ�����ȥ���*/
	char	GS_RVB_Level;		/* ��С��֡���٥롦����ȥ���*/
	char	GS_RVB_Time;		/* ��С��֡������ࡦ����ȥ���*/
	char	GS_RVB_Delay;		/* ��С��֡�DELAY��FEEDBACK������ȥ���*/
	char	GS_RVB_Send;		/* REVERB SEND LEVEL TO CHOURUS */
	char	GS_RVB_PreDelay;	/* REVERB PREDLY T. */

	char	GS_CHO_Macro;		/* �����饹�ޥ���	*/
	char	GS_CHO_Prelpf;		/* �����饹���Уңš��̣Уơ�����ȥ���*/
	char	GS_CHO_Level;		/* �����饹����٥롦����ȥ���*/
	char	GS_CHO_Feed;		/* �����饹���ե����ɡ��Хå�*/
	char	GS_CHO_Delay;		/* �����饹���ģ����������ȥ���*/
	char	GS_CHO_Rate;		/* �����饹���ң���塦����ȥ���*/
	char	GS_CHO_Depth;		/* �����饹���ģ����衦����ȥ���*/
	char	GS_CHO_Send;		/* CHORUS SEND LEVEL TO REVERB */
	char	GS_CHO_Send_Dly;

	char	GS_DLY_Macro;		/* �ǥ��쥤�ޥ���	*/ /*(v3.01)*/
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

	char	dummyD[32-16];		/* ��ĥ�ѥꥶ����	*/

	char	active[ TRK_NUM ];	/* �ȥ�å�ͭ��		*/
	char	trk_mask[ TRK_NUM ];	/* TRACK MASK		*/
	char	midich[ TRK_NUM ];	/* MIDI CH		*/

	int	noteptr;		/* ɰ����ݸ��߲��	*/
	unsigned char	*note_adr;	/* ɰ����ݸ��ޯ̧����*/
	char	*top[ TRK_NUM ];	/* �ȥ�å��ǡ�����Ƭ	*/
	unsigned char *ptr[ TRK_NUM ];	/* �����ׯ��߲�*/

	char	flg_vel[ TRK_NUM ];	/* VELOCITY ON �׸�	*/
	char	flg_off[ TRK_NUM ];	/* VELOCITY OFF �׸�	*/
	char	flg_act;		/* ACTIVE OFF �׸�	*/
	char	flg_bar;		/* BAR �ѹ� �׸�	*/
	char	flg_step;		/* STEP �ѹ� �׸�	*/
	char	flg_pbend;		/* PITCH BEND �ѹ� �׸�	*/
	char	flg_vol;		/* VOLUME �ѹ� �׸�	*/
	char	flg_prg;		/* PROGRAM �ѹ����׸�	*/
	char	flg_panpot;		/* PANPOT �ѹ� �׸�	*/
	char	flg_midich;		/* MIDI CH �ѹ� �׸�	*/

	char	flg_song;		/* SONG �ް� �׸�	*/
	char	flg_system;		/* SYSTEM ��X�׸�	*/ /*(v2.80)*/

	char	flg_expres;		/* EXPRESSION �ѹ� �׸�	*/
	char	flg_modula;		/* MODULATION �ѹ� �׸�	*/
	char	flg_bank;		/* BANK �ѹ� �׸�	*/
	char	flg_replay;		/* REPLAY �׸�		*/

	char	flg_gssys;		/* GS SYSTEM ��X�׸�*/ /*(v2.93)*/
	char	flg_gsrev;		/* GSREV �ѹ� �׸�	*/ /*(v2.93)*/
	char	flg_gscho;		/* GSCHO �ѹ� �׸�	*/ /*(v2.93)*/
	char	flg_gsinfo;		/* GS info �ѹ� �׸�	*/ /*(v2.93l)*/
	char	flg_gsinst;		/* GS inst �ѹ� �׸�	*/ /*(v2.93l)*/
	char	flg_gspanel;		/* GS panel �ѹ� �׸�	*/ /*(v2.93l)*/

	char	flg_hold1;		/* HOLD1 �ѹ� �׸�	*/
	char	flg_gsdly;		/* GSDLY �ѹ� �׸�	*/ /*(v3.00q)*/
	char	flg_bankl;		/* BANK L�ѹ� �׸�	*/ /*(v3.01n)*/

	char	dummyE[9];		/* ��ĥ�ѥꥶ����	*/

	int	panel_tempo;		/* �ѥͥ��Υƥ����	*/
	int	bar[ TRK_NUM ];		/* �����ֹ�		*/
	int	step[ TRK_NUM ];	/* ���ƥå��ֹ�		*/
	char	vel[ TRK_NUM ];		/* �٥��ƥ���		*/

	int	stepcount;		/* ���ճ��ϻ������STEP COUNT	*/ /*(v2.92)*/
	short	loopcount;		/* 255/256���ԡ��Ȥ�COUNT	*/ /*(v3.00f)*/

	char	dummyF[12-2];		/* ��ĥ�ѥꥶ����	*/

	char	song[20];		/* SONG�ǡ���(������)	*/
	char	dummyG[60];		/* ��ĥ�ѥꥶ����	*/

	char	gs_info[18];		/* gs patch name	*/ /*v2.93l*/
	char	gs_inst[34];		/* gs comment		*/ /*v2.93l*/
	char	gs_panel[64];		/* gs panel		*/ /*v2.93l*/

	char	ch_port[ CHL_NUM ];	/* �������i.f.���� 1:MIDI 2:RS-232C/POLYPHON */
	char	ch_part[ CHL_NUM ];	/* ������β������� 0:LA 1:PCM 2:¾(RHYTHM) */
	int	ch_pbend[ CHL_NUM ];	/* �������PITCH BEND��	*/
	char	ch_vol[ CHL_NUM ];	/* �������VOLUME��	*/
	char	ch_panpot[ CHL_NUM ];	/* �������PANPOT��	*/
	char	flg_ch_prg[ CHL_NUM ];	/* �������PROG.CHG�ե饰*/ /*v2.93j*/
	unsigned char ch_prg[ CHL_NUM ];/* �������PROGRAM�ֹ�	*/
	char	ch_reverb[ CHL_NUM ];	/* ��С��� OFF/ON	*/ /*(v2.80)*/
	char	ch_expr[ CHL_NUM ];	/* �������EXPRSSION��	*/ /*v2.92*/
	char	ch_modu[ CHL_NUM ];	/* �������MODULATION��	*/ /*v2.92*/
	char	ch_bank[ CHL_NUM ];	/* �������BANK��	*/ /*v2.92*/
	char	ch_gsrev[ CHL_NUM ];	/* �������GS REVERB��	*/ /*v2.93*/
	char	ch_gscho[ CHL_NUM ];	/* �������GS CHORUS��	*/ /*v2.93*/
	char	ch_hold1[ CHL_NUM ];	/* �������HOLD1��	*/ /*v2.93*/
	char	ch_gsdly[ CHL_NUM ];	/* �������GS DELAY��	*/ /*v3.00q*/
	char	ch_bankl[ CHL_NUM ];	/* �������GS BANK L.��	*/ /*v3.01n*/

	char	dummyH[34*1];		/* ��ĥ�ѥꥶ����	*/
};
