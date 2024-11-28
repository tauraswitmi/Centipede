#ifndef _MoveFSM
#define _MoveFSM


#include "MoveRightAndDownwards.h"
#include "MoveRightAndUpwards.h"
#include "MoveLeftAndDownwards.h"
#include "MoveLeftAndUpwards.h"
#include "TurnDownSwitchToLeft.h"
#include "TurnDownSwitchToRight.h"
#include "TurnUpSwitchToLeft.h"
#include "TurnUpSwitchToRight.h"
#include "PoisonedDownSwitchToLeft.h"
#include "PoisonedDownSwitchToRight.h"



class MoveFSM
{
private:

public:
	static const MoveRightAndDownwards StateMoveRightAndDownwards;
	static const MoveRightAndUpwards StateMoveRightAndUpwards;
	static const MoveLeftAndDownwards StateMoveLeftAndDownwards;
	static const MoveLeftAndUpwards StateMoveLeftAndUpwards;
	static const TurnDownSwitchToLeft StateTurnDownSwitchToLeft;
	static const TurnDownSwitchToRight StateTurnDownSwitchToRight;
	static const TurnUpSwitchToLeft StateTurnUpSwitchToLeft;
	static const TurnUpSwitchToRight StateTurnUpSwitchToRight;
	static const PoisonedDownSwitchToLeft StatePoisonedDownSwitchToLeft;
	static const PoisonedDownSwitchToRight StatePoisonedDownSwitchToRight;
};

#endif _MoveFSM