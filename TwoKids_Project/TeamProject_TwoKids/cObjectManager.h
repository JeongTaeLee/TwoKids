 #pragma once
#include "singleton.h"

class cGameObject;

class cObjectManager :
	public singleton<cObjectManager>
{
private:
	list< cGameObject* > liObjects;
public:
	cObjectManager();
	virtual ~cObjectManager();

	cGameObject* AddObject(cGameObject* object);
	cGameObject* FindObject(const wstring & key);

	void Reset();
	void Update(float ElapsedTime);
	void Render();

	void DestoryObject();

	void PushObject	(cGameObject * object);
	void PopObject	(cGameObject * object);
};

#define OBJECTMANAGER cObjectManager::GetInstance()
