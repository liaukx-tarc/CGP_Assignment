#include "Graphic.h"
#include "GameWindows.h"
#include "GameStateManager.h"

//singleton
Graphic* Graphic::sInstance = NULL;

Graphic* Graphic::getInstance()
{
	if (Graphic::sInstance == NULL)
	{
		sInstance = new Graphic;
	}

	return sInstance;
}

void Graphic::releaseInsrance()
{
	delete sInstance;
	sInstance = NULL;
}

Graphic::Graphic()
{
	ZeroMemory(&d3dPP, sizeof(d3dPP));
	d3dDevice = NULL;
	direct3D9 = NULL;

}

Graphic::~Graphic()
{
	d3dDevice->Release();
	d3dDevice = NULL;

	sprite->Release();
	sprite = NULL;

	cursorTexture->Release();
	cursorTexture = NULL;
}

void Graphic::createGraphic()
{
	direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = BUFFER_WIDTH;
	d3dPP.BackBufferHeight = BUFFER_HEIGHT;
	d3dPP.hDeviceWindow = GameWindows::getInstance()->g_hWnd;

	hr[0] = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GameWindows::getInstance()->g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
	
	//cursor
	hr[1] = D3DXCreateSprite(Graphic::getInstance()->d3dDevice, &sprite);
	hr[2] = D3DXCreateTextureFromFile(Graphic::getInstance()->d3dDevice, "resource/Cursor.png", &cursorTexture);

	for (int i = 0; i < sizeof(hr); i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}

	cursorRect.top = cursorRect.left = 0;
	cursorRect.bottom = cursorRect.right = 32;

	scaling.x = scaling.y = 1.5f;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, NULL);
}

void Graphic::graphicLoop()
{
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3dDevice->BeginScene();

	GameStateManager::getInstance()->draw();
	drawCursor();

	d3dDevice->EndScene();

	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Graphic::drawCursor()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);

	sprite->Draw(cursorTexture, &cursorRect, 
		&D3DXVECTOR3(cursorRect.left, cursorRect.top, 0), 
		&D3DXVECTOR3(GameWindows::getInstance()->mousePos.x / scaling.x, GameWindows::getInstance()->mousePos.y / scaling.y, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();
}