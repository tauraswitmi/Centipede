// CentipedeHead
// Charles Tiemeyer, Sep 2024

#ifndef _CentipedeHead
#define _CentipedeHead

#include "TEAL\CommonElements.h"

// Forward declarations
class Blaster;
class Bullet;
class MushroomManager;
class MoveState;
class CentipedeBody;

class CentipedeHead : public GameObject
{
public:
	CentipedeHead(const CentipedeHead&) = delete;
	CentipedeHead& operator=(const CentipedeHead&) = delete;
	~CentipedeHead() = default;

	CentipedeHead();

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* other) {};
	virtual void Collision(Blaster* other);
	virtual void Collision(Bullet* other);

	const int GetColumn() { return Col; }
	const int GetRow() { return Row; }

	MushroomManager* GetMushroomManager() { return reference; }
	const MoveState* GetPrevState() { return pPrevState; }


	// Initializers
	// * Main @Spawn
	// * Head @Spawn
	// * Main @Separation
	// * Head @PZ Spawn

	void Initialize(MushroomManager* ref, int length, float speed, bool left);
	void Initialize(MushroomManager* ref, int length, float speed, bool left, int column);
	void Initialize(CentipedeBody* cb, int length, float speed);



	void AddPrevCentipede(CentipedeBody* prev);

	void Explode();
	void Reset();

	float SPEED;

private:

	const MoveState* pCurrentState;
	const MoveState* pPrevState;

	// 
	CentipedeBody* prevCentipede;

	int Col;
	int Row;

	bool spawned;

	int centipedes;


	sf::Vector2f Pos;
	sf::Vector2f PosPrev;

	AnimatedSprite MainSprite;

	MushroomManager* reference;
	

};

#endif _CentipedeHead