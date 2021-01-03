
#include "common.h"
#include "game.h"
#include "Graphics.h"

#define DEF_BEFORE_FALL 1


Game::Game()
{
	timer.Init();
	timer.Start();

	keyTimer.Init();
	keyTimer.Start();

	running = true;
	srand(timer.GetTicks());

	isFresh = true;
	isGameOver = false;
	New();
}

Game::~Game()
{
	
}

void Game::New()
{
	isGameOver = false;
	isFastDrop = false;
	current.Rand();
	current.pos.y = 2;
	current.pos.x = stakan._w/2;
	next.pos.y = 2;
	next.pos.x = stakan._w/2;
	next.Rand();

	beforeFall = GenDifficulty();

	stakan.Clean();
	score = 0;
	lines = 0;
	keyTimer.SetWatch(DEF_KEY_TIME);
}

void Game::Start()
{


}

void Game::Pause()
{


}

void Game::Resume()
{


}

void Game::Draw()
{
	

	stakan.Draw();
	

	infoBar.Draw();
	

	scoreBar.Draw();
	

	
	
	if(isGameOver)
	{
		Color red;
		red.r = 0x80;
		red.g = 0x80;
		red.b = 0x40;
		red.a = 0x80;
		
		DrawRect(stakan._ox, stakan._oy,stakan._ox+(stakan._w-1)*BLOCK_SIZE, stakan._oy+(stakan._h-1)*BLOCK_SIZE, red);
		
		return;
	}
	
	current.Draw(stakan._ox, stakan._oy);
	
	//	draw figure shadow
	int l=0, r=0;
	for(int i = 0; i<4; i++)
	{
		if(current.blk[i].x<l)
			l = current.blk[i].x;
		if(current.blk[i].x>r)
			r = current.blk[i].x;
	}
	int x = stakan._ox + (current.pos.x + l)*BLOCK_SIZE;
	int y = stakan._oy + (stakan._h) * BLOCK_SIZE;

	DrawRect(x, y+BLOCK_SIZE/4, (r-l+1)*BLOCK_SIZE, BLOCK_SIZE/1.6, defColors[C_YELLOW]);
}
#define VK_PRESSED (1<<7)

bool KeyPressed(byte* keys, byte key)
{
	return (keys[key]>>7)?true:false;
}

void Game::ProcessInput(KeyState *keys)
{	
	if(!keyTimer.Watch())
		return;

	keyTimer.SetWatch(DEF_KEY_TIME);
	

	if(KeyPressed(keys, VK_ESCAPE))
		Quit();
	
	if(!isGameOver)
	{
		
		if(KeyPressed(keys, VK_LEFT))
		{
			if(isFastDrop)
			{
				isFastDrop = false;
				beforeFall = GenDifficulty();
			}
				

			if(KeyPressed(keys,VK_CONTROL))
				SlideLeft(current,stakan);
			else
				TryMoveLeft(current,stakan);
		}

		if(KeyPressed(keys, VK_RIGHT))
		{
			if(isFastDrop)
			{
				isFastDrop = false;
				beforeFall = GenDifficulty();
			}

			if(KeyPressed(keys,VK_CONTROL))
				SlideRight(current,stakan);
			else		
				TryMoveRight(current,stakan);
		}

		if(KeyPressed(keys, VK_UP))	
			TryTurnLeft(current,stakan);
		
		if(KeyPressed(keys, VK_DOWN))	
		{		
			isFastDrop = true;
			beforeFall = GenDifficulty();
		}
	}
			
		
	if(KeyPressed(keys, VK_F2))	
		New();
	
	for(int i=0;i<255;i++)
			keys[i]=0;

}

void Game::Update()
{
	if(isGameOver)
		return;

	double delta = timer.NewDelta();
	
	stakan.Update(delta);
	
	infoBar.Update(delta);
	
	scoreBar.Update(delta);
	
	current.Update(delta);
	
	next.Update(delta);
	
	beforeFall-=delta;	
	if(beforeFall<=0)
	{
		beforeFall = GenDifficulty();
		TryMoveDown(current, stakan);
	}


}

