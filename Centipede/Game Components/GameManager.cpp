// GameManager
// Charles Tiemeyer, Sep 2024


#include "BulletFactory.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeBodyFactory.h"
#include "MushroomFactory.h"
#include "FleaFactory.h"
#include "ScorpionFactory.h"
#include "PlayerFactory.h"
#include "SpiderFactory.h"
#include "BlasterFactory.h"


#include "Level1.h"
#include "AttractorMode.h"
#include "AttractorHUD.h"
#include "Player.h"
#include "HighScore.h"

#include "HUD.h"

#include "MushroomManager.h"
#include "WaveManager.h"
#include "PlayerManager.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "GameEntityManager.h"

#include "MainControlBaseStrategy.h"
#include "GameControl.h"
#include "AttractorControl.h"

#include "TEAL\CommonElements.h"


GameManager* GameManager::ptrInstance = nullptr;
const float GameManager::BOX_SIZE = 32.0f;
HUD* GameManager::hud;
Player* GameManager::currentPlayer = nullptr;
int GameManager::gameMode = 0;
GameEntityManager* GameManager::myEntityManager;



GameManager::GameManager()
{

}

void GameManager::Initialize()
{
	Instance().dead = false;

	MushroomFactory::Initialize();				// Before "PlayerManager" so that it can create the "MushroomManager" in Player
	PlayerManager::Initialize(gameMode);

	Instance().myEntityManager = new GameEntityManager();


	currentPlayer = PlayerManager::GetCurrent();
	currentPlayer->get_MushroomManager()->LoadMushroomPositions();


	if (gameMode == 0)
	{
		Instance().controller = new AttractorControl();
		new AttractorHUD(currentPlayer);
	}
	else
	{
		Instance().controller = new GameControl();
	}


	// Initialize all the ENEMY FACTORIES
	BlasterFactory::Initialize(&Instance());
	BulletFactory::Initialize();
	FleaFactory::Initialize();
	ScorpionFactory::Initialize();
	CentipedeHeadFactory::Initialize(&Instance());
	CentipedeBodyFactory::Initialize();
	SpiderFactory::Initialize();


	// Initialize Wave Data
	// Initialize Sound
	WaveManager::Initialize();
	SoundManager::Initialize(gameMode, 10);

	// Create a HUD
	hud = new HUD(gameMode);
	hud->UpdateText(currentPlayer);


	// Create a Blaster
	BlasterFactory::CreateBlaster(gameMode);


	// Process Game
	WaveManager::ProcessWave(currentPlayer->GetCurrentLevel(), currentPlayer);

	
}




// Switches Scenes
void GameManager::ChangeGameMode(int gm)
{
	gameMode = gm;

	// AI Game (Main Screen)
	if (gameMode == 0)
	{
		ConsoleMsg::WriteLine("GameMode " + Tools::ToString(gameMode) + ": AI Control");
		SceneManager::ChangeScene(new AttractorMode);
	}

	// Player Game (Game Screen)
	else
	{
		ConsoleMsg::WriteLine("GameMode " + Tools::ToString(gameMode) + ": Player Control");
		SceneManager::ChangeScene(new Level1);
	}
}



// (1) Activates when Player clears Centipedes!!!!
	//	Called from:	CentipedeHeadFactory.cpp,   RecycleCentipedeHead(); 
	//	Called from:	Player.cpp,   Alarm1();
void GameManager::EndOfWaveCallback()
{
	currentPlayer->LevelUpAlarm();
}
void GameManager::EndOfWaveCallback__2()
{
	if (!Instance().dead)
	{
		Instance().currentPlayer->LevelUp();
		WaveManager::ProcessWave(Instance().currentPlayer->GetCurrentLevel(), currentPlayer);
	}
}




// (2) Activates when Player dies!!!!!
	//	Called from:  Blaster.cpp, Explode();
	//	Called from:  MushroomManager.cpp,  Alarm1();
	//	Called from:  HighScore.cpp,  Alarm0();
	//	Called from:  GameManager.cpp   LossOfLifeCallback3();

// Mushroom Regeneration
void GameManager::LossOfLifeCallback() 
{
	Instance().dead = true;
	Pause();

	// AI Player does not lose lives
	if (Instance().gameMode != 0)
	{
		currentPlayer->LifeLose();
		hud->UpdateText(currentPlayer);
	}

	currentPlayer->RegenerateMushrooms();
}

// High Score Check
void GameManager::LossOfLifeCallback__2()
{
	// Get rid of Enemy Entities
	Clear();
	

	// Check if the current Player is out of Lives
	if ((currentPlayer->GetLives() == 0) && (currentPlayer->GetScore() > ScoreManager::GetBottomHighScore()))
	{
		// Check if the player's score is a New High Score
		new HighScore(currentPlayer);
	}
	// If not or if not a HighScore, Change Player
	else
	{
		LossOfLifeCallback__3();
	}

	
}

// Change Player
void GameManager::LossOfLifeCallback__3()
{
	if (Instance().gameMode == 0)
	{
		LossOfLifeCallback__4();
	}
	else
	{
		if (Instance().gameMode == 1)
		{
			currentPlayer = PlayerManager::SwitchPlayer__1P();
		}
		else if (Instance().gameMode == 2)
		{
			currentPlayer = PlayerManager::SwitchPlayer__2P();
			hud->UpdateText(currentPlayer);
		}

	
		if (Instance().gameMode != 0)
		{
			LossOfLifeCallback__4();
		}
	}
	
}

// Restart Level (Seperate method so that it isn't run when changing scenes)
// There would be a split frame after a game finished in either 2P or 1P modes
// where it would procccess a new wave
void GameManager::LossOfLifeCallback__4()
{
	Instance().dead = false;

	FleaFactory::Reactivate();
	ScorpionFactory::Reactivate();
	SpiderFactory::Reactivate();
	

	BlasterFactory::CreateBlaster(gameMode);
	WaveManager::ProcessWave(Instance().currentPlayer->GetCurrentLevel(), Instance().currentPlayer);
}



void GameManager::Pause()
{
	FleaFactory::Pause();
	ScorpionFactory::Pause();
	CentipedeHeadFactory::Pause();
	CentipedeBodyFactory::Pause();
	SpiderFactory::Pause();
}

void GameManager::Clear()
{
	FleaFactory::Remove();
	ScorpionFactory::Remove();
	CentipedeHeadFactory::Recall();
	CentipedeBodyFactory::Recall();
	SpiderFactory::Remove();
}




void GameManager::Terminate()
{
	delete Instance().myEntityManager;
	delete Instance().ptrInstance;
	ptrInstance = nullptr;

	PlayerManager::Terminate();
	MushroomFactory::Terminate();
	BlasterFactory::Terminate();
	BulletFactory::Terminate();
	FleaFactory::Terminate();
	ScorpionFactory::Terminate();
	CentipedeHeadFactory::Terminate();
	CentipedeBodyFactory::Terminate();
	SpiderFactory::Terminate();
	WaveManager::Terminate();

	ScoreManager::Terminate();
	SoundManager::Terminate();
	
}