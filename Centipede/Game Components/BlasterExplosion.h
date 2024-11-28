// BlasterExplosion
// Charles Tiemeyer, September 2024

#ifndef _BlasterExplosion
#define _BlasterExplosion

#include "TEAL\CommonElements.h"

class GameManager;

class BlasterExplosion : public GameObject
{
public:
	BlasterExplosion( sf::Vector2f pos, GameManager* Game_Ref);
	BlasterExplosion(const BlasterExplosion&) = delete;
	BlasterExplosion& operator=(const BlasterExplosion&) = delete;
	~BlasterExplosion() = default;

	virtual void Update();
	virtual void Draw();

private:
	AnimatedSprite MainSprite;
	GameManager* game_manager;
};


#endif _BlasterExplosion