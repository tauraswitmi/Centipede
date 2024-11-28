#include "CMDSoundLoop.h"

CMDSoundLoop::CMDSoundLoop(sf::SoundBuffer& _sound, float vol)
	:	CMDSound(_sound, vol)
{
	sound.setLoop(true);

}