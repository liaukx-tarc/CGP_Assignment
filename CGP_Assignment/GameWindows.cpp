#include "GameWindows.h"
#include "resource.h"

//Constant Variable
#define APP_NAME "Tower Defense"
#define WINDOWS_HIGH 720
#define WINDOWS_WIDTH 1280

//Singleton
GameWindows* GameWindows::sInstance = NULL;

GameWindows* GameWindows::getInstance()
{
	if (GameWindows::sInstance == NULL)
	{
		sInstance = new GameWindows;
	}

	return sInstance;
}

void GameWindows::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

GameWindows::GameWindows()
{
	g_hWnd = NULL;
	hInstance = GetModuleHandle(NULL);
	ZeroMemory(&wndClass, sizeof(wndClass));
}

GameWindows::~GameWindows()
{
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

//Input message
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void GameWindows::createWindows()
{
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//App Name
	wndClass.lpszClassName = APP_NAME; //APP_NAME is a constant variable at define

	//App Cursor
	wndClass.hCursor = LoadCursorFromFile("resource/Arrow.ani");

	//App Icon
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTATOM(IDI_ICON1));

	RegisterClass(&wndClass);

	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, APP_NAME, WS_OVERLAPPEDWINDOW, 100, 50, WINDOWS_WIDTH, WINDOWS_HIGH, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);
}

bool GameWindows::windowsLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) break;

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

	return msg.message != WM_QUIT;
}