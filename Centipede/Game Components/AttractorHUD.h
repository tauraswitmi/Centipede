// AttractorHUD
// Charles Tiemeyer, November 2024

#ifndef _AttractorHUD
#define _AttractorHUD

#include "TEAL/CommonElements.h"
#include <list>
#include "CrazyFont.h"
#include "MushroomManager.h"

class Player;

class AttractorHUD : public GameObject
{
public:
	AttractorHUD(Player* ai);
	virtual void Draw();

	static bool CheckPosition(sf::Vector2i);

private:
	
	CrazyFont myfont;	

	std::list<Glyph> text__High_Scores_Text;
	std::list<Glyph> text__High_Scores;
	std::list<Glyph> text__Bonus_Every;

	sf::Vector2f nextpos;

	static std::list<sf::Vector2i> positions;

	static const int Init_Row__HST = 2;
	static const int Init_Row__BE = 14;

	

	static const int MIDDLE = (MushroomManager::WIDTH / 2) ; // When calculating POS its (0 - 29) so it would have to be -1
};


#endif _AttractorHUD