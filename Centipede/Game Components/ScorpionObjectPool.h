// ScorpionObjectPool
// Charles Tiemeyer, Oct 2024

#ifndef _ScorpionObjectPool
#define _ScorpionObjectPool

#include <stack>
//#include "TEAL\CommonElements.h"
class Scorpion;


class ScorpionObjectPool
{
private:
	std::stack<Scorpion*> recycledItems;

	/*
		WARNING!!!

		For simplicity, I'm using 'counter' as a static data number.
		THIS IS THE WRONG APPROACH FOR A FACTORY!!! But we need ANOTHER design
		pattern to do it correctly. (See Singletons next week)
	*/

public:
	ScorpionObjectPool();
	ScorpionObjectPool(const ScorpionObjectPool&) = delete;
	ScorpionObjectPool& operator=(const ScorpionObjectPool&) = delete;
	~ScorpionObjectPool();

	Scorpion* GetScorpion();
	void ReturnScorpion(Scorpion* s);

};

#endif _ScorpionObjectPool