#include "TestLevel.h"
#include "../Component/Map.h"
#include "../Component/DirectInput.h"
#include "../Component/EnemyController.h"
#include "../Component/TowerBuilding.h"
#include "../Component/GameWindows.h"
#include "../Component/GameStateManager.h"
#include "../Component/UI.h"
#include "../Component/Physics.h"

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
	//level data
	maxHealth = 20;
	health = maxHealth;
	coin = 170;
	wave = 1;

	//load map
	std::string name = "data/Test_Level.txt";

	levelFile = new char[name.size() + 1];
	std::copy(name.begin(), name.end(), levelFile);
	levelFile[name.size()] = '\0';

	Map::getInstance()->createMap();
	Map::getInstance()->loadMap(levelFile);
	
	EnemyController::getInstance()->init();

	TowerBuilding::getInstance()->init();
	Physics::getInstance()->init();

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
	if (GameWindows::getInstance()->keyIn == VK_UP)
	{
		health--;
		EnemyController::getInstance()->isNextWave = true;
		coin--;
	}

	if (GameWindows::getInstance()->keyIn == VK_ESCAPE)
	{
		if (!ui->isMenu)
		{
			GameStateManager::getInstance()->isPause = true;
			ui->isMenu = true;
		}

		else
		{
			GameStateManager::getInstance()->isPause =false;
			ui->isMenu = false;
		}	
	}

	wave = EnemyController::getInstance()->currentWave + 1;

	ui->stateUpdate(maxHealth, health, wave, coin);

	ui->update();

	if (!GameStateManager::getInstance()->isPause)
	{
		TowerBuilding::getInstance()->update();
		EnemyController::getInstance()->update();
		Physics::getInstance()->update();
	}

	else if(ui->isMenu)
	{
		ui->pauseFunction();
	}
}

void TestLevel::draw()
{
	ui->backDraw();

	Map::getInstance()->drawMap();

	EnemyController::getInstance()->draw();

	TowerBuilding::getInstance()->draw();	

	Physics::getInstance()->draw();

	ui->draw();

	if (ui->isMenu)
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
	Physics::getInstance()->release();
	Physics::getInstance()->releaseInstance();
	ui->release();
}