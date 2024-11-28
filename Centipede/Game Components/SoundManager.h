// SoundManager.h
// Charles Tiemeyer, Nov 2024

#ifndef _SoundManager
#define _SoundManager

#include <queue>
#include <list>

class CMDSound;
class CMDSoundLoop;
class Player;

class SoundManager
{
private:
	
	static std::list<CMDSound*> Sounds;

	static bool muted;
	static float volume;
	static SoundManager* ptrInstance;

	SoundManager();
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	virtual ~SoundManager() = default;

	static SoundManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new SoundManager;
		return *ptrInstance;
	};

	void privProcessSounds();
	void privProcessPause();

public:
	// events
	enum class SoundEvents { Centipede, Flea, Scorpion, Spider, Fire, Kill, Death, Replenish, Extra_Life };

	static CMDSound* GetScoreCommand(SoundEvents ev);
	static bool GetMuteStatus() { return muted; };

	static void Mute();
	static void UnMute();

	static void SendSoundCMD(CMDSound* c);
	static void SendPauseCMD(CMDSound* c);
	static void ProcessSounds();
	static void ProcessPause();
	
	static void Initialize(int gameMode, float vol);
	static void Terminate();

protected:


	std::queue<CMDSound*> QueueCMDs;
	std::queue<CMDSound*> QueuePauseCMDs;
};

#endif _SoundManager