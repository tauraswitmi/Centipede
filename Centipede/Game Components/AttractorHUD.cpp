// AttractorHUD
// Charles Tiemeyer, November 2024

#include "AttractorHUD.h"
#include "Player.h"
#include "ScoreManager.h"
#include "GameManager.h"
#include "HighScoreEntry.h"
#include <list>
#include <algorithm>


std::list<sf::Vector2i> AttractorHUD::positions;

AttractorHUD::AttractorHUD(Player* ai)
{

	// Type out "HIGH SCORES"
	// Delete Mushrooms
	std::string Text = "HIGH SCORES";
	int digits = Text.length();
	nextpos = sf::Vector2f(GameManager::BOX_SIZE * (MIDDLE - digits / 2), GameManager::BOX_SIZE * Init_Row__HST);

	for (int i = 0; i < digits; i++)
	{
		text__High_Scores_Text.push_back(myfont.GetGlyph(Text.at(i), nextpos));
		nextpos.x += GameManager::BOX_SIZE;

		ai->get_MushroomManager()->RemoveMushroom((MIDDLE - digits/2) + i, Init_Row__HST);
		positions.push_back(sf::Vector2i((MIDDLE - digits / 2) + i, Init_Row__HST));
	}



	// Type out actual HIGH SCORES
	// Delete Mushrooms
	int j = 1;
	std::list<HighScoreEntry> hs_list = ScoreManager::GetHighScores();
	std::list<HighScoreEntry>::iterator it;
	for (it = hs_list.begin(); it != hs_list.end(); it++)
	{
		Text = it->name + " " + Tools::ToString(it->score);
		digits = Text.length();
		nextpos = sf::Vector2f(GameManager::BOX_SIZE * (MIDDLE - digits / 2), GameManager::BOX_SIZE * (Init_Row__HST + j));

		for (int i = 0; i < digits; i++)
		{
			text__High_Scores.push_back(myfont.GetGlyph(Text.at(i), nextpos));
			nextpos.x += GameManager::BOX_SIZE;

			ai->get_MushroomManager()->RemoveMushroom((MIDDLE - digits / 2) + i, Init_Row__HST + j);
		}
		j++;
	}


	// Type out "BONUS EVERY 12000"
	// Delete Mushrooms
	Text = "BONUS EVERY 12000";
	digits = Text.length();
	nextpos = sf::Vector2f(GameManager::BOX_SIZE * (MIDDLE - digits / 2), GameManager::BOX_SIZE * Init_Row__BE);

	for (int i = 0; i < digits; i++)
	{
		text__Bonus_Every.push_back(myfont.GetGlyph(Text.at(i), nextpos));
		nextpos.x += GameManager::BOX_SIZE;

		ai->get_MushroomManager()->RemoveMushroom((MIDDLE - digits / 2) + i, Init_Row__HST);
	}


	//SetDrawOrder(1000);
}




void AttractorHUD::Draw()
{
	std::list<Glyph>::iterator it;
	for (it = text__High_Scores_Text.begin(); it != text__High_Scores_Text.end(); it++)
		it->Draw();
	for (it = text__High_Scores.begin(); it != text__High_Scores.end(); it++)
		it->Draw();
	for (it = text__Bonus_Every.begin(); it != text__Bonus_Every.end(); it++)
		it->Draw();
}

