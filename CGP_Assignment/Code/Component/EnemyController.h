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

	HRESULT hr[4];

	void init();
	void fixUpdate();
	void update(int &coin, bool &isEnd, bool &isWin, int health);
	void draw();
	void release();

	//enemy control
	LPDIRECT3DTEXTURE9 minionTexture;
	LPDIRECT3DTEXTURE9 bossTexture;
	LPDIRECT3DTEXTURE9 explosionTexture;

	RECT explosionRect[4];
	D3DXVECTOR3 explosionPosition;
	int aniTimer;
	bool isComplete;

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

