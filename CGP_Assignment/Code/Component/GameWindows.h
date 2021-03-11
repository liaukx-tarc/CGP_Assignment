#ifndef GAMEWINDOWS
#define GAMEWINDOWS
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdio.h>

//Constant Variable
#define APP_NAME "Tower Defense"
#define WINDOWS_HIGH 720
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
	static void releaseInsrance();

	//windows variable
	HWND g_hWnd;
	WNDCLASS wndClass;
	HINSTANCE hInstance;

	int keyIn;

	//windows function
	void createWindows();
	bool windowsLoop();
};

#endif // !GAMEWINDOWS

