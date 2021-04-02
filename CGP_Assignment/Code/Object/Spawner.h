#ifndef SPAWNER
#define SPAWNER

#include <d3dx9.h>
#include <vector>

#include "Character.h"

class Spawner
{
public:
	Spawner();
	~Spawner();

	void init();
	void update();

	int wave,totalSpawn, enemyNum, currentSpawnMax;

	int spawnNum, spawnSpeed;
	float spawnTime;
};

#endif // !SPAWNER