bool Game::isRunning()
{
	return running;
}

void Game::Quit()
{
	running = false;
}

bool Game::Collision(Figure& figure, Stakan& stakan)
{
	for(int i=0; i<4 ;i++)
	{
		int x = figure.pos.x + figure.blk[i].x;
		int y = figure.pos.y + figure.blk[i].y;

		if((x<0)||(x>=(stakan._w))||(y<0)||(y>=(stakan._h)))
			return true;
		if( stakan.pBuff[ y * stakan._w + x] !=0 )
			return true;
	}
return false;
}

bool Game::TryMoveLeft(Figure &figure, Stakan &stakan)
{
	figure.MoveLeft();
	
	if(Collision(figure, stakan))
	{
		figure.MoveRight();
		return false;
	}
	return true;
}

bool Game::TryMoveRight(Figure &figure, Stakan &stakan)
{
	figure.MoveRight();
	
	if(Collision(figure, stakan))
	{
		figure.MoveLeft();
		return false;
	}
	return true;
}
	

bool Game::TryMoveDown(Figure &figure, Stakan &stakan)
{
	figure.MoveDown();

	if(Collision(figure, stakan))
	{
		if(isFresh)
		{
			isGameOver = true;
			figure.MoveUp();
			stakan.MapFigure(figure);
			return false;
		}

		figure.MoveUp();
		stakan.MapFigure(figure);
		
		//next Figure
		current = Figure(next);
		current.pos.y=2;
		next.Rand();
		isFresh = true;
		

		CheckLines();

		beforeFall = GenDifficulty();
		isFastDrop = false;
		return false;
	}
	beforeFall = GenDifficulty();
	isFresh = false;

	return true;
}

bool Game::TryTurnRight(Figure& figure, Stakan &stakan)
{
	figure.TurnRight();
	if(Collision(figure,stakan))
	{
		figure.TurnLeft();
		return false;
	}
	return true;
}

bool Game::TryTurnLeft(Figure& figure, Stakan &stakan)
{
	figure.TurnLeft();
	if(Collision(figure,stakan))
	{
		figure.TurnRight();
		return false;
	}
	return true;
}


void Game::CheckLines()
{
	int li = 0;
	int nlines[4]={0,0,0,0};
	int top = 0;

	byte *p = stakan.pBuff;

	for(int y=0; y<stakan._h; y++)
	{
		int x = 0;
		while(x<stakan._w)
		{
			if( p[y*stakan._w + x]==0) 
				break;
			

			if(x==(stakan._w-1))
			{
				nlines[li]=y;
				li++;		
			}
			
			x++;
		}
			
	}
	
	switch(li)
	{
		case 1:
			score+=5;
			break;
		case 2:
			score+=10;
			break;
		case 3:
			score+=20;
			break;
		case 4:
			score+=50;
			break;
		default:
			return;
	};

	lines+=li;	

	for(int i =0; i<li; i++)
	{
		for( int y = nlines[i]; y>1; y--)
			for(int x=0; x< stakan._w; x++)
			{
				p[y*stakan._w+x] = p[(y-1)*stakan._w+x];
				p[(y-1)*stakan._w+x] = 0;
			}
	}
}

double Game::GenDifficulty()
{
	double diff = DEF_BEFORE_FALL * ( 1 / GetLevel() );
	if(isFastDrop)
		diff = .0125;
return diff;
}

int Game::GetLevel()
{	
	if (score < 1000)
		return 1;
	return score/1000;
}

int Game::GetScore()
{
	return score;
}

int Game::GetLines()
{
	return lines;
}


void Game::SlideLeft(Figure& figure, Stakan &stakan)
{
	while(TryMoveLeft(figure,stakan)){};
		
}

void Game::SlideRight(Figure& figure, Stakan &stakan)
{
	while(TryMoveRight(figure,stakan)){};
	
}
