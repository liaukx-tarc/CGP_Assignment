#include "TestLevel.h"
#include "../Component/Map.h"
#include "../Component/DirectInput.h"
#include "../Component/EnemyController.h"
#include "../Component/TowerBuilding.h"
#include "../Component/GameWindows.h"
#include "../Component/GameStateManager.h"
#include "../Component/UI.h"

TestLevel::TestLevel()
{
	
}

TestLevel::~TestLevel()
{
	delete levelFile;
}

Ui * ui;

void TestLevel::init()
{
	//load map
	std::string name = "data/Test_Level.txt";

	levelFile = new char[name.size() + 1];
	std::copy(name.begin(), name.end(), levelFile);
	levelFile[name.size()] = '\0';

	Map::getInstance()->createMap();
	Map::getInstance()->loadMap(levelFile);
	
	EnemyController::getInstance()->init();

	TowerBuilding::getInstance()->init();

	ui = new Ui;
	ui->init();
}

void TestLevel::fixUpdate()
{
	if (!GameStateManager::getInstance()->isPause)
	{
		ui->fixUpdate();

		TowerBuilding::getInstance()->fixUpdate();
		EnemyController::getInstance()->fixUpdate();
	}
}

void TestLevel::update()
{
	if (!GameStateManager::getInstance()->isPause)
	{
		ui->update();

		if (GameWindows::getInstance()->keyIn == VK_DOWN)
		{
			EnemyController::getInstance()->isNextWave = true;
		}

		TowerBuilding::getInstance()->update();
		EnemyController::getInstance()->update();
	}

	else
	{
		ui->pauseFunction();
	}
}

void TestLevel::draw()
{
	ui->backDraw();

	Map::getInstance()->drawMap();

	EnemyController::getInstance()->draw();

	ui->draw();

	TowerBuilding::getInstance()->draw();	

	if (GameStateManager::getInstance()->isPause)
	{
		ui->pauseMenu();
	}
}

void TestLevel::release()
{
	Map::getInstance()->releaseInstance();
	EnemyController::getInstance()->release();
	EnemyController::getInstance()->releaseInstance();
	TowerBuilding::getInstance()->release();
	TowerBuilding::getInstance()->releaseInstance();
	ui->release();
}