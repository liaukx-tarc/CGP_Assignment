#include "GameWindows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) //App only
//int main()	//App and Console
{
	//create windows
	GameWindows::getInstance()->createWindows();

	//check any create function is correct or not
	if (NULL /*call create function*/)
	{
		return 0;
	}

	while (GameWindows::getInstance()->windowsLoop())
	{

	}

	//delete the class and clear
	GameWindows::getInstance()->releaseInsrance();

	return 0;
}