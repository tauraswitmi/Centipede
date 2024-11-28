// SpiderObjectPool
// Charles Tiemeyer, Oct 2024

#include "SpiderObjectPool.h"
#include "Spider.h"

#include "TEAL\CommonElements.h"



SpiderObjectPool::SpiderObjectPool()
{

}

SpiderObjectPool::~SpiderObjectPool()
{
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Spider");
	while (!recycledItems.empty())
	{
		delete recycledItems.top(); // already marked as destroyed, so it's okay to just delete
		recycledItems.pop();
	}
}

Spider* SpiderObjectPool::GetSpider()
{
	Spider* s;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New Scorpion");

		s = new Spider();
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled Scorpion");

		s = recycledItems.top();	// accesses top element of stack
		recycledItems.pop();		// removes top element of stack

		// Tell the object to register itself to the scene
		s->RegisterToCurrentScene();
	}


	return s;
}

void SpiderObjectPool::ReturnSpider(Spider* s)
{
	recycledItems.push(s);	// returns bullet to top of stack
}
