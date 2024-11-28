// CentipedeHeadObjectPool
// Charles Tiemeyer, Oct 2024

#include "CentipedeHeadObjectPool.h"
#include "CentipedeHead.h"

#include "TEAL\CommonElements.h"



CentipedeHeadObjectPool::CentipedeHeadObjectPool()
{

}

CentipedeHeadObjectPool::~CentipedeHeadObjectPool()
{
	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " CentipedeHead");
	while (!recycledItems.empty())
	{
		delete recycledItems.top(); // already marked as destroyed, so it's okay to just delete
		recycledItems.pop();
	}
}

CentipedeHead* CentipedeHeadObjectPool::GetCentipedeHead()
{
	CentipedeHead* ch;

	if (recycledItems.empty())
	{
		//ConsoleMsg::WriteLine("New CentipedeHead");

		ch = new CentipedeHead();
	}
	else
	{
		//ConsoleMsg::WriteLine("Recycled CentipedeHead");

		ch = recycledItems.top();	// accesses top element of stack
		recycledItems.pop();		// removes top element of stack

		// Tell the object to register itself to the scene
		ch->RegisterToCurrentScene();
	}


	return ch;
}

void CentipedeHeadObjectPool::ReturnCentipedeHead(CentipedeHead* ch)
{
	recycledItems.push(ch);	// returns bullet to top of stack
}
