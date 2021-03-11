#ifndef DEMON_S
#define DEMON_S
#include "Character.h"

class Demon_S : public Character
{
public:
	Demon_S();
	~Demon_S();

	void init();
	void draw();
	void fixUpdate();
	void update();
	void release();
};

#endif // !Demon_S