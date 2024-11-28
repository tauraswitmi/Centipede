#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "MoveLeftAndUpwards.h"
#include "MoveFSM.h"
#include <assert.h>


// MoveLeftAndUpwards
MoveLeftAndUpwards::MoveLeftAndUpwards()
{
	std::cout << "Initializing MoveLeftAndUpwards state\n";

	MyMoveOffsets = &MovementCollection::OffsetsStraightLeft;
}


void MoveLeftAndUpwards::Show() const
{
	ConsoleMsg::WriteLine("MoveLeftAndUpwards");
}


const MoveState* MoveLeftAndUpwards::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int row = chead->GetRow();
	int col = chead->GetColumn() - 1; // looking ahead while left

	MushroomManager* MushroomManager_Ref = chead->GetMushroomManager();
	MushroomManager::Obstacle obst = MushroomManager_Ref->Inspect(row, col);//MushroomManager::Inspect(row, col);



	if (obst == MushroomManager::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveLeftAndUpwards;
	}


	else if (obst == MushroomManager::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row == MushroomManager::TOP_PLAYER_ROW)
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