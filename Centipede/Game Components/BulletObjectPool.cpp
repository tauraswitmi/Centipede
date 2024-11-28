// BulletObjectPool
// Charles Tiemeyer, Sep 2024

#include "BulletObjectPool.h"
#include "Bullet.h"

#include "TEAL\CommonElements.h"



BulletObjectPool::BulletObjectPool()
{

}

BulletObjectPool::~BulletObjectPool()
{
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Bullets");
	while (!recycledItems.empty())
	{
		delete recycledItems.top(); // already marked as destroyed, so it's okay to just delete
		recycledItems.pop();
	}
}

Bullet* BulletObjectPool::GetBullet()
{
	Bullet* b;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New Bullet");

		b = new Bullet();
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled Bullet");

		b = recycledItems.top();	// accesses top element of stack
		recycledItems.pop();		// removes top element of stack

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}
	

	return b;
}

void BulletObjectPool::ReturnBullet(Bullet* b)
{
	recycledItems.push(b);	// returns bullet to top of stack
}
