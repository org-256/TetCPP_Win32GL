
#include "windows.h"
#include "Timer.h"
#include "Stakan.h"
#include "Figures.h"
#include "ScoreBar.h"
#include "InfoBar.h"
#include <list>
using namespace std;


#ifndef	__GAME_H__
#define __GAME_H__

#define DEF_KEY_TIME 0.0625

class Game
{
private:
	bool running;
	list <pos2d> dbgLines;

	Stakan stakan;
	ScoreBar scoreBar;
	InfoBar infoBar;

	int score;
	int lines;

	Timer keyTimer;
	Timer timer;
	Figure current;
	Figure next;
	double	beforeFall;

	bool Collision(Figure&, Stakan&);
	bool isFresh;
	bool isGameOver;
	bool isFastDrop;

	void SlideLeft(Figure& figure, Stakan &stakan);
	void SlideRight(Figure& figure, Stakan &stakan);
	

public:
	
	Game();
	~Game();

	void New();
	void Start();
	void Pause();
	void Resume();

	void Draw();
	void Update();
	void ProcessInput(KeyState *keys);
	bool isRunning();
	void Quit();

	bool TryMoveLeft(Figure &figure, Stakan& stakan);
	bool TryMoveRight(Figure &figure, Stakan& stakan);
	bool TryMoveDown(Figure &figure, Stakan& stakan);
	bool TryTurnLeft(Figure &figure, Stakan& stakan);
	bool TryTurnRight(Figure &figure, Stakan& stakan);	
	void NextFigure();
	void CheckLines();
	double GenDifficulty();
	int GetLevel();
	int GetLines();
	int GetScore();
};


#endif//__GAME_H__