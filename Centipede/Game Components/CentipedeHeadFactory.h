// CentipedeHeadFactory
// Charles Tiemeyer, Oct 2024

#ifndef _CentipedeHeadFactory
#define _CentipedeHeadFactory

#include <stack>
#include <list>
#include "TEAL\CommonElements.h"


class CentipedeHeadObjectPool;
class CentipedeHead;
class CentipedeBody;
class GameManager;
class MushroomManager;
class CMDScore;
class CMDSound;
class Player;


class CentipedeHeadFactory
{
private:
	static CentipedeHeadObjectPool* myCentipedeHeadPool;

	static CMDScore* pCentipedeHeadDeath;
	static CMDSound* pCentipedeHeadSound;



	// Active CentipedeHeads
	static std::list<CentipedeHead*> activeCentipedeHeads;


	// Starting Direction of the Centipedes (Per Round)
	bool left;
	bool priv_SetDirection();


	static GameManager* game_manager;


	static CentipedeHeadFactory* ptrInstance;

	static CentipedeHeadFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new CentipedeHeadFactory;
		return *ptrInstance;
	};

public:
	static void Initialize(GameManager* game_ref);

	static void Recall();
	static void Pause();
	static void SetNextLevel();
	static void SetSound(bool on);

	static CMDScore* GetScore() { return pCentipedeHeadDeath; };
	static CMDSound* GetSound() { return pCentipedeHeadSound; };

	static void CreateCentipedeHead(int length, float speed);
	static void CreateCentipedeHead(int length, float speed, int col);
	static void CreateCentipedeHead(CentipedeBody* cb, int length, float speed);

	static void RecycleCentipedeHead(GameObject* b);

	static void Terminate();


};

#endif _CentipedeHeadObjectPool