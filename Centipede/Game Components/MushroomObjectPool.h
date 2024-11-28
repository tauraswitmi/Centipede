// MushroomObjectPool
// Charles Tiemeyer, Oct 2024

#ifndef _MushroomObjectPool
#define _MushroomObjectPool

#include <stack>
//#include "TEAL\CommonElements.h"
class Mushroom;


class MushroomObjectPool
{
private:
	std::stack<Mushroom*> recycledItems;


public:
	MushroomObjectPool();
	MushroomObjectPool(const MushroomObjectPool&) = delete;
	MushroomObjectPool& operator=(const MushroomObjectPool&) = delete;
	~MushroomObjectPool();

	Mushroom* GetMushroom();
	void ReturnMushroom(Mushroom* b);

};

#endif _MushroomObjectPool