// CMDSound.h
// Charles Tiemeyer, Nov 2024

#ifndef _CMDSound
#define _CMDSound

#include "TEAL\CommonElements.h"

class CMDSound
{
public:
	CMDSound(sf::SoundBuffer& _sound, float vol);
	CMDSound() = delete;
	CMDSound(const CMDSound&) = delete;
	CMDSound& operator=(const CMDSound&) = delete;
	virtual ~CMDSound() = default;

	// Note: the Excecute method must NOT have _any_ paramters
	virtual void Execute();
	virtual void Pause();

	void SetVolume(float v);

protected:
	sf::Sound sound;
	float volume;
};


#endif _CMDSound