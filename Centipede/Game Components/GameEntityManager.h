// GameEntityManager
// Charles Tiemeyer, November 2024

#ifndef _GameEntityManager
#define _GameEntityManager

#include "TEAL\CommonElements.h"

//Forward declarations
class Player;
class HUD;
class SoundManager;
class WaveManager;
class CMDSound;



class GameEntityManager
{
public:
	GameEntityManager();
	GameEntityManager(const GameEntityManager&) = delete;
	GameEntityManager& operator=(const GameEntityManager&) = delete;
	~GameEntityManager();

	static CMDSound* pKilled;

private:

	// Supposed to have pointers towards spawners

};

#endif _GameEntityManager