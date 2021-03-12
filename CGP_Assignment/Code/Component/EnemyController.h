#ifndef ENEMYCONTROLLER
#define ENEMYCONTROLLER

#include <vector>

#include "../Enemy/Character.h"

class EnemyController
{
private:
	static EnemyController* sInstance;
	EnemyController();
	~EnemyController();

public:
	static EnemyController* getInstance();
	static void releaseInsrance();

	HRESULT hr;

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();

	LPD3DXSPRITE sprite;
	D3DXMATRIX mat;
	D3DXVECTOR2 charScaling;
	D3DXVECTOR3 drawPosition;

	int enemyNum;
	std::vector<Character*> enemyList;
};



#endif // !ENEMYCONTROLLER

