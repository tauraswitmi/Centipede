// FleeObjectPool
// Charles Tiemeyer, Oct 2024

#ifndef _FleaObjectPool
#define _FleaObjectPool

#include <stack>
//#include "TEAL\CommonElements.h"
class Flea;


class FleaObjectPool
{
private:
	std::stack<Flea*> recycledItems;

	/*
		WARNING!!!

		For simplicity, I'm using 'counter' as a static data number.
		THIS IS THE WRONG APPROACH FOR A FACTORY!!! But we need ANOTHER design
		pattern to do it correctly. (See Singletons next week)
	*/

public:
	FleaObjectPool();
	FleaObjectPool(const FleaObjectPool&) = delete;
	FleaObjectPool& operator=(const FleaObjectPool&) = delete;
	~FleaObjectPool();

	Flea* GetFlea();
	void ReturnFlea(Flea* b);

};

#endif _FleaObjectPool