#ifndef _TurnUpSwitchToRight
#define _TurnUpSwitchToRight

#include "MoveState.h"

struct OffsetArray;
class CentipedeHead;


class TurnUpSwitchToRight : public  MoveState
{
public:
	TurnUpSwitchToRight();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
	virtual void Show() const override;
};

#endif _TurnUpSwitchToRight