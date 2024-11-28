// FleaObjectPool
// Charles Tiemeyer, Oct 2024

#include "FleaObjectPool.h"
#include "Flea.h"

#include "TEAL\CommonElements.h"



FleaObjectPool::FleaObjectPool()
{

}

FleaObjectPool::~FleaObjectPool()
{
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Flea");
	while (!recycledItems.empty())
	{
		delete recycledItems.top(); // already marked as destroyed, so it's okay to just delete
		recycledItems.pop();
	}
}

Flea* FleaObjectPool::GetFlea()
{
	Flea* f;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New Flea");

		f = new Flea();
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled Flea");

		f = recycledItems.top();	// accesses top element of stack
		recycledItems.pop();		// removes top element of stack

		// Tell the object to register itself to the scene
		f->RegisterToCurrentScene();
	}


	return f;
}

void FleaObjectPool::ReturnFlea(Flea* b)
{
	recycledItems.push(b);	// returns bullet to top of stack
}
