#ifndef PHYSICS
#define PHYSICS

#include <vector>
#include <d3dx9.h>
#include "../Object/Character.h"
#include "EnemyController.h"
//#include "TowerBuilding.h"
#include "Graphic.h"
#include "SoundManager.h"

class Physics
{
private:
	static Physics* sInstance;
	Physics();
	~Physics();

public:
	static Physics* getInstance();
	static void releaseInstance();

	void init();
	void draw();
	void update();
	void release();
	void projectile(D3DXVECTOR3 towerPosition, int enemyCount, int towerNo);

	HRESULT hr[2];
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 projectileTexture;
	D3DXMATRIX mat;
	D3DXVECTOR2 scaling;
	RECT projectileRect[4];
	D3DXVECTOR3 totalDistance;
	float tDistance;
	D3DXVECTOR3 projectilePosition;
	D3DXVECTOR3 enemyPosition;
	D3DXVECTOR3 drawPosition;
	bool isComplete;
	std::vector<D3DXVECTOR3> towerPositionList;
	std::vector<Character*>enemy;
	std::vector<int> enemyCountList;
	std::vector<int> tower;
	std::vector<D3DXVECTOR3> projectilePositionList;
	int timer;
	int towerDamage[4];

};

#endif // !DIRECT_INPUT