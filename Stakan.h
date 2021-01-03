#include "common.h"
#include "figures.h"

#ifndef	__STAKAN_H__
#define __STAKAN_H__

class Stakan
{
private:
	
	byte* pBuff;//blocks
	int _w;		//width
	int _h;		//height
	int	_ox;	//screen x offset 
	int _oy;	//screen y offset 

public:
	
	Stakan();
	Stakan(int sx, int sy);
	~Stakan();
	
	void SetSize(int width, int height);
	void Draw();
	void Update( double delta );
	void MapFigure(Figure& figure);
	void Clean();
	friend class Game;
	friend class Figure;
};

#endif//__STAKAN_H__