#include "DXUT.h"
#include "cMonsterComponent.h"

#include "cBulletBase.h"
#include "cMap.h"
#include "cMonsterBullet.h"
#include "cMonsterDeath.h"

cMonsterComponent::cMonsterComponent()
	:lpNowMap(nullptr), fMonsterHp(0.f), fMonsterSpeed(0.f), fAttackElapsed(0), fAttackDelay(0)
{
	fAttackDelay = GetRandomNumber(2, 3);
}

cMonsterComponent::~cMonsterComponent()
{
}

void cMonsterComponent::Start()
{
	lpPlayer = OBJECTMANAGER->FindObject(L"Player");

	wpSpriteRenderer = AddComponent<cSpriteRenderer>();
	wpCollider2D = AddComponent<cCollider2D>();	
	wpRigidBody = AddComponent<cRigidBody>();
	wpAnimater = AddComponent<cAnimater>();

	eMonsterDir = MONSTERDIRECTION::E_MDIR_NONE;
	vDirection = D3DXVECTOR2(-1, 0);
}

void cMonsterComponent::Update(float ElapsedTime)
{
}

void cMonsterComponent::BasicMove(float ElapsedTime)
{
	GetTransform().translation(vDirection * (fMonsterSpeed * ElapsedTime));
}

void cMonsterComponent::BasicAttack(float ElapsedTime)
{
	fAttackElapsed += ElapsedTime;

	if (fAttackElapsed >= fAttackDelay)
	{
		fAttackElapsed = 0;

		cGameObject * object = new cGameObject(L"MonsterBullet", L"MonsterBullet", nullptr);
		shared_ptr<cMonsterBullet> spBulletBase = object->AddComponent<cMonsterBullet>();

		D3DXVECTOR2 dir = lpPlayer->GetTransform().vPos - GetTransform().vPos;
		D3DXVec2Normalize(&dir, &dir);

		spBulletBase->SetTexture(MyAddTexture(L"MonsterBullet", L"./Resource/Texture/Monster/MonsterBullet.png"));
		spBulletBase->SetBulletInfo(GetTransform().vPos, dir, 300, 1);
		spBulletBase->SetCollider({0, 0, 10, 10});

		OBJECTMANAGER->AddObject(object);

		fAttackDelay = GetRandomNumber(2, 3);
	}
}

void cMonsterComponent::OnColliderStay(shared_ptr<cCollider2D> collider)
{
	SetRandomDirection();
}

void cMonsterComponent::OnTriggerStay(shared_ptr<cCollider2D> collider)
{
	if (collider->GetTag() == L"PlayerBullet")
	{
		fMonsterHp -= collider->GetComponent<cBulletBase>()->GetDamage();

		if (fMonsterHp <= 0)
		{
			lpNowMap->GetComponent<cMap>()->DestroyMonster(gameObject);

			cGameObject *deathMotion = new cGameObject();
			deathMotion->AddComponent<cMonsterDeath>();
			deathMotion->GetTransform().vPos = GetTransform().vPos;
			OBJECTMANAGER->AddObject(deathMotion);
		}
	}
}

void cMonsterComponent::SetRandomDirection()
{
	MONSTERDIRECTION tempDirection;
	
	do
	{
		tempDirection = (MONSTERDIRECTION)GetRandomNumber(E_MDIR_UP, E_MDIR_RIGHT);
	} while (tempDirection == eMonsterDir);

	eMonsterDir = tempDirection;

	switch (eMonsterDir)
	{
	case MONSTERDIRECTION::E_MDIR_LEFT:
		wpAnimater.lock()->ChangeAnimation(L"left");
		vDirection = D3DXVECTOR2(-1, 0);
		break;

	case MONSTERDIRECTION::E_MDIR_RIGHT:
		wpAnimater.lock()->ChangeAnimation(L"right");
		vDirection = D3DXVECTOR2(1, 0);
		break;

	case MONSTERDIRECTION::E_MDIR_DOWN:
		wpAnimater.lock()->ChangeAnimation(L"front");
		vDirection = D3DXVECTOR2(0, 1);
		break;
	case MONSTERDIRECTION::E_MDIR_UP:
		wpAnimater.lock()->ChangeAnimation(L"back");
		vDirection = D3DXVECTOR2(0, -1);
		break;
	}
}

void cMonsterComponent::SetMonster(const D3DXVECTOR2 & vStartPos, cGameObject * _lpNowMap)
{
	lpNowMap = _lpNowMap;
	GetTransform().vPos = vStartPos;
}
