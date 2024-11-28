// MushroomManager.h
// Charles Tiemeyer, September 2024

#ifndef _MushroomManager
#define _MushroomManager

#include "TEAL\CommonElements.h"
#include <queue>

class Mushroom; // Note: Forward declare to avoid include-loop since Bullet.h includes Aseroids.h


class MushroomManager : public GameObject
{
public:
	MushroomManager(); 
	MushroomManager(const MushroomManager&) = delete;
	MushroomManager& operator=(const MushroomManager&) = delete;
	~MushroomManager() = default;

	// Reset Mushrooms
	// virtual void Alarm0();
	// 

	void regen();

	virtual void Destroy();
	virtual void Alarm0();
	virtual void Alarm1();



	void Initialize();


	void SpawnMushrooms();

	void AddMushroom(int col, int row);
	void RemoveMushroom(int col, int row);

	void SaveMushroomPositions();
	void LoadMushroomPositions();
	void SetMushroomPositions(std::queue<sf::Vector2i> positions) { mushroom_positions = positions; };
	std::queue<sf::Vector2i> GetMushroomPositions();

	void EmptyGrid();


	static const int TOP_PLAYER_ROW = 25;
	static const int BOTTOM_ROW = 30;
	static const int HEIGHT = 32;
	static const int WIDTH = 30;
	static const int MIN_BZ_MUSHROOMS = 5;



	enum class Obstacle { Clear, Blocked, Poisoned }; 
	Obstacle Inspect(int row, int col);

	int get_number_bz_mushrooms() { return number_bz_mushrooms; };
	std::queue<sf::Vector2i> get_mushroom_positions() { return mushroom_positions; };

private:


	Mushroom* mushroom_grid[32][30]; // Set to static so the CentipedeHead can work
	Mushroom* mushroom_destroyed;

	std::queue<sf::Vector2i> mushroom_positions; // Save here when switching players

	int number_bz_mushrooms;
	int col_reg;
	int row_reg;
	
	

};

#endif _MushroomManager