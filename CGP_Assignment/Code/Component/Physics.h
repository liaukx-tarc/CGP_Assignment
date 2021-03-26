#ifndef PHYSICS
#define PHYSICS
#include <dinput.h>

class Physics
{
private:
	static Physics* sInstance;
	Physics();
	~Physics();

public:
	static Physics* getInstance();
	static void releaseInstance();
};

#endif // !DIRECT_INPUT