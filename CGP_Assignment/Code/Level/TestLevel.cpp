#include "../Component/Spawner.h"
#include "TestLevel.h"
#include "../Component/Map.h"
#include "../Component/Collision.h"
#include "../Component/DirectInput.h"

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

bool isTrue = true;
std::vector<GameObject*> targetList;

void TestLevel::update()
{
	Spawner::getInstance()->enemySpawn();
	Spawner::getInstance()->update();

	if (DirectInput::getInstance()->diKeys[DIK_UP] && isTrue)
	{
		printf("isTrue\n");
		Spawner::getInstance()->spawnList[0]->objPosition.x += 60;
		Spawner::getInstance()->spawnList[1]->objPosition.x += 60;
		Spawner::getInstance()->spawnList[1]->objPosition.x += 25;
		targetList.push_back(Spawner::getInstance()->spawnList[1]);

		if (Collision::getInstance()->colliDetect(Spawner::getInstance()->spawnList[0], targetList))
		{
			printf("collision\n");
		}

		else
		{
			printf("Nope\n");
		}

		isTrue = false;
	}
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