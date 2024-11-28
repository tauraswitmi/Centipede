#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "TurnUpSwitchToLeft.h"
#include "MoveFSM.h"
#include <assert.h>

// TurnUpSwitchToLeft
TurnUpSwitchToLeft::TurnUpSwitchToLeft()
{
	std::cout << "Initializing TurnUpSwitchToLeft state\n";

	MyMoveOffsets = &MovementCollection::OffsetsTurnUpEndLeft;
}


void TurnUpSwitchToLeft::Show() const
{
	ConsoleMsg::WriteLine("TurnUpSwitchToLeft");
}


const MoveState* TurnUpSwitchToLeft::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int row = chead->GetRow();
	int col = chead->GetColumn() - 1; // looking ahead after turn -> left

	MushroomManager* MushroomManager_Ref = chead->GetMushroomManager();
	MushroomManager::Obstacle obst = MushroomManager_Ref->Inspect(row, col);//MushroomManager::Inspect(row, col);



	if (obst == MushroomManager::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveLeftAndUpwards;
	}


	else if (obst == MushroomManager::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row != MushroomManager::TOP_PLAYER_ROW)
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