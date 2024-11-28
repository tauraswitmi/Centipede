#include "CMDSound.h"

CMDSound::CMDSound(sf::SoundBuffer& _sound, float vol)
	: volume(vol)
{
	sound.setBuffer(_sound);
	sound.setVolume(volume);
}

void CMDSound::SetVolume(float v)
{
	sound.setVolume(v);
	volume = v;
}


void CMDSound::Execute()
{
	sound.play();
}

void CMDSound::Pause()
{
	sound.stop();
}