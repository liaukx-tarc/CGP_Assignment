#include "GameWindows.h"
#include "Graphic.h"
#include "../resource.h"

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

	keyIn = 0;
	ZeroMemory(&mousePos, sizeof(mousePos));
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

	case WM_KEYDOWN:
		GameWindows::getInstance()->keyIn = wParam;
		break;

	case WM_MOUSEMOVE:
		GameWindows::getInstance()->mousePos.x = LOWORD(lParam) * BUFFER_WIDTH / WINDOWS_WIDTH;
		GameWindows::getInstance()->mousePos.y = HIWORD(lParam) * BUFFER_HEIGHT / WINDOWS_HEIGHT;
		GameWindows::getInstance()->mousePos.x = min(GameWindows::getInstance()->mousePos.x, 1920);
		GameWindows::getInstance()->mousePos.y = min(GameWindows::getInstance()->mousePos.y, 1080);
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

	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, APP_NAME, WS_OVERLAPPEDWINDOW, 100, 50, WINDOWS_WIDTH + 17, WINDOWS_HEIGHT + 40, NULL, NULL, hInstance, NULL);
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