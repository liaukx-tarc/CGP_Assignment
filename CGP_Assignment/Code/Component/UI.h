#ifndef UI
#define UI

#include <d3dx9.h>
#include <vector>

#include "../Object/Button.h"

class Ui
{
public:
	Ui();
	~Ui();

	HRESULT hr[5];

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();

	void backDraw();

	LPD3DXSPRITE sprite;
	LPD3DXFONT font;

	LPDIRECT3DTEXTURE9 backgroundTexture;
	LPDIRECT3DTEXTURE9 buttonTexture;

	std::vector<Button*> buttonList;

	int function;
	bool isFunction;
};

#endif //!MAIN_MENU