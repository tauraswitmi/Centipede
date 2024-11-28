// LoadAllResources.cpp
// Andre Berthiaume, June 2012
//
// The user fills the method with all resources that need loading

#include "ResourceManager.h"
#include "../AttractorMode.h"

void ResourceManager::LoadAllResources()
{

	SetStartScene(new AttractorMode());

	// Demo Resources
	//AddTexture("Spaceship", "SpaceShip2.png");
	//AddTexture("Shots", "ColoredShots.png");
	//AddTexture("Mine", "Mine.png");


	AddSound("Centipede", "beat.wav"); // Loop
	AddSound("Death", "death.wav"); // Solo
	AddSound("Extra_Life", "extraLife.wav"); // Solo
	AddSound("Fire", "fire1.wav"); // Solo
	AddSound("Kill", "kill.wav"); // Solo
	AddSound("Replenish", "bonus.wav"); // Loop???
	AddSound("Spider", "spiderloop.wav"); // Loop
	AddSound("Scorpion", "scorpion_new.wav"); // Loop
	AddSound("Flea", "flea_new.wav"); // Solo


	//AddSound("Boom", "bazooka3.wav");
	//AddSound("Zap", "scifiblast.wav");
	//AddSound("Ding", "glass.wav");

	AddFont("PointFont", "MotorwerkOblique.ttf");


	// Centipede Resources
	AddTexture("Blaster", "blaster.png");
	AddTexture("Bullet", "bullet.png");
	AddTexture("Mushroom", "mushroom.png");

	AddTexture("Explosion", "spawn.png");
	AddTexture("Death", "death.png");

	AddTexture("Flea", "flea.png");
	AddTexture("Scorpion", "scorpion.png");
	AddTexture("Spider", "spider.png");
	AddTexture("CentipedeHead", "centipede_head.png");
	AddTexture("CentipedeBody", "centipede_segment.png");

	AddTexture("Alphabet", "FONTwPLAYER.bmp");

	AddTexture("SpiderScore", "spiderscore.png");


	// Figure out how I can add BMP File Fonts

}

