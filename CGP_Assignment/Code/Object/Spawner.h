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
	std::vector<Character*> spawnList;

	int spawnNum, spawnSpeed;
	float spawnTime;
};

#endif // !SPAWNER