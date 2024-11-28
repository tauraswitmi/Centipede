// Explosion.h
// Charles Tiemeyer, September 2024

#ifndef _Explosion
#define _Explosion

#include "TEAL\CommonElements.h"

class Explosion : public GameObject
{
public:
	Explosion(sf::Vector2f pos);
	Explosion() = delete;
	Explosion(const Explosion&) = delete;
	Explosion& operator=(const Explosion&) = delete;
	~Explosion() = default;

	virtual void Update();
	virtual void Draw();

private:
	AnimatedSprite MainSprite;
	sf::Vector2f Pos;
};


#endif _Explosion