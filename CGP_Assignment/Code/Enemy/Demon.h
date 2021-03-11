#ifndef DEMON
#define DEMON
#include "Character.h"

class Demon : public Character
{
public:
	Demon();
	~Demon();

	void init();
	void draw();
	void fixUpdate();
	void update();
	void release();
};

#endif // !Demon
