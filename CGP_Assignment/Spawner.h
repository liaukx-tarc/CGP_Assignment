#ifndef SPAWNER
#include <stdio.h>
#include <vector>

#include "Demon_S.h"

class Spawner
{
private:
	static Spawner* sInstance;
	Spawner();
	~Spawner();

public:
	static Spawner* getInstance();
	static void releaseInsrance();

	HRESULT hr;
	LPD3DXSPRITE sprite;
	D3DXMATRIX mat;
	D3DXVECTOR2 charScaling;

	std::vector<Character*> enemyList;

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();

	void enemySpawn();
};

#endif // !SPAWNER



