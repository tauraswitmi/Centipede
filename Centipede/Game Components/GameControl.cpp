// GameControl
// Charles Tiemeyer, Nov 2024


// CONCRETE STRATEGY //

#include "GameControl.h"
#include "SoundManager.h"


void GameControl::KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey)
{

	// Mute the Game
	if (k == sf::Keyboard::M)
	{
		if (SoundManager::GetMuteStatus())
		{
			SoundManager::UnMute();
		}
		else
		{
			SoundManager::Mute();
		}
	}
}