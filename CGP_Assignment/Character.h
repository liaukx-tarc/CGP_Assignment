#ifndef CHARACTER
#include <d3dx9.h>

class Character
{
public:
	Character();
	~Character();

	//Animation
	RECT charRect;			//the rect of the character sprite
	D3DXVECTOR2 charSize;	//character's size

	int charFrame;			//The character's animation at what frame in the sheet
	int charNo;				//The No. of character in the sheet
	int frameNum;			//The character's animation have how many frame

	float animationSpeed;	//How many frame want to diplay in 1 second
	float frameRate;		//How many second display 1 frame
	float frameTimer;		//The timer of each frame

	//Physics
	D3DXVECTOR2 charDirection;	//character's direction
	D3DXVECTOR3 charPosition;	//character's position
	D3DXVECTOR2 charVelocity;	//character's velocity

	float charSpeed;	//The movement speed of the character in 1 time
	
	void virtual init();
	void virtual draw();
	void virtual fixUpdate();
	void virtual update();
	void virtual release();
};

#endif // !CHARACTER