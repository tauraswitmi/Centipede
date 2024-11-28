// Blaster
// Charles Tiemeyer, Sep 2024

#include "CentipedeHead.h"
#include "CentipedeBody.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeBodyFactory.h"

#include "Bullet.h"
#include "Explosion.h"
#include "Mushroom.h"
#include "MoveState.h"
#include "MovementCollection.h"
#include "MoveFSM.h"

#include "MushroomManager.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "GameEntityManager.h"

CentipedeHead::CentipedeHead()
{
	SPEED = 2; // 8 pixels per frame

	// Get animated sprite
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("CentipedeHead"), 8, 2, 8.0f); /// 999 update frame per sec
	MainSprite.SetAnimation(0, 7);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 4.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(4, 4);
	MainSprite.setPosition(Pos);


	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("CentipedeHead");
	SetCollider(MainSprite, bitmap, true);
	

	// Order relative to other objects
	SetDrawOrder(1000);


	prevCentipede = nullptr;
}



/*
	EVENT METHODS ==========
*/

void CentipedeHead::Destroy()
{

	ConsoleMsg::WriteLine("CentipedeHead Destroyed");

	DeregisterCollision<CentipedeHead>(*this);
}



void CentipedeHead::Update()
{


	Pos.x += (pCurrentState->GetMoveOffsets())->coloffset * SPEED; // For rn only moves 1 pixel per frame
	Pos.y += (pCurrentState->GetMoveOffsets())->rowoffset * SPEED; // For rn only moves 1 pixel per frame



	// -IF-  CentipedeHead has moved to another cell   //
	if ((abs(Pos.x - PosPrev.x) >= GameManager::BOX_SIZE) || (abs(Pos.y - PosPrev.y) >= GameManager::BOX_SIZE))
	{

		this->Col += (pCurrentState->GetMoveOffsets())->coloffset; 
		this->Row += (pCurrentState->GetMoveOffsets())->rowoffset; 
		
		this->pPrevState = pCurrentState;
		this->pCurrentState = pCurrentState->GetNextState(this);

		Pos.x = (Col * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2);
		Pos.y = (Row * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2);
		PosPrev = Pos;
		//pCurrentState->Show();


		// SPAWN prevCentipede
		if (!spawned && centipedes != 0) 
		{
			spawned = true; // Does not activate again after running
			prevCentipede = CentipedeBodyFactory::CreateCentipedeBody(this, --centipedes, SPEED);
		}

		// UPDATE prevCentipede
		else if (this->prevCentipede != nullptr)
		{
			this->prevCentipede->SetCurrentState(pPrevState); // updates the status everytime
		}


	}
	 
	MainSprite.setPosition(Pos);
	MainSprite.Update();



}


void CentipedeHead::Collision(Blaster* other)
{
	//MarkForDestroy();
}


void CentipedeHead::Collision(Bullet* other)
{


	// Always spawns a mushroom at the Centipede's next destination
	this->reference->AddMushroom(Col + this->pCurrentState->GetMoveOffsets()->coloffset, Row + this->pCurrentState->GetMoveOffsets()->rowoffset);

	// -IF-   there exists a body behind the head
	if (this->prevCentipede != nullptr)
	{ 
 		this->prevCentipede->TurnToHead(); 
	}

	SoundManager::SendSoundCMD(GameEntityManager::pKilled);
	ScoreManager::SendScoreCMD(CentipedeHeadFactory::GetScore());
	Explode();
}



void CentipedeHead::Draw()
{
	WindowManager::Window().draw(MainSprite);
}





//	============== INITIALIZERS ==============	//


// Created from Spawn (Start of Level)
void CentipedeHead::Initialize(MushroomManager* ref, int length, float speed, bool left)
{
	
	RegisterCollision<CentipedeHead>(*this);

	this->reference = ref;
	this->centipedes = length;


	this->SPEED = speed;
	this->Col = MushroomManager::WIDTH / 2; // Middle 0-29
	this->Row = 0;
	
	// SPAWN moving either LEFT or RIGHT
	if (!left)
	{
		this->pCurrentState = &MoveFSM::StateTurnDownSwitchToRight;
	}
	else
	{
		this->pCurrentState = &MoveFSM::StateTurnDownSwitchToLeft;
	}


	this->Pos = sf::Vector2f(float(Col * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2), (GameManager::BOX_SIZE / 2));
	this->PosPrev = Pos;
	this->spawned = false;

	// Reset Linked List
	this->prevCentipede = nullptr;

	
}


// Created from Spawn (Start of Level) *SoloHead
void CentipedeHead::Initialize(MushroomManager* ref, int length, float speed, bool left, int column)
{

	RegisterCollision<CentipedeHead>(*this);

	this->reference = ref;
	this->centipedes = 0;


	this->SPEED = speed;
	this->Col = column; // Middle 0-29
	this->Row = 0;

	// SPAWN moving either LEFT or RIGHT
	if (!left)
	{
		this->pCurrentState = &MoveFSM::StateTurnDownSwitchToRight;
	}
	else
	{
		this->pCurrentState = &MoveFSM::StateTurnDownSwitchToLeft;
	}


	this->Pos = sf::Vector2f(float(Col * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2), (GameManager::BOX_SIZE / 2));
	this->PosPrev = Pos;

	this->spawned = false;

	// Reset Linked List
	this->prevCentipede = nullptr;
}


// Created from Separation (New Head)
void CentipedeHead::Initialize(CentipedeBody* ch, int length, float speed)
{

	RegisterCollision<CentipedeHead>(*this);

	this->reference = ch->GetMushroomManager();
	this->centipedes = length;

	this->SPEED = speed;
	this->Col = ch->GetColumn(); // Middle 0-29
	this->Row = ch->GetRow();
	
	// SPAWN from front Centipede's PREV STATE
	this->pCurrentState = ch->GetCurrentState(); // ->GetNextState(this);
	

	this->Pos = ch->Pos;
	this->PosPrev = ch->PosPrev;
	this->spawned = false;
	this->prevCentipede = ch->GetPrevCentipede();


	// If there exists a "CentipedeBody" behind, assign it's "pHeader" variable to this Header
	if (this->prevCentipede != nullptr)
	{
		this->prevCentipede->SetHead(this);
	}


	MainSprite.setPosition(Pos);
	MainSprite.Update();

	
}






void CentipedeHead::AddPrevCentipede(CentipedeBody* prev)
{
	prevCentipede = prev;
}


void CentipedeHead::Reset()
{
	MarkForDestroy();
}

void CentipedeHead::Explode()
{
	new Explosion(this->Pos);
	MarkForDestroy();
}