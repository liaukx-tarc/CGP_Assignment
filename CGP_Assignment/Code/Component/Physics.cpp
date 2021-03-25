#include "Physics.h"

//singleton
Physics* Physics::sInstance = NULL;

Physics* Physics::getInstance()
{
	if (Physics::sInstance == NULL)
	{
		sInstance = new Physics;
	}

	return sInstance;
}

void Physics::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

Physics::Physics()
{
	
}

Physics::~Physics()
{
	
}
