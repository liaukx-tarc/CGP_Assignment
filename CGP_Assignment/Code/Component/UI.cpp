#include "UI.h"
#include "GameWindows.h"
#include "Graphic.h"
#include "GameStateManager.h"
#include "DirectInput.h"
#include "Map.h"

#define UI_BUTTON_NUM		4
#define MENU_BUTTON_NUM		7
#define CONFIRM_BUTTON_NUM	9

#define TOWER1		0
#define TOWER2		1
#define TOWER3		2
#define TOWER4		3
#define RESUME		4
#define RESTART		5
#define MAIN_MENU	6

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

	hr[4] = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 15, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Pixel", &buttonFont);

	hr[5] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/BlurBackground.png", &blurBackground);
	hr[6] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/MenuBack.png", &menuBack);
	hr[7] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Yes_No.png", &yes_No);
	
	hr[8] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Button.png", &menuButtonTexture);
	
	hr[9] = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 25, 0, 0, 1, false,
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
		towerRect[i].top = 96 * i;
		towerRect[i].left = 96 * 3;
		towerRect[i].bottom = towerRect[i].top + 96;
		towerRect[i].right = towerRect[i].left + 96;

		towerTextMove[i] = 0;
	}

	//Wind Tower Button
	Button * button = new Button;
	button->position.x = 120;
	button->position.y = 900;
	button->size.x = 180;
	button->size.y = 225;

	button->r = 204;
	button->g = 112;
	button->b = 0;

	button->word = "Wind Tower";
	button->textRect.top = button->position.y + 70;
	button->textRect.left = button->position.x - 55;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 200;

	button->init();
	buttonList.push_back(button);

	//Thunder Tower Button
	button = new Button;
	button->position.x = 335;
	button->position.y = 900;
	button->size.x = 180;
	button->size.y = 225;

	button->r = 204;
	button->g = 112;
	button->b = 0;

	button->word = "Thunder Tower";
	button->textRect.top = button->position.y + 70;
	button->textRect.left = button->position.x - 78;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 250;

	button->init();
	buttonList.push_back(button);

	//Ice Tower Button
	button = new Button;
	button->position.x = 550;
	button->position.y = 900;
	button->size.x = 180;
	button->size.y = 225;

	button->r = 204;
	button->g = 112;
	button->b = 0;

	button->word = "Ice Tower";
	button->textRect.top = button->position.y + 70;
	button->textRect.left = button->position.x - 50;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 200;

	button->init();
	buttonList.push_back(button);

	//Fire Tower Button
	button = new Button;
	button->position.x = 765;
	button->position.y = 900;
	button->size.x = 180;
	button->size.y = 225;

	button->r = 204;
	button->g = 112;
	button->b = 0;

	button->word = "Fire Tower";
	button->textRect.top = button->position.y + 70;
	button->textRect.left = button->position.x - 55;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 200;

	button->init();
	buttonList.push_back(button);

	//Menu
	isConfirming = false;

	//Menu Background
	menuRect.top = menuRect.left = 0;
	menuRect.bottom = 576;
	menuRect.right = 768;

	//Menu Font
	menuTextRect.top = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) - 40;
	menuTextRect.left = BUFFER_WIDTH / 2 - 160;
	menuTextRect.bottom = menuTextRect.top + 100;
	menuTextRect.right = menuTextRect.left + 400;

	//Menu Button
	//Resume Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2;
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 150;
	button->size.x = 259;
	button->size.y = 84;

	button->r = 175;
	button->g = 210;
	button->b = 0;

	button->word = "Resume";
	button->textRect.top = button->position.y - 15;
	button->textRect.left = button->position.x - 60;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 200;

	button->init();
	buttonList.push_back(button);

	//Restart Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2;
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 280;
	button->size.x = 259;
	button->size.y = 84;

	button->r = 0;
	button->g = 47;
	button->b = 255;

	button->word = "Restart";
	button->textRect.top = button->position.y - 15;
	button->textRect.left = button->position.x - 65;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 300;

	button->init();
	buttonList.push_back(button);

	//Main Menu Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2;
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 410;
	button->size.x = 259;
	button->size.y = 84;

	button->r = 255;
	button->g = 47;
	button->b = 0;

	button->word = "Main Menu";
	button->textRect.top = button->position.y - 15;
	button->textRect.left = button->position.x - 85;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 300;

	button->init();
	buttonList.push_back(button);

	//Confirm Text Rect
	confrimRect[0].top = BUFFER_HEIGHT / 2 - 20;
	confrimRect[0].left = BUFFER_WIDTH / 2 - 65;
	confrimRect[0].bottom = confrimRect[0].top + 40;
	confrimRect[0].right = confrimRect[0].left + 400;

	confrimRect[1].top = BUFFER_HEIGHT / 2 - 20;
	confrimRect[1].left = BUFFER_WIDTH / 2 - 85;
	confrimRect[1].bottom = confrimRect[1].top + 40;
	confrimRect[1].right = confrimRect[1].left + 400;

	//Yes Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2 - 80;
	button->position.y = (BUFFER_HEIGHT / 2) + 140;
	button->size.x = 64;
	button->size.y = 64;

	button->r = 255;
	button->g = 255;
	button->b = 255;

	button->init();
	buttonList.push_back(button);

	//No Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2 + 80;
	button->position.y = (BUFFER_HEIGHT / 2) + 140;
	button->size.x = 64;
	button->size.y = 64;

	button->r = 255;
	button->g = 255;
	button->b = 255;

	button->init();

	button->buttonRect.top = button->size.y;
	button->buttonRect.bottom = button->buttonRect.top + 64;

	buttonList.push_back(button);
}

