// ScoreManager.h
// Charles Tiemeyer, Oct 2024


#include "ScoreManager.h"

#include <iostream>
#include "CMDScoreValue.h"
#include "CMDScoreByDistance.h"
#include "GameManager.h"
#include "Player.h"

#include "HighScoreEntry.h"

ScoreManager* ScoreManager::ptrInstance = nullptr;

std::list<HighScoreEntry> ScoreManager::HighScore_List =
{
	{"EJD", 16543},
	{"DFT", 15432},
	{"CAD", 14320},
	{"DCB", 13210},
	{"ED ", 13010},
	{"DEW", 12805},
	{"DFW", 12201},
	{"GJR", 2000}
};

int ScoreManager::GetBottomHighScore()
{
	return HighScore_List.back().score;
}

int ScoreManager::GetTopHighScore()
{
	return HighScore_List.front().score;
}


void ScoreManager::InsertHighScoreEntry(HighScoreEntry hs)
{
	// Delete the last entry

	std::list<HighScoreEntry>::iterator it;
	it = HighScore_List.begin();

	// Search the list until it's found a score lower than HS
	while ((it->score >= hs.score) && (it != HighScore_List.end()))
		it++;

	HighScore_List.insert(it, hs);

	HighScore_List.pop_back();
}



CMDScore* ScoreManager::GetScoreCommand(ScoreEvents ev)
{
	CMDScore* pCmd = nullptr;

	switch (ev)
	{

	case ScoreEvents::FleaKilled:
		pCmd = new CMDScoreValue(FleaDeath);
		break;

	case ScoreEvents::ScorpionKilled:
		pCmd = new CMDScoreValue(ScorpionDeath);
		break;

	case ScoreEvents::MushroomKilled:
		pCmd = new CMDScoreValue(MushroomDeath);
		break;

	case ScoreEvents::MushroomReset:
		pCmd = new CMDScoreValue(MushroomRestore);
		break;

	case ScoreEvents::CentipedeHeadKilled:
		pCmd = new CMDScoreValue(CentipedeHeadDeath);
		break;

	case ScoreEvents::CentipedeBodyKilled:
		pCmd = new CMDScoreValue(CentipedeBodyDeath);
		break;

	case ScoreEvents::SpiderKilled:
		pCmd = new CMDScoreByDistance(SpiderDistNear, SpiderDistMedium, SpiderDistFar,
			SpiderDeathNear, SpiderDeathMedium, SpiderDeathFar);
		break;

	default:
		break;
	}

	return pCmd;
}

void ScoreManager::AddScore(int val)
{

	GameManager::currentPlayer->AddScore(val);

}

void ScoreManager::SendScoreCMD(CMDScore* c)
{
	Instance().QueueCMDs.push(c);
}

void ScoreManager::ProcessScores()
{
	Instance().privProcessScore();
}

void ScoreManager::privProcessScore()
{
	printf("\n\tProcessing all scores commands for this frame:\n");

	CMDScore* c;

	while (!QueueCMDs.empty())
	{
		c = QueueCMDs.front();
		c->Execute();

		QueueCMDs.pop();
	}
}


void ScoreManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
