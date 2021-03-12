#include "TestLevel.h"
#include "../Component/Spawner.h"
#include "../Component/Map.h"
#include "../Component/Collision.h"
#include "../Component/DirectInput.h"
#include "../Component/EnemyController.h"

TestLevel::TestLevel()
{
	
}

TestLevel::~TestLevel()
{
	delete levelFile;
}

void TestLevel::init()
{
	//load map
	std::string name = "level/Test_Level.txt";

	levelFile = new char[name.size() + 1];
	std::copy(name.begin(), name.end(), levelFile);
	levelFile[name.size()] = '\0';

	Map::getInstance()->loadMap(levelFile);

	Spawner::getInstance()->init();
	EnemyController::getInstance()->init();
}

void TestLevel::fixUpdate()
{
	EnemyController::getInstance()->fixUpdate();
}

bool isTrue = true;
std::vector<GameObject*> targetList;

void TestLevel::update()
{
	Spawner::getInstance()->enemySpawn();
	EnemyController::getInstance()->update();

	if (DirectInput::getInstance()->diKeys[DIK_UP] && isTrue)
	{
		Spawner::getInstance()->isNextWave = true;

		isTrue = false;
	}

	for (int i = 0; i < EnemyController::getInstance()->enemyList.size(); i++)
	{
		EnemyController::getInstance()->enemyList[i]->charDirection.x = 1;
	}

	EnemyController::getInstance()->update();
}

void TestLevel::draw()
{
	Map::getInstance()->drawMap();

	EnemyController::getInstance()->draw();
}

void TestLevel::release()
{
	Spawner::getInstance()->release();
	EnemyController::getInstance()->release();
}