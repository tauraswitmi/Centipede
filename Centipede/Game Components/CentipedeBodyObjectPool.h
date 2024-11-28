// CentipedeBodyObjectPool
// Charles Tiemeyer, Oct 2024

#ifndef _CentipedeBodyObjectPool
#define _CentipedeBodyObjectPool

#include <stack>
//#include "TEAL\CommonElements.h"
class CentipedeBody;


class CentipedeBodyObjectPool
{
private:
	std::stack<CentipedeBody*> recycledItems;

	/*
		WARNING!!!

		For simplicity, I'm using 'counter' as a static data number.
		THIS IS THE WRONG APPROACH FOR A FACTORY!!! But we need ANOTHER design
		pattern to do it correctly. (See Singletons next week)
	*/

public:
	CentipedeBodyObjectPool();
	CentipedeBodyObjectPool(const CentipedeBodyObjectPool&) = delete;
	CentipedeBodyObjectPool& operator=(const CentipedeBodyObjectPool&) = delete;
	~CentipedeBodyObjectPool();

	CentipedeBody* GetCentipedeBody();
	void ReturnCentipedeBody(CentipedeBody* b);

};

#endif _CentipedeBodyObjectPool