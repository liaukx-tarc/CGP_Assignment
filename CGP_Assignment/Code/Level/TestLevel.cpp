#include "../Component/Spawner.h"
#include "TestLevel.h"
#include "../Component/Map.h"

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
}

void TestLevel::fixUpdate()
{
	Spawner::getInstance()->fixUpdate();
}

void TestLevel::update()
{
	Spawner::getInstance()->enemySpawn();
	Spawner::getInstance()->update();
}

void TestLevel::draw()
{
	Map::getInstance()->drawMap();

	Spawner::getInstance()->draw();
}

void TestLevel::release()
{
	Spawner::getInstance()->release();
}