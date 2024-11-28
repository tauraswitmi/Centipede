// MushroomFactory
// Charles Tiemeyer, Sep 2024

#include "TEAL\CommonElements.h"
#include "MushroomObjectPool.h"
#include "MushroomFactory.h"
#include "Mushroom.h"
#include "MushroomManager.h"
#include "ScoreManager.h"
#include "CMDScore.h"
#include <list>


MushroomFactory* MushroomFactory::ptrInstance = nullptr;
std::list<Mushroom*> MushroomFactory::activeMushrooms;
MushroomObjectPool* MushroomFactory::myMushroomPool = nullptr;
CMDScore* MushroomFactory::pMushroomDeath = nullptr;
CMDScore* MushroomFactory::pMushroomReset = nullptr;


void MushroomFactory::Initialize()
{
	myMushroomPool = new MushroomObjectPool();
	pMushroomDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::MushroomKilled);
	pMushroomReset = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::MushroomReset);
}


void MushroomFactory::Restore()
{
	std::for_each(activeMushrooms.begin(), activeMushrooms.end(), [](Mushroom* m) { m->Reset(); });
}



Mushroom* MushroomFactory::CreateMushroom(sf::Vector2i pos, MushroomManager* mm)
{
	
	Mushroom* b = myMushroomPool->GetMushroom();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	b->SetExternalManagement(RecycleMushroom);
	b->Initialize(pos, mm);


	activeMushrooms.push_front(b);
	return b;
}

void MushroomFactory::RecycleMushroom(GameObject* b)
{
	activeMushrooms.remove(static_cast<Mushroom*>(b));
	
	myMushroomPool->ReturnMushroom(static_cast<Mushroom*>(b));
}


void MushroomFactory::Terminate()
{
	delete myMushroomPool;
	delete pMushroomDeath;
	delete pMushroomReset;
	delete ptrInstance;
	ptrInstance = nullptr;
}