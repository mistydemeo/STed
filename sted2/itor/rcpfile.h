/***********************/
/* define for RCP file */
/***********************/

#include "rcpstruct.h"

static struct RCPHEAD RCP_HEAD = {
/* mark */
0x52,0x43,0x4D,0x2D,0x50,0x43,0x39,0x38,0x56,0x32,0x2E,0x30,0x28,0x43,0x29,0x43,
0x4F,0x4D,0x45,0x20,0x4F,0x4E,0x20,0x4D,0x55,0x53,0x49,0x43,0x0D,0x0A,0x00,0x00,
/* title */
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
/* memo */
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
/* MIDI bus mode */
0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,
/* misc */
0x00,0x00,0x00,0x00,0x00,0x00,

/* CM6/GSD name */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/* RHYTHM */
0x48,0x61,0x6E,0x64,0x20,0x43,0x6C,0x61,0x70,0x20,0x20,0x20,0x20,0x20,0x27,0x01,
0x4D,0x74,0x20,0x48,0x69,0x43,0x6F,0x6E,0x67,0x61,0x20,0x20,0x20,0x20,0x3E,0x01,
0x48,0x69,0x67,0x68,0x20,0x43,0x6F,0x6E,0x67,0x61,0x20,0x20,0x20,0x20,0x3F,0x01,
0x4C,0x6F,0x77,0x20,0x43,0x6F,0x6E,0x67,0x61,0x20,0x20,0x20,0x20,0x20,0x40,0x01,
0x43,0x72,0x61,0x73,0x68,0x20,0x43,0x79,0x6D,0x20,0x20,0x20,0x20,0x20,0x31,0x01,
0x52,0x69,0x64,0x65,0x20,0x43,0x79,0x6D,0x20,0x20,0x20,0x20,0x20,0x20,0x33,0x01,
0x4F,0x70,0x65,0x6E,0x48,0x69,0x48,0x61,0x74,0x32,0x20,0x20,0x20,0x20,0x2C,0x01,
0x4F,0x70,0x65,0x6E,0x48,0x69,0x48,0x61,0x74,0x31,0x20,0x20,0x20,0x20,0x2E,0x01,
0x43,0x6C,0x73,0x64,0x20,0x48,0x69,0x48,0x61,0x74,0x20,0x20,0x20,0x20,0x2A,0x01,
0x41,0x63,0x6F,0x75,0x20,0x48,0x69,0x54,0x6F,0x6D,0x20,0x20,0x20,0x20,0x30,0x01,
0x41,0x63,0x6F,0x75,0x4D,0x69,0x64,0x54,0x6F,0x6D,0x20,0x20,0x20,0x20,0x2D,0x01,
0x41,0x63,0x6F,0x75,0x4C,0x6F,0x77,0x54,0x6F,0x6D,0x20,0x20,0x20,0x20,0x29,0x01,
0x52,0x69,0x6D,0x20,0x53,0x68,0x6F,0x74,0x20,0x20,0x20,0x20,0x20,0x20,0x25,0x01,
0x45,0x6C,0x65,0x63,0x20,0x53,0x44,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x28,0x01,
0x41,0x63,0x6F,0x75,0x20,0x53,0x44,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x26,0x01,
0x41,0x63,0x6F,0x75,0x20,0x42,0x44,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x24,0x01,
0x48,0x69,0x20,0x54,0x69,0x6D,0x62,0x61,0x6C,0x65,0x20,0x20,0x20,0x20,0x41,0x01,
0x4C,0x6F,0x77,0x54,0x69,0x6D,0x62,0x61,0x6C,0x65,0x20,0x20,0x20,0x20,0x42,0x01,
0x43,0x6F,0x77,0x62,0x65,0x6C,0x6C,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x38,0x01,
0x48,0x69,0x67,0x68,0x20,0x42,0x6F,0x6E,0x67,0x6F,0x20,0x20,0x20,0x20,0x3C,0x01,
0x4C,0x6F,0x77,0x20,0x42,0x6F,0x6E,0x67,0x6F,0x20,0x20,0x20,0x20,0x20,0x3D,0x01,
0x48,0x69,0x67,0x68,0x20,0x41,0x67,0x6F,0x67,0x6F,0x20,0x20,0x20,0x20,0x43,0x01,
0x4C,0x6F,0x77,0x20,0x41,0x67,0x6F,0x67,0x6F,0x20,0x20,0x20,0x20,0x20,0x44,0x01,
0x54,0x61,0x6D,0x62,0x6F,0x75,0x72,0x69,0x6E,0x65,0x20,0x20,0x20,0x20,0x36,0x01,
0x43,0x6C,0x61,0x76,0x65,0x73,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x4B,0x01,
0x4D,0x61,0x72,0x61,0x63,0x61,0x73,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x46,0x01,
0x53,0x6D,0x62,0x61,0x57,0x68,0x69,0x73,0x20,0x4C,0x20,0x20,0x20,0x20,0x48,0x01,
0x53,0x6D,0x62,0x61,0x57,0x68,0x69,0x73,0x20,0x53,0x20,0x20,0x20,0x20,0x47,0x01,
0x43,0x61,0x62,0x61,0x73,0x61,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x45,0x01,
0x51,0x75,0x69,0x6A,0x61,0x64,0x61,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x49,0x01,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x01,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x01,
/* Exclusive define */
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,
0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7 
};

static struct RCPTRACK TRACK = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20
};
