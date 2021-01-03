#include "windows.h"
#include "gl\gl.h"

#ifndef	__COMMON_H__
#define __COMMON_H__

#define BLOCK_SIZE 18

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;

typedef byte KeyState;

typedef struct __pos2d
{
	double x,y;
}pos2d, *LPPOS2D;

typedef struct __pos2f
{
	float x,y;
}pos2f, *LPPOS2F;

typedef struct __pos2i
{
	int x,y;
}pos2i, *LPPOS2I;

template < class T >
void swap( T &a, T &b)
{
	T c = a;
	a = b;
	b = c;
}

typedef struct __Color
{
	union{
		struct  
		{
			byte r,g,b,a;
		};
		byte C[4];
	};	
}Color, *LPCOLOR;

enum e_defColors { C_BLACK, C_DKBLUE, C_DKGREEN, C_DRCYAN, C_DKRED, C_DKMAGENTA, C_DKYELLOW, C_GRAY, 
				C_DKGRAY,	 C_BLUE, C_GREEN, C_CYAN, C_RED, C_MAGENTA, C_YELLOW, C_WHITE, C_BROWN };

const Color defColors[17]=
{
	{ 0x00, 0x00, 0x00, 0xFF },	//C_BLACK
	{ 0x00, 0x00, 0x80, 0xFF },	//C_DKBLUE
	{ 0x00, 0x80, 0x00, 0xFF },	//C_DKGREEN
	{ 0x00, 0x80, 0x80, 0xFF },	//C_DKCYAN
	{ 0x80, 0x00, 0x00, 0xFF },	//C_DKRED
	{ 0x80, 0x00, 0x80, 0xFF },	//C_DKMAGENTA
	{ 0x80, 0x80, 0x00, 0xFF },	//C_DKYELLOW
	{ 0x80, 0x80, 0x80, 0xFF },	//C_GRAY
	{ 0x40, 0x40, 0x40, 0xFF },	//C_DKGRAY
	{ 0x00, 0x00, 0xFF, 0xFF },	//C_BLUE
	{ 0x00, 0xFF, 0x00, 0xFF },	//C_GREEN
	{ 0x00, 0xFF, 0xFF, 0xFF },	//C_CYAN
	{ 0xFF, 0x00, 0x00, 0xFF },	//C_RED
	{ 0xFF, 0x00, 0xFF, 0xFF },	//C_MAGENTA
	{ 0xFF, 0xFF, 0x00, 0xFF },	//C_YELLOW
	{ 0xFF, 0xFF, 0xFF, 0xFF },	//C_WHITE
	{ 0x10, 0x05, 0x00, 0xFF }	//C_BROWN
};

#endif//__COMMON_H__