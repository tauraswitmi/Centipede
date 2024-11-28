#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "MoveRightAndUpwards.h"
#include "MoveFSM.h"
#include <assert.h>


// MoveRightAndUpwards
MoveRightAndUpwards::MoveRightAndUpwards()
{
	std::cout << "Initializing MoveRightAndUpwards state\n";

	MyMoveOffsets = &MovementCollection::OffsetsStraightRight;
}


void MoveRightAndUpwards::Show() const
{
	ConsoleMsg::WriteLine("MoveRightAndUpwards");
}


const MoveState* MoveRightAndUpwards::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int row = chead->GetRow();
	int col = chead->GetColumn() + 1; // looking ahead while right

	MushroomManager* MushroomManager_Ref = chead->GetMushroomManager();
	MushroomManager::Obstacle obst = MushroomManager_Ref->Inspect(row, col);//MushroomManager::Inspect(row, col);



	if (obst == MushroomManager::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveRightAndUpwards;
	}


	else if (obst == MushroomManager::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row == MushroomManager::TOP_PLAYER_ROW)
			pNextState = &MoveFSM::StateTurnDownSwitchToLeft;
		else
			pNextState = &MoveFSM::StateTurnUpSwitchToLeft;
	}


	else if (obst == MushroomManager::Obstacle::Poisoned)
	{
		pNextState = &MoveFSM::StatePoisonedDownSwitchToLeft;
	}

	return pNextState;
}