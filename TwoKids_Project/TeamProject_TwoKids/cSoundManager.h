#pragma once
#include "singleton.h"

struct SoundPlayer
{
	Sound	* g_pSound;
	Channel	* g_pChannel;
};

class cSoundManager :
	public singleton<cSoundManager>
{
private:
	System * g_pSystem;
	map<wstring, SoundPlayer*> m_pSound;

public:
	cSoundManager();
	virtual ~cSoundManager();

public:
	void AddSound(wstring name, wstring path, bool loop);
	void PlayerSound(wstring name, float volume);
	void StopSound(wstring name);
};

#define SOUNDMANAGER cSoundManager::GetInstance()