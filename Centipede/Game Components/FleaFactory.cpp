// FleaFactory
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "FleaObjectPool.h"
#include "FleaFactory.h"
#include "FleaSpawner.h"
#include "Flea.h"
#include "MushroomManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "CMDScore.h"
#include "CMDSound.h"
#include "Player.h"
#include "GameManager.h"
#include <list>


FleaFactory* FleaFactory::ptrInstance = nullptr;
std::list<Flea*> FleaFactory::activeFleas;
FleaObjectPool* FleaFactory::myFleaPool = nullptr;
CMDScore* FleaFactory::pFleaDeath = nullptr;
CMDSound* FleaFactory::pFleaSound = nullptr;
CMDSound* FleaFactory::pFleaKilled = nullptr;


void FleaFactory::Initialize()
{
	myFleaPool = new FleaObjectPool();
	pFleaDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::FleaKilled);
	pFleaSound = SoundManager::GetScoreCommand(SoundManager::SoundEvents::Flea);
	pFleaKilled = SoundManager::GetScoreCommand(SoundManager::SoundEvents::Kill);

}



void FleaFactory::Remove()
{
	// Destroys the current Active Scorpions
	FleaSpawner::set_active_off();
	std::for_each(activeFleas.begin(), activeFleas.end(), [](Flea* m) { m->MarkForDestroy(); });
}

void FleaFactory::Reactivate()
{
	// Reactivates the spawner
	FleaSpawner::set_spawner(true);
}


void FleaFactory::Pause()
{
	SoundManager::SendPauseCMD(FleaFactory::GetSound());

	// Pauses the current Active Scorpions
	std::for_each(activeFleas.begin(), activeFleas.end(), [](Flea* m) { m->SPEED = 0; });

	// Deactivates the spawner
	FleaSpawner::set_spawner(false);
}



void FleaFactory::CreateFlea(float speed, int spawn_prob)
{

	Flea* f = myFleaPool->GetFlea();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	f->SetExternalManagement(RecycleFlea);
	f->Initialize(GameManager::currentPlayer->get_MushroomManager(), speed, spawn_prob);


	activeFleas.push_front(f);
}


void FleaFactory::RecycleFlea(GameObject* b)
{
	activeFleas.remove(static_cast<Flea*>(b));
	myFleaPool->ReturnFlea(static_cast<Flea*>(b));
}



void FleaFactory::Terminate()
{
	delete myFleaPool;
	delete pFleaDeath;
	delete pFleaSound;
	delete pFleaKilled;
	delete ptrInstance;
	ptrInstance = nullptr;

	FleaSpawner::Terminate();
}