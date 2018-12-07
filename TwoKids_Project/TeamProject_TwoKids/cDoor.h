#pragma once
#include "cComponent.h"
class cDoor :
	public cComponent
{
private:
	POINT pNowArrPos;
	POINT pNextArrPos;

	MAP_DIRECTION	eDirection;

	bool openDoor;
private:
	weak_ptr<cSpriteRenderer> m_SpriteRenderer;
public:
	cDoor();
	virtual ~cDoor();
	virtual void Start() override;
	virtual void Update(float ElapsedTime) override;
	void SetDoorInfo(POINT _pNowPoint, POINT _pNextPoint, MAP_DIRECTION _eDirection);

	virtual void OnColliderStay(shared_ptr<cCollider2D> collider);
};

