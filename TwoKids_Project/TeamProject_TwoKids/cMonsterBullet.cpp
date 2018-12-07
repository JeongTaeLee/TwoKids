#include "DXUT.h"
#include "cMonsterBullet.h"


#include "cPlayerComponent.h"


cMonsterBullet::cMonsterBullet()
{
}


cMonsterBullet::~cMonsterBullet()
{
}

void cMonsterBullet::Start()
{
	cBulletBase::Start();
	iDamage = 1;
	
}

void cMonsterBullet::Update(float ElapsedTime)
{
	cBulletBase::Update(ElapsedTime);

}

void cMonsterBullet::OnTriggerStay(shared_ptr<cCollider2D> collider)
{
	if (collider->GetTag() != L"Monsters" && collider->GetTag() != L"MonsterBullet" && collider->GetTag() != L"PlayerBullet")
	{
		if (collider->GetObjectName() == L"Player")
		{
			collider->GetComponent<cPlayerComponent>()->AddHurt(iDamage, D3DXVECTOR2(0, 0));
		}
		gameObject->Destroy();
	}
}
