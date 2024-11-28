// WaveData
// Charles Tiemeyer, Oct 2024

#ifndef _WaveData
#define _WaveData

#include "TEAL\CommonElements.h"

struct WaveData
{
	int CurrentWave;

	// Centipede Main
	int CentipedeMain_Length;
	float CentipedeMain_Speed;

	// Centipede Head
	int CentipedeHead_Count;
	float CentipedeHead_Speed;

	// Flea
	
	float Flea_Speed;
	int Flea_MushThresh;
	int Flea_SpawnProb;

	// Spider
	
	float Spider_Speed;
	float Spider_Timer;

	// Scorpion
	
	float Scorpion_Speed;
	float Scorpion_Timer;

	bool Flea_SpawnerOn;
	bool Spider_SpawnerOn;
	bool Scorpion_SpawnerOn;


	
	
	


};

#endif _WaveData