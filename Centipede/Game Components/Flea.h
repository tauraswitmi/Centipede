// Blaster
// Charles Tiemeyer, Sep 2024

#ifndef _Flea
#define _Flea

#include "TEAL\CommonElements.h"

// Forward declarations
class Blaster;
class Bullet;
class MushroomManager;

class Flea : public GameObject
{
public:
	Flea(const Flea&) = delete;
	Flea& operator=(const Flea&) = delete;
	~Flea() = default;

	Flea();

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* other) {};
	virtual void Collision(Blaster* other);
	virtual void Collision(Bullet* other);

	void Explode();
	void Initialize(MushroomManager* ref, float speed, int spawn_prob);
	void RespawnFlea();

	float SPEED;

private:

	int spawn_probability;

	int Col;
	int Row_Prev;

	sf::Vector2f Pos;

	AnimatedSprite MainSprite;

	sf::Sound MoveSnd;

	int health;
	static const int MAXHEALTH = 2;

	MushroomManager* reference;

};

#endif _Flea