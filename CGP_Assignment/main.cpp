#include "DirectInput.h"
#include "GameWindows.h"
#include "Graphic.h"
#include "GameStateManager.h"
#include "Spawner.h"
#include "Sprite.h"
#include "Tile.h"

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) //App only
int main()	//App and Console
{
	//create windows
	GameWindows::getInstance()->createWindows();
	Graphic::getInstance()->createGraphic();
	DirectInput::getInstance()->CreateInput();
	Sprite::getInstance()->createSprite();
	Tile::getInstance()->createTile();

	while (GameWindows::getInstance()->windowsLoop())
	{
		DirectInput::getInstance()->InputLoop();
		GameStateManager::getInstance()->update();
		Graphic::getInstance()->graphicLoop();
	}

	//delete the class and clear
	DirectInput::getInstance()->releaseInsrance();
	GameWindows::getInstance()->releaseInsrance();
	Graphic::getInstance()->releaseInsrance();
	GameStateManager::getInstance()->releaseInsrance();
	Sprite::getInstance()->releaseInsrance();
	Tile::getInstance()->releaseInsrance();
	Spawner::getInstance()->releaseInsrance();

	return 0;
}