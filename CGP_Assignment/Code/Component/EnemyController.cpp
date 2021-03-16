#include "EnemyController.h"
#include "Graphic.h"
#include "Map.h"
#include "../Enemy/Demon.h"
#include "../Enemy/Demon_W.h"
#include "../Enemy/Demon_S.h"

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

	//save the enemy in this level
	for (int a = 0; a < waveNum; a++)
	{
		for (int b = 0; b < MAX_ENEMY_ONEWAVE; b++)
		{
			if (enemyWave[a][b] != 0)
			{
				switch (enemyWave[a][b])
				{
				case 11:
				{
					Character * demon = new Demon;
					spawnList.push_back(demon);
					break;
				}

				case 12:
				{
					Character * demon = new Demon_S;
					spawnList.push_back(demon);
					break;
				}

				case 13:
				{
					Character * demon = new Demon_W;
					spawnList.push_back(demon);
					break;
				}

				default:
					break;
				}
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
			EnemyController::getInstance()->enemyList.push_back(spawnList[EnemyController::getInstance()->enemyNum]);

			//tile's middle point
			enemyList[EnemyController::getInstance()->enemyNum]->objPosition.x = (30 + (60 * Map::getInstance()->startPoint[Map::getInstance()->spawnPoint[currentWave]].x));
			enemyList[EnemyController::getInstance()->enemyNum]->objPosition.y = (30 + (60 * Map::getInstance()->startPoint[Map::getInstance()->spawnPoint[currentWave]].y));
			enemyList[EnemyController::getInstance()->enemyNum]->init();
			enemyNum++;
			spawnNum++;
			spawnTime = 0;
		}
	}
}