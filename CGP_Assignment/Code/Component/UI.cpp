#include "UI.h"
#include "GameWindows.h"
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

	hr[11] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Heart.png", &heartTexture);

	hr[12] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/coin.png", &coinTexture);
	
	hr[13] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Button3.png", &funcButtonTexture);

	hr[14] = D3DXCreateFont(Graphic::getInstance()->d3dDevice, 120, 0, 0, FW_BOLD, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Pixel", &winLoseFont);

	for (int i = 0; i < 15; i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	aniTimer = 0;

	//UI Element
	//Health
	heartRect[0].top = heartRect[0].left = 0;
	heartRect[0].bottom = 56;
	heartRect[0].right = 63;

	heartRect[1].top = 0;
	heartRect[1].left = 64;
	heartRect[1].bottom = 56;
	heartRect[1].right = 119;

	heartPos.x = 50;
	heartPos.y = 50;
	heartPos.z = 0;

	heartTextRect.top = heartPos.y - 10;
	heartTextRect.left = heartPos.x + heartRect[0].right /2 + 20;
	heartTextRect.bottom = heartTextRect.top + 25;
	heartTextRect.right = heartTextRect.left + 100;

	//Wave
	waveTextRect.top =  40;
	waveTextRect.left = BUFFER_WIDTH / 2 - 60;
	waveTextRect.bottom = waveTextRect.top + 25;
	waveTextRect.right = waveTextRect.left + 200;

	//Coin
	coinRect.top = coinRect.left = 0;
	coinRect.bottom = 64;
	coinRect.right = 64;

	coinPos.x = 250;
	coinPos.y = 50;
	coinPos.z = 0;

	coinTextRect.top = coinPos.y - 10;
	coinTextRect.left = coinPos.x + coinRect.right / 2 + 20;
	coinTextRect.bottom = coinTextRect.top + 25;
	coinTextRect.right = coinTextRect.left + 100;

	for (int i = 0; i < 3; i++)
	{
		coinColor[i] = 255;
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

	//Button TowerRect & Tower Price
	for (int i = 0; i < MAX_TOWER_TYPE; i++)
	{
		towerRect[i].top = 96 * i;
		towerRect[i].left = 96 * 3;
		towerRect[i].bottom = towerRect[i].top + 96;
		towerRect[i].right = towerRect[i].left + 96;

		towerTextMove[i] = 0;

		towerPrice[i] = std::to_string(TowerBuilding::getInstance()->towerData[i]->price);
	
		towerPriceText[i].top = buttonList[i]->position.y - 85;
		towerPriceText[i].left = buttonList[i]->position.x + 10;
		towerPriceText[i].bottom = towerPriceText[i].top + 50;
		towerPriceText[i].right = towerPriceText[i].left + 200;

		coinPosition[i].x = towerPriceText[i].left - 30;
		coinPosition[i].y = towerPriceText[i].top + 5;
	}

	//Destroy Button
	button = new Button;
	button->position.x = 1750;
	button->position.y = 800;
	button->size.x = 259;
	button->size.y = 84;

	button->r = 204;
	button->g = 112;
	button->b = 0;

	button->word = "Destroy";
	button->textRect.top = button->position.y - 15;
	button->textRect.left = button->position.x - 65;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 200;

	button->init();
	buttonList.push_back(button);

	//Pause Button
	button = new Button;
	button->position.x = 1750;
	button->position.y = 60;
	button->size.x = 64;
	button->size.y = 63;

	button->r = 255;
	button->g = 255;
	button->b = 255;

	button->init();
	buttonList.push_back(button);

	//Setting Button
	button = new Button;
	button->position.x = 1850;
	button->position.y = 60;
	button->size.x = 64;
	button->size.y = 63;

	button->r = 255;
	button->g = 255;
	button->b = 255;

	button->init();

	button->buttonRect.top = 2 * button->size.y;
	button->buttonRect.bottom = button->buttonRect.top + button->size.y;

	buttonList.push_back(button);

	//Menu
	isConfirming = false;
	isMenu = false;

	//Menu Background
	menuRect.top = menuRect.left = 0;
	menuRect.bottom = 576;
	menuRect.right = 576;

	//Menu Font
	menuTextRect.top = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) - 40;
	menuTextRect.left = BUFFER_WIDTH / 2 - 165;
	menuTextRect.bottom = menuTextRect.top + 100;
	menuTextRect.right = menuTextRect.left + 400;

	//Menu Button
	//Resume Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2;
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 160;
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
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 290;
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
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 415;
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

	//Win Screen
	winRect.top = BUFFER_HEIGHT / 2 - 150;
	winRect.left = BUFFER_WIDTH / 2 - 150;
	winRect.bottom = winRect.top + 120;
	winRect.right = winRect.left + 300;

	//Restart Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2 - 150;
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 400;
	button->size.x = 259;
	button->size.y = 84;

	button->r = 0;
	button->g = 47;
	button->b = 255;

	button->word = "Next Level";
	button->textRect.top = button->position.y - 15;
	button->textRect.left = button->position.x - 95;
	button->textRect.bottom = button->textRect.top + 40;
	button->textRect.right = button->textRect.left + 300;

	button->init();
	buttonList.push_back(button);

	//Main Menu Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2 + 150;
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 400;
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

	//Lose Screen
	loseRect.top = BUFFER_HEIGHT / 2 - 150;
	loseRect.left = BUFFER_WIDTH / 2 - 280;
	loseRect.bottom = loseRect.top + 120;
	loseRect.right = loseRect.left + 600;

	//Restart Button
	button = new Button;
	button->position.x = BUFFER_WIDTH / 2 - 150;
	button->position.y = (BUFFER_HEIGHT / 2) - (menuRect.bottom / 2) + 400;
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
}

void Ui::fixUpdate()
{
	aniTimer += 0.05f;

	if (aniTimer >= 1)
	{
		if (noCoin)
		{
			buttonList[wrongTowerNum]->g = 122;
			coinColor[1] = 255;
			coinColor[2] = 255;
			noCoin = false;
		}
		aniTimer = 0;
	}
}

void Ui::update(int coin)
{
	if (GameWindows::getInstance()->keyIn == VK_ESCAPE)
	{
		isConfirming = false;
	}

	if (!isMenu)
	{
		if (DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80)
		{
			for (int i = 0; i < FUNC_BUTTON_NUM; i++)
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
						towerPriceText[i].top += 8;
						towerPriceText[i].bottom += 8;
						coinPosition[i].y += 8;
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
						towerPriceText[i].top -= 8;
						towerPriceText[i].bottom -= 8;
						coinPosition[i].y -= 8;
					}
				}
			}
		}

		else if (!(DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80))
		{
			for (int i = 0; i < FUNC_BUTTON_NUM; i++)
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
						towerPriceText[i].top -= 8;
						towerPriceText[i].bottom -= 8;
						coinPosition[i].y -= 8;
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
			if (!GameStateManager::getInstance()->isPause)
			{
				if (function < TOWER_BUTTON_NUM - 1 &&coin - TowerBuilding::getInstance()->towerData[function]->price >= 0)
				{
					switch (function)
					{
					case TOWER1:
						TowerBuilding::getInstance()->isDestroy = false;
						TowerBuilding::getInstance()->isBuilding = true;
						TowerBuilding::getInstance()->towerSelect = 0;
						break;

					case TOWER2:
						TowerBuilding::getInstance()->isDestroy = false;
						TowerBuilding::getInstance()->isBuilding = true;
						TowerBuilding::getInstance()->towerSelect = 1;
						break;

					case TOWER3:
						TowerBuilding::getInstance()->isDestroy = false;
						TowerBuilding::getInstance()->isBuilding = true;
						TowerBuilding::getInstance()->towerSelect = 2;
						break;

					case TOWER4:
						TowerBuilding::getInstance()->isDestroy = false;
						TowerBuilding::getInstance()->isBuilding = true;
						TowerBuilding::getInstance()->towerSelect = 3;
						break;

					default:
						break;
					}
				}
				
				else
				{
					if (function < 4)
					{
						buttonList[function]->g = 0;
						buttonList[function]->b = 0;
						wrongTowerNum = function;
						noCoin = true;

						coinColor[1] = 0;
						coinColor[2] = 0;
					}	
					isFunction = false;
				}

				if (function == DESTROY)
				{
					TowerBuilding::getInstance()->isBuilding = false;
					TowerBuilding::getInstance()->isDestroy = true;
				}
			}

			switch (function)
			{
			case PAUSE:
				GameStateManager::getInstance()->isPause = !GameStateManager::getInstance()->isPause;
				if (GameStateManager::getInstance()->isPause)
				{
					buttonList[PAUSE]->buttonRect.top = buttonList[PAUSE]->size.y;
					TowerBuilding::getInstance()->isBuilding = false;
					TowerBuilding::getInstance()->isDestroy = false;
				}

				else
				{
					buttonList[PAUSE]->buttonRect.top = 0;
				}

				buttonList[PAUSE]->buttonRect.bottom = buttonList[PAUSE]->buttonRect.top + buttonList[PAUSE]->size.y;
				break;

			case SETTING:
				buttonList[PAUSE]->buttonRect.top = 0;
				buttonList[PAUSE]->buttonRect.bottom = buttonList[PAUSE]->size.y;
				TowerBuilding::getInstance()->isBuilding = false;
				TowerBuilding::getInstance()->isDestroy = false;
				GameStateManager::getInstance()->isPause = true;
				isMenu = true;
				break;

			default:
				break;
			}

			isFunction = false;
		}
	}
}

