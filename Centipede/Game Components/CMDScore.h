// CMDScore.h
// Charles Tiemeyer, Oct 2024

#ifndef _CMDScore
#define _CMDScore

class CMDScore
{
public:
	CMDScore() = default;
	CMDScore(const CMDScore&) = delete;
	CMDScore& operator=(const CMDScore&) = delete;
	virtual ~CMDScore() = default;

	// Note: the Excecute method must NOT have _any_ paramters
	virtual void Execute() = 0;
};


#endif _CMDScore