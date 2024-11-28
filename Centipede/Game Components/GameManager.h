// GameManager
// Charles Tiemeyer, September 2024

#ifndef _GameManager
#define _GameManager

#include "TEAL\CommonElements.h"

//Forward declarations
class Player;
class HUD;
class MainControlBaseStrategy;
class MushroomManager;
class WaveManager;
class GameEntityManager;



class GameManager
{
public:
	GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	~GameManager() = default;

	static void Initialize();

	static void EndOfWaveCallback();
	static void EndOfWaveCallback__2();
	static void LossOfLifeCallback();
	static void LossOfLifeCallback__2();
	static void LossOfLifeCallback__3();
	static void LossOfLifeCallback__4();

	static void Pause();
	static void Clear();
	static void Terminate();



	static void ChangeGameMode(int gm);

	static const float BOX_SIZE;
	static HUD* hud;
	static Player* currentPlayer;

private:


	bool dead;
	static int gameMode;
	MainControlBaseStrategy* controller;
	
	static GameEntityManager* myEntityManager;
	

	static GameManager* ptrInstance;

	static GameManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new GameManager;
		return *ptrInstance;
	};


};

#endif _GameManager