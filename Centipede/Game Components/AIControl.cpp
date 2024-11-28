// AIControl
// Charles Tiemeyer, Nov 2024


// CONCRETE STRATEGY //

#include "AIControl.h"
#include "BulletFactory.h"
#include "GameManager.h"
#include "Blaster.h"


AIControl::AIControl(Blaster* ref)
	:ControlBaseStrategy(ref)
{
	currentMove = Blaster::AIMovement::Mov_RightUp;
	iterator = 0;
	stopped = false;
}

void AIControl::ComputeNextMove()
{

	reference->Shoot();

	if (!stopped)
	{
		reference->CheckMove(currentMove);
		currentMove = reference->CheckBorder(currentMove);
	}

	iterator++;

	if (iterator > 120)
	{
		if (stopped)
		{
			stopped = false;
		}
		else
		{
			stopped = true;
		}
		iterator = 0;
	}

}
