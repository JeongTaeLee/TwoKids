#include "DXUT.h"
#include "cDoor.h"

#include "cMap.h"
#include "cSpriteRenderer.h"
#include "cPlayerComponent.h"

cDoor::cDoor()
	:openDoor(false)
{
}


cDoor::~cDoor()
{
}

void cDoor::Start()
{
	m_SpriteRenderer = AddComponent<cSpriteRenderer>();

	m_SpriteRenderer.lock()->SetTexture(MyAddTexture(L"Door", L"Resource/Texture/MapImage/Stage1_Door.png"));
	m_SpriteRenderer.lock()->SetMidCenter();
}

void cDoor::Update(float ElapsedTime)
{
	if (gameObject->GetParentObject()->GetComponent<cMap>()->IsAllMonsterDie())
		openDoor = true;
}

void cDoor::SetDoorInfo(POINT _pNowPoint, POINT _pNextPoint, MAP_DIRECTION _eDirection)
{
	pNowArrPos	= _pNowPoint;
	pNextArrPos = _pNextPoint;
	
	eDirection = _eDirection;

	float fRotation = 0;
	if (_eDirection == MAP_DIRECTION::TOP)
		fRotation = D3DXToRadian(0);
	else if (_eDirection == MAP_DIRECTION::BOTTOM)
		fRotation = D3DXToRadian(180);
	else if (_eDirection == MAP_DIRECTION::LEFT)
		fRotation = D3DXToRadian(270);
	else if (_eDirection == MAP_DIRECTION::RIGHT)
		fRotation = D3DXToRadian(90);

	gameObject->GetTransform().fRotation = fRotation;
}
void cDoor::OnColliderStay(shared_ptr<cCollider2D> collider)
{
	if (collider->GetObjectName() == L"PlayerBody" && openDoor)
	{
		cGameObject * lpPlayer = collider->gameObject->GetParentObject();
		shared_ptr<cPlayerComponent> spPlayerComponent = lpPlayer->GetComponent<cPlayerComponent>();
		
		if (!(spPlayerComponent->GetOnPortal()))
			return;

		spPlayerComponent->OnPortal();

		switch (eDirection)
		{
		case MAP_DIRECTION::LEFT:
			lpPlayer->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2 + 64 * 6 + 50, WINSIZEY / 2);
			break;
		case MAP_DIRECTION::RIGHT:
			lpPlayer->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2 - 64 * 6 - 50, WINSIZEY / 2);
			break;
		case MAP_DIRECTION::TOP:
			lpPlayer->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2 + 64 * 2 + 50);
			break;
		case MAP_DIRECTION::BOTTOM:
			lpPlayer->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2 - 64 * 2 - 50);
			break;
		}
		MAPMANAGER->ChangeMap(pNextArrPos);
	}
}