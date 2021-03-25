#ifndef UI
#define UI

#include <d3dx9.h>
#include <vector>

#include "../Object/Button.h"
#include "TowerBuilding.h"

class Ui
{
public:
	Ui();
	~Ui();

	HRESULT hr[11];

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();

	LPD3DXSPRITE sprite;
	LPD3DXFONT buttonFont;
	D3DXVECTOR2 scaling;
	D3DXMATRIX mat;
	

	//UI
	LPDIRECT3DTEXTURE9 backgroundTexture;
	LPDIRECT3DTEXTURE9 buttonTexture;

	std::vector<Button*> buttonList;

	RECT towerRect[MAX_TOWER_TYPE];

	int towerTexMove[MAX_TOWER_TYPE];
	int function;
	bool isFunction;

	//Function Menu
	LPDIRECT3DTEXTURE9 blurBackground;
	LPDIRECT3DTEXTURE9 menuBack;
	LPDIRECT3DTEXTURE9 yes_No;
	LPDIRECT3DTEXTURE9 menuButtonTexture;

	LPD3DXFONT menuFont;
	LPD3DXFONT menuButtonFont;
	RECT menuRect;
	RECT menuTextRect;
	RECT confrimRect[2];

	bool isConfirming;
	std::string cfmWord;

	void backDraw();
	void pauseMenu();
	void pauseFunction();
};

#endif //!MAIN_MENU