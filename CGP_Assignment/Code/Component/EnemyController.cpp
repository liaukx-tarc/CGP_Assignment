#pragma warning(disable : 4996)

#include "EnemyController.h"
#include "Graphic.h"
#include "Map.h"
#include "../Object/Character.h"

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

void EnemyController::releaseInsrance()
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
	spawnNum = 0;
	spawnTime = 0;
	spawnSpeed = 0;
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

	for (int i = 0; i < sizeof(hr); i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	charScaling.x = charScaling.y = 3.0f;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &charScaling, NULL, NULL, NULL);

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
		int sizeX, sizeY, aniSpeed, charSpeed, health;

		fscanf(fp, "%d", &health);
		fscanf(fp, "|%d,%d", &sizeX, &sizeY);
		fscanf(fp, "|%d", &aniSpeed);
		fscanf(fp, "|%d\n", &charSpeed);

		enemy->health = health;
		enemy->objSize.x = sizeX;
		enemy->objSize.y = sizeY;
		enemy->animationSpeed = aniSpeed;
		enemy->charSpeed = charSpeed;
		enemy->charNo = i;

		enemyData.push_back(enemy);

		//Testing
		printf("%.2f", enemyData[i]->health);
		printf("|%.2f,%.2f", enemyData[i]->objSize.x, enemyData[i]->objSize.y);
		printf("|%.2f", enemyData[i]->animationSpeed);
		printf("|%.2f\n", enemyData[i]->charSpeed);
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

				enemy->objSize = enemyData[enemyWave[a][b] - 1]->objSize;
				enemy->animationSpeed = enemyData[enemyWave[a][b] - 1]->animationSpeed;
				enemy->charSpeed = enemyData[enemyWave[a][b] - 1]->charSpeed;
				enemy->charNo = enemyData[enemyWave[a][b] - 1]->charNo;
				spawnList.push_back(enemy);

				totalSpawn[a]++;
			}
		}
	}

	spawnSpeed = 4;
}

void EnemyController::fixUpdate()
{
	//fix update the enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->fixUpdate();
	}
}

void EnemyController::update()
{
	enemySpawn();

	//update the enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->update();
	}
}

void EnemyController::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	//draw enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		drawPosition.x = enemyList[i]->objPosition.x * Map::getInstance()->tileScaling.x / charScaling.x;
		drawPosition.y = enemyList[i]->objPosition.y * Map::getInstance()->tileScaling.y / charScaling.y;
		drawPosition.z = enemyList[i]->objPosition.z;

		sprite->Draw(minionTexture, &enemyList[i]->charRect,
			&D3DXVECTOR3(enemyList[i]->spriteSize.x / 2, enemyList[i]->spriteSize.y / 2, 0), //set the charecter with center point
			&drawPosition, D3DCOLOR_XRGB(255, 255, 255));
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

	//release enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->release();
		delete enemyList[i];
		enemyList[i] = NULL;
	}

	sprite->Release();
	sprite = NULL;

	minionTexture->Release();
	minionTexture = NULL;

	bossTexture->Release();
	bossTexture = NULL;
}

void EnemyController::enemySpawn()
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
		spawnTime += (0.001f) * spawnSpeed;
		if (spawnTime > 1)
		{
			enemyList.push_back(spawnList[enemyNum]);
			//tile's middle point
			enemyList[enemyNum]->objPosition.x = (30 + (60 * Map::getInstance()->startPoint[Map::getInstance()->spawnPoint[currentWave]].x));
			enemyList[enemyNum]->objPosition.y = (30 + (60 * Map::getInstance()->startPoint[Map::getInstance()->spawnPoint[currentWave]].y));
			enemyList[enemyNum]->init();
			enemyNum++;
			spawnNum++;
			spawnTime = 0;
		}
	}
}