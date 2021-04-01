#ifndef SOUNDMANAGER
#define SOUNDMANAGER
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <fmod.hpp>

#define GAME_FPS 60
#define MAX_LEVEL 2

class SoundManager
{
private:
	static SoundManager* sInstance;
	SoundManager();
	~SoundManager();

public:
	static SoundManager* getInstance();
	static void releaseInstance();

	void init();
	void update();
	void sound();
	void release();
	FMOD_RESULT result;
	FMOD::System *system;
	FMOD::Sound *mainMenuBGM;
	FMOD::Sound *Level1BGM;
	FMOD::Channel *channelBGM;

};

#endif // !SOUNDMANAGER
