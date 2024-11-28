// BlasterFactory
// Charles Tiemeyer, Oct 2024


#ifndef _BlasterFactory
#define _BlasterFactory

class BlasterObjectPool;
class GameObjects;
class GameManager;
class CMDSound;

class BlasterFactory
{
private:
	static BlasterObjectPool* myBlasterPool;
	static GameManager* GameRef; // For callbacks
	static CMDSound* pDeathSound;

	static bool active;
	
	static BlasterFactory* ptrInstance;

	static BlasterFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BlasterFactory;
		return *ptrInstance;
	};

public:

	static CMDSound* GetSound() { return pDeathSound; };

	static void Initialize(GameManager* ref);

	static void CreateBlaster(int gm);

	static void RecycleBlaster(GameObject* b);

	static GameManager* get_GameRef() { return GameRef; };

	static void Terminate();

};


#endif _BlasterFactory
