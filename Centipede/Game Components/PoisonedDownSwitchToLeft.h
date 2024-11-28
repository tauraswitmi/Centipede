#ifndef _PoisonedDownSwitchToLeft
#define _PoisonedDownSwitchToLeft

#include "MoveState.h"

struct OffsetArray;
class CentipedeHead;


class PoisonedDownSwitchToLeft : public MoveState
{
public:
	PoisonedDownSwitchToLeft();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
	virtual void Show() const override;
};

#endif _PoisonedDownSwitchToLeft