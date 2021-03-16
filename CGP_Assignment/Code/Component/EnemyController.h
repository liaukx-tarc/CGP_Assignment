#ifndef ENEMYCONTROLLER
#define ENEMYCONTROLLER

#include <vector>

#include "../Enemy/Character.h"

#define MAX_ENEMY_ONEWAVE	50
#define MAX_WAVE			10

class EnemyController
{
private:
	static EnemyController* sInstance;
	EnemyController();
	~EnemyController();

public:
	static EnemyController* getInstance();
	static void releaseInsrance();

	HRESULT hr[3];

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();

	//enemy control
	LPDIRECT3DTEXTURE9 minionTexture;
	LPDIRECT3DTEXTURE9 bossTexture;

	LPD3DXSPRITE sprite;
	D3DXMATRIX mat;
	D3DXVECTOR2 charScaling;
	D3DXVECTOR3 drawPosition;

	int enemyNum;
	std::vector<Character*> enemyList;

	//Spawn
	int enemyWave[MAX_WAVE][MAX_ENEMY_ONEWAVE];
	int waveNum, currentWave;
	std::vector<Character*> spawnList;

	int spawnNum, totalSpawn[MAX_WAVE], spawnSpeed;
	float spawnTime;
	bool isNextWave;

	void enemySpawn();
};



#endif // !ENEMYCONTROLLER

