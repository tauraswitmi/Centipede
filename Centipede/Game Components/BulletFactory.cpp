// BulletFactory
// Charles Tiemeyer, Sep 2024

#include "TEAL\CommonElements.h"
#include "BulletObjectPool.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "CMDSound.h"
#include "SoundManager.h"


BulletFactory* BulletFactory::ptrInstance = nullptr;
BulletObjectPool* BulletFactory::myBulletPool = nullptr;
bool BulletFactory::active = true;
CMDSound* BulletFactory::pBulletSound = nullptr;


void BulletFactory::Initialize()
{
	myBulletPool = new BulletObjectPool();
	pBulletSound = SoundManager::GetScoreCommand(SoundManager::SoundEvents::Fire);
}


void BulletFactory::CreateBullet(sf::Vector2f pos)
{
	if (active) {

		Bullet* b = myBulletPool->GetBullet();

		// Declares that this object should be returned here (rather than deleted) when destroyed
		b->SetExternalManagement(RecycleBullet);

		b->Initialize(pos);
	}
	
	active = false;

}

void BulletFactory::RecycleBullet(GameObject* b)
{
	myBulletPool->ReturnBullet(static_cast<Bullet*>(b));

	active = true;
}


void BulletFactory::Terminate()
{
	delete pBulletSound;
	delete myBulletPool;

	delete ptrInstance;
	ptrInstance = nullptr;
}