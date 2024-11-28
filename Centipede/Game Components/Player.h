// Player
// Charles Tiemeyer, Oct 2024

#ifndef _Player
#define _Player

#include "MushroomManager.h"
#include "TEAL\CommonElements.h"

class Player : public GameObject
{
public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	~Player() = default;

	Player(int player_no);

	virtual void Update();
	virtual void Destroy();

	void Reset();
	void AddScore(int val);
	void GameEnd();
	void LevelUp();
	void OneUp();

	int GetScore() { return Score; };
	int GetLives() { return Lives; };
	int GetCurrentLevel() { return CurrentLevel; };
	int GetPlayerNumber() { return PlayerNumber; };

	void SetCurrentLevel(int curr) { CurrentLevel = curr; };

	void LifeLose() { Lives--; }
	void LifeGain() { Lives++; }

	void RegenerateMushrooms();
	void LevelUpAlarm();

	virtual void Alarm0();
	virtual void Alarm1();


	MushroomManager* get_MushroomManager() 
	{ 
		return mushroom_manager; 
	};

	const static int MAX_LIVES = 6;
	const static int INIT_LIVES = 3;
	const static int ONE_UP_POINTS = 12000;

private:
	int Score;
	int Lives;
	int CurrentLevel;

	int Score_NextOneUp;

	int PlayerNumber; // 0 (AI), 1 (P1), 2 (P2)

	MushroomManager* mushroom_manager;


};

#endif _Player