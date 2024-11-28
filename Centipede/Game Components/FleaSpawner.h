// FleaSpawner
// Charles Tiemeyer, Oct 2024

#ifndef _FleaSpawner
#define _FleaSpawner

#include "FleaFactory.h"
#include "Flea.h"
#include "TEAL\CommonElements.h"

class FleaSpawner : public GameObject
{
private:

	FleaSpawner() = default;
	FleaSpawner(const FleaSpawner&) = delete;
	FleaSpawner& operator=(const FleaSpawner&) = delete;
	~FleaSpawner() = default;

	// Control Elements
	static bool spawner_on;
	static float speed;
	static int spawn_probability;
	static int pz_mushroom_count_threshold;

	// Only spawns if there isn't an active Flea on screen
	bool active;
	

	static int num_mushrooms;


	static FleaSpawner* ptrInstance;
	static FleaSpawner& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new FleaSpawner;
		return *ptrInstance;
	};


public:
	static void Initialize();


	static void set_spawner(bool on) { spawner_on = on; };
	static void set_speed(float s) { speed = s; };
	static void set_spawn_prob(int sp) { spawn_probability = sp; };
	static void set_threshold(int t) { pz_mushroom_count_threshold = t; };
	static void set_active_off() { Instance().active = false; }

	static void update_number_of_pz_mushrooms(int add);


	static void ActivateSpawner(bool spawnerOn, float speed, int mushThresh, int mushSpawnProb, int num_mush);
	static void SpawnFlea();


	static void Terminate();

};

#endif _FleaSpawner