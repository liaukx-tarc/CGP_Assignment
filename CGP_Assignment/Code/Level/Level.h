#ifndef TEST_LEVEL
#define TEST_LEVEL

#include <d3dx9.h>
#include <string>

#include "GameState.h"

#define MAX_MAP_Y 21
#define MAX_MAP_X 38

class Level : public GameState
{
public:
	Level();
	~Level();

	char * levelFile;
	bool isWin;
	bool isEnd;
	bool isPlay;

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();

	int maxHealth, health, wave, coin;
	D3DXVECTOR2 crystalPos;
};

#endif