#ifndef TEST_LEVEL
#define TEST_LEVEL

#include <d3dx9.h>
#include <string>

#include "GameState.h"

#define MAX_MAP_Y 21
#define MAX_MAP_X 38

class TestLevel : public GameState
{
public:
	TestLevel();
	~TestLevel();
	
	char * levelFile;

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();
};

#endif

