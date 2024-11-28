//// GridObject.h
//// Charles Tiemeyer, November 2024
//
//#ifndef _GridObject
//#define _GridObject
//
//#include "TEAL\CommonElements.h"
//
//class Bullet; // Note: Forward declare to avoid include-loop since Bullet.h includes Aseroids.h
//class Spider;
//class MushroomManager;
//class CMDScore;
//
//class GridObject : public GameObject
//{
//public:
//	GridObject(const GridObject&) = delete;
//	GridObject& operator=(const GridObject&) = delete;
//	~GridObject() = default;
//	GridObject();
//
//
//
//	virtual void Draw();
//
//
//
//	virtual void Destroy();
//
//	virtual void Collision(GameObject* go) {};
//	virtual void Collision(Bullet* other);
//	virtual void Collision(Spider* other);
//
//	void Initialize(sf::Vector2i p, MushroomManager* ref);
//	void Reset();
//
//	void UpdateHealth();
//	void Regen();
//
//	sf::Vector2i Get_GridPos() { return Pos_Grid; }
//
//
//	// Moved here //
//	AnimatedSprite MainSprite;
//	bool Poisoned;
//	bool Damaged;
//
//private:
//
//	sf::Vector2i Pos_Grid;
//	int health;
//	static const int MAXHEALTH = 4; // assign = 4 and change to static 9999
//
//
//
//	MushroomManager* reference;
//};
//
//#endif _GridObject