void Ui::fixUpdate()
{

}

void Ui::update()
{
	if (GameWindows::getInstance()->keyIn == VK_ESCAPE)
	{
		isConfirming = false;
	}

	if (DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80)
	{
		for (int i = 0; i < UI_BUTTON_NUM; i++)
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
					towerTextMove[i] = 8;
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
					towerTextMove[i] = 0;
				}
			}
		}
	}

	else if (!(DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80))
	{
		for (int i = 0; i < UI_BUTTON_NUM; i++)
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
					towerTextMove[i] = 0;
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
		case TOWER1:
			TowerBuilding::getInstance()->isBuilding = true;
			TowerBuilding::getInstance()->towerSelect = 0;
			break;

		case TOWER2:
			TowerBuilding::getInstance()->isBuilding = true;
			TowerBuilding::getInstance()->towerSelect = 1;
			break;

		case TOWER3:
			TowerBuilding::getInstance()->isBuilding = true;
			TowerBuilding::getInstance()->towerSelect = 2;
			break;

		case TOWER4:
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

	for (int i = 0; i < UI_BUTTON_NUM; i++)
	{
		sprite->Draw(buttonTexture, &buttonList[i]->buttonRect,
			&D3DXVECTOR3(buttonList[i]->size.x / 2, buttonList[i]->size.y / 2, 0),
			&D3DXVECTOR3(buttonList[i]->position.x, buttonList[i]->position.y, 0),
			D3DCOLOR_XRGB(buttonList[i]->r, buttonList[i]->g, buttonList[i]->b));

		//draw tower on button
		if (i < MAX_TOWER_TYPE)
		{
			scaling.x = scaling.y = 1.5f;
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
			sprite->SetTransform(&mat);

			sprite->Draw(TowerBuilding::getInstance()->towerTexture, &towerRect[i],
				&D3DXVECTOR3(96 / 2, 96 * 3 / 4, 0),
				&D3DXVECTOR3(buttonList[i]->position.x / scaling.x, (buttonList[i]->position.y + towerTextMove[i]) / scaling.y, 0),
				D3DCOLOR_XRGB(255, 255, 255));

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

	if (!isConfirming)
	{
		sprite->Draw(menuBack, &menuRect,
			&D3DXVECTOR3(menuRect.right / 2, menuRect.bottom / 2, 0),
			&D3DXVECTOR3(BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2, 0),
			D3DCOLOR_XRGB(225, 122, 0));

		menuFont->DrawText(sprite, "MENU", -1, &menuTextRect, 0, D3DCOLOR_XRGB(255, 255, 255));

		for (int i = UI_BUTTON_NUM; i < MENU_BUTTON_NUM; i++)
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
	}
	
	else
	{
		scaling.x = scaling.y = 0.5f;
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
		sprite->SetTransform(&mat);

		sprite->Draw(menuBack, &menuRect,
			&D3DXVECTOR3(menuRect.right / 2, menuRect.bottom / 2, 0),
			&D3DXVECTOR3(BUFFER_WIDTH / scaling.x / 2, BUFFER_HEIGHT / scaling.y / 2, 0),
			D3DCOLOR_XRGB(225, 122, 0));

		scaling.x = scaling.y = 1.0f;
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
		sprite->SetTransform(&mat);

		menuButtonFont->DrawText(sprite, cfmWord.c_str(), -1, &confrimRect[function - 5], 0, D3DCOLOR_XRGB(255, 255, 255));
	
		for (int i = MENU_BUTTON_NUM; i < CONFIRM_BUTTON_NUM; i++)
		{
			sprite->Draw(yes_No, &buttonList[i]->buttonRect,
				&D3DXVECTOR3(buttonList[i]->size.x / 2, buttonList[i]->size.y / 2, 0),
				&D3DXVECTOR3(buttonList[i]->position.x, buttonList[i]->position.y, 0),
				D3DCOLOR_XRGB(buttonList[i]->r, buttonList[i]->g, buttonList[i]->b));
		}
	}

	sprite->End();
}

void Ui::pauseFunction()
{
	
	if (DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80)
	{
		if (!isConfirming)
		{
			for (int i = UI_BUTTON_NUM; i < MENU_BUTTON_NUM; i++)
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

		else
		{
			for (int i = MENU_BUTTON_NUM; i < CONFIRM_BUTTON_NUM; i++)
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
	}

	else if (!(DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80))
	{
		if (!isConfirming)
		{
			for (int i = UI_BUTTON_NUM; i < MENU_BUTTON_NUM; i++)
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

		else
		{
			for (int i = MENU_BUTTON_NUM; i < CONFIRM_BUTTON_NUM; i++)
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
					if (i == 7)
					{
						if (function == RESTART)
						{
							buttonList[i]->isClick = false;
							GameStateManager::getInstance()->restart();
							break;
						}

						else if (function == MAIN_MENU)
						{
							buttonList[i]->isClick = false;
							GameStateManager::getInstance()->currentState = 0;
						}
					}
					
					else if (i == 8)
					{
						buttonList[i]->isClick = false;
						isConfirming = false;
					}
				}
			}
		}
	}

	if (isFunction)
	{
		switch (function)
		{
		case RESUME:
			GameStateManager::getInstance()->isPause = false;
			break;

		case RESTART:
			isConfirming = true;
			cfmWord = buttonList[5]->word;
			break;

		case MAIN_MENU:
			isConfirming = true;
			cfmWord = buttonList[6]->word;
			break;

		default:
			break;
		}

		isFunction = false;
	}
}