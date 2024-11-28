// Explosion
// Charles Tiemeyer, September 2024

#include "Explosion.h"

Explosion::Explosion(sf::Vector2f pos) : Pos(pos)
{
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Explosion"), 3, 2, 16);
	MainSprite.SetAnimation(0, 5);
	MainSprite.scale(4, 4); // For some reason sprite is only 8x8
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setPosition(Pos);
}



/*
	EVENT METHODS ==========
*/

void Explosion::Update()
{
	if (MainSprite.IsLastAnimationFrame())
		MarkForDestroy();

	//MainSprite.setPosition(Pos);
	MainSprite.Update();
}


void Explosion::Draw()
{
	WindowManager::Window().draw(MainSprite);
}



/*
	HELPER METHODS ==========
*/