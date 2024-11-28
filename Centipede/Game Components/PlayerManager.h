// PlayerManager
// Charles Tiemeyer, Oct 2024

#ifndef _PlayerManager
#define _PlayerManager

#include "TEAL\CommonElements.h"
#include <queue>

// Forward Declarations
class Player;
class CMDSound;

class PlayerManager
{
private:

	Player* Player_1;
	Player* Player_2;

	Player* Player_Current;

	void priv_Switch_Player1();
	void priv_Switch_Player2();
	void priv_Switch_AI();


	// To be saved between Scenes
	static std::queue<sf::Vector2i> mushroom_positions;
	static int wave_number;

	static int prevScoreP1;
	static int prevScoreP2;

	static PlayerManager* ptrInstance;

	static PlayerManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new PlayerManager;
		return *ptrInstance;
	};

public:

	static CMDSound* pSound_MushRegen;
	static CMDSound* pSound_OneUp;

	static void Initialize(int gm);

	static Player* SwitchPlayer__FromAI();
	static Player* SwitchPlayer__1P();
	static Player* SwitchPlayer__2P();

	static Player* getPlayer1() { return Instance().Player_1; };
	static Player* getPlayer2() { return Instance().Player_2; };
	static int getP1ScorePrev() { return prevScoreP1; };
	static int getP2ScorePrev() { return prevScoreP2; };

	static void setPlayer1Prev(int score) { prevScoreP1 = score; };
	static void setPlayer2Prev(int score) { prevScoreP2 = score; };

	
	static Player* GetCurrent() { return Instance().Player_Current; };

	static void Terminate();



};

#endif _PlayerManager