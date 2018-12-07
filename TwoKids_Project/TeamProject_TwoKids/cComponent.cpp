#include "DXUT.h"
#include "cComponent.h"

cComponent::cComponent()
	:bEnable(true), gameObject(nullptr)
{
}


cComponent::~cComponent()
{
}

void cComponent::SetEnable(bool enable)
{
	bEnable = enable;
}

bool cComponent::GetEnable()
{
	return bEnable;
}

const wstring & cComponent::GetTag()
{
	assert(gameObject && "Don't have GameObject");

	return gameObject->GetTag();
}

const wstring & cComponent::GetObjectName()
{
	assert(gameObject && L"Don't have GameObject");

	return gameObject->GetObjectName();
}

cTransform & cComponent::GetTransform()
{
	assert(gameObject && L"Don't have GameObject");

	return gameObject->GetTransform();
}

cGameObject * cComponent::GetParentObject()
{
	return gameObject->GetParentObject();
}

void cComponent::SetOwner(cGameObject * _gameObject)
{
	gameObject = _gameObject;
}

/*
inline void cComponent::SetEnable(bool enable)
{
	bEnable = enable;
}

inline bool cComponent::GetEnable()
{
	return bEnable;
}

const inline wstring & cComponent::GetTag()
{
	assert(gameObject && "Don't have GameObject");

	return gameObject->GetTag();
}

const inline  wstring & cComponent::GetObjectName()
{
	assert(gameObject && L"Don't have GameObject");

	return gameObject->GetObjectName();
}

inline cTransform & cComponent::GetTransform()
{
	assert(gameObject && L"Don't have GameObject");

	return gameObject->GetTransform();
}

inline cGameObject * cComponent::GetParentObject()
{
	return gameObject->GetParentObject();
}
inline void cComponent::SetOwner(cGameObject * _gameObject)
{
	gameObject = _gameObject;
}
*/
