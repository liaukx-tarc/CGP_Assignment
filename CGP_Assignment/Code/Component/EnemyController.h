#ifndef ENEMYCONTROLLER
#define ENEMYCONTROLLER

#include <vector>

#include "../Object/Character.h"
#include "../Object/Spawner.h"
#include "Map.h"

class EnemyController
{
private:
	static EnemyController* sInstance;
	EnemyController();
	~EnemyController();

public:
	static EnemyController* getInstance();
	static void releaseInstance();

	HRESULT hr[3];

	void init();
	void fixUpdate();
	void update(int &coin, bool &isEnd, bool &isWin);
	void draw();
	void release();

	//enemy control
	LPDIRECT3DTEXTURE9 minionTexture;
	LPDIRECT3DTEXTURE9 bossTexture;

	LPD3DXSPRITE sprite;

	int enemyNum;
	int dieEnemyNum;
	std::vector<Character*> enemyList;

	//Enemy Data
	std::vector<Character*> enemyData;

	//Spawn
	int enemyWave[MAX_WAVE][MAX_ENEMY_ONEWAVE];
	int waveNum, currentWave;
	std::vector<Character*> spawnList;

	int totalSpawn[MAX_WAVE];
	bool isNextWave;
	std::vector<Spawner*> spawnerList;
};



#endif // !ENEMYCONTROLLER

