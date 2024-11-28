// AttractorControl
// Charles Tiemeyer, Nov 2024


// CONCRETE STRATEGY //

#ifndef _AttractorControl
#define _AttractorControl

#include "TEAL\CommonElements.h"
#include "MainControlBaseStrategy.h"


class AttractorControl : public MainControlBaseStrategy {
public:
	AttractorControl() = default;
	AttractorControl(const AttractorControl&) = delete;
	AttractorControl& operator=(const AttractorControl&) = delete;

	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey) override;
};

#endif _AttractorControl