
#include "common.h"

#ifndef __FIGURES_H__
#define __FIGURES_H__

enum Figs { FIG_Z, FIG_S, FIG_T, FIG_O, FIG_I, FIG_L, FIG_J};

class Figure
{
private:
	
	pos2i	pos;
	pos2i	blk[4];
	static	const pos2i src_blk[7][4];
	byte	figID;


public:
	Figure();
	virtual ~Figure();

	void Draw(int xOffset, int yOffset);
	void Update( double delta );
	
	void TurnLeft();
	void TurnRight();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void MoveUp();
	void SetPos(int x, int y);

	void Set(Figs id);
	void Rand();

	friend class Stakan;
	friend class Game;

	Figure operator= (const Figure& figure);

};	



#endif//__FIGURES_H__