#include "common.h"
#include "graphics.h"

void DrawRect(int x, int y, int w, int h, Color color )
{
	glBegin(GL_QUADS);
	glColor4ub(color.r,color.g,color.b, color.a);
	glVertex2i(x,y);
	glVertex2i(x,y+h);
	glVertex2i(x+w,y+h);
	glVertex2i(x+w,y);
	glEnd();
}

void DrawBlock(int x, int y, Color color, int blockSize)
{
	DrawRect(x,y,blockSize, blockSize, color);
	
}
