//// GridObject
//// // Charles Tiemeyer, Nov 2024
//
//#include "GridObject.h"
//#include "MushroomManager.h"
//#include "GameManager.h"
//#include "MushroomFactory.h"
//#include "Spider.h"
//#include "ScoreManager.h"
//#include "Explosion.h"
//
//#include <math.h>
//
//GridObject::GridObject()
//{
//	//SPEED = 200.0f + rand() % 100;	// Randomize the speed
//
//	MainSprite = AnimatedSprite(ResourceManager::GetTexture("Mushroom"), 4, 2);
//	MainSprite.SetAnimation(0, 3, false);
//
//
//	MainSprite.setOrigin(MainSprite.getTextureRect().width / 2.0f, MainSprite.getTextureRect().height / 2.0f);
//	MainSprite.setScale(2, 2); // No longer using scale() variable
//
//
//	CollisionTools::TextureBitmap& bitmap = ResourceManager::GetTextureBitmap("Mushroom");
//	SetCollider(MainSprite, bitmap, true);
//
//}
//
//
//
///*
//	EVENT METHODS ==========
//*/
//
//
//
//void Mushroom::Draw()
//{
//	WindowManager::Window().draw(MainSprite);
//}
//
//
//void Mushroom::Collision(Bullet* other)
//{
//	health -= 1;
//	Damaged = true;
//	//ConsoleMsg::WriteLine("Mushroom Hit");
//	UpdateHealth();
//
//}
//
//void Mushroom::Collision(Spider* other)
//{
//	MarkForDestroy();
//}
//
//
//void Mushroom::Destroy()
//{
//	DeregisterCollision<Mushroom>(*this);
//	this->reference->RemoveMushroom(Pos_Grid.x, Pos_Grid.y);
//}
//
//
//
///*
//	HELPER METHODS ==========
//*/
//
//
//void Mushroom::Initialize(sf::Vector2i p, MushroomManager* ref)
//{
//	this->Poisoned = false;
//	this->Damaged = false;
//
//	this->reference = ref;
//	this->health = MAXHEALTH;
//	this->Pos_Grid = p;
//
//	MainSprite.setPosition(sf::Vector2f(((float)p.x * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2), ((float)p.y * GameManager::BOX_SIZE) + (GameManager::BOX_SIZE / 2)));
//	MainSprite.SetFrame(4 - health);
//	MainSprite.Update();
//
//	RegisterCollision<Mushroom>(*this);
//}
//
//
//
//void Mushroom::UpdateHealth()
//{
//	if (health <= 0)
//	{
//		MarkForDestroy();
//		ScoreManager::SendScoreCMD(MushroomFactory::GetScore());
//	}
//	else
//	{
//		if (this->Poisoned)
//		{
//			MainSprite.SetFrame((MainSprite.GetFrameCount() * 2) - health);
//		}
//		else
//		{
//			MainSprite.SetFrame((MainSprite.GetFrameCount()) - health);
//		}
//	}
//
//	MainSprite.Update();
//}
//
//
//void Mushroom::Regen()
//{
//	Poisoned = false;
//	Damaged = false;
//	health = MAXHEALTH;
//	ScoreManager::SendScoreCMD(MushroomFactory::GetScoreReset());
//	UpdateHealth();
//
//	new Explosion(MainSprite.getPosition());
//}
//
//
//
//void Mushroom::Reset()
//{
//	if (health < MAXHEALTH || Poisoned)
//	{
//		Damaged = false;
//		Poisoned = false;
//		health = MAXHEALTH;
//		ScoreManager::SendScoreCMD(MushroomFactory::GetScoreReset());
//		UpdateHealth();
//	}
//}
