#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "MoveLeftAndDownwards.h"
#include "MoveFSM.h"
#include <assert.h>


// MoveLeftAndDownwards
MoveLeftAndDownwards::MoveLeftAndDownwards()
{
	std::cout << "Initializing MoveLeftAndDownwards state\n";

	MyMoveOffsets = &MovementCollection::OffsetsStraightLeft;
}


void MoveLeftAndDownwards::Show() const
{
	ConsoleMsg::WriteLine("MoveLeftAndDownwards"); 
}


const MoveState* MoveLeftAndDownwards::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int row = chead->GetRow();
	int col = chead->GetColumn() - 1; // looking ahead while left

	MushroomManager* MushroomManager_Ref = chead->GetMushroomManager();
	MushroomManager::Obstacle obst = MushroomManager_Ref->Inspect(row, col);//MushroomManager::Inspect(row, col);

	if (obst == MushroomManager::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveLeftAndDownwards;
	}


	else if (obst == MushroomManager::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row == MushroomManager::BOTTOM_ROW)
			pNextState = &MoveFSM::StateTurnUpSwitchToRight;
		else
			pNextState = &MoveFSM::StateTurnDownSwitchToRight;
	}


	else if (obst == MushroomManager::Obstacle::Poisoned)
	{
		pNextState = &MoveFSM::StatePoisonedDownSwitchToRight;
	}

	return pNextState;
}