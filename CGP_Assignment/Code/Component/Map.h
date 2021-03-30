#ifndef MAP
#define MAP
#include <d3dx9.h>

#define MAX_ENEMY_TYPE		17
#define MAX_ENEMY_ONEWAVE	50
#define MAX_WAVE			10

#define MAX_MAP_Y 12
#define MAX_MAP_X 32
#define TILE_HEIGHT 60
#define TILE_WIDTH 60
#define MAX_START 4
#define MAX_END 4

class Map
{
private:
	static Map* sInstance;
	Map();
	~Map();

	HRESULT hr[3];

public:
	static Map* getInstance();
	static void releaseInstance();

	LPD3DXSPRITE sprite;

	float aniTimer;

	LPDIRECT3DTEXTURE9 tile;
	LPDIRECT3DTEXTURE9 crystalTexture;

	RECT tileRect;
	RECT crystalRect;

	D3DXVECTOR3 crystalPos;
	int crystalState;
	int crystalFrame;
	int maxFrame;
	int crystalColor[2];

	//tile map
	int map[MAX_MAP_Y][MAX_MAP_X];
	int pathMap[MAX_MAP_Y][MAX_MAP_X];
	int tileCol, tileRow;
	RECT clipWindow;
	D3DXVECTOR3 pos;

	//path map
	int startPointNum, endPointNum;
	int spawnPoint[MAX_WAVE], targetPoint[MAX_WAVE];
	D3DXVECTOR2 startPoint[MAX_START], endPoint[MAX_END];

	void createMap();

	void fixUpdate();

	void loadMap(char * name, int &maxHealth, int &coin);
	void drawMap();
};
#endif // !MAP