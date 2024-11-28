// CMDScoreByDistance.h
// Charles Tiemeyer, Oct 2024

#ifndef _CMDScoreByDistance
#define _CMDScoreByDistance

#include "CMDScore.h"

class CMDScoreByDistance : public CMDScore
{
private:
	int dNear;
	int dMed;
	int dFar;
	int vNear;
	int vMed;
	int vFar;


public:
	CMDScoreByDistance() = delete;
	CMDScoreByDistance(const CMDScoreByDistance&) = delete;
	CMDScoreByDistance& operator=(const CMDScoreByDistance&) = delete;
	virtual ~CMDScoreByDistance() = default;

	CMDScoreByDistance(int dNear, int dMed, int dFar,
		int vNear, int vMed, int vFar);

	virtual void Execute() override;

};

#endif _CMDScoreByDistance