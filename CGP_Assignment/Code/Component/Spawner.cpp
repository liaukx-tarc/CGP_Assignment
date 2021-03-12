#include "EnemyController.h"
#include "Spawner.h"
#include "Map.h"

#include"../Enemy/Demon.h"
#include"../Enemy/Demon_S.h"
#include"../Enemy/Demon_W.h"

//singleton
Spawner* Spawner::sInstance = NULL;

Spawner* Spawner::getInstance()
{
	if (Spawner::sInstance == NULL)
	{
		sInstance = new Spawner;
	}

	return sInstance;
}

void Spawner::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

Spawner::Spawner()
{
	currentWave = 0;
	spawnNum = 0;
	spawnTime = 0;
	spawnSpeed = 0;
	waveNum = 0;

	isNextWave = false;
	
	ZeroMemory(&enemyWave, sizeof(enemyWave));
}

Spawner::~Spawner()
{
	
}

void Spawner::init()
{
	spawn_Timer = new G_Timer();
	spawn_Timer->init(1);

	//save the enemy in this level
	for (int a = 0; a < waveNum; a++)
	{
		for (int b = 0; b < ENEMY_TYPE_NUM; b++)
		{
			for (int c = 0; c < enemyWave[a][b]; c++)
			{
				if (enemyWave[a][b] != 0)
				{
					switch (b)
					{
					case 10:
					{
						Character * demon = new Demon;
						spawnList.push_back(demon);
						break;
					}

					case 11:
					{
						Character * demon = new Demon_S;
						spawnList.push_back(demon);
						break;
					}

					case 12:
					{
						Character * demon = new Demon_W;
						spawnList.push_back(demon);
						break;
					}

					default:
						break;
					}
				}
			}
			totalSpawn[a] += enemyWave[a][b];
		}
	}

	spawnSpeed = 8;
}

void Spawner::enemySpawn()
{
	//go to next wave
	if (isNextWave)
	{
		currentWave++;
		spawnNum = 0;
		isNextWave = false;
	}

	//spawner delay
	if (spawnNum < totalSpawn[currentWave])
	{
		for (int i = 0; i < spawn_Timer->framesToUpdate(); i++)
		{
			spawnTime += (1.0f / 10) * spawnSpeed;
			if (spawnTime > 1)
			{
				EnemyController::getInstance()->enemyList.push_back(spawnList[EnemyController::getInstance()->enemyNum]);

				//tile's middle point
				EnemyController::getInstance()->enemyList[EnemyController::getInstance()->enemyNum]->objPosition.x = (30 + (60 * Map::getInstance()->startPoint[Map::getInstance()->spawnPoint[currentWave]].x));
				EnemyController::getInstance()->enemyList[EnemyController::getInstance()->enemyNum]->objPosition.y = (30 + (60 * Map::getInstance()->startPoint[Map::getInstance()->spawnPoint[currentWave]].y));
				EnemyController::getInstance()->enemyList[EnemyController::getInstance()->enemyNum]->init();
				EnemyController::getInstance()->enemyNum++;
				spawnNum++;
				spawnTime = 0;
			}
		}
	}
}

void Spawner::release()
{
	delete spawn_Timer;
}