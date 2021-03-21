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

void GameStateManager::releaseInsrance()
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
	testLevel->init();
	stateList.push_back(testLevel);
}

GameStateManager::~GameStateManager()
{
	for (int i = 0; i < stateList.size(); i++)
	{
		stateList[i]->release();
		delete stateList[i];
		stateList[i] = NULL;
	}

	delete g_Timer;
}

void GameStateManager::update()
{
	if (GameWindows::getInstance()->keyIn == VK_ESCAPE)
	{
		isPause = !isPause;
	}

	if (!isPause && currentState != 0)
	{
		stateList[currentState]->update();

		framesToUpdate = g_Timer->framesToUpdate();

		for (int i = 0; i < framesToUpdate; i++)
		{
			stateList[currentState]->fixUpdate();
		}
	}

	else
	{
		stateList[0]->update();

		framesToUpdate = g_Timer->framesToUpdate();

		for (int i = 0; i < framesToUpdate; i++)
		{
			stateList[0]->fixUpdate();
		}
	}
}

void GameStateManager::draw()
{
	stateList[currentState]->draw();
}