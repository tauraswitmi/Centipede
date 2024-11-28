// BlasterFactory
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "BlasterObjectPool.h"
#include "BlasterFactory.h"
#include "Blaster.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "CMDSound.h"


BlasterFactory* BlasterFactory::ptrInstance = nullptr;

BlasterObjectPool* BlasterFactory::myBlasterPool = nullptr;
GameManager* BlasterFactory::GameRef = nullptr;
bool BlasterFactory::active = true;
CMDSound* BlasterFactory::pDeathSound = nullptr;


void BlasterFactory::Initialize(GameManager* ref)
{
	myBlasterPool = new BlasterObjectPool();
	GameRef = ref;
	pDeathSound = SoundManager::GetScoreCommand(SoundManager::SoundEvents::Death);
}


void BlasterFactory::CreateBlaster(int gm)
{
	if (active) {

		Blaster* b = myBlasterPool->GetBlaster();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleBlaster);
		b->Initialize(gm);

	}

	active = false;
}


void BlasterFactory::RecycleBlaster(GameObject* b)
{
	myBlasterPool->ReturnBlaster(static_cast<Blaster*>(b));
	active = true;

	//GameRef->Pause(); // Pause the level to reset wave // FIX THIS SO THAT IT ISN'T CALLED WHEN DESTROYED
	
}


void BlasterFactory::Terminate()
{
	delete myBlasterPool;
	delete pDeathSound;
	delete ptrInstance;
	ptrInstance = nullptr;
}