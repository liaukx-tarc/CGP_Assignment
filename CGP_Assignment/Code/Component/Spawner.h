#ifndef SPAWNER
#define SPAWNER

#include <stdio.h>
#include <vector>

#include "../Enemy/Character.h"
#include "G_Timer.h"

#define ENEMY_TYPE_NUM	20
#define MAX_WAVE		10

class Spawner
{
private:
	static Spawner* sInstance;
	Spawner();
	~Spawner();

public:
	static Spawner* getInstance();
	static void releaseInsrance();

	int enemyWave[MAX_WAVE][ENEMY_TYPE_NUM];
	int waveNum, currentWave;
	std::vector<Character*> spawnList;

	G_Timer * spawn_Timer;
	int spawnNum, totalSpawn[MAX_WAVE], spawnSpeed;
	float spawnTime;
	bool isNextWave;

	void init();
	void release();

	void enemySpawn();
};

#endif // !SPAWNER