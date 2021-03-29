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
	//load map
	std::string name = "data/Test_Level.txt";

	levelFile = new char[name.size() + 1];
	std::copy(name.begin(), name.end(), levelFile);
	levelFile[name.size()] = '\0';

	Map::getInstance()->createMap();
	Map::getInstance()->loadMap(levelFile, maxHealth, coin);
	
	health = maxHealth;
	wave = 1;

	EnemyController::getInstance()->init();

	TowerBuilding::getInstance()->init();
	Physics::getInstance()->init();

	ui = new Ui;
	ui->init();

	isWin = false;
	isEnd = false;
}

void TestLevel::fixUpdate()
{
	if (!isEnd)
	{
		if (!GameStateManager::getInstance()->isPause)
		{
			ui->fixUpdate();

			TowerBuilding::getInstance()->fixUpdate();
			EnemyController::getInstance()->fixUpdate();
		}
	}
}

void TestLevel::update()
{
	if (!isEnd)
	{
		if (GameWindows::getInstance()->keyIn == VK_ESCAPE)
		{
			if (!ui->isMenu)
			{
				ui->buttonList[PAUSE]->buttonRect.top = 0;
				ui->buttonList[PAUSE]->buttonRect.bottom = ui->buttonList[PAUSE]->size.y;
				GameStateManager::getInstance()->isPause = true;
				ui->isMenu = true;
			}

			else
			{
				GameStateManager::getInstance()->isPause = false;
				ui->isMenu = false;
			}
		}

		if (GameWindows::getInstance()->keyIn == VK_LEFT)
		{
			health--;
		}

		wave = EnemyController::getInstance()->currentWave + 1;

		ui->stateUpdate(maxHealth, health, wave, coin);

		ui->update(coin);

		if (!GameStateManager::getInstance()->isPause)
		{
			TowerBuilding::getInstance()->update(coin);
			EnemyController::getInstance()->update(coin,isEnd ,isWin);
			Physics::getInstance()->update();
		}

		else if (ui->isMenu)
		{
			ui->pauseFunction();
		}

		if (health == 0)
		{
			isEnd = true;
		}
	}

	else
	{
		ui->winLoseFunction(isWin);
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

	if (!isEnd)
	{
		if (ui->isMenu)
		{
			ui->pauseMenu();
		}
	}
	
	else
	{
		ui->winLoseDraw(isWin);
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