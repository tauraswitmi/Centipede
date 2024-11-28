// MushroomFactory
// Charles Tiemeyer, Oct 2024

#ifndef _MushroomFactory
#define _MushroomFactory

#include <stack>
#include <list>
#include "TEAL\CommonElements.h"

class MushroomManager;
class MushroomObjectPool;
class Mushroom;
class GameObjects;
class CMDScore;


class MushroomFactory
{
private:
	static MushroomObjectPool* myMushroomPool;

	static CMDScore* pMushroomDeath;
	static CMDScore* pMushroomReset;


	// Active Mushrooms
	static std::list<Mushroom*> activeMushrooms;



	static MushroomFactory* ptrInstance;

	static MushroomFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new MushroomFactory;
		return *ptrInstance;
	};

public:

	//MushroomFactory() = default;
	//MushroomFactory(const MushroomFactory&) = delete;
	//MushroomFactory& operator=(const MushroomFactory&) = delete;
	//~MushroomFactory() = default;

	static void Initialize();

	static void Restore(); // Refresh the Active Mushrooms


	static CMDScore* GetScore() { return pMushroomDeath; };
	static CMDScore* GetScoreReset() { return pMushroomReset; };


	static Mushroom* CreateMushroom(sf::Vector2i pos, MushroomManager* m);

	static void RecycleMushroom(GameObject* b);

	static void Terminate();


};

#endif _MushroomFactory