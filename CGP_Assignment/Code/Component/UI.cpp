#include "UI.h"
#include "Graphic.h"
#include "Map.h"

Ui::Ui()
{

}

Ui::~Ui()
{

}

void Ui::init()
{
	hr[0] = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
	hr[1] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/UI_Background.png", &backgroundTexture);
	hr[2] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Button2.png", &buttonTexture);

	for (int i = 0; i < 3; i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}
}

void Ui::fixUpdate()
{

}

void Ui::update()
{

}

void Ui::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	sprite->Draw(buttonTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(0, 0, 255));

	sprite->End();
}

void Ui::release()
{
	sprite->Release();
	sprite = NULL;

	backgroundTexture->Release();
	backgroundTexture = NULL;

	buttonTexture->Release();
	buttonTexture = NULL;
}

void Ui::backDraw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(backgroundTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();
}


