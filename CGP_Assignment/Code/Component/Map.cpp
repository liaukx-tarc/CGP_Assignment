#pragma warning(disable : 4996)

#include "EnemyController.h"
#include "Map.h"
#include "Graphic.h"
#include "../Object/Character.h"
#include <stdio.h>

Map* Map::sInstance = NULL;

Map* Map::getInstance()
{
	if (Map::sInstance == NULL)
	{
		sInstance = new Map;
	}

	return sInstance;
}

void Map::releaseInstance()
{
	delete sInstance;
	sInstance = NULL;
}

Map::Map()
{
	ZeroMemory(&map, sizeof(map));
	ZeroMemory(&pathMap, sizeof(pathMap));
	sprite = NULL;
	tile = NULL;

	startPointNum = 0;
	endPointNum = 0;
}

Map::~Map()
{
	sprite->Release();
	sprite = NULL;

	tile->Release();
	tile = NULL;

	crystalTexture->Release();
	crystalTexture = NULL;
}

void Map::createMap()
{
	hr[0] = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
	hr[1] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/TileSet.png", &tile);

	hr[2] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Crystal.png", &crystalTexture);

	for (int i = 0; i < 3; i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	tileRect.left = tileRect.top = 0;
	tileRect.right = 60;
	tileRect.bottom = 60;

	crystalRect.left = crystalRect.top = 0;
	crystalRect.right = 90;
	crystalRect.bottom = 90;

	aniTimer = 0;

	crystalState = 0;
	crystalFrame = 0;
	maxFrame = 4;

	crystalColor[0] = 255;
	crystalColor[1] = 255;
}

void Map::fixUpdate()
{
	aniTimer += 1.0f / 15;

	if (aniTimer >= 1)
	{
		crystalFrame++;
		crystalFrame %= maxFrame;

		crystalRect.top = crystalState * 90;
		crystalRect.left = crystalFrame * 90;
		crystalRect.bottom = crystalRect.top + 90;
		crystalRect.right = crystalRect.left + 90;

		crystalColor[0] = 255;
		crystalColor[1] = 255;

		aniTimer = 0;
	}
}

void Map::loadMap(char * name, int &maxHealth, int &coin)
{
	FILE *fp;
	fp = fopen(name, "rb");

	/* If we can't open the map then exit */
	if (fp == NULL) 
	{
		printf("Failed to open map %s\n", name);
		system("Pause");
		exit(1);
	}

	/* Read the data from the file into the map */

	fscanf(fp, "%d,%d", &maxHealth, &coin); //map health and coin

	for (int y = 0; y < MAX_MAP_Y; y++) 
	{
		for (int x = 0; x < MAX_MAP_X; x++) 
		{
			fscanf(fp, "%d,", &map[y][x]); //map[][] is a 2D array
		}
	}

	//load path
	for (int y = 0; y < MAX_MAP_Y; y++)
	{
		for (int x = 0; x < MAX_MAP_X; x++)
		{
			fscanf(fp, "%d,", &pathMap[y][x]); //map[][] is a 2D array
		}
	}

	//load wave number
	fscanf(fp, "%d", &EnemyController::getInstance()->waveNum);

	//load enemy list
	for (int i = 0; i < EnemyController::getInstance()->waveNum; i++)
	{
		for (int j = 0; j < MAX_ENEMY_ONEWAVE; j++)
		{
			fscanf(fp, "%d,", &EnemyController::getInstance()->enemyWave[i][j]);
		}
		fscanf(fp, "%d,%d,", &spawnPoint[i], &targetPoint[i]);
	}

	/* Close the file afterwards */
	fclose(fp);

	//Testing
	//path map test print
	for (int y = 0; y < MAX_MAP_Y; y++)
	{
		for (int x = 0; x < MAX_MAP_X; x++)
		{
			printf("%d,", pathMap[y][x]); //map[][] is a 2D array
		}
		printf("\n");
	}

	printf("\n");

	//enemy wave test print
	for (int i = 0; i < EnemyController::getInstance()->waveNum; i++)
	{
		for (int j = 0; j < MAX_ENEMY_ONEWAVE; j++)
		{
			printf("%d,", EnemyController::getInstance()->enemyWave[i][j]);
		}
		printf(" %d,%d", spawnPoint[i], targetPoint[i]);
		printf("\n");
	}

	for (int y = 0; y < MAX_MAP_Y; y++)
	{
		for (int x = 0; x < MAX_MAP_X; x++)
		{
			if (pathMap[y][x] == 2)
			{
				startPoint[startPointNum].x = x;
				startPoint[startPointNum].y = y;
				startPointNum++;
			}

			if (pathMap[y][x] == 3)
			{
				endPoint[endPointNum].x = x;
				endPoint[endPointNum].y = y;
				endPointNum++;
			}
		}
	}

	for (int y = 0; y < MAX_MAP_Y; y++)
	{
		for (int x = 0; x < MAX_MAP_X; x++)
		{
			if (pathMap[y][x] == 3)
			{
				crystalPos.x = x * TILE_WIDTH + TILE_WIDTH / 2;

				crystalPos.y = y * TILE_HEIGHT + TILE_HEIGHT / 2;

				crystalPos.z = 0.0f;

			}
		}
	}
}

void Map::drawMap()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//Draw the map 
	for (int y = 0; y < MAX_MAP_Y; y++) 
	{
		for (int x = 0; x < MAX_MAP_X; x++) 
		{
			if (map[y][x] != 0) 
			{
				//calculate the tile is at what row and col in the sprite
				tileRow = map[y][x] / 12;
				tileCol = map[y][x] % 12;

				clipWindow.top = tileRow * TILE_HEIGHT;

				clipWindow.left = (tileCol - 1) * TILE_WIDTH;

				clipWindow.bottom = clipWindow.top + TILE_HEIGHT;

				clipWindow.right = clipWindow.left + TILE_WIDTH;

				//render the tile at correct position

				pos.x = x * TILE_WIDTH;

				pos.y = y * TILE_HEIGHT;

				pos.z = 0.0f;

				sprite->Draw(tile, &clipWindow, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255));
			}
		}
	}

	sprite->Draw(crystalTexture, &crystalRect, &D3DXVECTOR3(90 / 2, 90 * 3 / 4, 0), &crystalPos, D3DCOLOR_XRGB(255, crystalColor[0], crystalColor[1]));

	sprite->End();
}