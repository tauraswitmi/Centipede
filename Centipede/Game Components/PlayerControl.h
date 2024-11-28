// PlayerControl
// Charles Tiemeyer, Sep 2024


// CONCRETE STRATEGY //

#ifndef _PlayerControl
#define _PlayerControl

#include "TEAL\CommonElements.h"
#include "ControlBaseStrategy.h"
#include "Blaster.h"


class PlayerControl : public ControlBaseStrategy {
public:
	PlayerControl() = default;
	PlayerControl(const PlayerControl&) = delete;
	PlayerControl& operator=(const PlayerControl&) = delete;

	PlayerControl(Blaster* ref);

	void ComputeNextMove() override;
};

#endif _PlayerControl