void Ui::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//UI element
	sprite->Draw(heartTexture, &heartRect[0],
		&D3DXVECTOR3(63 / 2, 56 / 2, 0), &heartPos, D3DCOLOR_XRGB(255, 255, 255));

	sprite->Draw(heartTexture, &heartRect[1],
		&D3DXVECTOR3(55 / 2, 56 / 2 - heartRect[1].top, 0), &heartPos, D3DCOLOR_XRGB(255, 255, 255));

	menuButtonFont->DrawText(sprite, heartText.c_str(), -1, &heartTextRect, 0, D3DCOLOR_XRGB(255, 255, 255));
	
	//Wave
	menuButtonFont->DrawText(sprite, waveText.c_str(), -1, &waveTextRect, 0, D3DCOLOR_XRGB(255, 255, 255));

	//Coin
	sprite->Draw(coinTexture, &coinRect,
		&D3DXVECTOR3(64 / 2, 64 / 2, 0), &coinPos, D3DCOLOR_XRGB(255, 255, 255));

	menuButtonFont->DrawText(sprite, coinText.c_str(), -1, &coinTextRect, 0, D3DCOLOR_XRGB(coinColor[0], coinColor[1], coinColor[2]));

	for (int i = 0; i < TOWER_BUTTON_NUM; i++)
	{
		//draw tower on button
		if (i < MAX_TOWER_TYPE)
		{
			sprite->Draw(buttonTexture, &buttonList[i]->buttonRect,
				&D3DXVECTOR3(buttonList[i]->size.x / 2, buttonList[i]->size.y / 2, 0),
				&D3DXVECTOR3(buttonList[i]->position.x, buttonList[i]->position.y, 0),
				D3DCOLOR_XRGB(buttonList[i]->r, buttonList[i]->g, buttonList[i]->b));

			sprite->Draw(TowerBuilding::getInstance()->towerTexture, &towerRect[i],
				&D3DXVECTOR3(96 / 2, 96 * 3 / 5, 0),
				&D3DXVECTOR3(buttonList[i]->position.x, buttonList[i]->position.y + towerTextMove[i], 0),
				D3DCOLOR_XRGB(255, 255, 255));

			scaling.x = scaling.y = 0.5f;
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
			sprite->SetTransform(&mat);

			sprite->Draw(coinTexture, &coinRect, &D3DXVECTOR3(coinRect.right / 2, coinRect.bottom / 2, 0),
				&D3DXVECTOR3(coinPosition[i].x / scaling.x, coinPosition[i].y / scaling.y, 0), D3DCOLOR_XRGB(255, 255, 255));
		
			scaling.x = scaling.y = 1.0f;
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
			sprite->SetTransform(&mat);

			buttonFont->DrawText(sprite, towerPrice[i].c_str(), -1, &towerPriceText[i], 0, D3DCOLOR_XRGB(255, 255, 255));
		
			buttonFont->DrawText(sprite, buttonList[i]->word.c_str(), -1, &buttonList[i]->textRect, 0, D3DCOLOR_XRGB(255, 255, 255));
		}

		else if(i == DESTROY)
		{
			sprite->Draw(menuButtonTexture, &buttonList[i]->buttonRect,
				&D3DXVECTOR3(buttonList[i]->size.x / 2, buttonList[i]->size.y / 2, 0),
				&D3DXVECTOR3(buttonList[i]->position.x, buttonList[i]->position.y, 0),
				D3DCOLOR_XRGB(buttonList[i]->r, buttonList[i]->g, buttonList[i]->b));
		
			menuButtonFont->DrawText(sprite, buttonList[i]->word.c_str(), -1, &buttonList[i]->textRect, 0, D3DCOLOR_XRGB(255, 255, 255));
		}
	}

	if (GameStateManager::getInstance()->isPause && !isMenu)
	{
		sprite->Draw(blurBackground, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}

	for (int i = TOWER_BUTTON_NUM; i < FUNC_BUTTON_NUM; i++)
	{
		sprite->Draw(funcButtonTexture, &buttonList[i]->buttonRect,
			&D3DXVECTOR3(buttonList[i]->size.x / 2, buttonList[i]->size.y / 2, 0),
			&D3DXVECTOR3(buttonList[i]->position.x, buttonList[i]->position.y, 0),
			D3DCOLOR_XRGB(buttonList[i]->r, buttonList[i]->g, buttonList[i]->b));
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

	heartTexture->Release();
	heartTexture = NULL;

	funcButtonTexture->Release();
	funcButtonTexture = NULL;

	winLoseFont->Release();
	winLoseFont = NULL;

	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i]->release();
		delete buttonList[i];
		buttonList[i] = NULL;
	}

	buttonList.clear();

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
void Ui::pauseFunction()
{
	if (DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80)
	{
		if (!isConfirming)
		{
			for (int i = FUNC_BUTTON_NUM; i < MENU_BUTTON_NUM; i++)
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
			for (int i = FUNC_BUTTON_NUM; i < MENU_BUTTON_NUM; i++)
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
					if (i == YES)
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

					else if (i == NO)
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
			isMenu = false;
			break;

		case RESTART:
			isConfirming = true;
			cfmWord = buttonList[RESTART]->word;
			break;

		case MAIN_MENU:
			isConfirming = true;
			cfmWord = buttonList[MAIN_MENU]->word;
			break;

		default:
			break;
		}

		isFunction = false;
	}
}

