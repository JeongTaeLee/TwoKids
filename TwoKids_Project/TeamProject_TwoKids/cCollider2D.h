#pragma once
#include "cComponent.h"
class cCollider2D :
	public cComponent
{
private:
	LONG colliderWidth, colliderHeight;

	D3DXVECTOR2 vColliderPos;
	D3DXVECTOR2 vVertex[5];

	RECT	reCollider;

	bool bIsTrigger;
public:
	cCollider2D();
	virtual ~cCollider2D();

	virtual void Start()						override;
	virtual void Destroy()						override;
	virtual void Update(float ElasedTime)		override;
	virtual void Render()						override;

	void SetColliderPos(const D3DXVECTOR2 & colliderPos);
	
	void SetColliderRect(const RECT & reRect);
	const RECT & GetColliderRect();
	
	bool GetTrigger() { return bIsTrigger; }
	void SetTrigger(bool trigger) { bIsTrigger = trigger; }
	
	void SetVertex();
	void OnCollider(shared_ptr<cCollider2D> collider);
};

