#include "Tower.h"

#include <stdio.h>

Tower::Tower()
{
	towerFrame = 0;
	towerNo = 0;
	frameNum = 0;

	animationSpeed = 0;
	frameRate = 0;
	frameTimer = 0;
}

Tower::~Tower()
{

}

void Tower::init()
{
	spriteSize.x = 46;
	spriteSize.y = 90;

	animationSpeed = 10;
	frameRate = 1.0f / animationSpeed;
	frameNum = 4;

	towerFrame = 0;

	towerRect.top = spriteSize.y* towerNo + 1;
	towerRect.left = spriteSize.x * towerFrame;
	towerRect.bottom = towerRect.top + spriteSize.y;
	towerRect.right = towerRect.left + spriteSize.x;
}

void Tower::fixUpdate()
{
	frameTimer += 1.0f / 60;

	if (frameTimer >= frameRate)
	{
		frameTimer -= frameRate;
		towerFrame++;
		towerFrame %= frameNum;
	}

	towerRect.top = spriteSize.y * towerNo + 1;
	towerRect.bottom = towerRect.top + spriteSize.y;
	towerRect.left = spriteSize.x * towerFrame;
	towerRect.right = towerRect.left + spriteSize.x;
}

void Tower::update()
{
	
}

void Tower::draw()
{

}

void Tower::release()
{

}