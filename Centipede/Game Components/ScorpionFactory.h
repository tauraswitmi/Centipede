// ScorpionFactory
// Charles Tiemeyer, Oct 2024

#ifndef _ScorpionFactory
#define _ScorpionFactory

#include <stack>
#include <list>
#include "TEAL\CommonElements.h"


class Scorpion;
class ScorpionObjectPool;
class GameObjects;
class Player;
class MushroomManager;
class CMDScore;
class CMDSound;


class ScorpionFactory
{
private:
	static ScorpionObjectPool* myScorpionPool;

	static CMDScore* pScorpionDeath;
	static CMDSound* pScorpionSound;


	// Active Scorpions
	static std::list<Scorpion*> activeScorpions;



	static ScorpionFactory* ptrInstance;

	static ScorpionFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ScorpionFactory;
		return *ptrInstance;
	};

public:
	static void Initialize();


	static void Remove();
	static void Reactivate();
	static void Pause();


	static CMDScore* GetScore() { return pScorpionDeath; };

	static void CreateScorpion(float speed);

	static void RecycleScorpion(GameObject* b);

	static void Terminate();


};

#endif _ScorpionFactory