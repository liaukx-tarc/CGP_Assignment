#ifndef UI
#define UI

#include <d3dx9.h>
#include <vector>

#include "../Object/Button.h"
#include "TowerBuilding.h"

#define TOWER_BUTTON_NUM	5
#define FUNC_BUTTON_NUM		7
#define MENU_BUTTON_NUM		10
#define CONFIRM_BUTTON_NUM	12
#define WIN_BUTTON_NUM		14
#define LOSE_BUTTON_NUM		15

#define TOWER1			0
#define TOWER2			1
#define TOWER3			2
#define TOWER4			3
#define DESTROY			4
#define PAUSE			5
#define SETTING			6
#define RESUME			7
#define RESTART			8
#define MAIN_MENU		9
#define YES				10
#define NO				11
#define NEXT_LEVEL		12
#define WIN_LOSE_MENU	13
#define LOSE_RESTART	14

class Ui
{
public:
	Ui();
	~Ui();

	HRESULT hr[15];

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
	
	//UI Element
	//HP
	LPDIRECT3DTEXTURE9 heartTexture;
	D3DXVECTOR3 heartPos;
	RECT heartRect[2];
	RECT heartTextRect;

	std::string heartText;

	//Wave
	RECT waveTextRect;

	std::string waveText;

	//Coin
	LPDIRECT3DTEXTURE9 coinTexture;
	D3DXVECTOR3 coinPos;
	RECT coinTextRect;
	RECT coinRect;
	
	std::string coinText;
	int coinColor[3];

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

	bool isConfirming, isMenu;
	std::string cfmWord;

	void backDraw();
	void pauseMenu();
	void pauseFunction();

	void stateUpdate(int maxHeart, int heart, int wave, int coin);

	//Win and Lose Screen
	LPD3DXFONT winLoseFont;
	RECT winRect;
	RECT loseRect;

	void winLoseFunction(bool isWin);
	void winLoseDraw(bool isWin);
};

#endif //!MAIN_MENU