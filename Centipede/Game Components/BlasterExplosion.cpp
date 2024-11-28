// BlasterExplosion
// Charles Tiemeyer, September 2024

#include "BlasterExplosion.h"
#include "GameManager.h"

BlasterExplosion::BlasterExplosion( sf::Vector2f pos,  GameManager* Game_Ref)
{
	MainSprite = AnimatedSprite(  ResourceManager::GetTexture("Death"), 4, 2, 20); 
	MainSprite.SetAnimation(0, 7); 
	MainSprite.scale(2,2);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setPosition(pos);

	game_manager = Game_Ref;
}



void BlasterExplosion::Update()
{
	if ( MainSprite.IsLastAnimationFrame() )
	{
		MarkForDestroy();
	}

	MainSprite.Update();
}


void BlasterExplosion::Draw()
{
	WindowManager::Window().draw(MainSprite);
}

