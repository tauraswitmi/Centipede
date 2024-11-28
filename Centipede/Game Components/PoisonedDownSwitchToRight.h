#ifndef _PoisonedDownSwitchToRight
#define _PoisonedDownSwitchToRight

#include "MoveState.h"

struct OffsetArray;
class CentipedeHead;


class PoisonedDownSwitchToRight : public MoveState
{
public:
	PoisonedDownSwitchToRight();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
	virtual void Show() const override;
};

#endif _PoisonedDownSwitchToRight