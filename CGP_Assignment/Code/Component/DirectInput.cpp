#include "DirectInput.h"
#include "GameWindows.h"
#include <stdio.h>

//singleton
DirectInput* DirectInput::sInstance = NULL;

DirectInput* DirectInput::getInstance()
{
	if (DirectInput::sInstance == NULL)
	{
		sInstance = new DirectInput;
	}

	return sInstance;
}

void DirectInput::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

DirectInput::DirectInput()
{
	hr = NULL;
	dInput = NULL;

	ZeroMemory(&diKeys, sizeof(diKeys));
	ZeroMemory(&mouseState, sizeof(mouseState));

	mouseMoveX = 0;
	mouseMoveY = 0;
	mousePosX = 0;
	mousePosY = 0;
}

DirectInput::~DirectInput()
{
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	dInput->Release();
	dInput = NULL;

	hr = NULL;
	ZeroMemory(&diKeys, sizeof(diKeys));
	ZeroMemory(&mouseState, sizeof(mouseState));
}

void DirectInput::CreateInput()
{
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//keyBoard
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//mouse
	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}

	dInputKeyboardDevice->SetCooperativeLevel(GameWindows::getInstance()->g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->SetCooperativeLevel(GameWindows::getInstance()->g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void DirectInput::InputLoop()
{
	hr = dInputKeyboardDevice->GetDeviceState(256, diKeys);
	hr = dInputMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);

	if (FAILED(hr))
	{
		dInputKeyboardDevice->Acquire();
		dInputMouseDevice->Acquire();
	}

	else
	{
		//mouse
		if (mouseState.rgbButtons[0] & 0x80 && mouseButton[0] == 0)
		{
			printf("Left press\n");
			mouseButton[0] = 1;
		}

		else if (mouseState.rgbButtons[0] & 0x80)
		{
			printf("Left drawing\n");
			mouseButton[0] = 2;
		}

		else if (!(mouseState.rgbButtons[0] & 0x80) && mouseButton[0] == 2)
		{
			printf("Left release\n\n");
			mouseButton[0] = 0;
		}

		mouseMoveX = mouseState.lX;
		mousePosX += mouseMoveX;
		mousePosX = max(mousePosX, 0);
		mousePosX = min(mousePosX, 1080);

		mouseMoveY = mouseState.lY;
		mousePosY += mouseMoveY;
		mousePosY = max(mousePosY, 0);
		mousePosY = min(mousePosY, 720);

		if (mouseMoveX != 0 || mouseMoveY != 0)
		{
			//printf("X-%d  Y-%d\n", mousePosX, mousePosY);
		}
	}
}