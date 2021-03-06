#ifndef TILE
#include <d3dx9.h>

#define MAX_MAP_Y 21
#define MAX_MAP_X 38
#define TILE_HIGHT 60
#define TILE_WIDTH 60

class Tile
{
private:
	static Tile* sInstance;
	Tile();
	~Tile();

	HRESULT hr;

public:
	static Tile* getInstance();
	static void releaseInsrance();

	RECT tileRect;
	LPDIRECT3DTEXTURE9 tile;
	LPD3DXSPRITE sprite;
	D3DXMATRIX mat;
	D3DXVECTOR2 scaling;

	int map[MAX_MAP_Y][MAX_MAP_X], tileCol, tileRow;
	RECT clipWindow;
	D3DXVECTOR3 pos;

	void createTile();

	void loadMap(char * name);
	void drawMap();
};
#endif // !TILE