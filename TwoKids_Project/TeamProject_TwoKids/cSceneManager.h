#pragma once
#include "singleton.h"

class cScene;

class cSceneManager :
	public singleton<cSceneManager>
{
private:
	map<wstring, shared_ptr<cScene> > mapScenes;

	shared_ptr<cScene> spNowScene;
	shared_ptr<cScene> spNextScene;
public:
	cSceneManager();
	virtual ~cSceneManager();

	weak_ptr<cScene> AddScene(const wstring & key, shared_ptr<cScene> scene);
	weak_ptr<cScene> ChangeScene(const wstring & key);

	void Update(float ElapseTime);
	void Render();
};

#define SCENEMANAGER cSceneManager::GetInstance()