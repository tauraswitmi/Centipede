// PlayerObjectPool
// Charles Tiemeyer, Oct 2024

#ifndef _PlayerObjectPool
#define _PlayerObjectPool

#include <stack>
//#include "TEAL\CommonElements.h"
class Player;


class PlayerObjectPool
{
private:
	std::stack<Player*> recycledItems;


public:
	PlayerObjectPool();
	PlayerObjectPool(const PlayerObjectPool&) = delete;
	PlayerObjectPool& operator=(const PlayerObjectPool&) = delete;
	~PlayerObjectPool();

	Player* GetPlayer();
	void ReturnPlayer(Player* b);

};

#endif _PlayerObjectPool