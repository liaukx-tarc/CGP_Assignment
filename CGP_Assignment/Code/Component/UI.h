#ifndef UI
#define UI

#include <d3dx9.h>
#include <vector>

#include "../Object/Button.h"

#define UI_X_FIX 20

class Ui
{
public:
	Ui();
	~Ui();

	HRESULT hr[3];

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();

	void backDraw();

	LPD3DXSPRITE sprite;

	LPDIRECT3DTEXTURE9 backgroundTexture;
	LPDIRECT3DTEXTURE9 buttonTexture;

	std::vector<Button*> buttonList;

	D3DXVECTOR2 mapPos;
};

#endif //!MAIN_MENU