// Player
// Charles Tiemeyer, Oct 2024

#include "Player.h"
#include "PlayerManager.h"
#include "HUD.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "ScoreManager.h"
#include "MushroomManager.h"




// Constructed only once throughout the entire program (specific player)
Player::Player(int player_no)
{

	PlayerNumber = player_no;
	mushroom_manager = new MushroomManager();

	Score_NextOneUp = ONE_UP_POINTS;

	Reset();
}

void Player::Update()
{
	SoundManager::ProcessSounds();
	ScoreManager::ProcessScores();
	SoundManager::ProcessPause();
}

void Player::Destroy()
{
	if (PlayerNumber == 1)
	{
		PlayerManager::setPlayer1Prev(Score);
	}
	else if (PlayerNumber == 2)
	{
		PlayerManager::setPlayer2Prev(Score);
	}
}




void Player::Reset()
{

	Score = 0;
	Score_NextOneUp = ONE_UP_POINTS;

	if (PlayerNumber == 0)
	{
		Lives = 1;
	}
	else
	{
		Lives = INIT_LIVES;
	}
	
	CurrentLevel = 1;
	
}

void Player::AddScore(int val)
{
	Score += val;

	if (Score > Score_NextOneUp)
	{
		OneUp();
		Score_NextOneUp += ONE_UP_POINTS;
	}

	GameManager::hud->UpdateText(this);
	ConsoleMsg::WriteLine("Player Score: " + Tools::ToString(Score));

}


void Player::LevelUp()
{
	CurrentLevel++;

	// If gone thru entire loop of levels
	if (CurrentLevel % 12 == 0)
	{
		CurrentLevel = 0;
	}
}


void Player::OneUp()
{
	Lives++;

	if (Lives > MAX_LIVES)
	{
		Lives = MAX_LIVES;
	}
	else
	{
		SoundManager::SendSoundCMD(PlayerManager::pSound_OneUp);
	}
}

void Player::GameEnd()
{
	MarkForDestroy();
}



void Player::RegenerateMushrooms()
{
	SetAlarm(0, 1);
}
void Player::LevelUpAlarm()
{
	SetAlarm(1, 2);
}


void Player::Alarm0()
{
	this->mushroom_manager->regen();
}
void Player::Alarm1()
{
	
	GameManager::EndOfWaveCallback__2();
}