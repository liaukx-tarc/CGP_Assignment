#pragma warning(disable : 4996)

#include "EnemyController.h"
#include "Graphic.h"
#include "Map.h"
#include "../Object/Character.h"
#include "../Object/Spawner.h"
#include "SoundManager.h"

#include <stdio.h>

//singleton
EnemyController* EnemyController::sInstance = NULL;

EnemyController* EnemyController::getInstance()
{
	if (EnemyController::sInstance == NULL)
	{
		sInstance = new EnemyController;
	}

	return sInstance;
}

void EnemyController::releaseInstance()
{
	delete sInstance;
	sInstance = NULL;
}

EnemyController::EnemyController()
{
	enemyNum = 0;
	ZeroMemory(&enemyList, sizeof(enemyList));
	ZeroMemory(&enemyData, sizeof(enemyData));

	currentWave = 0;
	waveNum = 0;

	isNextWave = false;

	ZeroMemory(&enemyWave, sizeof(enemyWave));
}

EnemyController::~EnemyController()
{

}

void EnemyController::init()
{
	hr[0] = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);

	hr[1] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Minion_Sheet.png", &minionTexture);
	hr[2] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Boss_Sheet.png", &bossTexture);
	hr[3] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/EnemyDead.png", &explosionTexture);

	for (int i = 0; i < sizeof(hr); i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		explosionRect[i].top = 0;
		explosionRect[i].left = 32 * i;
		explosionRect[i].bottom = explosionRect[i].top + 32;
		explosionRect[i].right = explosionRect[i].left + 32;
	}

	aniTimer = 10;
	isComplete = false;

	FILE *fp;
	fp = fopen("data/enemyData.txt", "rb");

	//Read Enemy Data
	/* If we can't open the map then exit */
	if (fp == NULL)
	{
		printf("Failed to open map data enemyData.txt\n");
		system("Pause");
		exit(1);
	}

	for (int i = 0; i < MAX_ENEMY_TYPE; i++)
	{
		Character * enemy = new Character;
		int sizeX, sizeY, aniSpeed, charSpeed, health, coin;

		fscanf(fp, "%d", &health);
		fscanf(fp, "|%d,%d", &sizeX, &sizeY);
		fscanf(fp, "|%d", &aniSpeed);
		fscanf(fp, "|%d", &charSpeed);
		fscanf(fp, "|%d\n", &coin);

		enemy->health = health;
		enemy->objSize.x = sizeX;
		enemy->objSize.y = sizeY;
		enemy->animationSpeed = aniSpeed;
		enemy->charSpeed = charSpeed;
		enemy->coin = coin;
		enemy->charNo = i;

		enemyData.push_back(enemy);
	}

	/* Close the file afterwards */
	fclose(fp);

	//save the enemy in this level
	for (int a = 0; a < waveNum; a++)
	{
		for (int b = 0; b < MAX_ENEMY_ONEWAVE; b++)
		{
			if (enemyWave[a][b] != 0)
			{
				Character * enemy = new Character;

				enemy->health = enemyData[enemyWave[a][b] - 1]->health;
				enemy->objSize = enemyData[enemyWave[a][b] - 1]->objSize;
				enemy->animationSpeed = enemyData[enemyWave[a][b] - 1]->animationSpeed;
				enemy->charSpeed = enemyData[enemyWave[a][b] - 1]->charSpeed;
				enemy->charNo = enemyData[enemyWave[a][b] - 1]->charNo;
				enemy->coin = enemyData[enemyWave[a][b] - 1]->coin;
				spawnList.push_back(enemy);

				totalSpawn[a]++;
			}
		}
	}

	Spawner * spawner = new Spawner;
	spawner->init();
	spawnerList.push_back(spawner);

	dieEnemyNum = 0;
}

void EnemyController::fixUpdate()
{
	//fix update the enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (!enemyList[i]->isDead)
		{
			enemyList[i]->fixUpdate();
		}
	}
}

void EnemyController::update(int &coin, bool &isEnd, bool &isWin, int health)
{
	if (dieEnemyNum == totalSpawn[currentWave] && currentWave != waveNum - 1)
	{
		isNextWave = true;
		dieEnemyNum = 0;
	}

	else if (health > 0 && dieEnemyNum == totalSpawn[currentWave])
	{
		isEnd = true;
		isWin = true;
	}
	//go to next wave
	if (isNextWave)
	{
		currentWave++;
		Spawner * spawner = new Spawner;
		spawner->init();
		spawnerList.push_back(spawner);
		isNextWave = false;
	}

	for (int i = 0; i < spawnerList.size(); i++)
	{
		spawnerList[i]->update();
	}

	//update the enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (!enemyList[i]->isDead)
		{
			if (enemyList[i]->health <= 0)
			{
				SoundManager::getInstance()->sound(6);
				enemyList[i]->isDead = true;
				dieEnemyNum++;

				//coin add
				coin += enemyList[i]->coin;
			}
			else
			{
				enemyList[i]->update();
			}
		}
	}
}

void EnemyController::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	//draw enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (!enemyList[i]->isDead)
		{
			sprite->Draw(minionTexture, &enemyList[i]->charRect,
				&D3DXVECTOR3(enemyList[i]->spriteSize.x / 2, enemyList[i]->spriteSize.y / 2, 0), //set the charecter with center point
				&enemyList[i]->objPosition, D3DCOLOR_XRGB(enemyList[i]->r, enemyList[i]->g, enemyList[i]->b));
		}
		else
		{
			if (!enemyList[i]->isAni)
			{
				explosionPosition.x = enemyList[i]->objPosition.x;
				explosionPosition.y = enemyList[i]->objPosition.y - 10;
				sprite->Draw(explosionTexture, &explosionRect[(int)enemyList[i]->aniState], &D3DXVECTOR3(16, 16, 0),
					&explosionPosition, D3DCOLOR_XRGB(255, 255, 255));

				enemyList[i]->aniState += 0.2f;
			
				if (enemyList[i]->aniState > 3)
				{
					enemyList[i]->isAni = true;
				}
			}
		}
	}

	sprite->End();
}

void EnemyController::release()
{
	//release enemy Data
	for (int i = 0; i < enemyData.size(); i++)
	{
		enemyData[i]->release();
		delete enemyData[i];
		enemyData[i] = NULL;
	}

	enemyData.clear();

	//release enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->release();
		delete enemyList[i];
		enemyList[i] = NULL;
	}
	
	enemyList.clear();

	for (int i = 0; i < spawnerList.size(); i++)
	{
		delete spawnerList[i];
		spawnerList[i] = NULL;
	}

	spawnerList.clear();

	sprite->Release();
	sprite = NULL;

	minionTexture->Release();
	minionTexture = NULL;

	bossTexture->Release();
	bossTexture = NULL;
}