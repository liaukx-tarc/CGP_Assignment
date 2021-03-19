#include "TestLevel.h"
#include "../Component/Map.h"
#include "../Component/Collision.h"
#include "../Component/DirectInput.h"
#include "../Component/EnemyController.h"
#include "../Component/TowerBuilding.h"

TestLevel::TestLevel()
{
	
}

TestLevel::~TestLevel()
{
	delete levelFile;
}

TowerBuilding * towerBuilding;

void TestLevel::init()
{
	//load map
	std::string name = "data/Test_Level.txt";

	levelFile = new char[name.size() + 1];
	std::copy(name.begin(), name.end(), levelFile);
	levelFile[name.size()] = '\0';

	Map::getInstance()->loadMap(levelFile);
	EnemyController::getInstance()->init();

	towerBuilding = new TowerBuilding;
	towerBuilding->init();
}

void TestLevel::fixUpdate()
{
	towerBuilding->fixUpdate();
	EnemyController::getInstance()->fixUpdate();
}

void TestLevel::update()
{
	//testing enemy move forward
	for (int i = 0; i < EnemyController::getInstance()->enemyList.size(); i++)
	{
		EnemyController::getInstance()->enemyList[i]->charDirection.x = 1;
	}

	towerBuilding->update();
	EnemyController::getInstance()->update();
}

void TestLevel::draw()
{
	Map::getInstance()->drawMap();

	EnemyController::getInstance()->draw();
	towerBuilding->draw();
}

void TestLevel::release()
{
	EnemyController::getInstance()->release();
	EnemyController::getInstance()->releaseInsrance();
	towerBuilding->release();
}