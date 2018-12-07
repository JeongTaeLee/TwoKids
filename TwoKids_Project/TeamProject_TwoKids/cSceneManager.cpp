#include "DXUT.h"
#include "cSceneManager.h"
#include "cScene.h"

cSceneManager::cSceneManager()
{
	spNowScene	= nullptr;
	spNextScene = nullptr;
}


cSceneManager::~cSceneManager()
{
	spNowScene->Release();
}

weak_ptr<cScene> cSceneManager::AddScene(const wstring & key, shared_ptr<cScene> scene)
{
	auto find = mapScenes.find(key);

	if (find != mapScenes.end())
		return weak_ptr<cScene>();

	return mapScenes.insert(make_pair(key, scene)).first->second;
}

weak_ptr<cScene> cSceneManager::ChangeScene(const wstring & key)
{
	auto find = mapScenes.find(key);
	
	if (find == mapScenes.end())
		return weak_ptr<cScene>();

	spNextScene = find->second;

	return spNextScene;
}

void cSceneManager::Update(float ElapseTime)
{
	if (spNextScene)
	{
		if (spNowScene)
		{	
			spNowScene->Release();
			spNowScene.reset();
		}
		spNextScene->Init();
		spNowScene = spNextScene;
		spNextScene.reset();
	}

	if (spNowScene)
		spNowScene->Update(ElapseTime);
}

void cSceneManager::Render()
{
	if (spNowScene)
		spNowScene->Render();
}
