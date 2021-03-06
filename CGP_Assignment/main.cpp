#include "GameWindows.h"
#include "Graphic.h"
#include "DirectInput.h"
#include "GameStateManager.h"
#include "Tile.h"

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) //App only
int main()	//App and Console
{
	//create windows
	GameWindows::getInstance()->createWindows();
	Graphic::getInstance()->createGraphic();
	DirectInput::getInstance()->CreateInput();
	Tile::getInstance()->createTile();

	while (GameWindows::getInstance()->windowsLoop())
	{
		GameStateManager::getInstance()->update();
		Graphic::getInstance()->graphicLoop();
		DirectInput::getInstance()->InputLoop();
	}

	//delete the class and clear
	GameWindows::getInstance()->releaseInsrance();
	Graphic::getInstance()->releaseInsrance();
	DirectInput::getInstance()->releaseInsrance();
	GameStateManager::getInstance()->releaseInsrance();
	Tile::getInstance()->releaseInsrance();

	return 0;
}