// BulletObjectPool
// Charles Tiemeyer, Sep 2024

#ifndef _BulletObjectPool
#define _BulletObjectPool

#include <stack>
//#include "TEAL\CommonElements.h"
class Bullet;


class BulletObjectPool
{
private:
	std::stack<Bullet*> recycledItems;

	/*
		WARNING!!!

		For simplicity, I'm using 'counter' as a static data number.
		THIS IS THE WRONG APPROACH FOR A FACTORY!!! But we need ANOTHER design
		pattern to do it correctly. (See Singletons next week)
	*/

public:
	BulletObjectPool();
	BulletObjectPool(const BulletObjectPool&) = delete;
	BulletObjectPool& operator=(const BulletObjectPool&) = delete;
	~BulletObjectPool();

	Bullet* GetBullet();
	void ReturnBullet(Bullet* b);

};

#endif _BulletObjectPool