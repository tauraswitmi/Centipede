// CentipedeSpawnerSoloHead
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "CentipedeSpawnerSoloHead.h"
#include "CentipedeHeadFactory.h"
#include "MushroomManager.h"

float CentipedeSpawnerSoloHead::speed;
int CentipedeSpawnerSoloHead::count_OnStart;
int CentipedeSpawnerSoloHead::count_PlayerZone;
CentipedeSpawnerSoloHead* CentipedeSpawnerSoloHead::ptrInstance = nullptr;


void CentipedeSpawnerSoloHead::Initialize()
{
	Instance();

	speed = 0;
	count_OnStart = 0;
	count_PlayerZone = 0;
}



void CentipedeSpawnerSoloHead::SpawnCentipedeHead_AtSpawn(float s, int c)
{

	speed = s;
	count_OnStart = c;

	// Math so that each spawn in Seperate Columns
	float column = (float)MushroomManager::WIDTH / (float)(count_OnStart + 1);
	for (int i = 1; i <= count_OnStart; i++)
	{
		CentipedeHeadFactory::CreateCentipedeHead(0, speed, (int)(column * i));
	}

}

void CentipedeSpawnerSoloHead::SpawnCentipedeHead_AtSpawn()
{

	// Math so that each spawn in Seperate Columns
	float column = (float)MushroomManager::WIDTH / (float)(count_OnStart + 1);
	for (int i = 1; i <= count_OnStart; i++)
	{
		CentipedeHeadFactory::CreateCentipedeHead(0, speed, (int)(column * i));
	}

}

void CentipedeSpawnerSoloHead::SpawnCentipedeHead_AtPlayerZone()
{

}




void CentipedeSpawnerSoloHead::Terminate()
{
	ptrInstance->MarkForDestroy();
	ptrInstance = nullptr;
}


