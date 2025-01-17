#ifndef _TurnUpSwitchToLeft
#define _TurnUpSwitchToLeft

#include "MoveState.h"

struct OffsetArray;
class CentipedeHead;


class TurnUpSwitchToLeft : public MoveState
{
public:
	TurnUpSwitchToLeft();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
	virtual void Show() const override;
};

#endif _TurnUpSwitchToLeft