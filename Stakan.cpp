
#include "common.h"
#include "Graphics.h"
#include "Stakan.h"



Stakan::Stakan()
{
	_ox = _oy = 12;
	_w = 12;
	_h = 25;

	pBuff = new byte [ _w*_h];
	
	Clean();
			
}

void Stakan::Clean()
{
	memset(pBuff,0,_w*_h*sizeof(byte));
}

Stakan::~Stakan()
{
	delete pBuff;

}


void Stakan::SetSize(int width, int height)
{
	if( width!=_w && height!=_h)
	{
		_w = width;
		_h = height;
		delete(pBuff);
		pBuff = new byte [_w*_h];
		
		realloc(pBuff,_w*_h*sizeof(byte));

	}
	
	
}

void Stakan::Draw()
{
	for(int y=0; y<_h; y++)
		for(int x=0; x<_w; x++)
		{
			byte c = pBuff[y*_w+x];
				
				DrawBlock(_ox + x*BLOCK_SIZE, _oy + y*BLOCK_SIZE, defColors[c]);
			if(c==0)
				DrawBlock(_ox + 4 + x*BLOCK_SIZE, _oy + y*BLOCK_SIZE + 4, defColors[C_BROWN], BLOCK_SIZE - 8);
		}

}

void Stakan::Update( double delta )
{


}

void Stakan::MapFigure(Figure& figure)
{
	for(int i=0; i<4 ;i++)
	{
		int x = figure.pos.x + figure.blk[i].x;
		int y = figure.pos.y + figure.blk[i].y;
		
	//	if((x<0)||(x>=(_w))||(y<0)||(y>=(_h)))
	//		continue;
		
		pBuff[y*_w + x] = figure.figID+1;
	}
}