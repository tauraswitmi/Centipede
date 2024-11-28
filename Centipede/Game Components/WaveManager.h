// WaveManager
// Charles Tiemeyer, Oct 2024

#ifndef _WaveManager
#define _WaveManager

#include "TEAL\CommonElements.h"
#include "WaveData.h"

#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <string>



class CentipedeHead;
class Flea;
class Spider;
class Scorpion;
class Player;

class WaveManager
{
private:
	//WaveManager(const WaveManager&) = delete;				
	//WaveManager& operator = (const WaveManager&) = delete;		
	//~WaveManager() = default;
	//
	//WaveManager();

	static std::vector<WaveData> Waves;


	static int numWaves;

	static WaveManager* ptrInstance;

	static WaveManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new WaveManager;
		return *ptrInstance;
	};

public:

	static WaveData GetWaveData(int WaveNumber);
	static void LoadWaveData();

	static void ProcessWave(int WaveNumber, Player* player);

	static void Initialize();

	static void Terminate();

};

#endif _WaveManager