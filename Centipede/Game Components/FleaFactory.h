// FleaFactory
// Charles Tiemeyer, Oct 2024

#ifndef _FleaFactory
#define _FleaFactory

#include <stack>
#include <list>
#include "TEAL\CommonElements.h"


class Flea;
class FleaObjectPool;
class GameObjects;
class MushroomManager;
class CMDScore;
class CMDSound;
class Player;

class FleaFactory
{
private:
	static FleaObjectPool* myFleaPool;

	static CMDScore* pFleaDeath;
	static CMDSound* pFleaSound;
	static CMDSound* pFleaKilled;


	// Active Fleas
	static std::list<Flea*> activeFleas;


	static FleaFactory* ptrInstance;

	static FleaFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new FleaFactory;
		return *ptrInstance;
	};

public:
	static void Initialize();

	static void Remove();
	static void Reactivate();
	static void Pause();


	static CMDScore* GetScore() { return pFleaDeath; };
	static CMDSound* GetSound() { return pFleaSound; };
	static CMDSound* GetKilled() { return pFleaKilled; }

	static void CreateFlea(float speed, int spawn_prob);

	static void RecycleFlea(GameObject* b);

	static void Terminate();


};

#endif _FleaFactory