void Ui::pauseMenu()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	sprite->Draw(blurBackground, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	if (!isConfirming)
	{
		sprite->Draw(menuBack, &menuRect,
			&D3DXVECTOR3(menuRect.right / 2, menuRect.bottom / 2, 0),
			&D3DXVECTOR3(BUFFER_WIDTH / 2, BUFFER_HEIGHT / 2, 0),
			D3DCOLOR_XRGB(255, 255, 255));

		menuFont->DrawText(sprite, "MENU", -1, &menuTextRect, 0, D3DCOLOR_XRGB(255, 255, 255));

		for (int i = FUNC_BUTTON_NUM; i < MENU_BUTTON_NUM; i++)
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
			D3DCOLOR_XRGB(255, 255, 255));

		scaling.x = scaling.y = 1.0f;
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
		sprite->SetTransform(&mat);

		menuButtonFont->DrawText(sprite, cfmWord.c_str(), -1, &confrimRect[function - (FUNC_BUTTON_NUM + 1)], 0, D3DCOLOR_XRGB(255, 255, 255));
	
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


void Ui::stateUpdate(int maxHeart, int heart, int wave, int coin)
{
	heartRect[1].top = heartRect[1].bottom - heartRect[1].bottom * (heart + 1) / (maxHeart + 1);
	
	heartText.clear();
	heartText.append(std::to_string(heart));
	heartText.append("/");
	heartText.append(std::to_string(maxHeart));

	waveText.clear();
	waveText.append("Wave ");
	waveText.append(std::to_string(wave));

	coinText.clear();
	coinText.append(std::to_string(coin));
}

void Ui::winLoseFunction(bool isWin)
{
	if (DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80)
	{
		if (!isConfirming)
		{
			if (isWin)
			{
				for (int i = CONFIRM_BUTTON_NUM; i < WIN_BUTTON_NUM; i++)
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
				for (int i = WIN_BUTTON_NUM - 1; i < LOSE_BUTTON_NUM; i++)
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
			if (isWin)
			{
				for (int i = CONFIRM_BUTTON_NUM; i < WIN_BUTTON_NUM; i++)
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
				for (int i = WIN_BUTTON_NUM - 1; i < LOSE_BUTTON_NUM; i++)
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
					if (i == YES)
					{
						if (function == WIN_LOSE_MENU)
						{
							buttonList[i]->isClick = false;
							GameStateManager::getInstance()->currentState = 0;
						}
					}

					else if (i == NO)
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
		case NEXT_LEVEL:
			if (GameStateManager::getInstance()->currentState < 1)
			{
				GameStateManager::getInstance()->currentState++;
			}

			else
			{
				GameStateManager::getInstance()->currentState = 0;
			}
			break;

		case WIN_LOSE_MENU:
			isConfirming = true;
			cfmWord = buttonList[MAIN_MENU]->word;
			break;

		case LOSE_RESTART:
			GameStateManager::getInstance()->restart();
			break;

		default:
			break;
		}

		isFunction = false;
	}
}

void Ui::winLoseDraw(bool isWin)
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	sprite->Draw(blurBackground, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	if (!isConfirming)
	{
		if (isWin)
		{
			winLoseFont->DrawText(sprite, "WIN", -1, &winRect, 0, D3DCOLOR_XRGB(255, 255, 255));

			for (int i = CONFIRM_BUTTON_NUM; i < WIN_BUTTON_NUM; i++)
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
			winLoseFont->DrawText(sprite, "DEFEAT", -1, &loseRect, 0, D3DCOLOR_XRGB(255, 255, 255));

			for (int i = WIN_BUTTON_NUM - 1; i < LOSE_BUTTON_NUM; i++)
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
	}

	else
	{
		scaling.x = scaling.y = 0.5f;
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
		sprite->SetTransform(&mat);

		sprite->Draw(menuBack, &menuRect,
			&D3DXVECTOR3(menuRect.right / 2, menuRect.bottom / 2, 0),
			&D3DXVECTOR3(BUFFER_WIDTH / scaling.x / 2, BUFFER_HEIGHT / scaling.y / 2, 0),
			D3DCOLOR_XRGB(255, 255, 255));

		scaling.x = scaling.y = 1.0f;
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
		sprite->SetTransform(&mat);

		menuButtonFont->DrawText(sprite, cfmWord.c_str(), -1, &confrimRect[1], 0, D3DCOLOR_XRGB(255, 255, 255));

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
