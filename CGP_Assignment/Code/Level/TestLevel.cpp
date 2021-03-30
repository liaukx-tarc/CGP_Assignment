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

	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			if (Map::getInstance()->pathMap[i][j] == 3)
			{
				crystalPos.x = j * TILE_WIDTH;
				crystalPos.y = i * TILE_HEIGHT;
				printf("%.2f,%.2f\n", crystalPos.x, crystalPos.y);
			}
		}
	}
}

void TestLevel::fixUpdate()
{
	if (!isEnd)
	{
		if (!GameStateManager::getInstance()->isPause)
		{
			ui->fixUpdate();

			Map::getInstance()->fixUpdate();

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
				TowerBuilding::getInstance()->isBuilding = false;
				GameStateManager::getInstance()->isPause = true;
				ui->isMenu = true;
			}

			else
			{
				GameStateManager::getInstance()->isPause = false;
				ui->isMenu = false;
			}
		}

		for (int i = 0; i < EnemyController::getInstance()->enemyList.size(); i++)
		{
			if (!EnemyController::getInstance()->enemyList[i]->isDead)
			{
				if (EnemyController::getInstance()->enemyList[i]->objPosition.x > crystalPos.x &&
					EnemyController::getInstance()->enemyList[i]->objPosition.x < crystalPos.x + TILE_WIDTH &&
					EnemyController::getInstance()->enemyList[i]->objPosition.y > crystalPos.y &&
					EnemyController::getInstance()->enemyList[i]->objPosition.y < crystalPos.y + TILE_HEIGHT)
				{
					if (health > 0)
					{
						health--;
						Map::getInstance()->crystalColor[0] = 0;
						Map::getInstance()->crystalColor[1] = 0;
					}

					if (health == 0)
					{
						Map::getInstance()->crystalState = 2;
						Map::getInstance()->crystalFrame = 0;
						Map::getInstance()->maxFrame = 7;
					}

					else if (health <= maxHealth / 2)
					{
						Map::getInstance()->crystalState = 1;
					}

					EnemyController::getInstance()->enemyList[i]->isDead = true;
					EnemyController::getInstance()->dieEnemyNum++;
				}
			}
		}

		if (Map::getInstance()->crystalFrame == 6)
		{
			isEnd = true;
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