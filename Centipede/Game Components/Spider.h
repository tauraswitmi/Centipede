// Spider
// Charles Tiemeyer, Oct 2024

#ifndef _Spider
#define _Spider

#include "TEAL\CommonElements.h"

// Forward declarations
class Bullet;
class Blaster;
class Mushroom;

class Spider : public GameObject
{
public:
	Spider(const Spider&) = delete;
	Spider& operator=(const Spider&) = delete;
	~Spider() = default;

	Spider();

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* other) {};
	virtual void Collision(Bullet* other);
	virtual void Collision(Blaster* other);

	void Explode();
	void Initialize(float speed);
	

	// Movement
	void Move__Up();
	void Move__Down();
	void Move__Up_Right();
	void Move__Up_Left();
	void Move__Down_Right();
	void Move__Down_Left();
	void Change__Up();
	void Change__Down();
	void Change_Movement();

	// Active calls
	void Pause();


	float SPEED;


private:

	enum Spider_Movement
	{
		Moving__Up,
		Moving__Up_Right,
		Moving__Up_Left,
		Moving__Down,
		Moving__Down_Right,
		Moving__Down_Left
	};

	Spider_Movement currentMove;

	// Counts number of frames
	int frameCounter;

	// Makes a change to the spider based on the number of frames
	int MAX_FramesPerChange;


	/*
		So essentially, the amount of movement the spider makes per
		"interval" is (MAX_FramesPerChange x SPEED)
	*/


	// Direction
	bool Left;		// If true, LEFT, if false, RIGHT


	sf::Vector2f Pos;
	sf::Vector2f Pos_Prev;

	AnimatedSprite MainSprite;

};

#endif _Spider