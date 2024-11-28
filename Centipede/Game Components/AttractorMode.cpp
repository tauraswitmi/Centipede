// AttractorMode
// Charles Tiemeyer, November 2024

#include "TEAL\CommonElements.h"

#include "AttractorMode.h"
#include "Blaster.h"
#include "Mushroom.h"
#include "MushroomManager.h"
#include "Flea.h"
#include "Scorpion.h"
#include "CentipedeHead.h"
#include "CentipedeBody.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "GameManager.h"
#include "Spider.h"

void AttractorMode::Initialize()
{
	WindowManager::SetBackgroundColor(sf::Color(0, 0, 0, 255));

	GameManager::Initialize();

	CollisionTestPair<Blaster, Spider>();
	CollisionTestPair<Mushroom, Spider>();
	CollisionTestPair<Bullet, Spider>();

	CollisionTestPair<Mushroom, Scorpion>();
	CollisionTestPair<Bullet, Scorpion>();

	CollisionTestPair<Bullet, CentipedeBody>();
	CollisionTestPair<Blaster, CentipedeBody>();
	CollisionTestPair<Bullet, CentipedeHead>();
	CollisionTestPair<Blaster, CentipedeHead>();

	CollisionTestPair<Bullet, Flea>();
	CollisionTestPair<Blaster, Flea>();

	CollisionTestPair<Bullet, Mushroom>();
	CollisionTestPair<Blaster, Mushroom>();

};

void AttractorMode::Terminate()
{
	GameManager::Terminate();
}
