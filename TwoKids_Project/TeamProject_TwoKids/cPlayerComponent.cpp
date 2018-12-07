#include "DXUT.h"
#include "cPlayerComponent.h"

#include "cPlayerHead.h"
#include "cPlayerBody.h"

#include "cMonsterComponent.h"
#include "cItem.h"
#define ZERO_INIT 0

cPlayerComponent::cPlayerComponent()
	:lpHeadObject(nullptr), lpBodyObject(nullptr),
	eCharState(E_CHARSTATE_IDLE), dwPortalDelay(0), bOnPortal(true)
{
}


cPlayerComponent::~cPlayerComponent()
{
}

void cPlayerComponent::Start()
{
	GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2, WINSIZEY/ 2);

	shared_ptr<cCollider2D> collider = AddComponent<cCollider2D>();
	collider->SetColliderRect({ 0, 0, 46, 51 });
	collider->SetTrigger(true);

	AddComponent<cRigidBody>();

	hurtDelay = ZERO_INIT;
	fixupDelay = 1.5f;

	hp = 6;
	maxHp = 6;
	isNoneDie = false;
	speed = 200;
}

void cPlayerComponent::Update(float ElapsedTime)
{

	InputKey(ElapsedTime);

	DWORD rgba = D3DCOLOR_RGBA(255, 255, 255, 255);
	if (hurtDelay > ZERO_INIT)
	{
		hurtDelay -= ElapsedTime;
		
		if ((int)(hurtDelay * 10) % 5 >= 3)
		{
			rgba = D3DCOLOR_RGBA(255, 255, 255, 100);
		}
		else
		{
			rgba = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	}
	else
	{
		rgba = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	lpBodyObject->GetComponent<cSpriteRenderer>()->SetColor(rgba);
	lpHeadObject->GetComponent<cSpriteRenderer>()->SetColor(rgba);

	if (!bOnPortal)
	{
		if (timeGetTime() >= dwPortalDelay)
		{
			bOnPortal		= true;
			dwPortalDelay	= 0;
		}
	}
	if (hp < 1)
	{
		SCENEMANAGER->ChangeScene(L"LoseScene");
	}
	if (INPUTMANAGER->GetKeyDown(VK_F2))
		isNoneDie = true;
}

void cPlayerComponent::OnTriggerStay(shared_ptr<cCollider2D> collider)
{
	if (collider->GetTag() == L"Monsters" && hurtDelay <= ZERO_INIT)
	{
		D3DXVECTOR2 tempVec2 = GetTransform().vPos - collider->GetTransform().vPos;

		D3DXVec2Normalize(&tempVec2, &tempVec2);
		AddHurt(1, tempVec2);
	}
}

void cPlayerComponent::InputKey(float ElapsedTime)
{
	D3DXVECTOR2 MoveVector = D3DXVECTOR2(0, 0);


	bool bBehavior = false;

	if (KEYPRESS('W') || KEYPRESS('S') || KEYPRESS('A') || KEYPRESS('D'))
	{
		
		
		bBehavior = true;

		if (KEYPRESS('W'))
		{
			MoveVector.y = -speed;
			eCharState = CHARSTATE::E_CHARSTATE_UP;
		}
		if (KEYPRESS('S'))
		{
			MoveVector.y = speed;
			eCharState = CHARSTATE::E_CHARSTATE_DOWN;
		}
		if (KEYPRESS('A'))
		{
			MoveVector.x = -speed;
			eCharState = CHARSTATE::E_CHARSTATE_LEFT;
		}
		if (KEYPRESS('D'))
		{
			MoveVector.x = speed;
			eCharState = CHARSTATE::E_CHARSTATE_RIGHT;
		}
	}

	if (KEYPRESS(VK_LEFT) || KEYPRESS(VK_RIGHT) || KEYPRESS(VK_DOWN) || KEYPRESS(VK_UP))
	{
		/*
		if(KEYPRESS(VK_LEFT))
			wpPlayerHead.lock()->C
		*/
	}


	if (bBehavior == false)
		eCharState = CHARSTATE::E_CHARSTATE_IDLE;

	GetTransform().translation(MoveVector * DXUTGetElapsedTime());
}

void cPlayerComponent::SetHeadBodyObject(cGameObject* _lpHeadObject, cGameObject* _lpBodyObject)
{
	lpHeadObject = _lpHeadObject;
	lpBodyObject = _lpBodyObject;

}

void cPlayerComponent::AddHurt(int damage, D3DXVECTOR2 direction)
{
	if (isNoneDie) return;
	hp -= damage;
	hurtDelay = fixupDelay;
}

void cPlayerComponent::SetItemAbility(ITEM_KIND kind)
{
	switch (kind)
	{
	case CLOVER:
		lpHeadObject->GetComponent<cPlayerHead>()->fireDelay += 100;
		lpHeadObject->GetComponent<cPlayerHead>()->filreDamage += 1;
		break;
	case COFFE:
		lpHeadObject->GetComponent<cPlayerHead>()->fireDelay -= 100;
		break;
	case SHOES:
		speed += 100;
		break;
	case MILK:
		lpHeadObject->GetComponent<cPlayerHead>()->fireDelay -= 50;
		lpHeadObject->GetComponent<cPlayerHead>()->filreDamage += 1;
		lpHeadObject->GetComponent<cPlayerHead>()->bulletSpeed -= 200;
		break;
	default:
		break;
	}
}

void cPlayerComponent::OnPortal()
{
	bOnPortal = false;
	dwPortalDelay = timeGetTime() + 1000;
}
