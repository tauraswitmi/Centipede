#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "PoisonedDownSwitchToLeft.h"
#include "MoveFSM.h"
#include <assert.h>


// PoisonedDownSwitchToLeft
PoisonedDownSwitchToLeft::PoisonedDownSwitchToLeft()
{
	std::cout << "Initializing PoisonedDownSwitchToLeft state\n";

	MyMoveOffsets = &MovementCollection::OffsetsTurnDownEndLeft;
}


void PoisonedDownSwitchToLeft::Show() const
{
	ConsoleMsg::WriteLine("PoisonedDownSwitchToLeft");
}


const MoveState* PoisonedDownSwitchToLeft::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int row = chead->GetRow();


	if (row != MushroomManager::BOTTOM_ROW)
		pNextState = &MoveFSM::StatePoisonedDownSwitchToRight;
	else
		pNextState = &MoveFSM::StateTurnUpSwitchToRight;


	return pNextState;
}