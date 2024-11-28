// AttractorControl
// Charles Tiemeyer, Nov 2024


// CONCRETE STRATEGY //

#include "AttractorControl.h"
#include "GameManager.h"



void AttractorControl::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{

	// Mute the Game
	if (k == sf::Keyboard::Num1)
	{
		GameManager::ChangeGameMode(1);
	}
	else if (k == sf::Keyboard::Num2)
	{
		GameManager::ChangeGameMode(2);
	}
}