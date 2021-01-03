#include "graphics.h"
#include "windows.h"
#include "windowsx.h"

#include "gl\gl.h"

#include "game.h"

long __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
const char* lpszClassName = "TetriZZZ";
const int WIDTH = 384;
const int HEIGHT = 512;
HGLRC glrc;

KeyState keys[256];

void InitGL(HDC dc)
{
	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd,0,sizeof(pfd));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.cAlphaBits = 8;	
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;
	pfd.cStencilBits = 8;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
	pfd.iPixelType = PFD_TYPE_RGBA;
	
	int pf = ChoosePixelFormat(dc,&pfd);
	SetPixelFormat(dc,pf,&pfd);
	
	glrc = wglCreateContext(dc);
    wglMakeCurrent(dc,glrc);

	glEnable(GL_COLOR);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	
	glDepthRange(-1200,1200);
	
	glClearColor(.5f,.3f,.7f,0);

}
void InitGLView(int W, int H)
{
	glViewport(0,-28,W,H);
    glMatrixMode(GL_PROJECTION);
	
    glLoadIdentity();
	//	glScaled(1,-1,-1);
    glScaled(1,-1,1);
    //glOrtho(-320,320,-240,240,1200,-1200);
	glOrtho(0,W,0,H,-1,1200);
    //glFrustum(-320,320,-240,240,1200,-1200);
	
	
	glMatrixMode(GL_TEXTURE);    
	glLoadIdentity();
    
	
    glMatrixMode(GL_MODELVIEW);

}
void KillGL()
{
	wglDeleteContext(glrc);	
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = lpszClassName;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);

	int sx = GetSystemMetrics(SM_CXSCREEN);
	int sy = GetSystemMetrics(SM_CYSCREEN);

	HWND hWnd = CreateWindowEx(	WS_EX_OVERLAPPEDWINDOW, lpszClassName,"TetriZzZz...",
								WS_SYSMENU | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
								sx/2-WIDTH/2,sy/2-HEIGHT/2,WIDTH,HEIGHT,
								NULL,NULL,NULL,0);
	UpdateWindow(hWnd);
	ShowWindow(hWnd, SW_SHOW );
	MSG msg;
	HDC gdc;
	InitGL(gdc=GetDC(hWnd));
	InitGLView(384,512);

	Game* game = new Game();
	
	game->New();
	game->Start();

	while(game->isRunning())
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if( msg.message == WM_QUIT )
				break;
		}	
		else
		{	

			game->ProcessInput(keys);
			game->Update();
			
			//glClearColor(1,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);

			game->Draw();	
			char buff[120];
			sprintf(buff,"TetriZZZ... Level: %d  Lines: %d  Score: %d   ", game->GetLevel(), game->GetLines(), game->GetScore());
			SetWindowText(hWnd,buff);
			//DrawRect(0,0,132,32,defColors[C_YELLOW]);

			SwapBuffers(gdc);
		}

	}

	delete game;
	KillGL();
	return 0;
}

long __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			GetKeyboardState(keys);
			break;
		default: return DefWindowProc(hWnd,msg,wp,lp);

	}	
	return 0;
}