#ifndef TOWER
#define TOWER

#include <d3dx9.h>
#include <vector>

#include "../Object/GameObject.h"
#include "Character.h"
#include "../Component/EnemyController.h"
#include "../Component/Physics.h"

class Tower : public GameObject
{
private:

public:
	Tower();
	~Tower();

	void init();
	void fixUpdate();
	void update();
	void draw();
	void release();
	void inRange(std::vector<Character*>enemy);

	RECT towerRect;
	D3DXVECTOR2 spriteSize;

	int towerFrame;			//The Tower's animation at what frame in the sheet
	int towerNo;				//The No. of Tower in the sheet
	int frameNum;			//The Tower's animation have how many frame

	float animationSpeed;	//How many frame want to diplay in 1 second
	float frameRate;		//How many second display 1 frame
	float frameTimer;		//The timer of each frame

	float damage;			//Tower attack damage
	float atkSpeed;			//Tower attack speed
	float rangeRadius;
	float distanceX;
	float distanceY;
	float distance;
	bool isFire;
	int fireCD;
};

#endif // !TOWER