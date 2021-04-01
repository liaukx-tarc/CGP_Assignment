#include "GameStateManager.h"
#include "GameWindows.h"
#include "SoundManager.h"

//Level
#include "../Level/Level.h"
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

	level = 1;

	isPause = false;
	isStart = false;
	isMenu = false;
	timer = 0;

	g_Timer = new G_Timer();
	g_Timer->init(GAME_FPS);

	MainMenu* mainMenu = new MainMenu;
	mainMenu->init();
	stateList.push_back(mainMenu);

	Level* level = new Level();
	stateList.push_back(level);
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
	//control start screen display
	if (isStart)
	{
		if (!isMenu)
		{
			timer += 0.01;

			if (timer >= 1)
			{
				isStart = false;
				isPause = false;
				timer = 0;
			}
		}	
	}

	stateList[currentState]->update();

	framesToUpdate = g_Timer->framesToUpdate();

	if (currentState == preState)
	{
		for (int i = 0; i < framesToUpdate; i++)
		{
			stateList[currentState]->fixUpdate();
		}
	}
	
	else
	{
		SoundManager::getInstance()->bgm();
		if (currentState != 0)
		{
			nextLevel();
		}
		
		else
		{
			stateList[currentState]->init();
			stateList[preState]->release();
		}
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
	if (currentState > 0)
	{
		isStart = true;
	}

	SoundManager::getInstance()->bgm();
	stateList[currentState]->release();
	stateList[currentState]->init();
	isPause = false;
}

void GameStateManager::nextLevel()
{
	SoundManager::getInstance()->bgm();
	switch (level)
	{
	case 1:
		levelFileName = "data/Level1.txt";
		levelName = "Level 1";

		stateList[currentState]->init();
		stateList[preState]->release();
		break;

	case 2:
		levelFileName = "data/Level2.txt";
		levelName = "Level 2";

		restart();
		break;

	default:
		currentState = 0;
		level = 1;
		break;
	}

	isStart = true;
	isPause = true;
}