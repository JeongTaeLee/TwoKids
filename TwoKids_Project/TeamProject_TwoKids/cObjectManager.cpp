#include "DXUT.h"
#include "cObjectManager.h"

#include "cGameObject.h"
#include "cCollider2D.h"

cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
	Reset();
}

cGameObject* cObjectManager::AddObject(cGameObject* object)
{
	if (!object)
		return nullptr;

	liObjects.push_back(object);

	return object;
}

cGameObject* cObjectManager::FindObject(const wstring & key)
{
	for (auto find : liObjects)
	{
		if (find->GetObjectName() == key)
			return find;
	}

	return nullptr;
}

void cObjectManager::Reset()
{
	for (auto Iter : liObjects)
		SAFE_DELETE(Iter);
	liObjects.clear();
}

void cObjectManager::Update(float ElapsedTime)
{	
	for (auto Iter : liObjects)
	{
		if (!(Iter->GetActive()))
			continue;
		Iter->Update(ElapsedTime);
	}

	DestoryObject();

	liObjects.sort(cGameObject::OrderSort);
	liObjects.sort(cGameObject::YSort);
}
void cObjectManager::Render()
{

	for (auto Iter : liObjects)
	{
		if (!(Iter->GetActive()))
			continue;
		Iter->Render();
	}
}

void cObjectManager::DestoryObject()
{
	for (auto Iter = liObjects.begin(); Iter != liObjects.end();)
	{
		if ((*Iter)->GetDestroy())
		{
			(*Iter)->Release();

			SAFE_DELETE(*Iter);
			Iter = liObjects.erase(Iter);
		}
		else
			++Iter;
	}
}

void cObjectManager::PushObject(cGameObject * object)
{
	if (!object)
		return;
	
	for (auto Iter : liObjects)
	{
		if (Iter == object)
			return;
	}

	liObjects.push_back(object);
}
void cObjectManager::PopObject(cGameObject * object)
{
	if (!object)
		return;
	
	for (auto Iter = liObjects.begin(); Iter != liObjects.end();)
	{
		if ((*Iter) == object)
		{
			liObjects.erase(Iter);
			break;
		}
		else
			++Iter;
	}
}
