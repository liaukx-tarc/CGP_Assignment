#ifndef DIRECT_INPUT
#include <dinput.h>

class DirectInput
{
private:
	static DirectInput* sInstance;
	DirectInput();
	~DirectInput();

	HRESULT hr;

public:
	static DirectInput* getInstance();
	static void releaseInsrance();

	LPDIRECTINPUT8 dInput;

	LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
	BYTE  diKeys[256];

	LPDIRECTINPUTDEVICE8 dInputMouseDevice;
	DIMOUSESTATE mouseState;
	int mouseMoveX, mouseMoveY, mousePosX, mousePosY;
	int mouseButton[3];

	void CreateInput();
	void InputLoop();
};

#endif // !DIRECT_INPUT

