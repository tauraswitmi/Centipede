// GameControl
// Charles Tiemeyer, Nov 2024


// CONCRETE STRATEGY //

#ifndef _GameControl
#define _GameControl

#include "TEAL\CommonElements.h"
#include "MainControlBaseStrategy.h"


class GameControl : public MainControlBaseStrategy {
public:
	GameControl() = default;
	GameControl(const GameControl&) = delete;
	GameControl& operator=(const GameControl&) = delete;

	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey) override;

};

#endif _GameControl