#ifndef PHYSICS
#define PHYSICS

#include <vector>
#include <d3dx9.h>

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
	void projectile(D3DXVECTOR3 towerPosition, D3DXVECTOR3 enemyPosition);

	HRESULT hr[2];
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 projectileTexture;
	D3DXMATRIX mat;
	D3DXVECTOR2 scaling;
	RECT projectileRect;
	D3DXVECTOR3 totalDistance;
	D3DXVECTOR3 currentDistance;
	float tDistance;
	float cDistance;
	D3DXVECTOR3 projectilePosition;
	D3DXVECTOR3 drawPosition;
	bool isComplete;
	std::vector<D3DXVECTOR3> towerPositionList;
	std::vector<D3DXVECTOR3> enemyPositionList;
	std::vector<D3DXVECTOR3> projectilePositionList;
	int timer;

};

#endif // !DIRECT_INPUT