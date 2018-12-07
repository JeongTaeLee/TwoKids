#include "DXUT.h"
#include "cCollisionManager.h"

#include "cCollider2D.h"

cCollisionManager::cCollisionManager()
{
}


cCollisionManager::~cCollisionManager()
{
}

void cCollisionManager::AddCollider(shared_ptr<cCollider2D> collider)
{
	for (auto Iter : liColliders)
	{
		if (Iter == collider)
			return;
	}

	liColliders.push_back(collider);
}

void cCollisionManager::DestroyCollider(shared_ptr<cCollider2D> collider)
{
	for (auto Iter = liColliders.begin(); Iter != liColliders.end(); ++Iter)
	{
		if ((*Iter) == collider)
		{
			liColliders.erase(Iter);
			break;
		}
	}
}

void cCollisionManager::Update()
{
	for (auto Iter01 = liColliders.begin(); Iter01 != liColliders.end(); Iter01++)
	{
		if (!((*Iter01)->GetEnable()) || !((*Iter01)->gameObject->GetActive()))
			continue;

		for (auto Iter02 = liColliders.begin(); Iter02 != liColliders.end(); Iter02++)
		{
			if (Iter01 == Iter02)
				continue;

			if ((*Iter01)->gameObject->GetParentObject() == (*Iter02)->gameObject)
				continue;

			if ((*Iter02)->gameObject->GetParentObject() == (*Iter01)->gameObject)
				continue;

			if (!((*Iter02)->GetEnable()) || !((*Iter02)->gameObject->GetActive()))
				continue;

			RECT reCollider01 = (*Iter01)->GetColliderRect();
			RECT reCollider02 = (*Iter02)->GetColliderRect();

			if ((reCollider01.right > reCollider02.left && reCollider02.right > reCollider01.left) &&
				(reCollider01.bottom > reCollider02.top && reCollider02.bottom > reCollider01.top))
			{
				(*Iter01)->OnCollider((*Iter02));
				(*Iter02)->OnCollider((*Iter01));

				(*Iter01)->GetTransform().Update(0.f);
				(*Iter02)->GetTransform().Update(0.f);
			
				(*Iter01)->Update(0.f);
				(*Iter02)->Update(0.f);
			}
		}
	}
}

void cCollisionManager::PushCollider(shared_ptr<cCollider2D> collider)
{
	for (auto Iter : liColliders)
	{
		if (Iter == collider)
			return;
	}

	liColliders.push_back(collider);
}

void cCollisionManager::PopCollfider(shared_ptr<cCollider2D> collider)
{
	for (auto Iter = liColliders.begin(); Iter != liColliders.end();)
	{
		if ((*Iter) == collider)
		{
			liColliders.erase(Iter);
			break;
		}
		else
			++Iter;
	}
}
