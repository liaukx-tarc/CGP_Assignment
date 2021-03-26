#include "GameStateManager.h"
#include "GameWindows.h"

//Level
#include "../Level/TestLevel.h"
#include "../Level/MainMenu.h"

//singleton
GameStateManager* GameStateManager::sInstance = NULL;

GameStateManager* GameStateManager::getInstance()
{
	if (GameStateManager::sInstance == NULL)
	{
		sInstance = new GameStateManager;
	}

	return sInstance;
}

void GameStateManager::releaseInstance()
{
	delete sInstance;
	sInstance = NULL;
}

GameStateManager::GameStateManager()
{
	currentState = 0;
	preState = 0;

	isPause = false;

	g_Timer = new G_Timer();
	g_Timer->init(GAME_FPS);

	MainMenu* mainMenu = new MainMenu;
	mainMenu->init();
	stateList.push_back(mainMenu);

	TestLevel* testLevel = new TestLevel();
	stateList.push_back(testLevel);
}

GameStateManager::~GameStateManager()
{
	stateList[currentState]->release();

	for (int i = 0; i < stateList.size(); i++)
	{
		delete stateList[i];
		stateList[i] = NULL;
	}

	delete g_Timer;
}

void GameStateManager::update()
{
	//Pause Funtion
	if (currentState != 0) //Not Main Menu
	{
		if (GameWindows::getInstance()->keyIn == VK_ESCAPE)
		{
			isPause = !isPause;
		}
	}

	stateList[currentState]->update();

	framesToUpdate = g_Timer->framesToUpdate();

	for (int i = 0; i < framesToUpdate; i++)
	{
		stateList[currentState]->fixUpdate();
	}

	if (currentState != preState)
	{
		isPause = false;
		stateList[currentState]->init();
		stateList[preState]->release();
	}
}

void GameStateManager::draw()
{
	if (currentState == preState)
	{
		stateList[currentState]->draw();
	}

	else
	{
		preState = currentState;
	}
}

void GameStateManager::restart()
{
	stateList[currentState]->release();
	stateList[currentState]->init();
	isPause = false;
}
