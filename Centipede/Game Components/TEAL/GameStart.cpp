// GameStart.cpp
// Andre Berthiaume, July 2019

#include "Game.h"
#include "CommonElements.h"

void Game::GameStart()
{
	WindowManager::SetWindowSize(960, 992); // Dimensions of Centipede are (240, 248)
	WindowManager::SetCaptionName("Centipede Test");
}
