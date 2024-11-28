// Scorpion
// Charles Tiemeyer, Oct 2024

#ifndef _Scorpion
#define _Scorpion

#include "TEAL\CommonElements.h"

// Forward declarations
class Bullet;
class MushroomManager;
class Mushroom;

class Scorpion : public GameObject
{
public:
	Scorpion(const Scorpion&) = delete;
	Scorpion& operator=(const Scorpion&) = delete;
	~Scorpion() = default;

	Scorpion();

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* other) {};
	virtual void Collision(Bullet* other);
	virtual void Collision(Mushroom* other);

	void Explode();
	void Initialize(MushroomManager* ref, float speed);

	float SPEED;

private:
	bool moving_right; // temporary 999
	int Col;
	int Row;

	sf::Vector2f Pos;
	sf::Vector2f Pos_Prev;

	AnimatedSprite MainSprite;
	MushroomManager* reference;

};

#endif _Scorpion