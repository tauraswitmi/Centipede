// PlayerFactory
// Charles Tiemeyer, Oct 2024

#ifndef _PlayerFactory
#define _PlayerFactory

#include <stack>
#include "TEAL\CommonElements.h"


class PlayerObjectPool;
class GameObjects;

class PlayerFactory
{
private:
	static PlayerObjectPool* myPlayerPool;

	static PlayerFactory* ptrInstance;

	static PlayerFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new PlayerFactory;
		return *ptrInstance;
	}

public:

	static void Initialize();

	static Player* CreatePlayer();

	static void RecyclePlayer(GameObject* b);

	static void Terminate();


};

#endif _PlayerFactory