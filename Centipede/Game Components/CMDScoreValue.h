// CMDScoreValue.h
// Charles Tiemeyer, Oct 2024

#ifndef _CMDScoreValue
#define _CMDScoreValue

#include "CMDScore.h"

class CMDScoreValue : public CMDScore
{
protected:
	int points;	// points to add

public:
	CMDScoreValue() = delete;
	CMDScoreValue(const CMDScoreValue&) = delete;
	CMDScoreValue& operator=(const CMDScoreValue&) = delete;
	virtual ~CMDScoreValue() = default;

	CMDScoreValue(int val);

	virtual void Execute() override;

};

#endif _CMDScoreValue