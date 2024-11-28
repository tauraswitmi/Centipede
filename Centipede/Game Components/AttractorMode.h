// AttractorMode
// Charles Tiemeyer, November 2024

#ifndef _AttractorMode
#define _AttractorMode

#include "TEAL\CommonElements.h"

class MushroomManager;
class GameManager;

class AttractorMode : public Scene
{
public:
	AttractorMode() = default;
	AttractorMode(const AttractorMode&) = delete;
	AttractorMode& operator=(const AttractorMode&) = delete;
	~AttractorMode() = default;

	virtual void Initialize();
	virtual void Terminate();


private:

	GameManager* GameManager_Ref;

};

#endif _AttractorMode