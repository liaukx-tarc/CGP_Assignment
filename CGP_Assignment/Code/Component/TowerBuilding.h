#ifndef TOWER_BUILDING
#define TOWER_BUILDING

#include <d3dx9.h>

class TowerBuilding
{
private:
	HRESULT hr[2];

	//mouse
	D3DXVECTOR2 mousePos;

	//sprite
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 towerTexture;
	RECT towerRect;

public:
	TowerBuilding();
	~TowerBuilding();

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();


};

#endif // !TOWERBUILDING


