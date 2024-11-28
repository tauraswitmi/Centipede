// Blaster
// Charles Tiemeyer, Sep 2024

#include "Flea.h"
#include "FleaFactory.h"
#include "FleaSpawner.h"
#include "Bullet.h"
#include "Mushroom.h"
#include "MushroomManager.h"
#include "Explosion.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "GameManager.h"

Flea::Flea()
{

	SPEED = 300;
	health = MAXHEALTH;

	// Get animated sprite
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Flea"), 2, 2, 8.0f); /// 999 update frame per sec
	MainSprite.SetAnimation(0, 3);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 4.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(2, 2);		// (16,16) -> (32,32)	
	MainSprite.setPosition(Pos);

	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Flea");
	SetCollider(MainSprite, bitmap, true);


	// Order relative to other objects
	SetDrawOrder(1000);


}



/*
	EVENT METHODS ==========
*/

void Flea::Destroy()
{
	DeregisterInput();
	ConsoleMsg::WriteLine("Flea Destroyed");
	DeregisterCollision<Flea>(*this);
}


void Flea::Update()
{
	Pos.y += SPEED * Game::FrameTime();



	// Only spawn mushrooms if the Flea has 2 health!!!
	if (health == 2) {

		int Row = (int)((Pos.y - (GameManager::BOX_SIZE / 2)) / GameManager::BOX_SIZE);

		// Checks every 32 pixels (or every row) *except for the last one
		if ((Row != Row_Prev) && (Row != 30) && (Row != 0))
		{
			Row_Prev = Row;

			// 25% chance of spawning mushroom
			if ((rand() % spawn_probability) == 0) { reference->AddMushroom(Col, Row); }
			
		}
	}


	MainSprite.setPosition(Pos);
	MainSprite.Update();  


	// Check if the Flea has reached the bottom of the screen
	if (Pos.y > WindowManager::Window().getView().getSize().y)
	{
		RespawnFlea();
		MarkForDestroy();
	}

}


void Flea::Collision(Blaster* other)
{
	MarkForDestroy();
}


void Flea::Collision(Bullet* other)
{
	if (health == MAXHEALTH)
	{
		health--;
		SPEED = 600;
	}
	else
	{
		ScoreManager::SendScoreCMD(FleaFactory::GetScore());
		Explode();
	}
}


void Flea::Draw()
{
	WindowManager::Window().draw(MainSprite);
}



/*
	HELPER METHODS ==========
*/

void Flea::RespawnFlea()
{
	FleaSpawner::set_active_off();
	FleaSpawner::SpawnFlea();
}


void Flea::Explode()
{
	RespawnFlea();
	new Explosion(this->Pos);
	SoundManager::SendSoundCMD(FleaFactory::GetKilled());
	MarkForDestroy();
}

void Flea::Initialize(MushroomManager* ref, float speed, int spawn_prob)
{
	Col = rand() % MushroomManager::WIDTH;
	Row_Prev = -1;
	Pos = sf::Vector2f(float(Col * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2), 0.0f);
	health = MAXHEALTH;
	reference = ref;


	SPEED = speed; 
	spawn_probability = spawn_prob;

	MainSprite.setPosition(Pos);
	MainSprite.Update();

	RegisterCollision<Flea>(*this);

	SoundManager::SendSoundCMD(FleaFactory::GetSound());
}
