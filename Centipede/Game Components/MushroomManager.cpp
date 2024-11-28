// MushroomManager
// // Charles Tiemeyer, Sep 2024

#include "MushroomManager.h"
#include "MushroomFactory.h"
#include "Mushroom.h"
#include "Flea.h"
#include "FleaFactory.h"
#include "FleaSpawner.h"

#include "AttractorHUD.h"

#include "GameManager.h"
#include "SoundManager.h"
#include "PlayerManager.h"
#include <math.h>


MushroomManager::MushroomManager()
{
	
	number_bz_mushrooms = 0;
	mushroom_destroyed = nullptr;

	col_reg = 0;
	row_reg = MushroomManager::HEIGHT - 1;


	// Set all values of Mushroom Grid to Nullptr
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			mushroom_grid[i][j] = nullptr;
		}
	}


}




void MushroomManager::Destroy()
{

}





// DEATH CYCLE //

// (0) Restores Mushroom, Spawns Explosion, Iterates
void MushroomManager::Alarm0()
{
	mushroom_grid[row_reg][col_reg]->Regen();
	row_reg--;

	regen();
}

// (1) Small pause before triggering second LoseLife method in GameManager
void MushroomManager::Alarm1()
{
	GameManager::LossOfLifeCallback__2();
}
void MushroomManager::regen()
{
	while (col_reg < MushroomManager::WIDTH)
	{
		while (row_reg >= 0)
		{
			if (mushroom_grid[row_reg][col_reg] != nullptr)
			{
				if (mushroom_grid[row_reg][col_reg]->Damaged || mushroom_grid[row_reg][col_reg]->Poisoned)
				{
					SoundManager::SendSoundCMD(PlayerManager::pSound_MushRegen);
					SetAlarm(0, 0.15f); 
					return;
				}
			}
			row_reg--;
		}

		row_reg = MushroomManager::HEIGHT - 1;
		col_reg++;
	}

	col_reg = 0;

	SetAlarm(1, 1);
}





// Sets up Mushrooms on Grid when First Created
void MushroomManager::SpawnMushrooms()
{
	// Rows 0 - 2 are always empty at the start
	// Row 31 is empty
	// Row 25 - 30
	// Has either 1 or 0 mushrooms
	// Usually only one or two rows has 0
	// 3 - 24
	// Has either 2 or 1 mushrooms
	// Usually only one or two rows has 1


	for (int i = 3; i < TOP_PLAYER_ROW; i++)
	{

		// Spawn first mushroom
		int j = rand() % WIDTH;
		mushroom_grid[i][j] = MushroomFactory::CreateMushroom(sf::Vector2i(j, i), this); // x = j, y = i


		// Spawn a second mushroom 
		if ((rand() % 10) >= 4) // 40% chance of spawning
		{
			int k = rand() % WIDTH;
			while (k == j) { k = rand() % WIDTH; } // randomize until it doesn't match the first mushroom's position

			mushroom_grid[i][k] = MushroomFactory::CreateMushroom(sf::Vector2i(k, i), this);
		}

	}


	for (int i = TOP_PLAYER_ROW; i < BOTTOM_ROW; i++)
	{

		// Spawn a mushroom

		if ((rand() % 10) >= 3) // 30% chance of spawning
		{
			int j = rand() % WIDTH;
			mushroom_grid[i][j] = MushroomFactory::CreateMushroom(sf::Vector2i(j, i), this);

			number_bz_mushrooms++;
		}
	}

}





void MushroomManager::AddMushroom(int col, int row)
{
	// Find the closest 

	if (mushroom_grid[row][col] == nullptr)
	{
		
		mushroom_grid[row][col] = MushroomFactory::CreateMushroom(sf::Vector2i(col, row), this);

		if (row >= TOP_PLAYER_ROW)
		{
			number_bz_mushrooms++;
			FleaSpawner::update_number_of_pz_mushrooms(1);
		}
	}
	
}

void MushroomManager::RemoveMushroom(int col, int row)
{
	
	mushroom_destroyed = mushroom_grid[row][col];
	mushroom_grid[row][col] = nullptr;

	if (row >= TOP_PLAYER_ROW)
	{
		number_bz_mushrooms--;
        FleaSpawner::update_number_of_pz_mushrooms(-1);
		FleaSpawner::SpawnFlea();
	}
}







// Saves the Positions of each Mushroom before clearing them
void MushroomManager::SaveMushroomPositions()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (mushroom_grid[i][j] != nullptr)
			{
				mushroom_positions.push(mushroom_grid[i][j]->Get_GridPos());
			}
		}
	}
}


// Loads the Saved Mushroom Positions, Spawns Mushrooms
void MushroomManager::LoadMushroomPositions()
{
	if (mushroom_positions.empty())
	{
		SpawnMushrooms();
	}
	else
	{
		while (!mushroom_positions.empty())
		{
			AddMushroom(mushroom_positions.front().x, mushroom_positions.front().y);
			mushroom_positions.pop();
		}
	}
	

}


// Grabs Mushroom Positions from outside
std::queue<sf::Vector2i> MushroomManager::GetMushroomPositions()
{

	std::queue<sf::Vector2i> positions;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (mushroom_grid[i][j] != nullptr)
			{
				positions.push(mushroom_grid[i][j]->Get_GridPos());
			}
		}
	}

	return positions;
}






// Clears grid of Mushrooms
void MushroomManager::EmptyGrid()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (mushroom_grid[i][j] != nullptr)
			{
				mushroom_grid[i][j]->MarkForDestroy();
				mushroom_grid[i][j] = nullptr;
			}
			
		}
	}
}



// Checks if the Position on the Grid is Covered
MushroomManager::Obstacle MushroomManager::Inspect(int row, int col)
{
	int ans;

	if (col >= 0 && col < WIDTH)
	{

		// If Empty
		if (mushroom_grid[row][col] == nullptr)
		{
			ans = 0;
		}

		// If Poisoned
		else if (mushroom_grid[row][col]->Poisoned == false)
		{
			ans = 1;
		}

		// If Wall
		else
		{
			ans = 2;
		}
	}
	else
	{
		ans = 1;
	}
	

	return (Obstacle)ans;
}