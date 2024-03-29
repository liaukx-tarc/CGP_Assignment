#ifndef TOWER_BUILDING
#define TOWER_BUILDING

#include "../Object/Tower.h"
#include "Map.h"
#include "DirectInput.h"
#include "GameWindows.h"
#include "Graphic.h"
#include "SoundManager.h"
#include "Physics.h"

#include <d3dx9.h>
#include <vector>

#define MAX_TOWER_TYPE 4

class TowerBuilding
{
private:
	static TowerBuilding * sInstance;
	TowerBuilding();
	~TowerBuilding();

public:
	//Singleton
	static TowerBuilding * getInstance();
	static void releaseInstance();

	HRESULT hr[3];

	//mouse
	D3DXVECTOR2 mousePos;

	//keyboard
	int keyIn;

	//sprite
	LPD3DXSPRITE sprite;

	LPDIRECT3DTEXTURE9 towerTexture;
	RECT towerRect;
	
	LPDIRECT3DTEXTURE9 selectBoxTeture;
	RECT selectBoxRect;
	int boxFrame;

	float frameRate;		//How many second display 1 frame
	float frameTimer;		//The timer of each frame

	//building / Destroy
	int tileSelectX, tileSelectY; //Selected tile
	int towerSelect;
	bool isBuilding;
	bool isDestroy;
	D3DXVECTOR2 buildPos;

	std::vector<Tower*> towerData;
	Tower * towerList[MAX_MAP_Y][MAX_MAP_X];
	
	void init();
	void fixUpdate();
	void update(int &coin);
	void draw();
	void release();
};

#endif // !TOWERBUILDING


