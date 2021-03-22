#include "MainMenu.h"

#include "../Component/Graphic.h"
#include "../Component/DirectInput.h"
#include "../Component/GameStateManager.h"

#include <d3d9.h>
#include <stdio.h>

MainMenu::MainMenu()
{
	sprite = NULL;
	buttonTexture = NULL;

	timer = 0;
	isFunction = false;
}

MainMenu::~MainMenu()
{

}

void MainMenu::init()
{
	hr[0] = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
	hr[1] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Button.png", &buttonTexture);
	hr[2] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/MainMenuBack.png", &background);

	hr[3] = AddFontResourceEx("resource/pixel.ttf", FR_PRIVATE, 0);

	hr[4] = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 35, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Pixel", &font);

	hr[5] = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 150, 0, 0, FW_BOLD, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Pixel", &title);

	hr[6] = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 30, 0, 0, 0, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &madeBy);

	for (int i = 0; i < 7; i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);	
		}
	}

	//Background
	backgroundRect.top = backgroundRect.left = 0;
	backgroundRect.bottom = 1440;
	backgroundRect.right = 2560;

	//Title
	titleRect1.top = 200;
	titleRect1.left = 950;
	titleRect1.bottom = titleRect1.top + 200;
	titleRect1.right = titleRect1.left + 2000;

	titleRect2.top = 400;
	titleRect2.left = 850;
	titleRect2.bottom = titleRect2.top + 200;
	titleRect2.right = titleRect2.left + 2000;

	//Made by
	madeByRect.top = 1250;
	madeByRect.left = 1075;
	madeByRect.bottom = madeByRect.top + 100;
	madeByRect.right = madeByRect.left + 2000;
	
	//Start Button
	Button * button = new Button;
	button->position.x = 1280;
	button->position.y = 720;
	button->size.x = 345;
	button->size.y = 122;

	button->r = 0;
	button->g = 200;
	button->b = 255;
	
	button->word = "START";
	button->textRect.top = (button->position.y - 25);
	button->textRect.left = (button->position.x - 60);
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 200;
	
	button->init();
	buttonList.push_back(button);
	
	//Quit Button
	button = new Button;
	button->position.x = 1280;
	button->position.y = 880;
	button->size.x = 345;
	button->size.y = 122;

	button->r = 255;
	button->g = 0;
	button->b = 0;
	
	button->word = "QUIT";
	button->textRect.top = button->position.y - 28;
	button->textRect.left = button->position.x - 45;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 100;
	
	button->init();
	buttonList.push_back(button);
}

void MainMenu::fixUpdate()
{

}

void MainMenu::update()
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
		timer += 0.03f;
		if (timer >= 1)
		{
			switch (function)
			{
			case 0:
				GameStateManager::getInstance()->currentState = 1;
				break;

			case 1:
				PostQuitMessage(0);
				break;

			default:
				break;
			}

			timer = 0;
			isFunction = false;
		}
	}
}

void MainMenu::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(background, &backgroundRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	title->DrawText(sprite, TITLE1, -1, &titleRect1, 0, D3DCOLOR_XRGB(255, 255, 255));
	title->DrawText(sprite, TITLE2, -1, &titleRect2, 0, D3DCOLOR_XRGB(255, 255, 255));

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

	madeBy->DrawText(sprite, MADEBY, -1, &madeByRect, 0, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();
}

void MainMenu::release()
{
	sprite->Release();
	sprite = NULL;

	buttonTexture->Release();
	buttonTexture = NULL;

	background->Release();
	background = NULL;

	font->Release();
	font = NULL;

	title->Release();
	title = NULL;

	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i]->release();
		delete buttonList[i];
		buttonList[i] = NULL;
	}

	RemoveFontResourceEx("resource\pixel.ttf", FR_PRIVATE, 0);
}
