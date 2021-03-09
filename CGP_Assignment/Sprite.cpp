#include "Graphic.h"
#include "Sprite.h"

Sprite* Sprite::sInstance = NULL;

Sprite* Sprite::getInstance()
{
	if (Sprite::sInstance == NULL)
	{
		sInstance = new Sprite;
	}

	return sInstance;
}

void Sprite::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

Sprite::Sprite()
{
	hr = NULL;

	minionTexture = NULL;
	bossTexture = NULL;
}

Sprite::~Sprite()
{
	minionTexture->Release();
	minionTexture = NULL;

	bossTexture->Release();
	bossTexture = NULL;
}

void Sprite::createSprite()
{
	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Minion_Sheet.png", &minionTexture);
	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Boss_Sheet.png", &bossTexture);
}