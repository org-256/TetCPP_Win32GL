
#include "Figures.h"

#ifndef __INFO_BAR_H__
#define __INFO_BAR_H__

class InfoBar
{
private:
public:
	
	InfoBar();
	~InfoBar();

	void CurrentFigure( Figure* figure );
	void NextFigure( Figure* next );
	void Draw();
	void Update( double delta );

};


#endif//__INFO_BAR_H__