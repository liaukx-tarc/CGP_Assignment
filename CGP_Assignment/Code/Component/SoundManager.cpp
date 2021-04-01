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

	result = system->init(50, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		if (result != FMOD_OK)
		{
			printf("FMOD error!");
			PostQuitMessage(0);
		}
	}
	system->createStream("resource/sound/Windless Slopes.mp3",FMOD_DEFAULT, 0 ,&mainMenuBGM);
	system->createStream("resource/sound/Level1.mp3", FMOD_DEFAULT, 0, &Level1BGM);
	channelBGM = NULL;
	system->playSound(mainMenuBGM, NULL, false, &channelBGM);
}

void SoundManager::update()
{
	system->update();
}

void SoundManager::sound()
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

void SoundManager::release()
{
	mainMenuBGM->release();
	system->release();
}

