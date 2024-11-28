// CentipedeSpawnerMain
// Charles Tiemeyer, Oct 2024

#ifndef _CentipedeSpawnerMain
#define _CentipedeSpawnerMain

#include "CentipedeHeadFactory.h"
#include "CentipedeHead.h"
#include "TEAL\CommonElements.h"

class CentipedeSpawnerMain : public GameObject
{
private:

	CentipedeSpawnerMain() = default;
	CentipedeSpawnerMain(const CentipedeSpawnerMain&) = delete;
	CentipedeSpawnerMain& operator=(const CentipedeSpawnerMain&) = delete;
	~CentipedeSpawnerMain() = default;

	// Control Elements
	static float speed;
	static int length;


	static CentipedeSpawnerMain* ptrInstance;
	static CentipedeSpawnerMain& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new CentipedeSpawnerMain;
		return *ptrInstance;
	};


public:
	static void Initialize();


	static void set_speed(float s) { speed = s; };
	static void set_length(int l) { length = l; };

	static void SpawnCentipede(float speed, int length);
	static void SpawnCentipede();

	static void Terminate();

};

#endif _CentipedeSpawnerMain