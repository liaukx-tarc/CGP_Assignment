#ifndef COLLISION
#define COLLISION

#include <vector>

#include "../GameObject.h"

class Collision
{
private:
	static Collision* sInstance;
	Collision();
	~Collision();

public:
	static Collision* getInstance();
	static void releaseInsrance();

	RECT objRect, targetRect;

	bool colliDetect(GameObject * object, std::vector<GameObject*> targetList);
};

#endif // !COLLISION
