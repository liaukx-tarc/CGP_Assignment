#include "../Code/Component/DirectInput.h"
#include "../Code/Component/GameWindows.h"
#include "../Code/Component/Graphic.h"
#include "../Code/Component/GameStateManager.h"
#include "../Code/Component/Map.h"

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) //App only
int main()	//App and Console
{
	//create windows
	GameWindows::getInstance()->createWindows();
	Graphic::getInstance()->createGraphic();
	DirectInput::getInstance()->CreateInput();

	while (GameWindows::getInstance()->windowsLoop())
	{
		DirectInput::getInstance()->InputLoop();
		GameStateManager::getInstance()->update();
		Graphic::getInstance()->graphicLoop();

		GameWindows::getInstance()->keyIn = 0;
	}

	//delete the class and clear
	DirectInput::getInstance()->releaseInstance();
	GameWindows::getInstance()->releaseInstance();
	Graphic::getInstance()->releaseInstance();
	GameStateManager::getInstance()->releaseInstance();

	return 0;
}