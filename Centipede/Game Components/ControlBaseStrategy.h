// ControlBaseStrategy
// Charles Tiemeyer, Sep 2024


// STRATEGY INTERFACE //

#ifndef _ControlBaseStrategy
#define _ControlBaseStrategy

#include "TEAL\CommonElements.h"
#include "Blaster.h"

class ControlBaseStrategy {
public:
	ControlBaseStrategy() = default;
	ControlBaseStrategy(const ControlBaseStrategy&) = delete;
	ControlBaseStrategy& operator=(const ControlBaseStrategy&) = delete;
	virtual ~ControlBaseStrategy() = default;

	ControlBaseStrategy(Blaster* ref) { reference = ref; };

	Blaster* reference;

	virtual void ComputeNextMove() = 0;
};

#endif _ControlBaseStrategy