#pragma warning(disable : 4996)

#include "TowerBuilding.h"
#include "DirectInput.h"
#include "GameWindows.h"
#include "Graphic.h"
#include "Map.h"

TowerBuilding::TowerBuilding()
{
	boxFrame = 0;
	frameRate = 0;
	frameTimer = 0;

	towerSelect = 0;
	isBuilding = false;

	for (int a = 0; a < MAX_MAP_Y; a++)
	{
		for (int b = 0; b < MAX_MAP_X; b++)
		{
			towerList[a][b] = NULL;
		}
	}
}

TowerBuilding::~TowerBuilding()
{

}

void TowerBuilding::init()
{
	hr[0] = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
	hr[1] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/tower.png", &towerTexture);
	hr[1] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/selectBox.png", &selectBoxTeture);

	for (int i = 0; i < sizeof(hr); i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	selectBoxRect.top = selectBoxRect.left = 0;
	selectBoxRect.bottom = 60;
	selectBoxRect.right = 60;

	frameRate = 1.0f / 6;
	
	FILE *fp;
	fp = fopen("data/TowerData.txt", "rb");

	//Read Enemy Data
	/* If we can't open the map then exit */
	if (fp == NULL)
	{
		printf("Failed to open map data TowerData.txt\n");
		system("Pause");
		exit(1);
	}

	for (int i = 0; i < MAX_TOWER_TYPE; i++)
	{
		Tower * tower = new Tower;
		int damage, atkSpeed;

		fscanf(fp, "%d|%d\n", &damage, &atkSpeed);

		tower->damage = damage;
		tower->atkSpeed = atkSpeed;

		towerData.push_back(tower);

		//Testing
		printf("%d|%d\n", damage, atkSpeed);
	}

	/* Close the file afterwards */
	fclose(fp);
}

void TowerBuilding::fixUpdate()
{
	//select box animation
	frameTimer += 1.0f / 60;

	if (frameTimer >= frameRate)
	{
		frameTimer -= frameRate;
		boxFrame++;
		boxFrame %= 2;
	}

	selectBoxRect.top = 0;
	selectBoxRect.bottom = selectBoxRect.top + 60;
	selectBoxRect.left = 60 * boxFrame;
	selectBoxRect.right = selectBoxRect.left + 60;

	for (int a = 0; a < MAX_MAP_Y; a++)
	{
		for (int b = 0; b < MAX_MAP_X; b++)
		{
			if (towerList[a][b] != NULL)
			{
				towerList[a][b]->fixUpdate();
			}	
		}
	}
}

//testing variable
int count = 0;

void TowerBuilding::update()
{
	mousePos = GameWindows::getInstance()->mousePos;

	//select tesing --> Future, it may change in button
	keyIn = GameWindows::getInstance()->keyIn;
	if (keyIn == VK_UP)
	{
		printf("is building\n");
		isBuilding = !isBuilding;
		
		//choose tower type 
		towerSelect = count;

		if (count < 3)
		{
			count++;
		}

		else
		{
			count = 0;
		}
	}

	//building function
	if (isBuilding)
	{
		tileSelectX = mousePos.x / TILE_WIDTH;
		tileSelectY = mousePos.y / TILE_HIGHT;

		towerRect.top = 90 * towerSelect;
		towerRect.left = 0;
		towerRect.bottom = towerRect.top + 90;
		towerRect.right = 46;

		if (DirectInput::getInstance()->mouseState.rgbButtons[0] & 0x80)
		{
			if (Map::getInstance()->pathMap[tileSelectY][tileSelectX] == 0)
			{
				if (towerList[tileSelectY][tileSelectX] == NULL)
				{
					Tower * tower = new Tower();

					//Save data
					tower->towerNo = towerSelect;
					tower->damage = towerData[towerSelect]->damage;
					tower->atkSpeed = towerData[towerSelect]->atkSpeed;
					tower->objPosition.x = tileSelectX * TILE_WIDTH + (TILE_WIDTH / 2);
					tower->objPosition.y = tileSelectY * TILE_WIDTH + (TILE_HIGHT / 2);

					tower->init();
					towerList[tileSelectY][tileSelectX] = tower;

					isBuilding = false;
					printf("Is Builded\n");
				}
			}
		}
	}

	for (int a = 0; a < MAX_MAP_Y; a++)
	{
		for (int b = 0; b < MAX_MAP_X; b++)
		{
			if (towerList[a][b] != NULL)
			{
				towerList[a][b]->update();
			}
		}
	}
}

void TowerBuilding::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	for (int a = 0; a < MAX_MAP_Y; a++)
	{
		for (int b = 0; b < MAX_MAP_X; b++)
		{
			if (towerList[a][b] != NULL)
			{
				sprite->Draw(towerTexture, &towerList[a][b]->towerRect, &D3DXVECTOR3(towerList[a][b]->spriteSize.x / 2, (towerList[a][b]->spriteSize.y * 3) / 4, 0), &D3DXVECTOR3(towerList[a][b]->objPosition.x, towerList[a][b]->objPosition.y, 0), D3DCOLOR_XRGB(255, 255, 255));
			}
		}
	}

	//draw a select Box
	if (Map::getInstance()->pathMap[tileSelectY][tileSelectX] == 0)
	{
		if (isBuilding && towerList[tileSelectY][tileSelectX] == NULL)
		{
			sprite->Draw(selectBoxTeture, &selectBoxRect,
				&D3DXVECTOR3((TILE_WIDTH / 2) * Map::getInstance()->tileScaling.x, (TILE_HIGHT / 2) * Map::getInstance()->tileScaling.y, 0),
				&D3DXVECTOR3((tileSelectX * TILE_WIDTH + (TILE_WIDTH / 2)) * Map::getInstance()->tileScaling.x, (tileSelectY * TILE_HIGHT + (TILE_HIGHT / 2)) * Map::getInstance()->tileScaling.y, 0),
				D3DCOLOR_XRGB(255, 255, 255));
		}
	}	
	
	if (isBuilding)
	{
		sprite->Draw(towerTexture, &towerRect, &D3DXVECTOR3(46 / 2, 90, 0), &D3DXVECTOR3(mousePos.x, mousePos.y, 0), D3DCOLOR_XRGB(255, 255, 255));
	}
	
	sprite->End();
}

void TowerBuilding::release()
{
	sprite->Release();
	sprite = NULL;

	towerTexture->Release();
	towerTexture = NULL;

	selectBoxTeture->Release();
	selectBoxTeture = NULL;

	for (int i = 0; i < MAX_TOWER_TYPE; i++)
	{
		towerData[i]->release();
		delete towerData[i];
		towerData[i] = NULL;
	}

	for (int a = 0; a < MAX_MAP_Y; a++)
	{
		for (int b = 0; b < MAX_MAP_X; b++)
		{
			if (towerList[a][b] != NULL)
			{
				towerList[a][b]->release();
				delete towerList[a][b];
				towerList[a][b] = NULL;
			}
		}
	}
}