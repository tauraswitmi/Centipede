// Bullet
// Charles Tiemeyer, September 2024

#ifndef _Bullet
#define _Bullet

#include "TEAL\CommonElements.h"

//Forward declarations
class Mushroom;
class Blaster;
class Flea;
class CentipedeHead;
class CentipedeBody;
class Spider;
class Scorpion;

class Bullet : public GameObject
{
public:
	
	Bullet();
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;
	~Bullet() = default;

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision( GameObject *go){};
	virtual void Collision( Mushroom* other);
	virtual void Collision( Flea* other);
	virtual void Collision(Spider* other);
	virtual void Collision(Scorpion* other);
	virtual void Collision(CentipedeHead* other);
	virtual void Collision(CentipedeBody* other);

	sf::Vector2f getSpawn() { return Spawn; }

	void Initialize(sf::Vector2f pos);


private:
	float SPEED;

	sf::Vector2f Spawn;
	sf::Vector2f Pos;
	AnimatedSprite MainSprite;
	
};

#endif _Bullet