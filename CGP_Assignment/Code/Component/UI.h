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

	HRESULT hr[14];

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
	LPDIRECT3DTEXTURE9 funcButtonTexture;

	std::vector<Button*> buttonList;

	RECT towerRect[MAX_TOWER_TYPE];

	int towerTextMove[MAX_TOWER_TYPE];
	int function;
	bool isFunction;

	//Function Menu
	LPDIRECT3DTEXTURE9 blurBackground;
	LPDIRECT3DTEXTURE9 menuBack;
	LPDIRECT3DTEXTURE9 yes_No;
	LPDIRECT3DTEXTURE9 menuButtonTexture;

	LPD3DXFONT menuFont;
	LPD3DXFONT menuButtonFont;
	
	//UI Element
	LPDIRECT3DTEXTURE9 heartTexture;
	RECT heartRect[2];
	RECT heartTextRect;
	D3DXVECTOR3 heartPos;
	std::string heartText;

	RECT waveTextRect;
	std::string waveText;

	LPDIRECT3DTEXTURE9 coinTexture;
	RECT coinTextRect;
	RECT coinRect;
	D3DXVECTOR3 coinPos;
	std::string coinText;

	RECT menuRect;
	RECT menuTextRect;
	RECT confrimRect[2];

	bool isConfirming, isMenu;
	std::string cfmWord;

	void backDraw();
	void pauseMenu();
	void pauseFunction();

	void stateUpdate(int maxHeart, int heart, int wave, int coin);
};

#endif //!MAIN_MENU