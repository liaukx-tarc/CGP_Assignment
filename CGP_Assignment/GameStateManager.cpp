#include "GameStateManager.h"
#include "TestLevel.h"

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
}

void GameStateManager::update()
{
	stateList[currentState]->update();
}

void GameStateManager::draw()
{
	stateList[currentState]->draw();
}