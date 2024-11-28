#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "PoisonedDownSwitchToRight.h"
#include "MoveFSM.h"
#include <assert.h>


// PoisonedDownSwitchToRight
PoisonedDownSwitchToRight::PoisonedDownSwitchToRight()
{
	std::cout << "Initializing PoisonedDownSwitchToRight state\n";

	MyMoveOffsets = &MovementCollection::OffsetsTurnDownEndLeft;
}


void PoisonedDownSwitchToRight::Show() const
{
	ConsoleMsg::WriteLine("PoisonedDownSwitchToRight");
}


const MoveState* PoisonedDownSwitchToRight::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int row = chead->GetRow();


	if (row != MushroomManager::BOTTOM_ROW)
		pNextState = &MoveFSM::StatePoisonedDownSwitchToLeft;
	else
		pNextState = &MoveFSM::StateTurnUpSwitchToLeft;


	return pNextState;
}