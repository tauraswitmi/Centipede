#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "MoveFSM.h"
#include <assert.h>

// Set up all the unique copies of states
const MoveRightAndDownwards MoveFSM::StateMoveRightAndDownwards;
const MoveRightAndUpwards MoveFSM::StateMoveRightAndUpwards;
const MoveLeftAndDownwards MoveFSM::StateMoveLeftAndDownwards;
const MoveLeftAndUpwards MoveFSM::StateMoveLeftAndUpwards;
const TurnDownSwitchToLeft MoveFSM::StateTurnDownSwitchToLeft;
const TurnDownSwitchToRight MoveFSM::StateTurnDownSwitchToRight;
const TurnUpSwitchToLeft MoveFSM::StateTurnUpSwitchToLeft;
const TurnUpSwitchToRight MoveFSM::StateTurnUpSwitchToRight;
const PoisonedDownSwitchToLeft MoveFSM::StatePoisonedDownSwitchToLeft;
const PoisonedDownSwitchToRight MoveFSM::StatePoisonedDownSwitchToRight;