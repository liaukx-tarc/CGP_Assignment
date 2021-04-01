#include "Spawner.h"
#include "../Component/EnemyController.h"
#include <stdio.h>

Spawner::Spawner()
{

}

Spawner::~Spawner()
{

}

void Spawner::init()
{
	wave = EnemyController::getInstance()->currentWave;
	for (int i = 0; i < wave; i++)
	{
		currentSpawnMax += EnemyController::getInstance()->totalSpawn[i];
	}
	totalSpawn = EnemyController::getInstance()->totalSpawn[wave];
	spawnNum = 0;

	for (int i = currentSpawnMax; i < currentSpawnMax + totalSpawn ; i++)
	{
		spawnList.push_back(EnemyController::getInstance()->spawnList[i]);
	}

	spawnSpeed = 15;
}

void Spawner::update()
{
	//spawner delay
	if (spawnNum < totalSpawn)
	{
		spawnTime += (0.001f) * spawnSpeed;
		if (spawnTime > 1)
		{
			enemyNum = EnemyController::getInstance()->enemyNum;
			EnemyController::getInstance()->enemyList.push_back(spawnList[spawnNum]);
			//tile's middle point
			EnemyController::getInstance()->enemyList[enemyNum]->objPosition.x = (30 + (60 * Map::getInstance()->startPoint[Map::getInstance()->spawnPoint[wave]].x));
			EnemyController::getInstance()->enemyList[enemyNum]->objPosition.y = (30 + (60 * Map::getInstance()->startPoint[Map::getInstance()->spawnPoint[wave]].y));
			EnemyController::getInstance()->enemyList[enemyNum]->init();
			EnemyController::getInstance()->enemyNum++;
			spawnNum++;
			spawnTime = 0;
		}
	}
}
