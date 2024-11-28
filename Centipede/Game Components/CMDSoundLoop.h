// CMDSoundLoop.h
// Charles Tiemeyer, Nov 2024

#ifndef _CMDSoundLoop
#define _CMDSoundLoop

#include "CMDSound.h"

class CMDSoundLoop : public CMDSound
{
public:
	CMDSoundLoop(sf::SoundBuffer& _sound, float vol);
	CMDSoundLoop() = delete;
	CMDSoundLoop(const CMDSoundLoop&) = delete;
	CMDSoundLoop& operator=(const CMDSoundLoop&) = delete;
	virtual ~CMDSoundLoop() = default;

};

#endif _CMDSoundLoop