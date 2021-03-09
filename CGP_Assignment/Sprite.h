#ifndef SPRITE
#include <d3dx9.h>

class Sprite
{
private:
	static Sprite* sInstance;
	Sprite();
	~Sprite();

	HRESULT hr;

public:
	static Sprite* getInstance();
	static void releaseInsrance();

	LPDIRECT3DTEXTURE9 minionTexture;
	LPDIRECT3DTEXTURE9 bossTexture;

	void createSprite();
};

#endif // !SPRITE