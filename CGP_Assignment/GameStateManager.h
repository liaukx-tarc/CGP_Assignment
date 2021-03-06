#ifndef GAMESTATEMANAGER
#include <stdio.h>
#include <vector>

#include "G_Timer.h"
#include "GameState.h"

#define GAME_FPS 60

class GameStateManager
{
private:
	static GameStateManager* sInstance;
	GameStateManager();
	~GameStateManager();

public:
	static GameStateManager* getInstance();
	static void releaseInsrance();

	G_Timer * g_Timer;

	int currentState, preState;
	float framesToUpdate;
	std::vector<GameState*> stateList;

	void update();
	void draw();

};

#endif // !GAMESTATEMANAGER