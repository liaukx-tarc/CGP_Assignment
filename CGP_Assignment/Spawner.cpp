#include "Graphic.h"
#include "Spawner.h"
#include "Sprite.h"
#include "Tile.h"

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
		sprite->Draw(Sprite::getInstance()->minionTexture, &enemyList[i]->charRect, 
			&D3DXVECTOR3(enemyList[i]->charSize.x/2, enemyList[i]->charSize.y/2, 0), //set the charecter with center point
			&enemyList[i]->charPosition, D3DCOLOR_XRGB(255, 255, 255));
	}

	sprite->End();
}

void Spawner::enemySpawn()
{
	//push back each enemy
	for (int i = 0; i < 2; i++)
	{
		Character * demon = new Demon_S;
		enemyList.push_back(demon);
	}

	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->init();
		enemyList[i]->charPosition.x += (30 + (60 * i/*Starter point.x*/)) * Tile::getInstance()->tileScaling.x / charScaling.x;
		enemyList[i]->charPosition.y += (30 /*+ (60 * i /*Starter point.y)*/) * Tile::getInstance()->tileScaling.y / charScaling.y;
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
}