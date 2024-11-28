// ScorpionObjectPool
// Charles Tiemeyer, Oct 2024

#include "ScorpionObjectPool.h"
#include "Scorpion.h"

#include "TEAL\CommonElements.h"



ScorpionObjectPool::ScorpionObjectPool()
{

}

ScorpionObjectPool::~ScorpionObjectPool()
{
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Scorpion");
	while (!recycledItems.empty())
	{
		delete recycledItems.top(); // already marked as destroyed, so it's okay to just delete
		recycledItems.pop();
	}
}

Scorpion* ScorpionObjectPool::GetScorpion()
{
	Scorpion* s;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New Scorpion");

		s = new Scorpion();
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

void ScorpionObjectPool::ReturnScorpion(Scorpion* s)
{
	recycledItems.push(s);	// returns bullet to top of stack
}
