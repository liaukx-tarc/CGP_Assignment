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
	void bgm();
	void winLoseBgm(bool isWin);
	void sound(int count);
	void release();
	FMOD_RESULT result;
	FMOD::System *system;
	FMOD::Sound *mainMenuBGM;
	FMOD::Sound *Level1BGM;
	FMOD::Sound *VictoryBGM;
	FMOD::Sound *DefeatBGM;
	FMOD::Sound *shootSound;
	FMOD::Sound *crystalDamaged;
	FMOD::Sound *crystalDestroy;
	FMOD::Sound *towerBuild;
	FMOD::Channel *channelBGM;



};

#endif // !SOUNDMANAGER
