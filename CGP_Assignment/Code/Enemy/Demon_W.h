#ifndef DEMON_W
#include "Character.h"

class Demon_W : public Character
{
public:
	Demon_W();
	~Demon_W();

	void init();
	void draw();
	void fixUpdate();
	void update();
	void release();
};

#endif // !Demon_W