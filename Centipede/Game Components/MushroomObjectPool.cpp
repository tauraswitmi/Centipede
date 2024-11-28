// MushroomObjectPool
// Charles Tiemeyer, Oct 2024

#include "MushroomObjectPool.h"
#include "Mushroom.h"

#include "TEAL\CommonElements.h"



MushroomObjectPool::MushroomObjectPool()
{

}

MushroomObjectPool::~MushroomObjectPool()
{
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Mushroom");
	while (!recycledItems.empty())
	{
		delete recycledItems.top(); // already marked as destroyed, so it's okay to just delete
		recycledItems.pop();
	}
}

Mushroom* MushroomObjectPool::GetMushroom()
{
	Mushroom* m;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New Mushroom");

		m = new Mushroom();
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled Mushroom");

		m = recycledItems.top();	// accesses top element of stack
		recycledItems.pop();		// removes top element of stack

		// Tell the object to register itself to the scene
		m->RegisterToCurrentScene();
	}


	return m;
}

void MushroomObjectPool::ReturnMushroom(Mushroom* m)
{
	recycledItems.push(m);	// returns bullet to top of stack
}
