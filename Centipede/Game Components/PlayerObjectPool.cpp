// PlayerObjectPool
// Charles Tiemeyer, Oct 2024

#include "PlayerObjectPool.h"
#include "Player.h"

#include "TEAL\CommonElements.h"



PlayerObjectPool::PlayerObjectPool()
{

}

PlayerObjectPool::~PlayerObjectPool()
{
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Player");
	while (!recycledItems.empty())
	{
		delete recycledItems.top(); // already marked as destroyed, so it's okay to just delete
		recycledItems.pop();
	}
}

Player* PlayerObjectPool::GetPlayer()
{
	Player* m;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Player");

		m = new Player();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Player");

		m = recycledItems.top();	// accesses top element of stack
		recycledItems.pop();		// removes top element of stack

		// Tell the object to register itself to the scene
		m->RegisterToCurrentScene();
	}


	return m;
}

void PlayerObjectPool::ReturnPlayer(Player* m)
{
	recycledItems.push(m);	// returns bullet to top of stack
}