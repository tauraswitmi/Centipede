// CentipedeHeadObjectPool
// Charles Tiemeyer, Oct 2024

#ifndef _CentipedeHeadObjectPool
#define _CentipedeHeadObjectPool

#include <stack>
//#include "TEAL\CommonElements.h"
class CentipedeHead;


class CentipedeHeadObjectPool
{
private:
	std::stack<CentipedeHead*> recycledItems;

	/*
		WARNING!!!

		For simplicity, I'm using 'counter' as a static data number.
		THIS IS THE WRONG APPROACH FOR A FACTORY!!! But we need ANOTHER design
		pattern to do it correctly. (See Singletons next week)
	*/

public:
	CentipedeHeadObjectPool();
	CentipedeHeadObjectPool(const CentipedeHeadObjectPool&) = delete;
	CentipedeHeadObjectPool& operator=(const CentipedeHeadObjectPool&) = delete;
	~CentipedeHeadObjectPool();

	CentipedeHead* GetCentipedeHead();
	void ReturnCentipedeHead(CentipedeHead* b);

};

#endif _CentipedeHeadObjectPool