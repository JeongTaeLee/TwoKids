#include "DXUT.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
{
	System_Create(&g_pSystem);

	g_pSystem->init(10, FMOD_INIT_NORMAL, 0);

}


cSoundManager::~cSoundManager()
{
	for (auto iter : m_pSound)
	{
		iter.second->g_pSound->release();
	}
	g_pSystem->release();
	g_pSystem->close();
	m_pSound.clear();
}

void cSoundManager::AddSound(wstring name, wstring path, bool loop)
{
	auto iter = m_pSound.find(name);
	if (iter != m_pSound.end()) return;

	SoundPlayer *tempSound = new SoundPlayer();
	string translate;
	translate.assign(path.begin(), path.end());

	if(loop)
		g_pSystem->createSound(translate.c_str(), FMOD_LOOP_NORMAL, 0, &tempSound->g_pSound);
	else
		g_pSystem->createSound(translate.c_str(), FMOD_DEFAULT, 0, &tempSound->g_pSound);

	m_pSound.insert(make_pair(name, tempSound));
}

void cSoundManager::PlayerSound(wstring name, float volume)
{
	auto iter = m_pSound.find(name);
	if (iter == m_pSound.end()) return;

	iter->second->g_pChannel->setVolume(volume);

	g_pSystem->playSound(FMOD_CHANNEL_FREE, iter->second->g_pSound, 0, &iter->second->g_pChannel);
}

void cSoundManager::StopSound(wstring name)
{
	auto iter = m_pSound.find(name);
	if (iter == m_pSound.end()) return;

	iter->second->g_pChannel->stop();
}
