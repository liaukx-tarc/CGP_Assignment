#include "TowerBuilding.h"
#include "GameWindows.h"
#include "Graphic.h"

TowerBuilding::TowerBuilding()
{
	
}

TowerBuilding::~TowerBuilding()
{

}

void TowerBuilding::init()
{
	hr[0] = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
	hr[1] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/tower.png", &towerTexture);

	for (int i = 0; i < sizeof(hr); i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	towerRect.top = towerRect.left = 0;
	towerRect.bottom = 82;
	towerRect.right = 46;
}

void TowerBuilding::fixUpdate()
{
	
}

void TowerBuilding::update()
{
	mousePos = GameWindows::getInstance()->mousePos;
	
}

void TowerBuilding::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(towerTexture, &towerRect, &D3DXVECTOR3(towerRect.right/2, towerRect.bottom, 0), &D3DXVECTOR3(mousePos.x, mousePos.y, 0), D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void TowerBuilding::release()
{
	sprite->Release();
	sprite = NULL;

	towerTexture->Release();
	towerTexture = NULL;
}