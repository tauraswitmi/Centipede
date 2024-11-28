// BlasterObjectPool
// Charles Tiemeyer, Oct 2024

#ifndef _BlasterObjectPool
#define _BlasterObjectPool

#include <stack>
//#include "TEAL\CommonElements.h"
class Blaster;


class BlasterObjectPool
{
private:
	std::stack<Blaster*> recycledItems;


public:
	BlasterObjectPool();
	BlasterObjectPool(const BlasterObjectPool&) = delete;
	BlasterObjectPool& operator=(const BlasterObjectPool&) = delete;
	~BlasterObjectPool();

	Blaster* GetBlaster();
	void ReturnBlaster(Blaster* b);

};

#endif _BlasterObjectPool