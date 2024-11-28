// HighScoreInput
// Charles Tiemeyer, November 2024

#ifndef _HighScore
#define _HighScore

#include "TEAL/CommonElements.h"
#include <list>
#include "CrazyFont.h"

class Player;

class HighScore : public GameObject
{
public:
	HighScore(Player* p);
	virtual void Draw();
	virtual void TextEntered(sf::Uint32 UnicodeValue);
	virtual void Alarm0();

private:

	CrazyFont myfont;	

	std::list<Glyph> text__Great_Score;
	std::list<Glyph> text__Enter_Your_Initials;
	std::list<Glyph> text__input;

	static const sf::Vector2i Init_GPos__GS;
	static const sf::Vector2i Init_GPos__EYI;
	static const sf::Vector2i Init_GPos__I;

	sf::Vector2f nextpos__GreatScore;
	sf::Vector2f nextpos__Enter_Your_Initials;
	sf::Vector2f nextpos__input;

	int count;
	Player* curr_player;

	std::string name;
};


#endif _HighScore