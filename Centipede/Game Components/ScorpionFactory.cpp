// ScorpionFactory
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "ScorpionObjectPool.h"
#include "ScorpionFactory.h"
#include "ScorpionSpawner.h"
#include "Scorpion.h"
#include "Player.h"

#include "MushroomManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "GameManager.h"

#include "CMDScore.h"
#include "CMDSound.h"
#include <list>


ScorpionFactory* ScorpionFactory::ptrInstance = nullptr;
std::list<Scorpion*> ScorpionFactory::activeScorpions;
ScorpionObjectPool* ScorpionFactory::myScorpionPool = nullptr;
CMDScore* ScorpionFactory::pScorpionDeath = nullptr;
CMDSound* ScorpionFactory::pScorpionSound = nullptr;


void ScorpionFactory::Initialize()
{
	myScorpionPool = new ScorpionObjectPool();
	pScorpionDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::ScorpionKilled);
	pScorpionSound = SoundManager::GetScoreCommand(SoundManager::SoundEvents::Scorpion);
}



void ScorpionFactory::Remove()
{
	// Destroys the current Active Scorpions
	ScorpionSpawner::set_active_off();
	std::for_each(activeScorpions.begin(), activeScorpions.end(), [](Scorpion* m) { m->MarkForDestroy(); });
}

void ScorpionFactory::Reactivate()
{
	// Reactivates the spawner
	ScorpionSpawner::set_spawner(true);
	if (!ScorpionSpawner::get_alarm_on()) { ScorpionSpawner::SpawnerActivate(); }
}

void ScorpionFactory::Pause()
{
	SoundManager::SendPauseCMD(pScorpionSound);

	// Pauses the current Active Scorpions
	std::for_each(activeScorpions.begin(), activeScorpions.end(), [](Scorpion* m) { m->SPEED = 0; });

	// Deactivates the spawner
	ScorpionSpawner::set_spawner(false);
}



void ScorpionFactory::CreateScorpion(float speed)
{
	SoundManager::SendSoundCMD(pScorpionSound);

	Scorpion* f = myScorpionPool->GetScorpion();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	f->SetExternalManagement(RecycleScorpion);
	f->Initialize(GameManager::currentPlayer->get_MushroomManager(), speed); // 999, LATER, IT SHOULD BE UPDATED TO BE ASSIGNED TO "PLAYER" OBJ

	activeScorpions.push_front(f);

}

void ScorpionFactory::RecycleScorpion(GameObject* b)
{

	SoundManager::SendPauseCMD(pScorpionSound);

	activeScorpions.remove(static_cast<Scorpion*>(b));
	myScorpionPool->ReturnScorpion(static_cast<Scorpion*>(b));

	// Starts spawning cycle
	ScorpionSpawner::SpawnerActivate();
}


void ScorpionFactory::Terminate()
{
	delete myScorpionPool;
	delete pScorpionDeath;
	delete pScorpionSound;
	delete ptrInstance;
	ptrInstance = nullptr;

	ScorpionSpawner::Terminate();
}