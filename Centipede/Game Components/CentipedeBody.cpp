#include "CentipedeBody.h"
#include "CentipedeHead.h"
#include "CentipedeHeadFactory.h"
#include "CentipedeBodyFactory.h"
#include "CentipedeSpawnerMain.h"

#include "Bullet.h"
#include "Explosion.h"
#include "MoveState.h"
#include "MovementCollection.h"
#include "MoveFSM.h"

#include "MushroomManager.h"
#include "GameManager.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include "GameEntityManager.h"

CentipedeBody::CentipedeBody()
{
	SPEED = 2; // 8 pixels per frame

	// Get animated sprite
	MainSprite = AnimatedSprite(ResourceManager::GetTexture("CentipedeBody"), 8, 2, 8.0f); /// 999 update frame per sec
	MainSprite.SetAnimation(0, 7);
	MainSprite.setOrigin(MainSprite.getTextureRect().width / 4.0f, MainSprite.getTextureRect().height / 2.0f);
	MainSprite.setScale(4, 4);
	MainSprite.setPosition(Pos);


	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("CentipedeBody");
	SetCollider(MainSprite, bitmap, true);


	// Order relative to other objects
	SetDrawOrder(1000);

}



/*
	EVENT METHODS ==========
*/

void CentipedeBody::Destroy()
{

	//ConsoleMsg::WriteLine("CentipedeBody Destroyed");
	DeregisterCollision<CentipedeBody>(*this);
}


void CentipedeBody::Update()
{


	Pos.x += (pCurrentState->GetMoveOffsets())->coloffset * SPEED; // For rn only moves 1 pixel per frame
	Pos.y += (pCurrentState->GetMoveOffsets())->rowoffset * SPEED; // For rn only moves 1 pixel per frame
	
	
	MainSprite.setPosition(Pos);
	MainSprite.Update();


}


void CentipedeBody::Collision(Blaster* other)
{
	//MarkForDestroy();
}



void CentipedeBody::Collision(Bullet* other)
{

	
	// Always spawns a mushroom at the Centipede's next destination
	this->reference->AddMushroom(Col + this->pCurrentState->GetMoveOffsets()->coloffset, Row + this->pCurrentState->GetMoveOffsets()->rowoffset);



	// Split the centipede!!!

	// -IF-   this is NOT the back of the centipede
	if (this->prevCentipede != nullptr)
	{
		this->prevCentipede->TurnToHead();
	}

	// -IF-   this body is NOT behind the header
	if (this->nextCentipede != nullptr)
	{
		this->nextCentipede->prevCentipede = nullptr;
	}

	// -ELSE IF-   this body IS behind the header
	else
	{
		// Separate old head from new centipede
		this->pHeader->AddPrevCentipede(nullptr);
	}



	// Add Score!!!
	SoundManager::SendSoundCMD(GameEntityManager::pKilled);
	ScoreManager::SendScoreCMD(CentipedeBodyFactory::GetScore());
	Explode();
	
}


void CentipedeBody::Draw()
{
	WindowManager::Window().draw(MainSprite);
}



/*
	HELPER METHODS =================
*/




// -WHEN ACTIVATED-   CentipedeBody has moved to another cell   //
void CentipedeBody::SetCurrentState(const MoveState* now)
{
	
	this->Col += (pCurrentState->GetMoveOffsets())->coloffset;
	this->Row += (pCurrentState->GetMoveOffsets())->rowoffset;

	this->pPrevState = pCurrentState;
	this->pCurrentState = now;

	Pos.x = (Col * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2);
	Pos.y = (Row * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2);
	PosPrev = Pos;
	//pCurrentState->Show();


	// SPAWN prevCentipede
	if (!spawned && centipedes != 0) 
	{
		spawned = true; // Does not activate again after running
		this->prevCentipede = CentipedeBodyFactory::CreateCentipedeBody(this, --centipedes, SPEED);
		
	}

	// UPDATE prevCentipede
	else if (this->prevCentipede != nullptr)
	{
		this->prevCentipede->SetCurrentState(pPrevState);
	}

}


void CentipedeBody::SetHead(CentipedeHead* ch)
{
	this->pHeader = ch;
	this->nextCentipede = nullptr;
}


// Created from the CENTIPEDE HEAD
void CentipedeBody::Initialize(CentipedeHead* ch, int num, float speed)
{

	RegisterCollision<CentipedeBody>(*this);

	this->reference = ch->GetMushroomManager();
	this->centipedes = num;

	this->SPEED = speed;
	this->Col = MushroomManager::WIDTH / 2; // Middle 0-29
	this->Row = 0;

	// SPAWN from front Centipede's PREV STATE
	this->pCurrentState = ch->GetPrevState();


	this->Pos = sf::Vector2f(float(Col * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2), (GameManager::BOX_SIZE / 2));
	this->PosPrev = Pos;

	this->spawned = false;

	this->prevCentipede = nullptr;
	this->nextCentipede = nullptr;
	this->pHeader = ch;

	
}


// Created from the CENTIPEDE BODY
void CentipedeBody::Initialize(CentipedeBody* cb, int num, float speed)
{

	RegisterCollision<CentipedeBody>(*this);

	this->reference = cb->GetMushroomManager();
	this->centipedes = num;

	this->SPEED = speed;
	this->Col = MushroomManager::WIDTH / 2; // Middle 0-29
	this->Row = 0;

	// SPAWN from front Centipede's PREV STATE
	this->pCurrentState = cb->GetPrevState();


	this->Pos = sf::Vector2f(float(Col * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2), (GameManager::BOX_SIZE / 2));
	this->PosPrev = Pos;

	this->spawned = false;

	this->prevCentipede = nullptr;
	this->nextCentipede = cb;
	this->pHeader = nullptr;

	
}


void CentipedeBody::TurnToHead()
{
	CentipedeHeadFactory::CreateCentipedeHead(this, 0, this->SPEED); 
	this->MarkForDestroy();
}



void CentipedeBody::Reset()
{
	this->MarkForDestroy();
}


void CentipedeBody::Explode()
{
	new Explosion(this->Pos);
	this->MarkForDestroy();
}