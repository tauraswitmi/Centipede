#include <iostream>
#include "MoveState.h"
#include "CentipedeHead.h"
#include "MovementCollection.h"
#include "MushroomManager.h"
#include "TurnDownSwitchToRight.h"
#include "MoveFSM.h"
#include <assert.h>


// TurnDownSwitchToRight
TurnDownSwitchToRight::TurnDownSwitchToRight()
{
	std::cout << "Initializing TurnDownSwitchToRight state\n";

	MyMoveOffsets = &MovementCollection::OffsetsTurnDownEndRight;
}


void TurnDownSwitchToRight::Show() const
{
	ConsoleMsg::WriteLine("TurnDownSwitchToRight");
}


const MoveState* TurnDownSwitchToRight::GetNextState(CentipedeHead* chead) const
{
	const MoveState* pNextState;

	int row = chead->GetRow();
	int col = chead->GetColumn() + 1; // looking ahead after turn -> right

	MushroomManager* MushroomManager_Ref = chead->GetMushroomManager();
	MushroomManager::Obstacle obst = MushroomManager_Ref->Inspect(row, col);//MushroomManager::Inspect(row, col);



	if (obst == MushroomManager::Obstacle::Clear)
	{
		pNextState = &MoveFSM::StateMoveRightAndDownwards;
	}


	else if (obst == MushroomManager::Obstacle::Blocked) // Edge, shroom or letter?
	{
		if (row != MushroomManager::BOTTOM_ROW)
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