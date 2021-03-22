#ifndef MAIN_MENU
#define MAIN_MENU

#include <d3dx9.h>
#include <vector>

#include "GameState.h"
#include "../Object/Button.h"

class MainMenu : public GameState
{
public:
	MainMenu();
	~MainMenu();

	HRESULT hr[5];

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

	LPDIRECT3DTEXTURE9 buttonTexture;
	LPDIRECT3DTEXTURE9 background;

	RECT backgroundRect;

	std::vector<Button*> buttonList;
	
};

#endif //!MAIN_MENU