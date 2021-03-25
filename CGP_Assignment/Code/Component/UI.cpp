#include "UI.h"
#include "Graphic.h"
#include "GameStateManager.h"
#include "DirectInput.h"
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
	
	hr[3] = AddFontResourceEx("resource/pixel.ttf", FR_PRIVATE, 0);

	hr[4] = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 20, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Pixel", &buttonFont);

	hr[5] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/BlurBackground.png", &blurBackground);
	hr[6] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/MenuBack.png", &menuBack);
	hr[7] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Yes_No.png", &yes_No);
	
	hr[8] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Button.png", &menuButtonTexture);
	
	hr[9] = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 35, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Pixel", &menuButtonFont);

	hr[10] = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 90, 0, 0, FW_BOLD, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Pixel", &menuFont);

	for (int i = 0; i < 11; i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	//Button TowerRect
	for (int i = 0; i < MAX_TOWER_TYPE; i++)
	{
		towerRect[i].top = 32 * i;
		towerRect[i].left = 0;
		towerRect[i].bottom = towerRect[i].top + 32;
		towerRect[i].right = 32;

		towerTexMove[i] = 0;
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

	//Menu
	menuButtonNum = 4;

	//Menu Background
	menuRect.top = menuRect.left = 0;
	menuRect.bottom = 753;
	menuRect.right = 1024;

	//Menu Font
	menuTextRect.top = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) - 40;
	menuTextRect.left = BUFFER_WIDTH / 2 - 150;
	menuTextRect.bottom = menuTextRect.top + 100;
	menuTextRect.right = menuTextRect.left + 400;

	//Menu Button
	//Resume Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2;
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 180;
	button->size.x = 345;
	button->size.y = 122;

	button->r = 175;
	button->g = 210;
	button->b = 0;

	button->word = "Resume";
	button->textRect.top = button->position.y - 25;
	button->textRect.left = button->position.x - 85;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 200;

	button->init();
	buttonList.push_back(button);

	//Main Menu Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2;
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 330;
	button->size.x = 345;
	button->size.y = 122;

	button->r = 255;
	button->g = 47;
	button->b = 0;

	button->word = "Main Menu";
	button->textRect.top = button->position.y - 25;
	button->textRect.left = button->position.x - 120;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 300;

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
		for (int i = 0; i < menuButtonNum; i++)
		{
			buttonList[i]->update();

			if (buttonList[i]->isClick && !buttonList[i]->isAni)
			{
				buttonList[i]->frame = 1;
				buttonList[i]->textRect.top += 8;
				buttonList[i]->textRect.bottom += 8;
				buttonList[i]->isAni = true;

				if (i < MAX_TOWER_TYPE)
				{
					towerTexMove[i] = 8;
				}
			}

			else if (!buttonList[i]->isClick && buttonList[i]->isAni)
			{
				buttonList[i]->frame = 0;
				buttonList[i]->update();
				buttonList[i]->textRect.top -= 8;
				buttonList[i]->textRect.bottom -= 8;
				buttonList[i]->isAni = false;

				if (i < MAX_TOWER_TYPE)
				{
					towerTexMove[i] = 0;
				}
			}
		}
	}

	else if (!(DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80))
	{
		for (int i = 0; i < menuButtonNum; i++)
		{
			buttonList[i]->frame = 0;

			if (buttonList[i]->isAni)
			{
				buttonList[i]->update();
				buttonList[i]->textRect.top -= 8;
				buttonList[i]->textRect.bottom -= 8;
				buttonList[i]->isAni = false;

				if (i < MAX_TOWER_TYPE)
				{
					towerTexMove[i] = 0;
				}
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

	for (int i = 0; i < menuButtonNum; i++)
	{
		sprite->Draw(buttonTexture, &buttonList[i]->buttonRect,
			&D3DXVECTOR3(buttonList[i]->size.x / 2, buttonList[i]->size.y / 2, 0),
			&D3DXVECTOR3(buttonList[i]->position.x, buttonList[i]->position.y, 0),
			D3DCOLOR_XRGB(buttonList[i]->r, buttonList[i]->g, buttonList[i]->b));

		//draw tower on button
		if (i < MAX_TOWER_TYPE)
		{
			scaling.x = scaling.y = 4.0f;
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
			sprite->SetTransform(&mat);

			sprite->Draw(TowerBuilding::getInstance()->towerTexture, &towerRect[i],
				&D3DXVECTOR3(32 / 2, 32 / 2, 0),
				&D3DXVECTOR3(buttonList[i]->position.x / scaling.x, (buttonList[i]->position.y + towerTexMove[i]) / scaling.y, 0),
				D3DCOLOR_XRGB(255, 255, 255));;

			scaling.x = scaling.y = 1.0f;
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
			sprite->SetTransform(&mat);
		}

		if (buttonList[i]->word != "")
		{
			buttonFont->DrawText(sprite, buttonList[i]->word.c_str(), -1, &buttonList[i]->textRect, 0, D3DCOLOR_XRGB(255, 255, 255));
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

	blurBackground->Release();
	blurBackground = NULL;

	menuBack->Release();
	menuBack = NULL;

	yes_No->Release();
	yes_No = NULL;

	buttonFont->Release();
	buttonFont = NULL;

	menuButtonFont->Release();
	menuButtonFont = NULL;

	menuButtonTexture->Release();
	menuButtonTexture = NULL;

	menuFont->Release();
	menuFont = NULL;

	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i]->release();
		delete buttonList[i];
		buttonList[i] = NULL;
	}

	buttonList.erase(buttonList.begin(), buttonList.begin() + buttonList.size());

	RemoveFontResourceEx("resource\pixel.ttf", FR_PRIVATE, 0);
}

//Background
void Ui::backDraw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(backgroundTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();
}

//Menu
void Ui::pauseMenu()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(blurBackground, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	
	sprite->Draw(menuBack, &menuRect, 
		&D3DXVECTOR3(menuRect.right / 2, menuRect.bottom / 2, 0), 
		&D3DXVECTOR3(BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	menuFont->DrawText(sprite, "MENU", -1, &menuTextRect, 0, D3DCOLOR_XRGB(255, 255, 255));

	for (int i = menuButtonNum; i < buttonList.size(); i++)
	{
		sprite->Draw(menuButtonTexture, &buttonList[i]->buttonRect,
			&D3DXVECTOR3(buttonList[i]->size.x / 2, buttonList[i]->size.y / 2, 0),
			&D3DXVECTOR3(buttonList[i]->position.x, buttonList[i]->position.y, 0),
			D3DCOLOR_XRGB(buttonList[i]->r, buttonList[i]->g, buttonList[i]->b));
	
		if (buttonList[i]->word != "")
		{
			menuButtonFont->DrawText(sprite, buttonList[i]->word.c_str(), -1, &buttonList[i]->textRect, 0, D3DCOLOR_XRGB(255, 255, 255));
		}
	}

	sprite->End();
}

void Ui::pauseFunction()
{
	if (DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80)
	{
		for (int i = menuButtonNum; i < buttonList.size(); i++)
		{
			buttonList[i]->update();

			if (buttonList[i]->isClick && !buttonList[i]->isAni)
			{
				buttonList[i]->frame = 1;
				buttonList[i]->textRect.top += 8;
				buttonList[i]->textRect.bottom += 8;
				buttonList[i]->isAni = true;
			}

			else if (!buttonList[i]->isClick && buttonList[i]->isAni)
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
		for (int i = menuButtonNum; i < buttonList.size(); i++)
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
		case 4:
			GameStateManager::getInstance()->isPause = false;
			break;

		case 5:
			GameStateManager::getInstance()->currentState = 0;
			break;

		default:
			break;
		}

		isFunction = false;
	}
}