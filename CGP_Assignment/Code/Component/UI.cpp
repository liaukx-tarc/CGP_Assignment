#include "UI.h"
#include "Graphic.h"
#include "DirectInput.h"
#include "Map.h"
#include "TowerBuilding.h"

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
	
	hr[3] = AddFontResourceEx("resource/pixel.ttf", FR_PRIVATE, 0);

	hr[4] = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 20, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Pixel", &font);

	for (int i = 0; i < 5; i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	//Wind Tower Button
	Button * button = new Button;
	button->position.x = 140;
	button->position.y = 1250;
	button->size.x = 240;
	button->size.y = 300;

	button->r = 204;
	button->g = 112;
	button->b = 0;

	button->word = "Wind Tower";
	button->textRect.top = button->position.y + 90;
	button->textRect.left = button->position.x - 75;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 200;

	button->init();
	buttonList.push_back(button);

	//Thunder Tower Button
	button = new Button;
	button->position.x = 400;
	button->position.y = 1250;
	button->size.x = 240;
	button->size.y = 300;

	button->r = 204;
	button->g = 112;
	button->b = 0;

	button->word = "Thunder Tower";
	button->textRect.top = button->position.y + 90;
	button->textRect.left = button->position.x - 105;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 250;

	button->init();
	buttonList.push_back(button);

	//Ice Tower Button
	button = new Button;
	button->position.x = 660;
	button->position.y = 1250;
	button->size.x = 240;
	button->size.y = 300;

	button->r = 204;
	button->g = 112;
	button->b = 0;

	button->word = "Ice Tower";
	button->textRect.top = button->position.y + 90;
	button->textRect.left = button->position.x - 65;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 200;

	button->init();
	buttonList.push_back(button);

	//Fire Tower Button
	button = new Button;
	button->position.x = 920;
	button->position.y = 1250;
	button->size.x = 240;
	button->size.y = 300;

	button->r = 204;
	button->g = 112;
	button->b = 0;

	button->word = "Fire Tower";
	button->textRect.top = button->position.y + 90;
	button->textRect.left = button->position.x - 70;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 200;

	button->init();
	buttonList.push_back(button);
}

void Ui::fixUpdate()
{

}

void Ui::update()
{
	if (DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80)
	{
		for (int i = 0; i < buttonList.size(); i++)
		{
			buttonList[i]->update();

			if (buttonList[i]->isClick && !buttonList[i]->isAni)
			{
				buttonList[i]->frame = 1;
				buttonList[i]->textRect.top += 8;
				buttonList[i]->textRect.bottom += 8;
				buttonList[i]->isAni = true;
			}

			if (!buttonList[i]->isClick && buttonList[i]->isAni)
			{
				buttonList[i]->frame = 0;
				buttonList[i]->update();
				buttonList[i]->textRect.top -= 8;
				buttonList[i]->textRect.bottom -= 8;
				buttonList[i]->isAni = false;
			}
		}
	}

	else if (!(DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80))
	{
		for (int i = 0; i < buttonList.size(); i++)
		{
			buttonList[i]->frame = 0;

			if (buttonList[i]->isAni)
			{
				buttonList[i]->update();
				buttonList[i]->textRect.top -= 8;
				buttonList[i]->textRect.bottom -= 8;
				buttonList[i]->isAni = false;
			}

			if (buttonList[i]->isClick)
			{
				function = i;
				isFunction = true;
				buttonList[i]->isClick = false;
			}
		}
	}

	if (isFunction)
	{
		switch (function)
		{
		case 0:
			TowerBuilding::getInstance()->isBuilding = true;
			TowerBuilding::getInstance()->towerSelect = 0;
			break;

		case 1:
			TowerBuilding::getInstance()->isBuilding = true;
			TowerBuilding::getInstance()->towerSelect = 1;
			break;

		case 2:
			TowerBuilding::getInstance()->isBuilding = true;
			TowerBuilding::getInstance()->towerSelect = 2;
			break;

		case 3:
			TowerBuilding::getInstance()->isBuilding = true;
			TowerBuilding::getInstance()->towerSelect = 3;
			break;

		default:
			break;
		}

		isFunction = false;
	}
}

void Ui::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	for (int i = 0; i < buttonList.size(); i++)
	{
		sprite->Draw(buttonTexture, &buttonList[i]->buttonRect,
			&D3DXVECTOR3(buttonList[i]->size.x / 2, buttonList[i]->size.y / 2, 0),
			&D3DXVECTOR3(buttonList[i]->position.x, buttonList[i]->position.y, 0),
			D3DCOLOR_XRGB(buttonList[i]->r, buttonList[i]->g, buttonList[i]->b));

		if (buttonList[i]->word != "")
		{
			font->DrawText(sprite, buttonList[i]->word.c_str(), -1, &buttonList[i]->textRect, 0, D3DCOLOR_XRGB(255, 255, 255));
		}
	}

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

	font->Release();
	font = NULL;

	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i]->release();
		delete buttonList[i];
		buttonList[i] = NULL;
	}

	RemoveFontResourceEx("resource\pixel.ttf", FR_PRIVATE, 0);
}

void Ui::backDraw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(backgroundTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();
}


