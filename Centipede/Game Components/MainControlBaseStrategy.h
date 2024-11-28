// MainControlBaseStrategy
// Charles Tiemeyer, Nov 2024


// STRATEGY INTERFACE //

#ifndef _MainControlBaseStrategy
#define _MainControlBaseStrategy

#include "TEAL\CommonElements.h"

class MainControlBaseStrategy : GameObject {
public:
	MainControlBaseStrategy() { RegisterInput(InputFlags::KeyPressed); };
	MainControlBaseStrategy(const MainControlBaseStrategy&) = delete;
	MainControlBaseStrategy& operator=(const MainControlBaseStrategy&) = delete;
	virtual ~MainControlBaseStrategy() = default;

	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey) = 0;

};

#endif _MainControlBaseStrategy