// Spider
// Charles Tiemeyer, Oct 2024

#include "Spider.h"
#include "SpiderFactory.h"
#include "SpiderSpawner.h"
#include "Bullet.h"
#include "Blaster.h"
#include "Mushroom.h"

#include "MushroomManager.h"
#include "GameEntityManager.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"

#include "Explosion.h"
#include "CMDScore.h"
#include "CMDSound.h"

#include <math.h>


Spider::Spider()
{

	SPEED = 8;

	// Get animated sprite
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Spider"), 4, 2, 8.0f); 
	MainSprite.SetAnimation(0, 3);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(4, 4);	
	MainSprite.setPosition(Pos);

	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Spider");
	SetCollider(MainSprite, bitmap, true);

	// Order relative to other objects
	SetDrawOrder(1000);

}



void Spider::Destroy()
{
	ConsoleMsg::WriteLine("Spider Destroyed");
	DeregisterCollision<Spider>(*this);
}


void Spider::Update()
{
	
	frameCounter++;


	// Checks if SPIDER has reached it's MAX
	if (frameCounter % MAX_FramesPerChange == 0)
	{
		frameCounter = 0;
		Change_Movement();
	}

	//Checks if SPIDER has a random change
	else if (rand() % (MAX_FramesPerChange * 2) == 0)
	{
		frameCounter = MAX_FramesPerChange - frameCounter;
		Change_Movement();
	}
	

	// Still an unfavomable amount of cheese...
	// atleast it looks cool???
	// (Could be turned into a FSM) 999

	if (currentMove == Moving__Up)
	{
		Move__Up();
	}
	else if (currentMove == Moving__Down)
	{
		Move__Down();
	}
	else if (currentMove == Moving__Up_Left)
	{
		Move__Up_Left();
	}
	else if (currentMove == Moving__Up_Right)
	{
		Move__Up_Right();
	}
	else if (currentMove == Moving__Down_Left)
	{
		Move__Down_Left();
	}
	else if (currentMove == Moving__Down_Right)
	{
		Move__Down_Right();
	}


	MainSprite.setPosition(Pos);
	MainSprite.Update();


	// Destroy SPIDER if it has reached either side of the screen
	if ((Pos.x > WindowManager::Window().getView().getSize().x) || (Pos.x < 0))
	{
		SpiderSpawner::set_active_off();
		MarkForDestroy();
	}


}


void Spider::Collision(Bullet* other)
{
	sf::Vector2f spawn = other->getSpawn();
	float distance = sqrtf((powf(Pos.x - spawn.x, 2)) + (powf(Pos.y - spawn.y, 2)));

	SpiderFactory::distance = distance;
	SoundManager::SendSoundCMD(GameEntityManager::pKilled);
	ScoreManager::SendScoreCMD(SpiderFactory::GetScore());
	
	Explode();
	
}


void Spider::Collision(Blaster* other)
{
	Explode();
}


void Spider::Draw()
{
	WindowManager::Window().draw(MainSprite);
}



/*
	HELPER METHODS ==========
*/

void Spider::Explode()
{
	SpiderSpawner::set_active_off();
	new Explosion(this->Pos);
	MarkForDestroy();
}

void Spider::Initialize(float speed)
{

	// Must be a factor of "GameManager::BOX_SIZE" (ie. 32)
	SPEED = speed;

	MAX_FramesPerChange = (int)((GameManager::BOX_SIZE * (((MushroomManager::BOTTOM_ROW + 1) - MushroomManager::TOP_PLAYER_ROW))) / SPEED);

	frameCounter = rand() % MAX_FramesPerChange;


	if (rand() % 2 == 0)
	{
		Left = true; // move left

		if (rand() % 2 == 0)
		{
			currentMove = Moving__Down_Left;
			Pos = sf::Vector2f(WindowManager::Window().getView().getSize().x, SpiderFactory::TOP_BORDER + (SPEED * frameCounter) - (GameManager::BOX_SIZE / 2));
		}
		else
		{
			currentMove = Moving__Up_Left;
			Pos = sf::Vector2f(WindowManager::Window().getView().getSize().x, SpiderFactory::BOTTOM_BORDER - (SPEED * frameCounter) - (GameManager::BOX_SIZE / 2));
		}

	}
	else
	{
		Left = false; // move right

		if (rand() % 2 == 0)
		{
			currentMove = Moving__Down_Right;
			Pos = sf::Vector2f(0, SpiderFactory::TOP_BORDER + (SPEED * frameCounter) - (GameManager::BOX_SIZE / 2));
		}
		else
		{
			currentMove = Moving__Up_Right;
			Pos = sf::Vector2f(0, SpiderFactory::BOTTOM_BORDER - (SPEED * frameCounter) - (GameManager::BOX_SIZE / 2));
		}

	}




	


	RegisterCollision<Spider>(*this);
}


// Movement Methods

void Spider::Move__Up()
{
	Pos.y -= SPEED;
}
void Spider::Move__Up_Left()
{
	Pos.y -= SPEED;
	Pos.x -= SPEED;
}
void Spider::Move__Up_Right()
{
	Pos.y -= SPEED;
	Pos.x += SPEED;
}
void Spider::Move__Down()
{
	Pos.y += SPEED;
}
void Spider::Move__Down_Left()
{
	Pos.y += SPEED;
	Pos.x -= SPEED;
}
void Spider::Move__Down_Right()
{
	Pos.y += SPEED;
	Pos.x += SPEED;
}

void Spider::Change__Up()
{
	if (rand() % 2 == 0)
	{
		currentMove = Moving__Down;
	}
	else
	{
		if (Left)
		{
			currentMove = Moving__Down_Left;
		}
		else
		{
			currentMove = Moving__Down_Right;
		}
	}
}
void Spider::Change__Down()
{
	if (rand() % 2 == 0)
	{
		currentMove = Moving__Up;
	}
	else
	{
		if (Left)
		{
			currentMove = Moving__Up_Left;
		}
		else
		{
			currentMove = Moving__Up_Right;
		}
	}
}

void Spider::Change_Movement()
{
	if (currentMove == Moving__Up || currentMove == Moving__Up_Left || currentMove == Moving__Up_Right)
	{
		Change__Up();
	}
	else
	{
		Change__Down();
	}
}



// Outside call method

void Spider::Pause()
{
	SPEED = 0;
}