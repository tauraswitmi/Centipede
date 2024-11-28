// Blaster
// Charles Tiemeyer, Sep 2024

#ifndef _Blaster
#define _Blaster

#include "TEAL\CommonElements.h"

// Forward declarations
class Mushroom;
class Flea;
class CentipedeHead;
class CentipedeBody;
class BulletFactory;
class ControlBaseStrategy;
class PlayerControl;
class Spider;

class Blaster : public GameObject
{
public:
	Blaster();
	Blaster(const Blaster&) = delete;
	Blaster& operator=(const Blaster&) = delete;
	~Blaster() = default;

	enum AIMovement
	{
		Mov_RightUp,
		Mov_RightDown,
		Mov_LeftUp,
		Mov_LeftDown
	};

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* other) {};
	virtual void Collision(Mushroom* other);
	virtual void Collision(Flea* other);
	virtual void Collision(CentipedeHead* other);
	virtual void Collision(CentipedeBody* other);
	virtual void Collision(Spider* other);

	void SetStrategy(ControlBaseStrategy* strategy);
	void Explode();
	void Initialize(int gm);
	
	

	void Up();
	void Down();
	void Left();
	void Right();

	void Shoot();

	AIMovement CheckBorder(AIMovement curr_mov);
	void CheckMove(AIMovement curr_mov);

	sf::Vector2f get_Pos() { return Pos; };

	static float PZB_LEFT;
	static float PZB_RIGHT;
	static float PZB_UP;
	static float PZB_DOWN;


private:
	
	float SPEED;
	float offset;

	sf::Vector2f GunOffset;
	sf::Vector2f Pos;
	sf::Vector2f Pos_Prev;
	sf::Vector2f Impulse;

	AnimatedSprite MainSprite;

	sf::Sound FireSnd;


	ControlBaseStrategy* Controller;
	
};

#endif _Blaster