// BulletFactory
// Charles Tiemeyer, Sep 2024

#ifndef _BulletFactory
#define _BulletFactory

#include <stack>
#include "TEAL\CommonElements.h"


class BulletObjectPool;
class GameObjects;
class CMDSound;


class BulletFactory
{
private:

	static CMDSound* pBulletSound;

	static BulletObjectPool* myBulletPool;


	static BulletFactory* ptrInstance;
	static BulletFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BulletFactory;
		return *ptrInstance;
	};

	static bool active;

public:

	static CMDSound* GetSound() { return pBulletSound; };

	static void Initialize();

	static void CreateBullet(sf::Vector2f pos);

	static void RecycleBullet(GameObject* b);

	static void Terminate();


};

#endif _BulletFactory