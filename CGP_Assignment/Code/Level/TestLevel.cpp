#include "TestLevel.h"
#include "../Component/Map.h"
#include "../Component/DirectInput.h"
#include "../Component/EnemyController.h"
#include "../Component/TowerBuilding.h"
#include "../Component/GameWindows.h"
#include "../Component/UI.h"

TestLevel::TestLevel()
{
	
}

TestLevel::~TestLevel()
{
	delete levelFile;
}

TowerBuilding * towerBuilding;
Ui * ui;

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

	ui = new Ui;
	ui->init();
}

void TestLevel::fixUpdate()
{
	ui->fixUpdate();

	towerBuilding->fixUpdate();
	EnemyController::getInstance()->fixUpdate();
}

void TestLevel::update()
{
	ui->update();

	if (GameWindows::getInstance()->keyIn == VK_DOWN)
	{
		EnemyController::getInstance()->isNextWave = true;
	}

	towerBuilding->update();
	EnemyController::getInstance()->update();
}

void TestLevel::draw()
{
	ui->backDraw();

	Map::getInstance()->drawMap();

	EnemyController::getInstance()->draw();
	towerBuilding->draw();

	ui->draw();
}

void TestLevel::release()
{
	EnemyController::getInstance()->release();
	EnemyController::getInstance()->releaseInsrance();
	towerBuilding->release();
	ui->release();
}