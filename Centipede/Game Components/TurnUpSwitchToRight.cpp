#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "TurnUpSwitchToRight.h"
#include "MoveFSM.h"
#include <assert.h>


// TurnUpSwitchToRight
TurnUpSwitchToRight::TurnUpSwitchToRight()
{
	std::cout << "Initializing TurnUpSwitchToRight state\n";

	MyMoveOffsets = &MovementCollection::OffsetsTurnUpEndRight;
}


void TurnUpSwitchToRight::Show() const
{
	ConsoleMsg::WriteLine("TurnUpSwitchToRight");
}


const MoveState* TurnUpSwitchToRight::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int row = chead->GetRow();
	int col = chead->GetColumn() + 1; // looking ahead after turn -> Right

	MushroomManager* MushroomManager_Ref = chead->GetMushroomManager();
	MushroomManager::Obstacle obst = MushroomManager_Ref->Inspect(row, col);//MushroomManager::Inspect(row, col);



	if (obst == MushroomManager::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveRightAndUpwards;
	}


	else if (obst == MushroomManager::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row != MushroomManager::TOP_PLAYER_ROW)
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