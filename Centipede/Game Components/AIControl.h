// AIControl
// Charles Tiemeyer, Nov 2024


// CONCRETE STRATEGY //

#ifndef _AIControl
#define _AIControl

#include "TEAL\CommonElements.h"
#include "ControlBaseStrategy.h"
#include "Blaster.h"


class AIControl : public ControlBaseStrategy {
public:
	AIControl() = default;
	AIControl(const AIControl&) = delete;
	AIControl& operator=(const AIControl&) = delete;

	AIControl(Blaster* ref);

	void ComputeNextMove() override;

	Blaster::AIMovement currentMove;
	int iterator;
	bool stopped;
};

#endif _AIControl