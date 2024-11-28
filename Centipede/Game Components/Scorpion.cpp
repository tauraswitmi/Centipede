// Scorpion
// Charles Tiemeyer, Oct 2024

#include "Scorpion.h"
#include "ScorpionFactory.h"
#include "ScorpionSpawner.h"
#include "Bullet.h"
#include "Mushroom.h"
#include "MushroomManager.h"
#include "GameManager.h"
#include "Explosion.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "GameEntityManager.h"

Scorpion::Scorpion()
{

	SPEED = 200;

	// Get animated sprite
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Scorpion"), 4, 1, 8.0f); /// 999 update frame per sec
	MainSprite.SetAnimation(0, 3);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(2, 2);		// (16,16) -> (32,32)	
	MainSprite.setPosition(Pos);

	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Scorpion");
	SetCollider(MainSprite, bitmap, true);

	// Order relative to other objects
	SetDrawOrder(1000);

}



/*
	EVENT METHODS ==========
*/

void Scorpion::Destroy()
{
	DeregisterInput();
	ConsoleMsg::WriteLine("Scorpion Destroyed");
	DeregisterCollision<Scorpion>(*this);
}


void Scorpion::Update()
{

	if (moving_right)
	{
		Pos.x += SPEED * Game::FrameTime();
	}
	else
	{
		Pos.x -= SPEED * Game::FrameTime();
	}



	MainSprite.setPosition(Pos);
	MainSprite.Update();


	// Check if the Flea has reached the bottom of the screen
	if ((Pos.x > WindowManager::Window().getView().getSize().x) || (Pos.x < 0))
	{
		ScorpionSpawner::set_active_off();
		MarkForDestroy();
	}

}


void Scorpion::Collision(Bullet* other)
{
	SoundManager::SendSoundCMD(GameEntityManager::pKilled);
	ScoreManager::SendScoreCMD(ScorpionFactory::GetScore());
	Explode();
}

void Scorpion::Collision(Mushroom* other)
{
	other->Poisoned = true;

	other->MainSprite.SetAnimation(other->MainSprite.GetFrameCount(), other->MainSprite.GetFrameCount() * 2 - 1, false);
}


void Scorpion::Draw()
{
	WindowManager::Window().draw(MainSprite);
}



/*
	HELPER METHODS ==========
*/

void Scorpion::Explode()
{
	ScorpionSpawner::set_active_off();
	new Explosion(this->Pos);
	MarkForDestroy();
}

void Scorpion::Initialize(MushroomManager* ref, float speed)
{
	SPEED = speed;
	
	Row = rand() % MushroomManager::TOP_PLAYER_ROW;

	if (rand() % 2 == 0)
	{
		Col = 0;
		moving_right = true;
	}
	else
	{
		Col = MushroomManager::WIDTH - 1;
		moving_right = false;
	}


	Pos = sf::Vector2f(float(Col * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2), float(Row * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2));
	reference = ref;
	RegisterCollision<Scorpion>(*this);
}

