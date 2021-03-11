#include "Graphic.h"
#include "Spawner.h"
#include "Sprite.h"
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
	enemyNum = 0;
	spawnNum = 0;
	spawnTime = 0;
	spawnSpeed = 0;
	waveNum = 0;

	isSpawn = false;
	isNextWave = false;
	
	ZeroMemory(&enemyWave, sizeof(enemyWave));
	ZeroMemory(&enemyList, sizeof(enemyList.size()));
}

Spawner::~Spawner()
{
	
}

void Spawner::init()
{
	hr = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);

	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}

	charScaling.x = charScaling.y = 3.0f;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &charScaling, NULL, NULL, NULL);

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

void Spawner::fixUpdate()
{
	//fix update the enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->fixUpdate();
	}
}

void Spawner::update()
{
	//update the enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->update();
	}
}

void Spawner::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	//draw enemy
	for (int i = 0; i < Spawner::getInstance()->enemyList.size(); i++)
	{
		drawPosition.x = enemyList[i]->objPosition.x * Map::getInstance()->tileScaling.x / charScaling.x;
		drawPosition.y = enemyList[i]->objPosition.y * Map::getInstance()->tileScaling.y / charScaling.y;
		drawPosition.z = enemyList[i]->objPosition.z;

		sprite->Draw(Sprite::getInstance()->minionTexture, &enemyList[i]->charRect, 
			&D3DXVECTOR3(enemyList[i]->spriteSize.x/2, enemyList[i]->spriteSize.y/2, 0), //set the charecter with center point
			&drawPosition,D3DCOLOR_XRGB(255, 255, 255));
	}

	sprite->End();
}

void Spawner::enemySpawn()
{
	//spawner delay
	for (int i = 0; i < spawn_Timer->framesToUpdate(); i++)
	{
		spawnTime += (1.0f / 10) * spawnSpeed;
		if (spawnTime > 1)
		{
			isSpawn = true;
			spawnTime = 0;
		}

	}

	//go to next wave
	if (isNextWave)
	{
		currentWave++;
		spawnNum = 0;
		isNextWave = false;
	}

	//spawn enemy in the wave
	if (spawnNum < totalSpawn[currentWave])
	{
		if (isSpawn)
		{
			enemyList.push_back(spawnList[enemyNum]);

			//tile's middle point
			enemyList[enemyNum]->objPosition.x = (30 + (60 * Map::getInstance()->startPoint[Map::getInstance()->spawnPoint[currentWave]].x));
			enemyList[enemyNum]->objPosition.y = (30 + (60 * Map::getInstance()->startPoint[Map::getInstance()->spawnPoint[currentWave]].y));
			enemyList[enemyNum]->init();
			enemyNum++;
			spawnNum++;
			isSpawn = false;
		}
	}
}

void Spawner::release()
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

	delete spawn_Timer;
}