// ScorpionSpawner
// Charles Tiemeyer, Oct 2024

#ifndef _SpiderSpawner
#define _SpiderSpawner

#include "SpiderFactory.h"
#include "Spider.h"
#include "TEAL\CommonElements.h"

class SpiderSpawner : public GameObject
{
private:

	SpiderSpawner() = default;
	SpiderSpawner(const SpiderSpawner&) = delete;
	SpiderSpawner& operator=(const SpiderSpawner&) = delete;
	~SpiderSpawner() = default;

	// Control Elements
	static bool spawner_on;
	static float speed;
	static float timer;
	static bool alarm_on; // For when the spider spawns again

	bool active;


	static SpiderSpawner* ptrInstance;
	static SpiderSpawner& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpiderSpawner;
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

	static void ActivateSpawner(bool spawner, float speed, float timer);

	static void SpawnSpider();
	static void SpawnerActivate();

	static void Terminate();

};

#endif _SpiderSpawner