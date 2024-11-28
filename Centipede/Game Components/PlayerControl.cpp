// PlayerControl
// Charles Tiemeyer, Sep 2024


// CONCRETE STRATEGY //

#include "PlayerControl.h"
#include "BulletFactory.h"
#include "TEAL\CommonElements.h"
#include "AttractorMode.h"
#include "Blaster.h"

PlayerControl::PlayerControl(Blaster* ref)
	:ControlBaseStrategy(ref)
{

}


void PlayerControl::ComputeNextMove()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { reference->Right(); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { reference->Left(); }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { reference->Down(); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { reference->Up(); }


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { reference->Shoot(); }

}
