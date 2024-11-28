// CMDScoreByDistance.h
// Charles Tiemeyer, Oct 2024

#include "CMDScoreByDistance.h"
#include <iostream>
#include "ScoreManager.h"
#include "SpiderFactory.h"

CMDScoreByDistance::CMDScoreByDistance(int dn, int dm, int df,
	int vn, int vm, int vf)
	: dNear(dn), dMed(dm), dFar(df), vNear(vn), vMed(vm), vFar(vf)
{
	//printf("Score by distance command created\n");
	//printf("\tdist <= %i  is worth %i points\n", dNear, vNear);
	//printf("\tdist <= %i  is worth %i points\n", dMed, vMed);
	//printf("\tdist <= %i  is worth %i points\n", dFar, vFar);
}

void CMDScoreByDistance::Execute()
{

	// Realistically: this cmd also gets the position of the player and spider on death to compute the distance
	// This data is passed to the command before sending it to the broker.


	// processing distance to score:
	if (SpiderFactory::distance <= dNear)
	{
		ScoreManager::AddScore(vNear);
	}
	else if (SpiderFactory::distance <= dMed)
	{
		ScoreManager::AddScore(vMed);
	}
	else
	{
		ScoreManager::AddScore(vFar);
	}
}