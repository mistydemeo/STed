/************************/
/* Constant definitions */
/************************/

#define uchar unsigned char

#define Y_OFT	10
#define X_TRK	1
#define X_CH	4
#define X_BAR	6
#define X_STP	10
#define X_VEL	16
#define X_VOL	21
#define X_EXP	26
#define X_PAN	32
#define X_PBEND	36
#define X_PRG	42
#define	X_NAME	46
#define X_BANK	59
#define X_MODU	63
#define X_GSREV	69
#define X_GSCHO	75
#define X_GSDLY	81
#define X_MEMO	59
#define X_STS	78
#define X_TRBAR	85

/**************************/
/*  structure definitions */
/**************************/

/* MCP data */
struct MCPDATA {
  struct {
    char	mark[2];	/* 'M1' mark   */
    char	name[30];	/* Song Name   */
    char	tmbase;		/* Time base   */
    char	tempo;		/* Tempo       */
    char	rhythm0;	/* Rhythm 分子 */
    char	rhythm1;	/* Rhythm 分母 */
    char	volume;		/* Volume      */
    char	d1[27];		/*             */
    char	midich[9];	/* MIDI ch 1-R */
    char	d2[23];		/*             */
    char	mtdname[6];	/* MTD name    */
    char	mtdext[3];	/* MTD ext     */
    char	d3[7];		/*             */
    char	trname[9][16];	/* Track name  */
  } hd;
  char dt[1];
};

/* RCP data */
struct rset {
  char	name[14];	/* rhythm name */
  uchar	note;		/* note no     */
  uchar	gate;		/* gate        */
};

struct RCPDATA {
  struct {
    char 		mark[32];	/* COME ON ....*/
    char 		name[64];	/* Song Name   */
    char 		memo[12][28];	/* memorandam  */
    char 		x40[16];	/* 0x40 .......*/
    uchar 		tmbase;		/* Time base   */
    uchar 		tempo;		/* Tempo       */
    uchar 		rhythm0;	/* Rhythm 分子 */
    uchar 		rhythm1;	/* Rhythm 分母 */
    uchar 		key;		/* key         */
    uchar 		play_bias;	/* play bias   */
    char		cm6name[12];	/* CM6 name    */
    char		x00[4];		/* 0x00        */
    char		gsdname[12];	/* GSD name    */
    char		x00b[4];	/* 0x00        */
    uchar		trkmax;		/* track max   */
    uchar		tmbase_h;	/* Time base h */
    char		x00c[30];	/* 0x00        */
    struct rset	rhythm[32];	/* rhythm      */
    uchar		exclu[8][48];	/* 音源設定    */
  } hd;
  char dt[1];
};

struct track_head {
  uchar	sizel;		/* track size Low */
  uchar	sizeh;		/* track size High */
  uchar	trk;		/* track no. */
  uchar	rhythm_flag;	/* rhythm flag */
  uchar	channel;	/* channel no. */
  uchar	key;		/* key#+ */
  uchar	st;		/* st+ */
  uchar	mode;		/* mode */
  char	comment[36];	/* track comment */
};

/* G36 data *//* 未使用 */
struct G36DATA {
  struct {
    char 		mark[32];	/* COME ON ....*/
    char 		name[128];	/* Song Name   */
    char 		memo[12][30];	/* memorandam  */
    char		trkmax;		/* track max   */
    char 		x00[1];		/* 0x00 .......*/
    uchar 		tmbase;		/* Time base   */
    uchar		tmbase_h;	/* Time base h */
    uchar 		tempo;		/* Tempo       */
    uchar 		tempo_h;	/* Tempo       */
    uchar 		rhythm0;	/* Rhythm 分子 */
    uchar 		rhythm1;	/* Rhythm 分母 */
    uchar 		key;		/* key         */
    uchar 		play_bias;	/* play bias   */
    char 		x00b[6];	/* 0x00 .......*/
    char 		x40[16];	/* 0x40 .......*/
    char 		x00c[112];	/* 0x00 .......*/
    char		cm6name[12];	/* CM6 name    */
    char		x00d[4];	/* 0x00        */
    char		gsdname[12];	/* GSD name    */
    char		x00e[4];	/* 0x00        */
    char		gsdname2[12];	/* GSD name2   */
    char		x00f[4];	/* 0x00        */
    char		x00g[80];	/* 0x00        */
    struct rset	rhythm[128];	/* rhythm      */
    char		exclu[8][48];	/* 音源設定    */
  } hd;
  char dt[1];
};

struct G36track_head {
  uchar	sizel;		/* track size Low */
  uchar	sizeh;		/* track size High */
  uchar	sizeh2;		/* track size High2 */
  uchar	sizeh3;		/* track size High3 */
  uchar	trk;		/* track no. */
  uchar	rhythm_flag;	/* rhythm flag */
  uchar	channel;	/* channel no. */
  uchar	key;		/* key#+ */
  uchar	st;		/* st+ */
  uchar	mode;		/* mode */
  char	comment[36];	/* track comment */
};
