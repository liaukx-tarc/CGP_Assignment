#ifndef MAIN_MENU
#define MAIN_MENU

#include <d3dx9.h>
#include <vector>

#include "GameState.h"
#include "../Object/Button.h"

#define TITLE1 "TOWER"
#define TITLE2 "DEFENSE"
#define MADEBY "Made by Voon Meng & Kai Xian"

class MainMenu : public GameState
{
public:
	MainMenu();
	~MainMenu();

	HRESULT hr[7];

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();

	int function;
	float timer;
	bool isFunction;

	LPD3DXSPRITE sprite;
	LPD3DXFONT font;
	LPD3DXFONT title;
	LPD3DXFONT title2;
	LPD3DXFONT madeBy;

	LPDIRECT3DTEXTURE9 buttonTexture;
	LPDIRECT3DTEXTURE9 background;

	RECT backgroundRect;
	RECT titleRect1;
	RECT titleRect2;
	RECT titleRect3;
	RECT titleRect4;
	RECT madeByRect;

	std::vector<Button*> buttonList;
};

#endif //!MAIN_MENU