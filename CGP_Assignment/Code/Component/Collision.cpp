#include <stdio.h>
#include "Collision.h"

#define TOP_FIX		0.2f
#define BOTTOM_FIX	0.3f
#define LEFT_FIX	0.4f
#define RIGHT_FIX	0.3f

//singleton
Collision* Collision::sInstance = NULL;

Collision* Collision::getInstance()
{
	if (Collision::sInstance == NULL)
	{
		sInstance = new Collision;
	}

	return sInstance;
}

void Collision::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::colliDetect(GameObject * object, std::vector<GameObject*> targetList)
{
	objRect.top = object->objPosition.y - ((object->objSize.y / (2 + BOTTOM_FIX))* 3.0f);
	objRect.bottom = objRect.top + (object->objSize.y / (1 + TOP_FIX))* 3.0f;
	objRect.left = object->objPosition.x - ((object->objSize.x / (2 + LEFT_FIX))* 3.0f);
	objRect.right = objRect.left + (object->objSize.x / (1 + RIGHT_FIX)) *  3.0f;

	for (int i = 0; i < targetList.size(); i++)
	{
		targetRect.top = targetList[i]->objPosition.y - ((targetList[i]->objSize.y / (2 + TOP_FIX)) * 3.0f);
		targetRect.bottom = targetRect.top + (targetList[i]->objSize.y / (1 + BOTTOM_FIX))* 3.0f;
		targetRect.left = targetList[i]->objPosition.x - ((targetList[i]->objSize.x / (2 + RIGHT_FIX))* 3.0f);
		targetRect.right = targetRect.left + (targetList[i]->objSize.x / (1 + LEFT_FIX))* 3.0f;

		if (objRect.bottom < targetRect.top)
		{
			return false;
		}

		if (objRect.top > targetRect.bottom)
		{
			return false;
		}

		if (objRect.right < targetRect.left) 
		{
			return false;
		}

		if (objRect.left > targetRect.right)
		{
			return false;
		}

		else
			return true;
	}
}