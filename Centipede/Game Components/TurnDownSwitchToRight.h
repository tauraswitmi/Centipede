#ifndef _TurnDownSwitchToRight
#define _TurnDownSwitchToRight

#include "MoveState.h"

struct OffsetArray;
class CentipedeHead;


class TurnDownSwitchToRight : public  MoveState
{
public:
	TurnDownSwitchToRight();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
	virtual void Show() const override;
};

#endif _TurnDownSwitchToRight