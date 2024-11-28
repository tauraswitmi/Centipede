// Mushroom.h
// Charles Tiemeyer, Sept 2024

#ifndef _Mushroom
#define _Mushroom

#include "TEAL\CommonElements.h"

class Bullet; // Note: Forward declare to avoid include-loop since Bullet.h includes Aseroids.h
class Spider;
class MushroomManager;
class CMDScore;

class Mushroom : public GameObject
{
public:
	Mushroom(const Mushroom&) = delete;
	Mushroom& operator=(const Mushroom&) = delete;
	~Mushroom() = default;

	// I will use "p" later to randomly spawn mushrooms //
	Mushroom();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* go) {};
	virtual void Collision(Bullet* other);
	virtual void Collision(Spider* other);

	void Initialize(sf::Vector2i p, MushroomManager* ref);
	void Reset();

	void UpdateHealth();
	void Regen();

	sf::Vector2i Get_GridPos() { return Pos_Grid; }


	// Moved here //
	AnimatedSprite MainSprite;
	bool Poisoned;
	bool Damaged;

private:
	
	sf::Vector2i Pos_Grid;
	int health;
	static const int MAXHEALTH = 4; // assign = 4 and change to static 9999

	

	MushroomManager* reference;
};

#endif _Mushroom