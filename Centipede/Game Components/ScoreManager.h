// ScoreManager.h
// Charles Tiemeyer, Oct 2024

#ifndef _ScoreManager
#define _ScoreManager

#include <queue>
#include "HighScoreEntry.h"

class CMDScore;
class Player;

class ScoreManager
{
private:
	// Score values;
	static const int FleaDeath = 200;
	static const int ScorpionDeath = 1000;

	static const int CentipedeHeadDeath = 100;
	static const int CentipedeBodyDeath = 10;

	static const int MushroomDeath = 1;
	static const int MushroomRestore = 5;

	static const int SpiderDeathFar = 300;
	static const int SpiderDistFar = 9999;

	static const int SpiderDeathMedium = 600;
	static const int SpiderDistMedium = 160;

	static const int SpiderDeathNear = 900;
	static const int SpiderDistNear = 64;

	std::queue<CMDScore*> QueueCMDs;
	static std::list<HighScoreEntry> HighScore_List;

	static ScoreManager* ptrInstance;

	ScoreManager() = default;
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;
	virtual ~ScoreManager() = default;

	static ScoreManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new ScoreManager;
		return *ptrInstance;
	};

	void privProcessScore();
	

public:

	// events
	enum class ScoreEvents { FleaKilled, ScorpionKilled, MushroomKilled, MushroomReset, CentipedeHeadKilled, CentipedeBodyKilled, SpiderKilled };

	static void AddScore(int val);

	static int GetSpiderScore(float distance);

	static CMDScore* GetScoreCommand(ScoreEvents ev);
	static int GetBottomHighScore();
	static int GetTopHighScore();

	static std::list<HighScoreEntry> GetHighScores() { return HighScore_List; };

	static void InsertHighScoreEntry(HighScoreEntry hs);

	static void SendScoreCMD(CMDScore* c);
	static void ProcessScores();

	static void Terminate();


};

#endif _ScoreManager