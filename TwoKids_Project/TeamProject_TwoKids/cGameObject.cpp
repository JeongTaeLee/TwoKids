#include "DXUT.h"
#include "cCollider2D.h"

cGameObject::cGameObject(cGameObject * parent)
	:bDestroy(false), bActive(true),
	tcTag(L"None"), tcObjectName(L"EmptyObject"),
	lpParentObject(nullptr), iDrawingOrder(0)
{
	transform.SetOwner(this);

	if (parent)
		parent->AddChild(this);
}

cGameObject::cGameObject(const wstring & _tcObjectName, cGameObject * parent)
	:tcObjectName(_tcObjectName), tcTag(L"None"), 
	bDestroy(false), bActive(true), lpParentObject(nullptr), iDrawingOrder(0)
{
	transform.SetOwner(this);

	if (parent)
		parent->AddChild(this);
}

cGameObject::cGameObject(const wstring & _tcObjectName, const wstring & _tcTag, cGameObject * parent)
	: tcObjectName(_tcObjectName), tcTag(_tcTag), 
	bDestroy(false), bActive(true), lpParentObject(nullptr), iDrawingOrder(0)
{
	transform.SetOwner(this);

	if (parent)
		parent->AddChild(this);
}


cGameObject::~cGameObject()
{
	for (auto Iter : liComponents)
		Iter->Destroy();
	liComponents.clear();
}

void cGameObject::Release()
{
	if (lpParentObject)
		lpParentObject->DeleteChild(this);

	for (auto Iter : liComponents)
		Iter->Destroy();
	liComponents.clear();

	for (auto Iter = liChildObjects.begin(); Iter != liChildObjects.end(); Iter = liChildObjects.begin())
		(*Iter)->CutParent();
}

void cGameObject::Update(float ElapseTime)
{
	transform.Update(ElapseTime);
	for (auto Iter : liComponents)
	{
		if (!(Iter->GetEnable()))
			continue;

		Iter->Update(ElapseTime);	
	}
}
void cGameObject::Render()
{
	transform.SetTransform();

	for (auto Iter : liComponents)
	{
		if (!(Iter->GetEnable()))
			continue;
			
		Iter->Render();
	}
}

cGameObject * cGameObject::AddChild(cGameObject * lpChild)
{
	if (!lpChild)
		return nullptr;
	
	for (auto Iter : liChildObjects)
	{
		if (Iter == lpChild)
			return nullptr;
	}

	liChildObjects.push_back(lpChild);
	lpChild->SetParentObject(this);

	return lpChild;
}

void cGameObject::DeleteChild(cGameObject * lpChild)
{
	if (!lpChild)
		return;

	for (auto Iter = liChildObjects.begin(); Iter != liChildObjects.end();)
	{
		if ((*Iter) == lpChild)
		{
			liChildObjects.erase(Iter);
			return;
		}
		else
			Iter++;
	}
}

void cGameObject::Send(const wstring & message)
{
	for (auto Iter : liComponents)
		Iter->Receive(message);
}

void cGameObject::OnTriggerSend(shared_ptr<cCollider2D> collider)
{
	for (auto Iter : liComponents)
	{
		if(!(dynamic_pointer_cast<cCollider2D>(Iter)))
			Iter->OnTriggerStay(collider);
	}
}

void cGameObject::OnColliderSend(shared_ptr<cCollider2D> collider)
{
	for (auto Iter : liComponents)
	{
		if (!(dynamic_pointer_cast<cCollider2D>(Iter)))
			Iter->OnColliderStay(collider);
	}
}

void cGameObject::CutParent()
{
	lpParentObject->DeleteChild(this);
	lpParentObject = nullptr;
}

void cGameObject::Destroy()
{
	SetActive(false);
	bDestroy = true;
}

void cGameObject::SetActive(bool _bActive)
{
	bActive = _bActive;

	for (auto Iter : liComponents)
		Iter->SetEnable(_bActive);

	for (auto Iter : liChildObjects)
		Iter->SetActive(_bActive);
}

void cGameObject::SetDrawingOrder(int order)
{
	iDrawingOrder = order;
}
