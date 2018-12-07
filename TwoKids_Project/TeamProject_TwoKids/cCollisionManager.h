#pragma once
#include "singleton.h"

class cCollider2D;

class cCollisionManager :
	public singleton<cCollisionManager>
{
private:
	list<shared_ptr<cCollider2D>> liColliders;
public:
	cCollisionManager();
	virtual ~cCollisionManager();

	void AddCollider(shared_ptr<cCollider2D> collider);
	void DestroyCollider(shared_ptr<cCollider2D> collider);

	void Update();

	void PushCollider(shared_ptr<cCollider2D> collider);
	void PopCollfider(shared_ptr<cCollider2D> collider);
};

#define COLLIDERMANAGER cCollisionManager::GetInstance()