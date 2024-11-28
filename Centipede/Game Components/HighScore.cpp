// HighScoreInput
// Charles Tiemeyer, November 2024

#include "HighScore.h"
#include "HighScoreEntry.h"
#include "Player.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "MushroomManager.h"


const sf::Vector2i HighScore::Init_GPos__GS = sf::Vector2i(9, 19);
const sf::Vector2i HighScore::Init_GPos__EYI = sf::Vector2i(5, 20);
const sf::Vector2i HighScore::Init_GPos__I = sf::Vector2i(12, 22);


HighScore::HighScore(Player* p)
{
	RegisterInput(InputFlags::TextEntered);
	curr_player = p;
	count = 0;

	std::string Great_Score = "GREAT SCORE";
	std::string Enter_Your_Initials = "ENTER YOUR INITIALS";

	nextpos__GreatScore =			sf::Vector2f(GameManager::BOX_SIZE * Init_GPos__GS.x, GameManager::BOX_SIZE * Init_GPos__GS.y);
	nextpos__Enter_Your_Initials =	sf::Vector2f(GameManager::BOX_SIZE * Init_GPos__EYI.x, GameManager::BOX_SIZE * Init_GPos__EYI.y);
	nextpos__input =				sf::Vector2f(GameManager::BOX_SIZE * Init_GPos__I.x, GameManager::BOX_SIZE * Init_GPos__I.y);

	// Type out "GREAT SCORE"
	// Delete Mushrooms
	for (size_t i = 0; i < Great_Score.length(); i++)
	{
		text__Great_Score.push_back(myfont.GetGlyph(Great_Score.at(i), nextpos__GreatScore));
		nextpos__GreatScore.x += GameManager::BOX_SIZE;

		curr_player->get_MushroomManager()->RemoveMushroom(Init_GPos__GS.x + i, Init_GPos__I.y);
	}

	// Type out "ENTER YOUR INITIALS"
	// Delete Mushrooms
	for (size_t i = 0; i < Enter_Your_Initials.length(); i++)
	{
		text__Enter_Your_Initials.push_back(myfont.GetGlyph(Enter_Your_Initials.at(i), nextpos__Enter_Your_Initials));
		nextpos__Enter_Your_Initials.x += GameManager::BOX_SIZE;

		curr_player->get_MushroomManager()->RemoveMushroom(Init_GPos__GS.x + i, Init_GPos__I.y);
	}
}



void HighScore::Draw()
{
	std::list<Glyph>::iterator it;
	for (it = text__Great_Score.begin(); it != text__Great_Score.end(); it++)
		it->Draw();
	for (it = text__Enter_Your_Initials.begin(); it != text__Enter_Your_Initials.end(); it++)
		it->Draw();
	for (it = text__input.begin(); it != text__input.end(); it++)
		it->Draw();
}


void HighScore::TextEntered(sf::Uint32 UnicodeValue)
{
	std::string temp;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		// If typed more than 0 characters, Delete the Last Char
		if (count != 0)
		{
			name.pop_back();
			text__input.pop_back();
			nextpos__input.x -= GameManager::BOX_SIZE;
			count--;
		}
	}
	else
	{
		count++;

		// If typed 3 or less characters, Keep Typing
		if (count <= 3)
		{
			name += Tools::ToString((char)UnicodeValue);
			text__input.push_back(myfont.GetGlyph((char)UnicodeValue, nextpos__input));
			nextpos__input.x += GameManager::BOX_SIZE;
		}

		// If typed more than 3 characters, Submit Score
		else
		{
			ScoreManager::InsertHighScoreEntry({ name, curr_player->GetScore() });
			SetAlarm(0, 1);
		}
	}
}



void HighScore::Alarm0()
{
	DeregisterInput();
	GameManager::LossOfLifeCallback__3();
	MarkForDestroy();
}