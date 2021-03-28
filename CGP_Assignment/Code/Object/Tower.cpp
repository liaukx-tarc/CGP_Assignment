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
	rangeRadius = 0;
}

Tower::~Tower()
{

}

void Tower::init()
{
	spriteSize.x = 96;
	spriteSize.y = 96;

	animationSpeed = 10;
	frameRate = 1.0f / animationSpeed;
	frameNum = 4;

	towerFrame = 0;

	rangeRadius = 150;

	towerRect.top = spriteSize.y* towerNo + 1;
	towerRect.left = spriteSize.x * towerFrame;
	towerRect.bottom = towerRect.top + spriteSize.y;
	towerRect.right = towerRect.left + spriteSize.x;

	isFire = false;
	fireCD = 0;
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
	inRange(EnemyController::getInstance()->enemyList);
	if (isFire)
	{
		fireCD -= 1;
		if (fireCD <= 0)
		{
			isFire = false;
		}
	}
}

void Tower::draw()
{

}

void Tower::release()
{

}
void Tower::inRange(std::vector<Character*>enemy)
{
	if (!isFire)
	{
		for (int i = 0; i < enemy.size(); i++)
		{
			if (!enemy[i]->isDead)
			{
				distanceX = objPosition.x - enemy[i]->objPosition.x;
				distanceY = objPosition.y - enemy[i]->objPosition.y;
				distance = sqrt((distanceX*distanceX) + (distanceY*distanceY));

				if (rangeRadius + enemy[i]->hitboxRadius > distance)
				{
					printf("%d in range\n", i);
					isFire = true;
					switch (towerNo)
					{
					case 0:
						fireCD = 50;
						break;
					case 1:
						fireCD = 20;
						break;
					case 2:
						fireCD = 40;
						break;
					case 3:
						fireCD = 80;
						break;
					}
					Physics::getInstance()->projectile(objPosition, i, towerNo);
					break;
				}
			}
		}
	}
}