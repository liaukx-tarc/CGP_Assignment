#pragma once
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

	HRESULT hr;
	LPD3DXSPRITE sprite;
	D3DXMATRIX mat;
	D3DXVECTOR2 charScaling;

	int enemyWave[MAX_WAVE][ENEMY_TYPE_NUM];
	int waveNum, enemyNum, currentWave;
	std::vector<Character*> spawnList;
	std::vector<Character*> enemyList;

	G_Timer * spawn_Timer;
	int spawnNum, totalSpawn[MAX_WAVE], spawnSpeed;
	float spawnTime;
	bool isSpawn, isNextWave;

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();

	void enemySpawn();
};
