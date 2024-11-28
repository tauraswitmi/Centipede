// SpiderObjectPool
// Charles Tiemeyer, Oct 2024

#ifndef _SpiderObjectPool
#define _SpiderObjectPool

#include <stack>
//#include "TEAL\CommonElements.h"
class Spider;


class SpiderObjectPool
{
private:
	std::stack<Spider*> recycledItems;

	/*
		WARNING!!!

		For simplicity, I'm using 'counter' as a static data number.
		THIS IS THE WRONG APPROACH FOR A FACTORY!!! But we need ANOTHER design
		pattern to do it correctly. (See Singletons next week)
	*/

public:
	SpiderObjectPool();
	SpiderObjectPool(const SpiderObjectPool&) = delete;
	SpiderObjectPool& operator=(const SpiderObjectPool&) = delete;
	~SpiderObjectPool();

	Spider* GetSpider();
	void ReturnSpider(Spider* s);

};

#endif _SpiderObjectPool