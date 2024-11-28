#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "TurnDownSwitchToLeft.h"
#include "MoveFSM.h"
#include <assert.h>


// TurnDownSwitchToLeft
TurnDownSwitchToLeft::TurnDownSwitchToLeft()
{
	std::cout << "Initializing TurnDownSwitchToLeft state\n";

	MyMoveOffsets = &MovementCollection::OffsetsTurnDownEndLeft;
}


void TurnDownSwitchToLeft::Show() const
{
	ConsoleMsg::WriteLine("TurnDownSwitchToLeft");
}


const MoveState* TurnDownSwitchToLeft::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int row = chead->GetRow();
	int col = chead->GetColumn() - 1; // looking ahead after turn ->left

	MushroomManager* MushroomManager_Ref = chead->GetMushroomManager();
	MushroomManager::Obstacle obst = MushroomManager_Ref->Inspect(row, col);//MushroomManager::Inspect(row, col);



	if (obst == MushroomManager::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveLeftAndDownwards;
	}


	else if (obst == MushroomManager::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row != MushroomManager::BOTTOM_ROW)
			pNextState = &MoveFSM::StateTurnDownSwitchToRight;
		else
			pNextState = &MoveFSM::StateTurnUpSwitchToRight;
	}


	else if (obst == MushroomManager::Obstacle::Poisoned)
	{
		pNextState = &MoveFSM::StatePoisonedDownSwitchToRight;
	}

	return pNextState;
}