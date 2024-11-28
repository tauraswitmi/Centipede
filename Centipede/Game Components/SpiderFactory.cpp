// SpiderFactory
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "SpiderObjectPool.h"
#include "SpiderFactory.h"
#include "SpiderSpawner.h"
#include "Spider.h"

#include "MushroomManager.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "GameEntityManager.h"

#include "CMDScore.h"
#include "CMDSoundLoop.h"
#include <list>


SpiderFactory* SpiderFactory::ptrInstance = nullptr;
std::list<Spider*> SpiderFactory::activeSpiders;
SpiderObjectPool* SpiderFactory::mySpiderPool = nullptr;

CMDScore* SpiderFactory::pSpiderDeath = nullptr;
CMDSound* SpiderFactory::pSpiderSound = nullptr;

float SpiderFactory::distance = 0;


const float SpiderFactory::TOP_BORDER = GameManager::BOX_SIZE * MushroomManager::TOP_PLAYER_ROW;
const float SpiderFactory::BOTTOM_BORDER = GameManager::BOX_SIZE * (MushroomManager::BOTTOM_ROW + 1); // Plus 1 because the Manager Excludes the ACTUAL bottom row that avoids spawning mushrooms


void SpiderFactory::Initialize()
{
	mySpiderPool = new SpiderObjectPool();
	pSpiderDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::SpiderKilled);
	pSpiderSound = SoundManager::GetScoreCommand(SoundManager::SoundEvents::Spider);

}


void SpiderFactory::Remove()
{
	// Destroys the current Active Scorpions
	SpiderSpawner::set_active_off();
	std::for_each(activeSpiders.begin(), activeSpiders.end(), [](Spider* m) { m->MarkForDestroy(); });
}

void SpiderFactory::Reactivate()
{
	// Reactivates the spawner
	SpiderSpawner::set_spawner(true);
	if (!SpiderSpawner::get_alarm_on()) { SpiderSpawner::SpawnerActivate(); }
}

void SpiderFactory::Pause()
{

	SoundManager::SendPauseCMD(pSpiderSound);

	// Pauses the current Active Scorpions
	std::for_each(activeSpiders.begin(), activeSpiders.end(), [](Spider* m) { m->SPEED = 0; });

	// Deactivates the spawner
	SpiderSpawner::set_spawner(false);
}


void SpiderFactory::CreateSpider(float speed)
{

	SoundManager::SendSoundCMD(pSpiderSound);

	Spider* f = mySpiderPool->GetSpider();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	f->SetExternalManagement(RecycleSpider);
	f->Initialize(speed);

	activeSpiders.push_front(f);
	

}

void SpiderFactory::RecycleSpider(GameObject* b)
{

	SoundManager::SendPauseCMD(pSpiderSound);

	activeSpiders.remove(static_cast<Spider*>(b));
	mySpiderPool->ReturnSpider(static_cast<Spider*>(b));

	SpiderSpawner::SpawnerActivate();
}


void SpiderFactory::Terminate()
{
	delete mySpiderPool;
	delete pSpiderDeath;
	delete pSpiderSound;
	delete ptrInstance;
	ptrInstance = nullptr;

	SpiderSpawner::Terminate();
}