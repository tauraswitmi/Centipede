// CentipedeSpawnerMain
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "CentipedeSpawnerMain.h"
#include "CentipedeHeadFactory.h"

float CentipedeSpawnerMain::speed;
int CentipedeSpawnerMain::length;
CentipedeSpawnerMain* CentipedeSpawnerMain::ptrInstance = nullptr;


void CentipedeSpawnerMain::Initialize()
{
	Instance();

	speed = 0;
	length = 0;
}


// Create Centipede //

void CentipedeSpawnerMain::SpawnCentipede(float s, int l)
{
	speed = s;
	length = l;
	CentipedeHeadFactory::CreateCentipedeHead(length, speed);
}

void CentipedeSpawnerMain::SpawnCentipede()
{
	CentipedeHeadFactory::CreateCentipedeHead(length, speed);
}



void CentipedeSpawnerMain::Terminate()
{
	ptrInstance->MarkForDestroy();
	ptrInstance = nullptr;
}


