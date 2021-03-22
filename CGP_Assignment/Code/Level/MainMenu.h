#ifndef MAIN_MENU
#define MAIN_MENU

#include <d3dx9.h>
#include <vector>

#include "GameState.h"
#include "../Object/Button.h"

#define TITLE1 "TOWER"
#define TITLE2 "DEFENSE"
#define MADEBY "Made by Voong Meng & Kai Xian Team"

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
	LPD3DXFONT madeBy;

	LPDIRECT3DTEXTURE9 buttonTexture;
	LPDIRECT3DTEXTURE9 background;

	RECT backgroundRect;
	RECT titleRect1;
	RECT titleRect2;
	RECT madeByRect;

	std::vector<Button*> buttonList;
};

#endif //!MAIN_MENU