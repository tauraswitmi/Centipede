// Blaster
// Charles Tiemeyer, Sep 2024

#include "Blaster.h"
#include "Bullet.h"
#include "BulletFactory.h"

#include "Mushroom.h"
#include "MushroomManager.h"
#include "SoundManager.h"
#include "Flea.h"
#include "BlasterExplosion.h"
#include "BlasterFactory.h"
#include "GameManager.h"

#include "PlayerControl.h"
#include "AIControl.h"


float Blaster::PZB_LEFT;
float Blaster::PZB_RIGHT;
float Blaster::PZB_UP;
float Blaster::PZB_DOWN;

Blaster::Blaster()
{
	SPEED = 400;
	offset = 0;

	// Relative to the position of the spaceship, where do the bullets spawn from???
	GunOffset = sf::Vector2f(0, -10);

	// Get animated sprite // Might change to sf:Sprite 9999
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Blaster"), 1, 1);
	MainSprite.SetAnimation(0, 0, false);


	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);	// Origin is the center of the sprite
	MainSprite.setScale(2, 2);		// (16,16) -> (32,32)															// Sets the scale of the sprite (USE THIS TO EXPAND THE CENTIPEDE
	MainSprite.setPosition(Pos);

	Impulse = sf::Vector2f(0, 0);

	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Blaster");
	SetCollider(MainSprite, bitmap, true);
	

	// Order relative to other objects
	SetDrawOrder(1000);


	PZB_LEFT = (float)MainSprite.getTextureRect().width;
	PZB_RIGHT = WindowManager::Window().getView().getSize().x - MainSprite.getTextureRect().width;
	PZB_UP = MushroomManager::TOP_PLAYER_ROW * GameManager::BOX_SIZE + MainSprite.getTextureRect().width;
	PZB_DOWN = WindowManager::Window().getView().getSize().y - MainSprite.getTextureRect().height;
}




void Blaster::Destroy()
{

	ConsoleMsg::WriteLine("Controller Destroyed");
	delete Controller;
	DeregisterInput();
	DeregisterCollision<Blaster>(*this);
}


void Blaster::Update()
{
	offset = SPEED * Game::FrameTime();

	// What is the controller's input???
	Controller->ComputeNextMove();


	Pos_Prev = Pos;
	Pos += Impulse;

	Impulse = sf::Vector2f(0, 0);

	// Wall for Ship
	Tools::Clamp<float>(Pos.x, PZB_LEFT, PZB_RIGHT);   // (Val, Min, Max)
	Tools::Clamp<float>(Pos.y, PZB_UP, PZB_DOWN);		// 100 is leacing room for scoreboard, subtracting the height makes the ship stay on screen


	// Update the sprite after position is clamped
	MainSprite.setPosition(Pos);
	MainSprite.Update();  // update animation (flames in back)


}



void Blaster::Collision(Mushroom* other)
{

	/*
		Incapable of stopping opposite directional movement when
		colliding because it moves the sprite back to a place where
		it can move any direction.

		"Pos" when colliding
		  ---
		 |  [|]
		  ---

		"Pos" after colliding
		 ---
		|   | [ ]
		 ---
	*/

	Pos = Pos_Prev;

	// Update the sprite after position is clamped
	MainSprite.setPosition(Pos);
	MainSprite.Update();  // update animation (flames in back)

}

void Blaster::Collision(Flea* other)
{
	Explode();
}
void Blaster::Collision(CentipedeHead* other)
{
	Explode();
}
void Blaster::Collision(CentipedeBody* other)
{
	Explode();
}
void Blaster::Collision(Spider* other)
{
	Explode();
}


void Blaster::Draw()
{
	WindowManager::Window().draw(MainSprite);
}




/*
	HELPER METHODS ==========
*/


// Manage The Player's Controls
void Blaster::SetStrategy(ControlBaseStrategy* strategy)
{
	this->Controller = strategy;
}


void Blaster::Explode()
{
	new BlasterExplosion(this->Pos, BlasterFactory::get_GameRef());

	// Trigger Loss of Life in GameManager!!!
	BlasterFactory::get_GameRef()->LossOfLifeCallback();

	SoundManager::SendSoundCMD(BlasterFactory::GetSound());

	MarkForDestroy();
}


void Blaster::Initialize(int gm)
{
	// If AI GameMode, Set the Controller to AI
	if (gm == 0)
	{
		SetStrategy(new AIControl(this));
	}

	// If Player GameMode, Set the Controleer to Player Input
	else
	{
		SetStrategy(new PlayerControl(this));
	}
	
	Pos = sf::Vector2f(WindowManager::Window().getView().getSize().x / 2.0f, WindowManager::Window().getView().getSize().y - MainSprite.getTextureRect().height);	// Starting Position
	RegisterCollision<Blaster>(*this);
}



void Blaster::Up()
{
	Impulse.y = -offset;
}
void Blaster::Down()
{
	Impulse.y = offset;
}
void Blaster::Left()
{
	Impulse.x = -offset;
}
void Blaster::Right()
{
	Impulse.x = offset;
}

void Blaster::Shoot()
{
	BulletFactory::CreateBullet(Pos + GunOffset);
}



void Blaster::CheckMove(Blaster::AIMovement curr_mov)
{
	if (curr_mov == Mov_RightUp)
	{
		Right();
		Up();
	}
	else if (curr_mov == Mov_RightDown)
	{
		Right();
		Down();
	}
	else if (curr_mov == Mov_LeftUp)
	{
		Left();
		Up();
	}
	else if (curr_mov == Mov_LeftDown)
	{
		Left();
		Down();
	}
}



Blaster::AIMovement Blaster::CheckBorder(Blaster::AIMovement curr_mov)
{
	if (Pos.x == PZB_LEFT)
	{
		if (curr_mov == Mov_LeftUp)
		{
			return Mov_RightUp;
		}
		else if (curr_mov == Mov_LeftDown)
		{
			return Mov_RightDown;
		}
	}
	else if (Pos.x == PZB_RIGHT)
	{
		if (curr_mov == Mov_RightUp)
		{
			return Mov_LeftUp;
		}
		else if (curr_mov == Mov_RightDown)
		{
			return Mov_LeftDown;
		}
	}
	else if (Pos.y == PZB_UP)
	{
		if (curr_mov == Mov_LeftUp)
		{
			return Mov_LeftDown;
		}
		else if (curr_mov == Mov_RightUp)
		{
			return Mov_RightDown;
		}
	}
	else if (Pos.y == PZB_DOWN)
	{
		if (curr_mov == Mov_LeftDown)
		{
			return Mov_LeftUp;
		}
		else if (curr_mov == Mov_RightDown)
		{
			return Mov_RightUp;
		}
	}

	return curr_mov;
}