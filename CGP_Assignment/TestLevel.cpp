#include "Spawner.h"
#include "TestLevel.h"
#include "Tile.h"

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

	Tile::getInstance()->loadMap(levelFile);

	Spawner::getInstance()->init();

	Spawner::getInstance()->enemySpawn();
}

void TestLevel::fixUpdate()
{
	Spawner::getInstance()->fixUpdate();
}

void TestLevel::update()
{
	Spawner::getInstance()->update();
}

void TestLevel::draw()
{
	Tile::getInstance()->drawMap();

	Spawner::getInstance()->draw();
}

void TestLevel::release()
{
	Spawner::getInstance()->release();
}