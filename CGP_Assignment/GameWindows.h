#ifndef GAMEWINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>

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

	//windows function
	void createWindows();
	bool windowsLoop();
};

#endif // !GAMEWINDOWS

