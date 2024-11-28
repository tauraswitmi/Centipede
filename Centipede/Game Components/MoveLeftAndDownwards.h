#ifndef _MoveLeftAndDownwards
#define _MoveLeftAndDownwards


#include "MoveState.h"

struct OffsetArray;
class CentipedeHead;


class MoveLeftAndDownwards : public  MoveState
{
public:
	MoveLeftAndDownwards();
	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
	virtual void Show() const override;
};

#endif _MoveLeftAndDownwards