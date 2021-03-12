#include "Character.h"
#include "../Component/DirectInput.h"
#include "../Component/Graphic.h"
#include "../Component/Sprite.h"

#include <stdio.h>

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

	charState = 1; //0 = idle, 1 = move
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
	objPosition.x += direction.x * (0.05f * charSpeed);
	objPosition.y += direction.y * (0.05f * charSpeed);
}
