// CMDSoundSingle.h
// Charles Tiemeyer, Nov 2024

#ifndef _CMDSoundSingle
#define _CMDSoundSingle

#include "CMDSound.h"

class CMDSoundSingle : public CMDSound
{
public:
	CMDSoundSingle(sf::SoundBuffer& _sound, float vol);
	CMDSoundSingle() = delete;
	CMDSoundSingle(const CMDSoundSingle&) = delete;
	CMDSoundSingle& operator=(const CMDSoundSingle&) = delete;
	virtual ~CMDSoundSingle() = default;

};

#endif _CMDSoundSingle