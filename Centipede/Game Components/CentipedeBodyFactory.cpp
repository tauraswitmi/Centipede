// CentipedeBodyFactory
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "CentipedeBodyObjectPool.h"
#include "CentipedeBodyFactory.h"
#include "CentipedeHead.h"
#include "CentipedeBody.h"
#include "MushroomManager.h"
#include "ScoreManager.h"
#include "CMDScore.h"
#include <list>


CentipedeBodyFactory* CentipedeBodyFactory::ptrInstance = nullptr;
std::list<CentipedeBody*> CentipedeBodyFactory::activeCentipedeBodies;
CentipedeBodyObjectPool* CentipedeBodyFactory::myCentipedeBodyPool = nullptr;
CMDScore* CentipedeBodyFactory::pCentipedeBodyDeath = nullptr;


void CentipedeBodyFactory::Initialize()
{
	myCentipedeBodyPool = new CentipedeBodyObjectPool();
	pCentipedeBodyDeath = ScoreManager::GetScoreCommand(ScoreManager::ScoreEvents::CentipedeBodyKilled);
}



void CentipedeBodyFactory::Recall()
{
	std::for_each(activeCentipedeBodies.begin(), activeCentipedeBodies.end(), [](CentipedeBody* m) { m->Reset(); });
}

void CentipedeBodyFactory::Pause()
{
	std::for_each(activeCentipedeBodies.begin(), activeCentipedeBodies.end(), [](CentipedeBody* m) { m->SPEED = 0; });
}



// Created from Spawn (Start of Level)
CentipedeBody* CentipedeBodyFactory::CreateCentipedeBody(CentipedeHead* ch, int num, float speed)
{

	CentipedeBody* cb = myCentipedeBodyPool->GetCentipedeBody();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	cb->SetExternalManagement(RecycleCentipedeBody);
	cb->Initialize(ch, num, speed);


	activeCentipedeBodies.push_front(cb);
	return cb;
}



// Created from Separation (New Head)
CentipedeBody* CentipedeBodyFactory::CreateCentipedeBody(CentipedeBody* cb, int num, float speed)
{

	CentipedeBody* cbb = myCentipedeBodyPool->GetCentipedeBody();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	cbb->SetExternalManagement(RecycleCentipedeBody);
	cbb->Initialize(cb, num, speed);
	

	activeCentipedeBodies.push_front(cbb);
	return cbb;
}




void CentipedeBodyFactory::RecycleCentipedeBody(GameObject* b)
{
	activeCentipedeBodies.remove(static_cast<CentipedeBody*>(b));
	
	myCentipedeBodyPool->ReturnCentipedeBody(static_cast<CentipedeBody*>(b));
}


void CentipedeBodyFactory::Terminate()
{
	delete myCentipedeBodyPool;
	delete pCentipedeBodyDeath;
	delete ptrInstance;
	ptrInstance = nullptr;
}


