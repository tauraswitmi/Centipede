// CentipedeBodyObjectPool
// Charles Tiemeyer, Oct 2024

#include "CentipedeBodyObjectPool.h"
#include "CentipedeBody.h"

#include "TEAL\CommonElements.h"



CentipedeBodyObjectPool::CentipedeBodyObjectPool()
{

}

CentipedeBodyObjectPool::~CentipedeBodyObjectPool()
{
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " CentipedeBody");
	while (!recycledItems.empty())
	{
		delete recycledItems.top(); // already marked as destroyed, so it's okay to just delete
		recycledItems.pop();
	}
}



CentipedeBody* CentipedeBodyObjectPool::GetCentipedeBody()
{
	CentipedeBody* ch;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New CentipedeBody");

		ch = new CentipedeBody();
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled CentipedeBody");

		ch = recycledItems.top();	// accesses top element of stack
		recycledItems.pop();		// removes top element of stack

		// Tell the object to register itself to the scene
		ch->RegisterToCurrentScene();
	}


	return ch;
}



void CentipedeBodyObjectPool::ReturnCentipedeBody(CentipedeBody* ch)
{
	recycledItems.push(ch);	// returns bullet to top of stack
}
