/* struct definition for RCP file */

#define uchar unsigned char

struct RCPHEAD {
	uchar mark[32];
	uchar title[64];
	uchar memo[336];
	uchar MIDI_busmode[16];
	uchar Timebase;
	uchar Tempo;
	uchar Beathigh;
	uchar Beatlow;
	uchar Key;
	uchar Playbias;
	uchar CM6name[16];
	uchar GSDname[16];
	uchar trkmax;
	uchar Timebaseh;
	uchar dumy[30];
	uchar Rhythm[32][16];
	uchar Exclusive[8][48];
};

struct RCPTRACK {
	uchar len_low;
	uchar len_high;
	uchar track_no;
	uchar rhythm_flag;
	uchar MIDI_CH;
	uchar Play_bias;
	uchar ST_offset;
	uchar Mode;
	uchar Memo[36];
/*	uchar note[65536]; */
};
