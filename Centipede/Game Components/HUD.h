// HUD
// Charles Tiemeyer, November 2024

#ifndef _HUD
#define _HUD

#include "TEAL/CommonElements.h"
#include <list>
#include "CrazyFont.h"

class Player;

class HUD : public GameObject
{
public:
	HUD(int gm);
	virtual void Draw();

	void UpdateText(Player* player);
	

private:
	
	void priv_UpdatePlayer1Side(int score);
	void priv_UpdatePlayer2Side(int score);
	void priv_UpdateHighScore();
	
	CrazyFont myfont;	

	static std::list<Glyph> text__player1;
	static std::list<Glyph> text__player2;
	static std::list<Glyph> text__highscore;

	std::string text;
	sf::Vector2f nextpos;
	int digits;

	static int prev_GameMode;
	static int curr_GameMode;

	static int MAX_ScoreDigits;
	static int MAX_StartingZeros;

	const static int MIDDLE = 18; // 5 30 - 17 or -18
};


#endif _HUD