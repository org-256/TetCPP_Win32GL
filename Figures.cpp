#include "stdlib.h"
#include "Figures.h"
#include "graphics.h"

const pos2i Figure::src_blk[7][4]={	
	{ {  0,  0 } , {  0,  1 }, { -1,  0 } , { -1, -1 } },	// Z
	{ {  0,  0 } , {  0,  1 }, {  1,  0 } , {  1, -1 } },	// S
	{ {  0,  0 } , { -1,  0 }, {  1,  0 } , {  0, -1 } },	// T
	{ { -1, -1 } , {  0, -1 }, { -1,  0 } , {  0,  0 } },	// O	
	{ {  0,  0 } , {  0,  1 }, {  0, -1 } , {  0, -2 } },	// I
	{ {  0,  0 } , {  0, -1 }, {  0,  1 } , {  1,  1 } },	// L
	{ {  0,  0 } , {  0, -1 }, {  0,  1 } , { -1,  1 } },	// J	
};

Figure::Figure()
{
	pos.x = 2;
	pos.y = 2;

	Rand();
}

Figure::~Figure()
{


}


void Figure::Update( double delta )
{
	


}

void Figure::Draw(int xOffset, int yOffset)
{
	for(int i=0; i<4; i++)
	{
		DrawBlock( xOffset + pos.x*BLOCK_SIZE + blk[i].x*BLOCK_SIZE, yOffset + pos.y*BLOCK_SIZE+ blk[i].y*BLOCK_SIZE, defColors[figID+9]);
	}
}

void Figure::MoveDown()
{
	pos.y++;

}

void Figure::MoveUp()
{
	pos.y--;

}

void Figure::MoveLeft()
{
	pos.x--;

}

void Figure::MoveRight()
{
	pos.x++;

}

void Figure::TurnLeft()
{
	if(figID!=FIG_O)
	for (int i =0; i<4; i++)
	{
		blk[i].x = -blk[i].x;
		swap(blk[i].x, blk[i].y);
		
	}
}

void Figure::TurnRight()
{
	if(figID!=FIG_O)
	for (int i =0; i<4; i++)
	{
		blk[i].y = -blk[i].y;
		swap(blk[i].x, blk[i].y);
	}
}

void Figure::Rand()
{
	
	figID = rand()%7;

	for(int i=0;i<4;i++)
	{
		blk[i].x = src_blk[figID][i].x;
		blk[i].y = src_blk[figID][i].y;
	}

}

void Figure::SetPos(int x, int y)
{
	pos.x=x;
	pos.y=y;
}

void Figure::Set(Figs id)
{
	figID = id;
	for(int i=0;i<4;i++)
	{
		blk[i].x = src_blk[figID][i].x;
		blk[i].y = src_blk[figID][i].y;
	}
}


Figure Figure::operator= (const Figure& figure)
{
	this->figID = figure.figID;
	this->pos = figure.pos;
	for(int i=0; i<4; i++)
	{	
		this->blk[i]=figure.blk[i];
	}
	return *this;
}


