// CMDScoreValue.h
// Charles Tiemeyer, Oct 2024

#include "CMDScoreValue.h"
#include <iostream>
#include "ScoreManager.h"

CMDScoreValue::CMDScoreValue(int val)
	: points(val)
{
	//printf("Score Command created: Points = %i\n", val);
}

void CMDScoreValue::Execute()
{
	ScoreManager::AddScore(points);
}