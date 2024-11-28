#ifndef _MoveLeftAndUpwards
#define _MoveLeftAndUpwards

#include "MoveState.h"

struct OffsetArray;
class CentipedeHead;


class MoveLeftAndUpwards : public  MoveState
{
public:
	MoveLeftAndUpwards();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
	virtual void Show() const override;
};

#endif _MoveLeftAndUpwards