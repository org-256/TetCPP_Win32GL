
#include "common.h"
#include "windows.h"
#include "gl\gl.h"

extern HGLRC glrc;

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


void DrawRect(int x, int y, int w, int h, Color color );
void DrawBlock(int x, int y, Color color, int blockSize = BLOCK_SIZE);



#endif//__GRAPHICS_H__
