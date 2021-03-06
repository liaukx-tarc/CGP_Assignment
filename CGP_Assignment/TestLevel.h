#ifndef TEST_LEVEL
#include <d3dx9.h>
#include "GameState.h"

class TestLevel: public GameState
{
	public:
		TestLevel();
		~TestLevel();

		void init();
		void fixUpdate();
		void update();
		void draw();
		void release();
};

#endif

