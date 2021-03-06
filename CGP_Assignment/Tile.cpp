#pragma warning(disable : 4996)

#include "Tile.h"
#include "Graphic.h"

#include <stdio.h>

Tile* Tile::sInstance = NULL;

Tile* Tile::getInstance()
{
	if (Tile::sInstance == NULL)
	{
		sInstance = new Tile;
	}

	return sInstance;
}

void Tile::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

Tile::Tile()
{
	sprite = NULL;
	tile = NULL;
}

Tile::~Tile()
{
	sprite->Release();
	sprite = NULL;

	tile->Release();
	tile = NULL;
}

void Tile::createTile()
{
	hr = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
	hr = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/TileSet.png", &tile);

	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}

	tileRect.left = tileRect.top = 0;
	tileRect.right = 60;
	tileRect.bottom = 60;

	scaling.x = 9.0f / 16;
	scaling.y = 9.0f / 16;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
}

void Tile::loadMap(char * name) {

	FILE *fp;
	fp = fopen(name, "rb");

	/* If we can't open the map then exit */
	if (fp == NULL) {

		printf("Failed to open map %s\n", name);
		system("Pause");
		exit(1);
	}

	/* Read the data from the file into the map */

	for (int y = 0; y < MAX_MAP_Y; y++) {

		for (int x = 0; x < MAX_MAP_X; x++) {

			fscanf(fp, "%d", &map[y][x]); //map[][] is a 2D array
		}

	}

	/* Close the file afterwards */
	fclose(fp);
}

void Tile::drawMap()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&Tile::getInstance()->mat);

	/* Draw the map */
	for (int y = 0; y < MAX_MAP_Y; y++) {

		for (int x = 0; x < MAX_MAP_X; x++) {

			if (map[y][x] != 0) {

				clipWindow.top = (map[y][x] - 1)*(tileRect.bottom);

				clipWindow.left = 0;

				clipWindow.bottom = clipWindow.top + tileRect.bottom;

				clipWindow.right = clipWindow.left + tileRect.right;

				//render the tile at correct position

				pos.x = x * tileRect.right;

				pos.y = y * tileRect.bottom;

				pos.z = 0.0f;

				sprite->Draw(tile, &clipWindow, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255));
			}

		}

	}

	sprite->End();
}