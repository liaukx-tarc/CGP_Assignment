#include "Character.h"
#include "../Component/DirectInput.h"
#include "../Component/Graphic.h"
#include "../Component/Map.h"

#include <stdio.h>
#include <algorithm>

Character::Character()
{
	ZeroMemory(&charRect, sizeof(charRect));			
	ZeroMemory(&objSize, sizeof(objSize));
	ZeroMemory(&spriteSize, sizeof(spriteSize));
	ZeroMemory(&charDirection, sizeof(charDirection));	
	ZeroMemory(&objPosition, sizeof(objPosition));	
	ZeroMemory(&charVelocity, sizeof(charVelocity));	
	
	animationSpeed = 0;
	charFrame = 0;
	charNo = 0;
	charSpeed = 0;
	charState = 0;
	frameNum = 0;
	frameRate = 0;
	frameTimer = 0;
	health = 0;
	hitboxRadius = 0;
}

Character::~Character()
{
	
}

void Character::init()
{
	spriteSize.x = 20;
	spriteSize.y = 30;

	charRect.top = 30 * charNo;
	charRect.left = 0;
	charRect.bottom = charRect.top + spriteSize.y;
	charRect.right = charRect.right + spriteSize.x;

	frameRate = 1.0f / animationSpeed;
	frameNum = 4;

	charState = 0; //0 = idle, 1 = move

	for (int y = 0; y < MAX_MAP_Y; y++)
	{
		for (int x = 0; x < MAX_MAP_X; x++)
		{
			pathRoute[y][x] = Map::getInstance()->pathMap[y][x];
			if (pathRoute[y][x] == 3)
			{
				endPoint.x = x;
				endPoint.y = y;
			}
		}
	}
	currentPointX = objPosition.x / TILE_WIDTH;
	currentPointY = objPosition.y / TILE_HIGHT;

	hitboxRadius = 30;
}

void Character::draw()
{

}

void Character::fixUpdate()
{
	frameTimer += 1.0f / 60;

	if (frameTimer >= frameRate)
	{
		frameTimer -= frameRate;
		charFrame++;
		charFrame %= frameNum;
	}

	charRect.top = 30 * charNo;
	charRect.bottom = charRect.top + spriteSize.y;
	charRect.left = 20 * (charFrame + (charState * 4));
	charRect.right = charRect.left + spriteSize.x;
}

void Character::update()
{
	move(charDirection);
}

void Character::release()
{

}

void Character::move(D3DXVECTOR2 direction)
{
	leftX = currentPointX - 1;
	leftY = currentPointY;
	rightX = currentPointX + 1;
	rightY = currentPointY;
	topX = currentPointX;
	topY = currentPointY - 1;
	btmX = currentPointX;
	btmY = currentPointY + 1;

	if (leftX < 0 || directionState == 'r')
	{
		if (pathRoute[rightY][rightX] == 1)
		{
			direction.x = 1;
			direction.y = 0;
			directionState = 'r';
		}
		else if (pathRoute[topY][topX] == 1)
		{
			direction.x = 0;
			direction.y = -1;
			directionState = 't';
		}
		else if (pathRoute[btmY][btmX] == 1)
		{
			direction.x = 0;
			direction.y = 1;
			directionState = 'b';
		}
	}
	else if (rightX > MAX_MAP_X || directionState == 'l')
	{
		if (pathRoute[leftY][leftX] == 1)
		{
			direction.x = -1;
			direction.y = 0;
			directionState = 'l';
		}
		else if (pathRoute[topY][topX] == 1)
		{
			direction.x = 0;
			direction.y = -1;
			directionState = 't';
		}
		else if (pathRoute[btmY][btmX] == 1)
		{
			direction.x = 0;
			direction.y = 1;
			directionState = 'b';
		}
	}
	else if (topY < 0 || directionState == 'b')
	{
		if (pathRoute[btmY][btmX] == 1)
		{
			direction.x = 0;
			direction.y = 1;
			directionState = 'b';
		}
		else if (pathRoute[rightY][rightX] == 1)
		{
			direction.x = 1;
			direction.y = 0;
			directionState = 'r';
		}
		else if (pathRoute[leftY][leftX] == 1)
		{
			direction.x = -1;
			direction.y = 0;
			directionState = 'l';
		}
	}
	else if (btmY > MAX_MAP_Y || directionState == 't')
	{
		if (pathRoute[topY][topX] == 1)
		{
			direction.x = 0;
			direction.y = -1;
			directionState = 't';
		}

		else if (pathRoute[rightY][rightX] == 1)
		{
			direction.x = 1;
			direction.y = 0;
			directionState = 'r';
		}
		else if (pathRoute[leftY][leftX] == 1)
		{
			direction.x = -1;
			direction.y = 0;
			directionState = 'l';
		}
	}

	else
	{
		if (pathRoute[topY][topX] == 1)
		{
			direction.x = 0;
			direction.y = -1;
			directionState = 't';
		}

		else if (pathRoute[rightY][rightX] == 1)
		{
			direction.x = 1;
			direction.y = 0;
			directionState = 'r';
		}
		else if (pathRoute[leftY][leftX] == 1)
		{
			direction.x = -1;
			direction.y = 0;
			directionState = 'l';
		}
		else if (pathRoute[btmY][btmX] == 1)
		{
			direction.x = 0;
			direction.y = 1;
			directionState = 'b';
		}
	}

	charState = 1; //move
	objPosition.x += direction.x * (0.1f * charSpeed);
	objPosition.y += direction.y * (0.1f * charSpeed);
	
	if (directionState == 'l' || directionState == 't')
	{
		currentPointX = (objPosition.x + 29) / TILE_WIDTH;
		currentPointY = (objPosition.y + 29) / TILE_HIGHT;
	}

	if (directionState == 'r' || directionState == 'b')
	{
		currentPointX = (objPosition.x - 29) / TILE_WIDTH;
		currentPointY = (objPosition.y - 29) / TILE_HIGHT;
	}

	//printf("%d |%d | %c\n", currentPointX, currentPointY, directionState);
}
