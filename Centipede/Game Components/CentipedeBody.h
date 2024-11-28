// CentipedeBody
// Charles Tiemeyer, Oct 2024

#ifndef _CentipedeBody
#define _CentipedeBody

#include "TEAL\CommonElements.h"

// Forward declarations
class Blaster;
class Bullet;
class MushroomManager;
class MoveState;
class CentipedeHead;

class CentipedeBody : public GameObject
{
public:
	CentipedeBody(const CentipedeBody&) = delete;
	CentipedeBody& operator=(const CentipedeBody&) = delete;
	~CentipedeBody() = default;

	CentipedeBody();

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void Collision(GameObject* other) {};
	virtual void Collision(Blaster* other);
	virtual void Collision(Bullet* other);


	const int GetColumn() { return Col; }
	const int GetRow() { return Row; }

	MushroomManager* GetMushroomManager() { return reference; } // Cheese because demo assumes MM is static
	CentipedeBody* GetPrevCentipede() { return prevCentipede; }
	CentipedeHead* GetHead() { return pHeader; }
	const MoveState* GetCurrentState() { return pCurrentState; }
	const MoveState* GetPrevState() { return pPrevState; }

	void SetHead(CentipedeHead* ch);
	void SetCurrentState(const MoveState* now);

	void Initialize(CentipedeHead* ch, int num, float speed);
	void Initialize(CentipedeBody* cb, int num, float speed);

	void TurnToHead(); // Turn this centipedebody into a head

	void Reset();
	void Explode();

	sf::Vector2f Pos;
	sf::Vector2f PosPrev;

	float SPEED;

private:

	const MoveState* pCurrentState;
	const MoveState* pPrevState;

	

	int Col;
	int Row;

	bool spawned;
	

	int centipedes;

	CentipedeBody* prevCentipede; 
	CentipedeBody* nextCentipede;
	CentipedeHead* pHeader;

	AnimatedSprite MainSprite;
	MushroomManager* reference;

};

#endif _CentipedeBody