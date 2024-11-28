// PlayerManager
// Charles Tiemeyer, Oct 2024

#include "PlayerManager.h"
#include "PlayerFactory.h"
#include "Player.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "CMDSound.h"


std::queue<sf::Vector2i> PlayerManager::mushroom_positions;
int PlayerManager::wave_number = 1;
int PlayerManager::prevScoreP1 = 0;
int PlayerManager::prevScoreP2 = 0;
PlayerManager* PlayerManager::ptrInstance = nullptr;
CMDSound* PlayerManager::pSound_MushRegen = nullptr;
CMDSound* PlayerManager::pSound_OneUp = nullptr;


/*
	When new scene is made, Assign new Players to corresponding GameMode
*/
void PlayerManager::Initialize(int gm)
{

	pSound_MushRegen = SoundManager::GetScoreCommand(SoundManager::SoundEvents::Replenish);
	pSound_OneUp = SoundManager::GetScoreCommand(SoundManager::SoundEvents::Extra_Life);


	if (gm == 0)
	{
		Instance().Player_1 = new Player(0);
		Instance().Player_2 = nullptr;

		// Store Data from previous Game
		Instance().Player_1->SetCurrentLevel(wave_number);
		Instance().Player_1->get_MushroomManager()->SetMushroomPositions(mushroom_positions);
	}
	else if (gm == 1)
	{
		Instance().Player_1 = new Player(1);
		Instance().Player_2 = nullptr;
	}
	else
	{
		Instance().Player_1 = new Player(1);
		Instance().Player_2 = new Player(2);
	}
	

	// Always start with 1st Player
	Instance().Player_Current = Instance().Player_1;


}


Player* PlayerManager::SwitchPlayer__FromAI()
{
	Instance().Player_Current->get_MushroomManager()->EmptyGrid();
	Instance().Player_Current = Instance().Player_1;
	Instance().Player_Current->get_MushroomManager()->LoadMushroomPositions();
	return Instance().Player_Current;
}
Player* PlayerManager::SwitchPlayer__1P()
{
	if (Instance().Player_Current->GetLives() == 0)
	{
		ConsoleMsg::WriteLine("Game Over!");
		prevScoreP1 = PlayerManager::getPlayer1()->GetScore();
		Instance().priv_Switch_AI();
	}

	return Instance().Player_Current;
}
Player* PlayerManager::SwitchPlayer__2P()
{

	if (Instance().Player_Current == Instance().Player_1)
	{
		Instance().priv_Switch_Player1();
	}
	else
	{
		Instance().priv_Switch_Player2();
	}

	return Instance().Player_Current;
}


void PlayerManager::priv_Switch_Player1()
{
	// If (P1) has no lives
	if (Player_Current->GetLives() == 0)
	{
		// If (P1) & (P2) has no lives
		if (Player_2->GetLives() == 0)
		{
			ConsoleMsg::WriteLine("Game Over!");
			prevScoreP1 = PlayerManager::getPlayer1()->GetScore();
			prevScoreP2 = PlayerManager::getPlayer2()->GetScore();
			priv_Switch_AI();
		}
		// If (P1) has no lives, but (P2) still has lives
		else
		{
			ConsoleMsg::WriteLine("Player 2 Turn!");
			Player_1->get_MushroomManager()->EmptyGrid();
			Player_Current = Player_2;
			Player_Current->get_MushroomManager()->LoadMushroomPositions();
		}
	}
	// If (P1) has lives
	else
	{
		// If (P1) & (P2) still has lives
		if (Player_2->GetLives() != 0)
		{
			ConsoleMsg::WriteLine("Player 2 Turn!");
			Player_1->get_MushroomManager()->SaveMushroomPositions();
			Player_1->get_MushroomManager()->EmptyGrid();
			Player_Current = Player_2;
			Player_Current->get_MushroomManager()->LoadMushroomPositions();
		}
	}
}
void PlayerManager::priv_Switch_Player2()
{
	// If (P2) has no lives
	if (Player_Current->GetLives() == 0)
	{
		// If (P2) & (P1) has no lives
		if (Player_1->GetLives() == 0)
		{
			ConsoleMsg::WriteLine("Game Over!");
			priv_Switch_AI();
		}
		// If (P2) has no lives, but (P1) still has lives
		else
		{
			ConsoleMsg::WriteLine("Player 1 Turn!");
			Player_2->get_MushroomManager()->EmptyGrid();
			Player_Current = Player_1;
			Player_Current->get_MushroomManager()->LoadMushroomPositions();
		}
	}
	// If (P2) has lives
	else
	{

		// If (P2) & (P1) still has lives
		if (Player_1->GetLives() != 0)
		{
			ConsoleMsg::WriteLine("Player 1 Turn!");
			Player_2->get_MushroomManager()->SaveMushroomPositions();
			Player_2->get_MushroomManager()->EmptyGrid();
			Player_Current = Player_1;
			Player_Current->get_MushroomManager()->LoadMushroomPositions();
		}
	}
}
void PlayerManager::priv_Switch_AI()
{
	mushroom_positions = Player_Current->get_MushroomManager()->GetMushroomPositions();
	wave_number = Player_Current->GetCurrentLevel();



	// Copies Mushroom Manager data from Player
	//AI->get_MushroomManager()->get_mushroom_positions() = Player_Current->get_MushroomManager()->GetMushroomPositions();
	//Player_Current->get_MushroomManager()->EmptyGrid();
	//Player_Current = AI;
	//Player_Current->get_MushroomManager()->LoadMushroomPositions();

	GameManager::ChangeGameMode(0);
}



void PlayerManager::Terminate()
{
	delete ptrInstance;
	delete pSound_MushRegen;
	delete pSound_OneUp;
	ptrInstance = nullptr;
}