#include "Character.h"
#include "../Component/DirectInput.h"
#include "../Component/Graphic.h"
#include "../Component/Sprite.h"

#include <stdio.h>

Character::Character()
{
	ZeroMemory(&charRect, sizeof(charRect));			
	ZeroMemory(&charSize, sizeof(charSize));			
	ZeroMemory(&charDirection, sizeof(charDirection));	
	ZeroMemory(&charPosition, sizeof(charPosition));	
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
	charSize.x = 20;
	charSize.y = 30;

	charRect.top = 30 * charNo;
	charRect.left = 0;
	charRect.bottom = charRect.top + charSize.y;
	charRect.right = charRect.right + charSize.x;

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
	charRect.bottom = charRect.top + charSize.y;
	charRect.left = 20 * (charFrame + (charState * 4));
	charRect.right = charRect.left + charSize.x;
}

void Character::update()
{
	if (DirectInput::getInstance()->diKeys[DIK_UP])
	{
		charDirection.x = 0;
		charDirection.y = -1;
		charState = 1;
	}

	else if (DirectInput::getInstance()->diKeys[DIK_DOWN])
	{
		charDirection.x = 0;
		charDirection.y = 1;
		charState = 1;
	}

	else
	{
		charDirection.x = 0;
		charDirection.y = 0;
		charState = 0;
	}

	move(charDirection);

}

void Character::release()
{

}

void Character::move(D3DXVECTOR2 direction)
{
	charPosition.x += direction.x * (0.01f * charSpeed);
	charPosition.y += direction.y * (0.01f * charSpeed);
}
