// SpiderSpawner
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "SpiderSpawner.h"
#include "SpiderFactory.h"

bool SpiderSpawner::spawner_on;
bool SpiderSpawner::alarm_on;
float SpiderSpawner::speed;
float SpiderSpawner::timer;
SpiderSpawner* SpiderSpawner::ptrInstance = nullptr;


void SpiderSpawner::Initialize()
{
	Instance().active = false;

	spawner_on = false;
	speed = 0;
	timer = 0;
	
}


void SpiderSpawner::ActivateSpawner(bool spawn, float s, float t)
{
	spawner_on = spawn;
	speed = s;
	timer = t;

	Instance().SetAlarm(0, timer);
}


// Called when Alarm ends
void SpiderSpawner::SpawnSpider()
{
	if (spawner_on && !Instance().active)
	{
		SpiderFactory::CreateSpider(speed);
		Instance().active = true;
	}
}


// Called when Scorpion is destroyed
void SpiderSpawner::SpawnerActivate()
{
	if (spawner_on)
	{
		alarm_on = true;
		Instance().SetAlarm(0, timer);
	}
}


// Called if spawner is on and Scorpion is destroyed
void SpiderSpawner::Alarm0()
{
	alarm_on = false;
	SpawnSpider();
}




void SpiderSpawner::Terminate()
{
	ptrInstance->MarkForDestroy();
	ptrInstance = nullptr;
}


