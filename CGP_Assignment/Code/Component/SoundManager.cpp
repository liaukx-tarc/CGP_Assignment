#include "SoundManager.h"
#include <fmod.hpp>
#include "GameStateManager.h"

//singleton
SoundManager* SoundManager::sInstance = NULL;

SoundManager* SoundManager::getInstance()
{
	if (SoundManager::sInstance == NULL)
	{
		sInstance = new SoundManager;
	}

	return sInstance;
}

void SoundManager::releaseInstance()
{
	delete sInstance;
	sInstance = NULL;
}

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{

}

void SoundManager::init()
{
	system = NULL;
	result = FMOD::System_Create(&system);      // Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error!");
		PostQuitMessage(0);
	}

	result = system->init(100, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		if (result != FMOD_OK)
		{
			printf("FMOD error!");
			PostQuitMessage(0);
		}
	}
	system->createStream("resource/sound/MainMenu.mp3", FMOD_LOOP_NORMAL, 0 ,&mainMenuBGM);
	system->createStream("resource/sound/Level1.mp3", FMOD_LOOP_NORMAL, 0, &Level1BGM);
	system->createStream("resource/sound/Victory.mp3", FMOD_DEFAULT, 0, &VictoryBGM);
	system->createStream("resource/sound/Defeat.mp3", FMOD_DEFAULT, 0, &DefeatBGM);
	system->createSound("resource/sound/Shoot.mp3", FMOD_DEFAULT, 0, &shootSound);
	system->createSound("resource/sound/CrystalDamaged.mp3", FMOD_DEFAULT, 0, &crystalDamaged);
	system->createSound("resource/sound/CrystalDestroy.mp3", FMOD_DEFAULT, 0, &crystalDestroy);
	system->createSound("resource/sound/TowerBuild.mp3", FMOD_DEFAULT, 0, &towerBuild);
	channelBGM = NULL;
	system->playSound(mainMenuBGM, NULL, false, &channelBGM);
}

void SoundManager::update()
{
	system->update();
}

void SoundManager::bgm()
{
	channelBGM->stop();
	if (GameStateManager::getInstance()->currentState == 0)
	{
		system->playSound(mainMenuBGM, NULL, false, &channelBGM);
	}
	else
	{
		system->playSound(Level1BGM, NULL, false, &channelBGM);
	}
}
void SoundManager::winLoseBgm(bool isWin)
{
	channelBGM->stop();
	printf("winlose\n");
	if (isWin)
	{
		printf("win\n");
		system->playSound(VictoryBGM, NULL, false, &channelBGM);
	}
	else
	{
		printf("lose\n");
		system->playSound(DefeatBGM, NULL, false, &channelBGM);
	}
}

void SoundManager::sound(int count)
{
	switch (count)
	{
	case 1:
		system->playSound(shootSound, NULL, false, NULL);
		break;
	case 2:
		system->playSound(crystalDamaged, NULL, false, NULL);
		break;
	case 3:
		channelBGM->stop();
		system->playSound(crystalDestroy, NULL, false, NULL);
		break;
	case 4:
		system->playSound(towerBuild, NULL, false, NULL);
		break;
	}
}

void SoundManager::release()
{
	mainMenuBGM->release();
	Level1BGM->release();
	VictoryBGM->release();
	DefeatBGM->release();
	shootSound->release();
	system->release();
}

