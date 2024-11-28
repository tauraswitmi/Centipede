// BlasterObjectPool
// Charles Tiemeyer, Sep 2024

#include "BlasterObjectPool.h"
#include "Blaster.h"

#include "TEAL\CommonElements.h"



BlasterObjectPool::BlasterObjectPool()
{

}

BlasterObjectPool::~BlasterObjectPool()
{
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Blaster");
	while (!recycledItems.empty())
	{
		delete recycledItems.top(); // already marked as destroyed, so it's okay to just delete
		recycledItems.pop();
	}
}

Blaster* BlasterObjectPool::GetBlaster()
{
	Blaster* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Blaster");

		b = new Blaster();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Blaster");

		b = recycledItems.top();	// accesses top element of stack
		recycledItems.pop();		// removes top element of stack

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}


	return b;
}

void BlasterObjectPool::ReturnBlaster(Blaster* b)
{
	recycledItems.push(b);	// returns bullet to top of stack
}
