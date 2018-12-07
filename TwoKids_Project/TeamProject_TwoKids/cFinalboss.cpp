#pragma once

#include "DXUT.h"
#include "cFinalboss.h"
#include "cStageChange.h"
#include "cMonsterBullet.h"

cFinalboss::cFinalboss()
	:fWaveElapsed(0.f), fWaveDelay(1.f), iNextWave(1), fRad(0.f), fRad_step(D3DXToRadian(10)), iAttackCount(0)
{
}


cFinalboss::~cFinalboss()
{
	if (fMonsterHp < 1)
	{
		cGameObject *object = new cGameObject();
		object->AddComponent<cStageChange>()->SetStage1(false);
		object->GetTransform().vPos = GetTransform().vPos;

		OBJECTMANAGER->AddObject(object);
	}
}

void cFinalboss::Start()
{
	cMonsterComponent::Start();

	fMonsterHp = 30;
	fMonsterSpeed = 50;

	wpCollider2D.lock()->SetColliderRect({ 0, 0, 100, 100 });
	wpAnimater.lock()->AddAnimationClip(L"front", MyAddVecTexture(L"Finalboss_front", L"./Resource/Texture/Monster/Stage03_Monster/Finalboss/front/finalboss_front%02d.png", 1, 4), 0.1);
	wpAnimater.lock()->AddAnimationClip(L"back", MyAddVecTexture(L"Finalboss_front", L"./Resource/Texture/Monster/Stage03_Monster/Finalboss/front/finalboss_back%02d.png", 1, 4), 0.1);

	wpSpriteRenderer.lock()->SetMidCenter();

	SetRandomDirection();
}

void cFinalboss::Update(float ElapsedTime)
{

	cMonsterComponent::BasicMove(ElapsedTime);

	Attack(ElapsedTime);

}

void cFinalboss::Attack(float ElapsedTime)
{
	fWaveElapsed += ElapsedTime;




	if (fWaveElapsed > fWaveDelay)
	{
		switch (iNextWave)
		{
		case 1:
			Wave01();
			break;
		case 2:
			Wave02();
			break;
		}
	}
}

void cFinalboss::Wave01()
{
	vDirection = D3DXVECTOR2(0, 0);
	eMonsterDir = E_MDIR_NONE;

	fRad_step = (D3DX_PI * 2) / 30;

	if (iAttackCount < 30)
	{
		float cos = cosf(fRad), sin = sinf(fRad);

		CreateBullet(GetTransform().vPos, D3DXVECTOR2(cos, sin), 200);

		fRad += fRad_step;

		iAttackCount++;
		fWaveDelay = 0.01f;
		fWaveElapsed = 0.f;
	}
	else
	{
		iAttackCount = 0;
		fWaveElapsed = 0.f;
		fWaveDelay = 2;
		fRad = 0.f;


		SetRandomDirection();

		iNextWave = 2;
	}
}

void cFinalboss::Wave02()
{
	vDirection = D3DXVECTOR2(0, 0);
	eMonsterDir = E_MDIR_NONE;

	fRad_step = (D3DX_PI * 2) / 15;

	if (iAttackCount < 15)
	{
		float cos = cosf(fRad), sin = sinf(fRad);

		CreateBullet(GetTransform().vPos, D3DXVECTOR2(cos, sin), 200);

		cos = cosf(fRad + D3DXToRadian(180)); sin = sinf(fRad + D3DXToRadian(180));
		CreateBullet(GetTransform().vPos, D3DXVECTOR2(cos, sin), 200);

		fRad += fRad_step;

		iAttackCount++;
		fWaveDelay = 0.01f;
		fWaveElapsed = 0.f;
	}
	else
	{
		iAttackCount = 0;
		fWaveElapsed = 0.f;
		fWaveDelay = 2;
		fRad = 0.f;

		SetRandomDirection();
		iNextWave = 1;
	}
}


void cFinalboss::CreateBullet(const D3DXVECTOR2 & pos, const D3DXVECTOR2 & dir, float speed)
{
	cGameObject *bullet = new cGameObject(L"MonsterBullet", L"MonsterBullet");
	shared_ptr<cMonsterBullet> bulletCom = bullet->AddComponent<cMonsterBullet>();

	bulletCom->SetTexture(MyAddTexture(L"MonsterBullet", L"./Resource/Texture/Monster/MonsterBullet.png"));
	bulletCom->SetBulletInfo(pos, dir, speed, 1);
	bulletCom->SetCollider({ 0, 0, 10, 10 });

	OBJECTMANAGER->AddObject(bullet);
}
