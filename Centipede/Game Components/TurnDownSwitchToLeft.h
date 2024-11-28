#ifndef _TurnDownSwitchToLeft
#define _TurnDownSwitchToLeft

#include "MoveState.h"

struct OffsetArray;
class CentipedeHead;


class TurnDownSwitchToLeft : public MoveState
{
public:
	TurnDownSwitchToLeft();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
	virtual void Show() const override;
};

#endif _TurnDownSwitchToLeft