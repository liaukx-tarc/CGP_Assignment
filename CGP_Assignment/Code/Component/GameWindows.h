#ifndef GAMEWINDOWS
#define GAMEWINDOWS
#define WIN32_LEAN_AND_MEAN

#include <d3dx9.h>
#include <Windows.h>
#include <stdio.h>

//Constant Variable
#define APP_NAME "Tower Defense"
#define WINDOWS_HEIGHT 720
#define WINDOWS_WIDTH 1280

class GameWindows
{
private:
	//Singleton
	static GameWindows * sInstance;
	GameWindows();
	~GameWindows();

public:
	//Singleton
	static GameWindows * getInstance();
	static void releaseInstance();

	//windows variable
	HWND g_hWnd;
	WNDCLASS wndClass;
	HINSTANCE hInstance;

	int keyIn;
	D3DXVECTOR2 mousePos;

	//windows function
	void createWindows();
	bool windowsLoop();
};

#endif // !GAMEWINDOWS

