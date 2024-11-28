// FleaSpawner
// Charles Tiemeyer, Oct 2024

#include "TEAL\CommonElements.h"
#include "FleaSpawner.h"
#include "FleaFactory.h"
#include "Player.h"

bool FleaSpawner::spawner_on;
float FleaSpawner::speed;
int FleaSpawner::spawn_probability;
int FleaSpawner::pz_mushroom_count_threshold;
int FleaSpawner::num_mushrooms;
FleaSpawner* FleaSpawner::ptrInstance = nullptr;


void FleaSpawner::Initialize()
{

	spawner_on = false;
	speed = 0;
	spawn_probability = 0;
	pz_mushroom_count_threshold = 0;
	num_mushrooms = 0;

	Instance().active = false;
}


void FleaSpawner::ActivateSpawner(bool spawnerOn, float s, int mushThresh, int mushSpawnProb, int num_mush)
{
	spawner_on = spawnerOn;
	speed = s;
	pz_mushroom_count_threshold = mushThresh;
	spawn_probability = mushSpawnProb;
	num_mushrooms = num_mush;

	SpawnFlea();
}




// Called when there are less mushrooms in playerzone than the threshold
void FleaSpawner::SpawnFlea()
{
	if (spawner_on && !Instance().active)
	{
		if (num_mushrooms < pz_mushroom_count_threshold)
		{
			FleaFactory::CreateFlea(speed, spawn_probability);
			Instance().active = true;
		}
	}
}


// Called when (Flea is destroyed) or (Mushroom from player zone gets destroyed)
void FleaSpawner::update_number_of_pz_mushrooms(int add)
{
	num_mushrooms += add;
}




void FleaSpawner::Terminate()
{
	ptrInstance->MarkForDestroy();
	ptrInstance = nullptr;
}

