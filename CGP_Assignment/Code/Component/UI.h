#ifndef UI
#define UI

#include <d3dx9.h>
#include <vector>

#include "../Object/Button.h"
#include "TowerBuilding.h"

#define TOWER_BUTTON_NUM	4
#define FUNC_BUTTON_NUM		6
#define MENU_BUTTON_NUM		9
#define CONFIRM_BUTTON_NUM	11

#define TOWER1		0
#define TOWER2		1
#define TOWER3		2
#define TOWER4		3
#define PAUSE		4
#define SETTING		5
#define RESUME		6
#define RESTART		7
#define MAIN_MENU	8
#define YES			9
#define NO			10

class Ui
{
public:
	Ui();
	~Ui();

	HRESULT hr[14];

	void init();
	void fixUpdate();
	void update(int coin);
	void draw();
	void release();

	LPD3DXSPRITE sprite;
	LPD3DXFONT buttonFont;
	D3DXVECTOR2 scaling;
	D3DXMATRIX mat;

	float aniTimer;

	//UI
	LPDIRECT3DTEXTURE9 backgroundTexture;
	LPDIRECT3DTEXTURE9 buttonTexture;
	LPDIRECT3DTEXTURE9 funcButtonTexture;

	std::vector<Button*> buttonList;

	RECT towerRect[MAX_TOWER_TYPE];
	RECT pauseButtonRect[2];
	
	D3DXVECTOR2 coinPosition[4];
	std::string towerPrice[4];
	RECT towerPriceText[4];

	bool noCoin;
	int wrongTowerNum;

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
	int coinColor[3];

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