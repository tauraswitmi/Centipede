// SoundManager.h
// Charles Tiemeyer, Nov 2024


#include "SoundManager.h"

#include <iostream>
#include <list>
#include "CMDSound.h"
#include "CMDSoundLoop.h"
#include "CMDSoundSingle.h"
#include "GameManager.h"
#include "Player.h"



std::list<CMDSound*> SoundManager::Sounds;
bool SoundManager::muted = true;
float SoundManager::volume = 0;
SoundManager* SoundManager::ptrInstance = nullptr;

SoundManager::SoundManager()
{

}


CMDSound* SoundManager::GetScoreCommand(SoundEvents ev)
{
	CMDSound* pCmd = nullptr;

	switch (ev)
	{
	case SoundEvents::Centipede:
		pCmd = new CMDSoundLoop(ResourceManager::GetSound("Centipede"), volume);
		break;

	case SoundEvents::Flea:
		pCmd = new CMDSoundSingle(ResourceManager::GetSound("Flea"), volume);
		break;

	case SoundEvents::Scorpion:
		pCmd = new CMDSoundLoop(ResourceManager::GetSound("Scorpion"), volume);
		break;

	case SoundEvents::Spider:
		pCmd = new CMDSoundLoop(ResourceManager::GetSound("Spider"), volume);
		break;

	case SoundEvents::Fire:
		pCmd = new CMDSoundSingle(ResourceManager::GetSound("Fire"), volume);
		break;

	case SoundEvents::Kill:
		pCmd = new CMDSoundSingle(ResourceManager::GetSound("Kill"), volume);
		break;

	case SoundEvents::Death:
		pCmd = new CMDSoundSingle(ResourceManager::GetSound("Death"), volume);
		break;

	case SoundEvents::Replenish:
		pCmd = new CMDSoundSingle(ResourceManager::GetSound("Replenish"), volume);
		break;

	case SoundEvents::Extra_Life:
		pCmd = new CMDSoundSingle(ResourceManager::GetSound("Extra_Life"), volume);
		break;


	default:
		break;
	}

	Sounds.push_back(pCmd);

	return pCmd;
}



void SoundManager::Mute()
{
	muted = true;
	std::for_each(Sounds.begin(), Sounds.end(), [](CMDSound* m) {m->SetVolume(0); });
}
void SoundManager::UnMute()
{
	muted = false;
	std::for_each(Sounds.begin(), Sounds.end(), [](CMDSound* m) {m->SetVolume(volume); });
}


void SoundManager::SendSoundCMD(CMDSound* c)
{
	Instance().QueueCMDs.push(c);
}
void SoundManager::SendPauseCMD(CMDSound* c)
{
	Instance().QueuePauseCMDs.push(c);
}


void SoundManager::ProcessSounds()
{
	Instance().privProcessSounds();
}
void SoundManager::ProcessPause()
{
	Instance().privProcessPause();
}


void SoundManager::privProcessSounds()
{
	printf("\n\tProcessing all scores commands for this frame:\n");

	CMDSound* c;

	while (!QueueCMDs.empty())
	{
		c = QueueCMDs.front();
		c->Execute();

		QueueCMDs.pop();
	}
}
void SoundManager::privProcessPause()
{
	printf("\n\tProcessing all scores commands for this frame:\n");

	CMDSound* c;

	while (!QueuePauseCMDs.empty())
	{
		c = QueuePauseCMDs.front();
		c->Pause();

		QueuePauseCMDs.pop();
	}
}


void SoundManager::Initialize(int gameMode, float vol)
{
	volume = vol;
	
	if (gameMode == 0)
	{
		Mute();
	}
	else
	{
		UnMute();
	}
}
void SoundManager::Terminate()
{
	Sounds.clear();

	delete ptrInstance;
	ptrInstance = nullptr;
}
