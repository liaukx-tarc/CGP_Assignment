#ifndef GAMESTATEMANAGER
#define GAMESTATEMANAGER
#include <stdio.h>
#include <string>
#include <vector>

#include "G_Timer.h"
#include "../Level/GameState.h"

#define GAME_FPS 60
#define MAX_LEVEL 2

class GameStateManager
{
private:
	static GameStateManager* sInstance;
	GameStateManager();
	~GameStateManager();

public:
	static GameStateManager* getInstance();
	static void releaseInstance();

	G_Timer * g_Timer;

	int currentState, preState;
	float framesToUpdate;
	std::vector<GameState*> stateList;
	std::string levelFileName;
	std::string levelName;

	bool isPause;

	//Start screen
	bool isStart;
	float timer;

	void update();
	void draw();
	void restart();

};

#endif // !GAMESTATEMANAGER