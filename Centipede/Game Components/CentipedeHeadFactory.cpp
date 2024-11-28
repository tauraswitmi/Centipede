// CentipedeHeadFactory
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"

#include "CentipedeHeadObjectPool.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeHead.h"
#include "CentipedeBody.h"
#include "CentipedeSpawnerMain.h"
#include "CentipedeSpawnerSoloHead.h"


#include "GameManager.h"
#include "MushroomManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "CMDScore.h"
#include "CMDSound.h"
#include "Player.h"
#include <list>


CentipedeHeadFactory* CentipedeHeadFactory::ptrInstance = nullptr;
std::list<CentipedeHead*> CentipedeHeadFactory::activeCentipedeHeads;
CentipedeHeadObjectPool* CentipedeHeadFactory::myCentipedeHeadPool = nullptr;
CMDScore* CentipedeHeadFactory::pCentipedeHeadDeath = nullptr;
CMDSound* CentipedeHeadFactory::pCentipedeHeadSound = nullptr;
GameManager* CentipedeHeadFactory::game_manager = nullptr;


void CentipedeHeadFactory::Initialize(GameManager* ref)
{
	myCentipedeHeadPool = new CentipedeHeadObjectPool();
	pCentipedeHeadDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::CentipedeHeadKilled);
	pCentipedeHeadSound = SoundManager::GetScoreCommand(SoundManager::SoundEvents::Centipede);
	game_manager = ref;


	// Below is what's in place before I fully establish a WAVE system
	// To be ridded of when WAVE is made. (999)

	Instance().priv_SetDirection();
	
}




void CentipedeHeadFactory::Recall()
{
	
	// Destroys the current Active CentipedeHeads
	std::for_each(activeCentipedeHeads.begin(), activeCentipedeHeads.end(), [](CentipedeHead* m) { m->Reset(); });


}

void CentipedeHeadFactory::Pause()
{
	// PAUSE SOUND
	SoundManager::SendPauseCMD(pCentipedeHeadSound);
	std::for_each(activeCentipedeHeads.begin(), activeCentipedeHeads.end(), [](CentipedeHead* m) { m->SPEED = 0; });
}

void CentipedeHeadFactory::SetNextLevel()
{
	Instance().priv_SetDirection();

	CentipedeSpawnerMain::set_length(12 - GameManager::currentPlayer->GetCurrentLevel());
	CentipedeSpawnerMain::SpawnCentipede();
}

/// 999 delete
void CentipedeHeadFactory::SetSound(bool on)
{
	SoundManager::SendSoundCMD(pCentipedeHeadSound);
}


bool CentipedeHeadFactory::priv_SetDirection()
{
	if (rand() % 2 == 0)
	{
		Instance().left = true;
	}
	else
	{
		Instance().left = false;
	}

	return left;
}







// ==== CREATE CENTIPEDES ==== //


// Created from Spawn (Start of Level)
void CentipedeHeadFactory::CreateCentipedeHead(int length, float s)
{

	// EXECUTE SOUND
	SoundManager::SendSoundCMD(pCentipedeHeadSound);


	CentipedeHead* ch = myCentipedeHeadPool->GetCentipedeHead();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	ch->SetExternalManagement(RecycleCentipedeHead);
	ch->Initialize(GameManager::currentPlayer->get_MushroomManager(), length, s, Instance().left);


	activeCentipedeHeads.push_front(ch);
}


// Created from Spawn (Start of Level) *Solo Head
void CentipedeHeadFactory::CreateCentipedeHead(int length, float s, int col)
{

	CentipedeHead* ch = myCentipedeHeadPool->GetCentipedeHead();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	ch->SetExternalManagement(RecycleCentipedeHead);
	ch->Initialize(GameManager::currentPlayer->get_MushroomManager(), length, s, Instance().left, col);

	activeCentipedeHeads.push_front(ch);
}


// Created from Separation (New Head)
void CentipedeHeadFactory::CreateCentipedeHead(CentipedeBody* cb, int length, float s)
{

	CentipedeHead* ch = myCentipedeHeadPool->GetCentipedeHead();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	ch->SetExternalManagement(RecycleCentipedeHead);
	ch->Initialize(cb, length, s);


	activeCentipedeHeads.push_front(ch);
}




// ==== RECYCLE CENTIPEDES ==== //

void CentipedeHeadFactory::RecycleCentipedeHead(GameObject* b)
{

	activeCentipedeHeads.remove(static_cast<CentipedeHead*>(b));

	myCentipedeHeadPool->ReturnCentipedeHead(static_cast<CentipedeHead*>(b));

	if (activeCentipedeHeads.empty())
	{
		SoundManager::SendPauseCMD(pCentipedeHeadSound);
		GameManager::EndOfWaveCallback();
	}
}


void CentipedeHeadFactory::Terminate()
{
	delete myCentipedeHeadPool;
	delete pCentipedeHeadDeath;
	delete pCentipedeHeadSound;
	delete ptrInstance;
	ptrInstance = nullptr;
}