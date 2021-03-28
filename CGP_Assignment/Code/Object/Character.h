#ifndef CHARACTER
#define CHARACTER

#include <d3dx9.h>
#include <vector>

#include "../Component/Map.h"
#include "GameObject.h"

class Character : public GameObject
{
public:
	Character();
	~Character();

	//Animation
	RECT charRect;			//the rect of the character sprite
	D3DXVECTOR2 spriteSize;

	int charFrame;			//The character's animation at what frame in the sheet
	int charNo;				//The No. of character in the sheet
	int frameNum;			//The character's animation have how many frame

	int r, g, b;

	int pathRoute[MAX_MAP_Y][MAX_MAP_X]; // get path from map
	D3DXVECTOR2 startPoint;
	D3DXVECTOR2 endPoint;
	int currentPointX;
	int currentPointY;
	char directionState;
	int leftX;
	int leftY;
	int rightX;
	int rightY;
	int topX;
	int topY;
	int btmX;
	int btmY;

	float animationSpeed;	//How many frame want to diplay in 1 second
	float frameRate;		//How many second display 1 frame
	float frameTimer;		//The timer of each frame

	//Physics
	D3DXVECTOR2 charDirection;	//character's direction
	D3DXVECTOR2 charVelocity;	//character's velocity

	int charState;		//Character State. 0 = idle, 1 = move

	float health;
	float charSpeed;	//The movement speed of the character in 1 time
	float speedFactor;
	bool isSlow;
	int slowTimer;
	bool isHit;
	int hitTimer;
	bool isDead;
	
	float hitboxRadius;

	void init();
	void draw();
	void fixUpdate();
	void update();
	void release();
	void move(D3DXVECTOR2 direction);
};

#endif // !CHARACTER
