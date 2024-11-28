// CentipedeBodyFactory
// Charles Tiemeyer, Oct 2024

#ifndef _CentipedeBodyFactory
#define _CentipedeBodyFactory

#include <stack>
#include <list>
#include "TEAL\CommonElements.h"


class CentipedeBodyObjectPool;
class CentipedeBody;
class CentipedeHead;
class GameObjects;
class CMDScore;


class CentipedeBodyFactory
{
private:
	static CentipedeBodyObjectPool* myCentipedeBodyPool;

	static CMDScore* pCentipedeBodyDeath;


	// Active CentipedeBodies
	static std::list<CentipedeBody*> activeCentipedeBodies;


	// Control Elements
	static float speed;



	static CentipedeBodyFactory* ptrInstance;

	static CentipedeBodyFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new CentipedeBodyFactory;
		return *ptrInstance;
	};


public:
	static void Initialize();

	static void Recall();
	static void Pause();


	static CMDScore* GetScore() { return pCentipedeBodyDeath; };

	static CentipedeBody* CreateCentipedeBody(CentipedeHead* ch, int num, float speed); // Run first one after header
	static CentipedeBody* CreateCentipedeBody(CentipedeBody* cb, int num, float speed); // Run for rest of bodies

	static void RecycleCentipedeBody(GameObject* b);

	static void Terminate();


};

#endif _CentipedeBodyObjectPool