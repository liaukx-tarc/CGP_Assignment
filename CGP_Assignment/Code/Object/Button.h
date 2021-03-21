#ifndef BUTTON
#define BUTTON

#include <d3dx9.h>
#include <string>

class Button
{
public:
	Button();
	~Button();

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();

	D3DXVECTOR2 position;
	D3DXVECTOR2 size;
	RECT buttonRect;
	RECT textRect;

	int r,g,b;

	int frame;
	std::string word;
	
	bool isClick, isAni;
	D3DXVECTOR2 mousePos;
	RECT positionRect;
};

#endif //!MAIN_MENU