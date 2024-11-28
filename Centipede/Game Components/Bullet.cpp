// Bullet
// Charles Tiemeyer, September 2024

#include "Bullet.h"
#include "BulletFactory.h"
#include "Blaster.h"
#include "Flea.h"
#include "Scorpion.h"
#include "Spider.h"
#include "CentipedeHead.h"
#include "CentipedeBody.h"
#include "SoundManager.h"
	
Bullet::Bullet()
{

	SPEED = 800;

	// Get animated sprite // Might change to sf:Sprite 9999
	MainSprite = AnimatedSprite(  ResourceManager::GetTexture("Bullet"), 1, 1);
	MainSprite.SetAnimation(0, 0, false);


	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(2, 2);

	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Bullet");
	SetCollider(MainSprite, bitmap);

	
}



/*
	EVENT METHODS ==========
*/

void Bullet::Update()
{
	Pos.y -= Game::FrameTime() * SPEED;

	if (Pos.y < 0 /* WindowManager::Window().getSize().x */) MarkForDestroy();

	MainSprite.setPosition(Pos);
	MainSprite.Update();
}


void Bullet::Draw()
{
	WindowManager::Window().draw(MainSprite);
}


void Bullet::Destroy()
{
	//ConsoleMsg::WriteLine("Bullet Destroyed");
	DeregisterCollision<Bullet>( *this );
}


void Bullet::Collision(Mushroom* other)
{
	MarkForDestroy();
}


void Bullet::Collision(Flea* other)
{
	MarkForDestroy();
}

void Bullet::Collision(Spider* other)
{
	MarkForDestroy();
}

void Bullet::Collision(Scorpion* other)
{
	MarkForDestroy();
}

void Bullet::Collision(CentipedeHead* other)
{
	MarkForDestroy();
}

void Bullet::Collision(CentipedeBody* other)
{
	MarkForDestroy();
}


/*
	HELPER METHODS ===============================
*/

void Bullet::Initialize(sf::Vector2f p)
{
	Spawn = p;
	Pos = p;
	RegisterCollision<Bullet>(*this);

	SoundManager::SendSoundCMD(BulletFactory::GetSound());
}