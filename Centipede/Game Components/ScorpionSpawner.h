// ScorpionSpawner
// Charles Tiemeyer, Oct 2024

#ifndef _ScorpionSpawner
#define _ScorpionSpawner

#include "ScorpionFactory.h"
#include "Scorpion.h"
#include "TEAL\CommonElements.h"

class ScorpionSpawner : public GameObject
{
private:

	ScorpionSpawner() = default;
	ScorpionSpawner(const ScorpionSpawner&) = delete;
	ScorpionSpawner& operator=(const ScorpionSpawner&) = delete;
	~ScorpionSpawner() = default;

	// Control Elements
	static bool spawner_on;	
	static float speed;
	static float timer;
	static bool alarm_on;

	bool active;


	static ScorpionSpawner* ptrInstance;
	static ScorpionSpawner& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ScorpionSpawner;
		return *ptrInstance;
	};

	virtual void Alarm0();


public:
	static void Initialize();


	static void set_spawner(bool on) { spawner_on = on; };
	static void set_speed(float s) { speed = s; };
	static void set_timer(float t) { timer = t; };
	static void set_active_off() { Instance().active = false; };

	static bool get_alarm_on() { return alarm_on; };


	static void ActivateSpawner(bool spawnerOn, float speed, float timer);

	static void SpawnScorpion();
	static void SpawnerActivate();

	static void Terminate();

};

#endif _ScorpionSpawner