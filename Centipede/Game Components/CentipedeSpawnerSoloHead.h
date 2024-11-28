// CentipedeSpawnerSoloHead
// Charles Tiemeyer, Oct 2024

#ifndef _CentipedeSpawnerSoloHead
#define _CentipedeSpawnerSoloHead

#include "CentipedeHeadFactory.h"
#include "CentipedeHead.h"
#include "TEAL\CommonElements.h"

class CentipedeSpawnerSoloHead : public GameObject
{
private:

	CentipedeSpawnerSoloHead() = default;
	CentipedeSpawnerSoloHead(const CentipedeSpawnerSoloHead&) = delete;
	CentipedeSpawnerSoloHead& operator=(const CentipedeSpawnerSoloHead&) = delete;
	~CentipedeSpawnerSoloHead() = default;

	// Control Elements
	static float speed;
	static int count_OnStart;
	static int count_PlayerZone;

	static CentipedeSpawnerSoloHead* ptrInstance;
	static CentipedeSpawnerSoloHead& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new CentipedeSpawnerSoloHead;
		return *ptrInstance;
	};


public:
	static void Initialize();


	static void set_speed(float s) { speed = s; };
	static void set_count_OnStart(int c) { count_OnStart = c; };
	static void set_count_PlayerZone(int c) { count_PlayerZone = c; };


	static void SpawnCentipedeHead_AtSpawn(float speed, int count);
	static void SpawnCentipedeHead_AtSpawn();
	static void SpawnCentipedeHead_AtPlayerZone();

	static void Terminate();

};

#endif _CentipedeSpawnerSoloHead