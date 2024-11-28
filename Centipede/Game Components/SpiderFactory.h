// SpidersFactory
// Charles Tiemeyer, Oct 2024

#ifndef _SpiderFactory
#define _SpiderFactory

#include <stack>
#include <list>
#include "TEAL\CommonElements.h"


class Spider;
class SpiderObjectPool;
class GameObjects;
class CMDScore;
class CMDSound;


class SpiderFactory
{
private:
	static SpiderObjectPool* mySpiderPool;

	static CMDScore* pSpiderDeath;
	static CMDSound* pSpiderSound;
	static CMDSound* pSpiderKilled;


	// Active Spiders
	static std::list<Spider*> activeSpiders;



	static SpiderFactory* ptrInstance;

	static SpiderFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpiderFactory;
		return *ptrInstance;
	};


public:

	static float distance;

	static const float TOP_BORDER;
	static const float BOTTOM_BORDER;


	static void Reactivate();
	static void Remove();
	static void Pause();

	static void Initialize();

	static CMDScore* GetScore() { return pSpiderDeath; };

	static void CreateSpider(float speed);

	static void RecycleSpider(GameObject* b);

	static void Terminate();


};

#endif _SpiderFactory