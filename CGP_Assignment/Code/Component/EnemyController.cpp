#include "EnemyController.h"
#include "Graphic.h"
#include "Sprite.h"
#include "Map.h"
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
}

EnemyController::~EnemyController()
{

}

void EnemyController::init()
{
	hr = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);

	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}

	charScaling.x = charScaling.y = 3.0f;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &charScaling, NULL, NULL, NULL);
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

		sprite->Draw(Sprite::getInstance()->minionTexture, &enemyList[i]->charRect,
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
}