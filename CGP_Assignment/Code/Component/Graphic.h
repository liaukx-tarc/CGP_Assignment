#ifndef GRAPHIC
#define GRAPHIC
#include <d3d9.h>
#include <d3dx9.h>

class Graphic
{
private:
	static Graphic* sInstance;
	Graphic();
	~Graphic();

	HRESULT hr;

public:
	static Graphic* getInstance();
	static void releaseInsrance();

	D3DPRESENT_PARAMETERS d3dPP;
	IDirect3DDevice9 * d3dDevice;
	IDirect3D9 * direct3D9;

	void createGraphic();
	void graphicLoop();
};

#endif // !GRAPHIC



