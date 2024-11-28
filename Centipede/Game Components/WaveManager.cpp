// WaveManager
// Charles Tiemeyer, Oct 2024

#include "WaveManager.h"
#include "WaveData.h"

#include "CentipedeSpawnerMain.h"
#include "CentipedeSpawnerSoloHead.h"
#include "FleaSpawner.h"
#include "ScorpionSpawner.h"
#include "SpiderSpawner.h"

#include "Player.h"

std::vector<WaveData> WaveManager::Waves;
int WaveManager::numWaves;
WaveManager* WaveManager::ptrInstance = nullptr;

//WaveManager::WaveManager()
//{
//
//}


void WaveManager::Initialize()
{

	Instance().numWaves = 4;

	// Not necessary, just doing so for insecurity reasons 999 //
	CentipedeSpawnerMain::Initialize();
	CentipedeSpawnerSoloHead::Initialize();
	FleaSpawner::Initialize();
	SpiderSpawner::Initialize();
	ScorpionSpawner::Initialize();


	// Get Data from Text File
	LoadWaveData();
}


WaveData WaveManager::GetWaveData(int WaveNumber)
{
	return Instance().Waves[WaveNumber - 1];


}


void WaveManager::LoadWaveData()
{
	std::ifstream File;
	std::string temp;

	WaveData current_wave;

	File.open("Game Components\\Wave.txt"); // Open File


	if (!File)
	{
		ConsoleMsg::WriteLine("why the fuck");
	}

	
	for (int i = 0; i < Instance().numWaves; i++)
	{
		File >> temp;
		File >> current_wave.CurrentWave;
		File >> temp;
		File >> current_wave.CentipedeMain_Length;
		File >> temp;
		File >> current_wave.CentipedeMain_Speed;
		File >> temp;
		File >> current_wave.CentipedeHead_Count;
		File >> temp;
		File >> current_wave.CentipedeHead_Speed;
		File >> temp;
		File >> current_wave.Flea_SpawnerOn;
		File >> temp;
		File >> current_wave.Flea_Speed;
		File >> temp;
		File >> current_wave.Flea_MushThresh;
		File >> temp;
		File >> current_wave.Flea_SpawnProb;
		File >> temp;
		File >> current_wave.Spider_SpawnerOn;
		File >> temp;
		File >> current_wave.Spider_Speed;
		File >> temp;
		File >> current_wave.Spider_Timer;
		File >> temp;
		File >> current_wave.Scorpion_SpawnerOn;
		File >> temp;
		File >> current_wave.Scorpion_Speed;
		File >> temp;
		File >> current_wave.Scorpion_Timer;

		Instance().Waves.push_back(current_wave);
	}
	

	File.close(); // Close File
}


// The idea is that I shouldn't have to treat the Spawners as statics
void WaveManager::ProcessWave(int WaveNumber, Player* player)
{
	WaveData current = Instance().Waves[WaveNumber - 1];

	CentipedeSpawnerMain::SpawnCentipede(current.CentipedeMain_Speed, current.CentipedeMain_Length);
	CentipedeSpawnerSoloHead::SpawnCentipedeHead_AtSpawn(current.CentipedeHead_Speed, current.CentipedeHead_Count);
	FleaSpawner::ActivateSpawner(current.Flea_SpawnerOn, current.Flea_Speed, current.Flea_MushThresh, current.Flea_SpawnProb, player->get_MushroomManager()->get_number_bz_mushrooms());
	SpiderSpawner::ActivateSpawner(current.Spider_SpawnerOn, current.Spider_Speed, current.Spider_Timer);
	ScorpionSpawner::ActivateSpawner(current.Scorpion_SpawnerOn, current.Scorpion_Speed, current.Scorpion_Timer);
}


void WaveManager::Terminate()
{
	delete Instance().ptrInstance;
	ptrInstance = nullptr;
}