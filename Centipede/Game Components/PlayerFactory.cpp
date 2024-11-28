// PlayerFactory
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "PlayerObjectPool.h"
#include "PlayerFactory.h"
#include "Player.h"
#include "ScoreManager.h"


PlayerFactory* PlayerFactory::ptrInstance = nullptr;

PlayerObjectPool* PlayerFactory::myPlayerPool = nullptr;


void PlayerFactory::Initialize()
{
	myPlayerPool = new PlayerObjectPool();
}


Player* PlayerFactory::CreatePlayer()
{

	Player* b = myPlayerPool->GetPlayer();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	b->SetExternalManagement(RecyclePlayer);

	b->Initialize();

	return b;

}

void PlayerFactory::RecyclePlayer(GameObject* b)
{
	myPlayerPool->ReturnPlayer(static_cast<Player*>(b));

}


void PlayerFactory::Terminate()
{
	delete myPlayerPool;
	delete ptrInstance;
	ptrInstance = nullptr;
}