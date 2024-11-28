// ScorpionSpawner
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "ScorpionSpawner.h"
#include "ScorpionFactory.h"

bool ScorpionSpawner::spawner_on;
bool ScorpionSpawner::alarm_on;
float ScorpionSpawner::speed;
float ScorpionSpawner::timer;
ScorpionSpawner* ScorpionSpawner::ptrInstance = nullptr;


void ScorpionSpawner::Initialize()
{
	Instance().active = false;

	spawner_on = false;
	speed = 0;
	timer = 0;
}


void ScorpionSpawner::ActivateSpawner(bool spawn, float s, float t)
{
	spawner_on = spawn;
	speed = s;
	timer = t;

	SpawnScorpion();
}


// For some retarded reason this spawns scorpions twice
// Called when Alarm ends
void ScorpionSpawner::SpawnScorpion()
{
	if (spawner_on && !Instance().active)
	{
		ScorpionFactory::CreateScorpion(speed);
		Instance().active = true;
	}
}


// Called when Scorpion is destroyed
void ScorpionSpawner::SpawnerActivate()
{
	if (spawner_on)
	{
		alarm_on = true;
		Instance().SetAlarm(0, timer);
	}
}


// Called if spawner is on and Scorpion is destroyed
void ScorpionSpawner::Alarm0()
{
	alarm_on = false;
	SpawnScorpion();
}




void ScorpionSpawner::Terminate()
{
	ptrInstance->MarkForDestroy();
	ptrInstance = nullptr;
}


