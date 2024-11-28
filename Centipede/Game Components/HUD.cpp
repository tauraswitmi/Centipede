// HUD
// Charles Tiemeyer, November 2024

#include "HUD.h"
#include "Player.h"
#include "PlayerManager.h"
#include "ScoreManager.h"
#include "GameManager.h"


int HUD::MAX_ScoreDigits = 6;
int HUD::MAX_StartingZeros = 2;

int HUD::prev_GameMode = 0;
int HUD::curr_GameMode = 0;

std::list<Glyph> HUD::text__player1;
std::list<Glyph> HUD::text__player2;
std::list<Glyph> HUD::text__highscore;


HUD::HUD(int gm)
{
	prev_GameMode = curr_GameMode;
	curr_GameMode = gm;

	if (curr_GameMode == 0)
	{
		if (prev_GameMode == 0)
		{
			// Set P1 == 00
			// Clear P2
			priv_UpdatePlayer1Side(PlayerManager::getPlayer1()->GetScore());
			text__player2.clear();
		}
		else if (prev_GameMode == 1)
		{
			// Set P1 == Prev
			// Clear P2
			priv_UpdatePlayer1Side(PlayerManager::getP1ScorePrev());
			text__player2.clear();
		}
		else if (prev_GameMode == 2)
		{
			// Set P1 == Prev
			// Set P2 == Prev
			priv_UpdatePlayer1Side(PlayerManager::getP1ScorePrev());
			priv_UpdatePlayer2Side(PlayerManager::getP2ScorePrev());
			ConsoleMsg::WriteLine("Prev Updated!");
		}
	}
	else if (curr_GameMode == 1)
	{
		text__player2.clear();
	}
}



void HUD::priv_UpdatePlayer1Side(int score)
{

	text__player1.clear();
	text = Tools::ToString(score);
	nextpos = sf::Vector2f(0, 0);
	digits = text.length();

	//  (LEFT SIDE) High Score =======================================

	// Accurate to Game have it display "00" or "0x"
	if (digits <= 1)
	{
		// 1st DIGIT
		nextpos.x += (myfont.CellWidth() * 2) * (MAX_ScoreDigits - 2);
		text__player1.push_back(myfont.GetGlyph('0', nextpos));

		// 2nd DIGIT
		nextpos.x += (myfont.CellWidth() * 2);
		text__player1.push_back(myfont.GetGlyph(text.at(0), nextpos));

		nextpos.x += (myfont.CellWidth() * 2);
	}

	// Caps out at 999,999
	else if (digits > MAX_ScoreDigits)
	{
		for (int i = digits - MAX_ScoreDigits; i < digits; i++)
		{
			text__player1.push_back(myfont.GetGlyph(text.at(i), nextpos));

			// we must update the next position ourselves
			nextpos.x += myfont.CellWidth() * 2;
		}
	}

	// Normal Display (Skip digits behind it)
	else
	{
		nextpos.x += (myfont.CellWidth() * 2) * (MAX_ScoreDigits - digits);

		for (int i = 0; i < digits; i++)
		{
			text__player1.push_back(myfont.GetGlyph(text.at(i), nextpos));

			// we must update the next position ourselves
			nextpos.x += myfont.CellWidth() * 2;
		}

	}

	// (LEFT SIDE) Lives =======================================
	if (curr_GameMode != 0)
	{
		for (int i = 0; i < PlayerManager::getPlayer1()->GetLives() - 1; i++)
		{
			text__player1.push_back(myfont.GetGlyph('@', nextpos));

			// we must update the next position ourselves
			nextpos.x += myfont.CellWidth() * 2;
		}
	}
	

}

void HUD::priv_UpdatePlayer2Side(int score)
{
	
	text__player2.clear();
	text = Tools::ToString(score);
	digits = text.length();


	// (RIGHT SIDE) Lives =======================================

	if (curr_GameMode != 0)
	{

		nextpos = sf::Vector2f((MIDDLE + Player::MAX_LIVES - 1) * GameManager::BOX_SIZE, 0);
		for (int i = 0; i < PlayerManager::getPlayer2()->GetLives() - 1; i++)
		{

			text__player2.push_back(myfont.GetGlyph('@', nextpos));

			// we must update the next position ourselves
			nextpos.x -= myfont.CellWidth() * 2;
		}
	}
	
		nextpos = sf::Vector2f((MIDDLE + Player::MAX_LIVES) * GameManager::BOX_SIZE, 0);
	
	

	// (RIGHT SIDE) Score =======================================

	// Accurate to Game have it display "00" or "0x"
	if (digits <= 1)
	{

		// 1st DIGIT
		nextpos.x += GameManager::BOX_SIZE * (MAX_ScoreDigits - MAX_StartingZeros);
		text__player2.push_back(myfont.GetGlyph('0', nextpos));

		// 2nd DIGIT
		nextpos.x += (myfont.CellWidth() * 2);
		text__player2.push_back(myfont.GetGlyph(text.at(0), nextpos));

	}

	// Caps out at 999,999
	else if (digits > MAX_ScoreDigits)
	{
		nextpos.x += GameManager::BOX_SIZE * (MAX_ScoreDigits - digits);

		for (int i = digits - MAX_ScoreDigits; i < digits; i++)
		{
			text__player2.push_back(myfont.GetGlyph(text.at(i), nextpos));

			// we must update the next position ourselves
			nextpos.x += myfont.CellWidth() * 2;
		}
	}

	// Normal Display (Skip digits behind it)
	else
	{
		nextpos.x += (myfont.CellWidth() * 2) * (MAX_ScoreDigits - digits);

		for (int i = 0; i < digits; i++)
		{
			text__player2.push_back(myfont.GetGlyph(text.at(i), nextpos));

			// we must update the next position ourselves
			nextpos.x += myfont.CellWidth() * 2;
		}

	}
}

void HUD::priv_UpdateHighScore()
{

	text__highscore.clear();
	text = Tools::ToString(ScoreManager::GetTopHighScore());
	digits = text.length();
	nextpos.x = (MIDDLE - digits) * GameManager::BOX_SIZE;


	//  (MIDDLE SIDE) High Score =======================================
	for (int i = 0; i < digits; i++)
	{
		text__highscore.push_back(myfont.GetGlyph(text.at(i), nextpos));
		nextpos.x += GameManager::BOX_SIZE;
	}
}



void HUD::UpdateText(Player* player)
{


	if (curr_GameMode == 1)
	{
		priv_UpdatePlayer1Side(PlayerManager::getPlayer1()->GetScore());
	}
	else if (curr_GameMode == 2)
	{
		priv_UpdatePlayer1Side(PlayerManager::getPlayer1()->GetScore());
		priv_UpdatePlayer2Side(PlayerManager::getPlayer2()->GetScore());
	}
	
	priv_UpdateHighScore();


}


void HUD::Draw()
{
	std::list<Glyph>::iterator it;
	for (it = text__player1.begin(); it != text__player1.end(); it++)
		it->Draw();
	for (it = text__player2.begin(); it != text__player2.end(); it++)
		it->Draw();
	for (it = text__highscore.begin(); it != text__highscore.end(); it++)
		it->Draw();
}