#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "MoveRightAndDownwards.h"
#include "MoveFSM.h"
#include <assert.h>


// MoveRightAndDownwards *
MoveRightAndDownwards::MoveRightAndDownwards()
{
	std::cout << "Initializing MoveRightAndDownwards state\n";

	MyMoveOffsets = &MovementCollection::OffsetsStraightRight;
}


void MoveRightAndDownwards::Show() const
{
	ConsoleMsg::WriteLine("MoveRightAndDownwards");
}


const MoveState* MoveRightAndDownwards::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int row = chead->GetRow();
	int col = chead->GetColumn() + 1; // looking ahead while right

	MushroomManager* MushroomManager_Ref = chead->GetMushroomManager();
	MushroomManager::Obstacle obst = MushroomManager_Ref->Inspect(row, col);//MushroomManager::Inspect(row, col);



	if (obst == MushroomManager::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveRightAndDownwards;
	}


	else if (obst == MushroomManager::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row == MushroomManager::BOTTOM_ROW)
			pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
		else
			pNextState = &MoveFSM::StateTurnDownSwitchToLeft;
	}


	else if (obst == MushroomManager::Obstacle::Poisoned)
	{
		pNextState = &MoveFSM::StatePoisonedDownSwitchToLeft;
	}

	return pNextState;
}