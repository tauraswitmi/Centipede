// GameEntityManager
// Charles Tiemeyer, November 2024

#include "TEAL\CommonElements.h"
#include "GameEntityManager.h"
#include "SoundManager.h"
#include "CMDSound.h"


CMDSound* GameEntityManager::pKilled = nullptr;

GameEntityManager::GameEntityManager()
{
	pKilled = SoundManager::GetScoreCommand(SoundManager::SoundEvents::Kill);
}

GameEntityManager::~GameEntityManager()
{
	delete pKilled;
}