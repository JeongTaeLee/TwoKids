#include "DXUT.h"
#include "cSlime.h"

#include "cMonsterBullet.h"


cSlime::cSlime()
{
}


cSlime::~cSlime()
{
}

void cSlime::Start()
{
	cMonsterComponent::Start();

	fMonsterHp = 5;
	fMonsterSpeed = 0;

	wpCollider2D.lock()->SetColliderRect({ 0, 0, 63, 63 });

	wpAnimater.lock()->AddAnimationClip(L"front",
		MyAddVecTexture(L"Slime_front", L"./Resource/Texture/Monster/Stage03_Monster/Slime/front/slime_front%02d.png", 1, 4), 0.1);

	wpSpriteRenderer.lock()->SetMidCenter();

	bulletDelay = 0.0f;
	lpPlayer = OBJECTMANAGER->FindObject(L"Player");
}

void cSlime::Update(float ElaspedTime)
{
	cMonsterComponent::Update(ElaspedTime);
	float tempX = lpPlayer->GetTransform().vPos.x - GetTransform().vPos.x;
	float tempY = lpPlayer->GetTransform().vPos.y - GetTransform().vPos.y;

	float radius = tempX * tempX + tempY * tempY;
	float range = 300;
	if (bulletDelay <= 0.0f && radius < range * range)
	{
		cGameObject *bullet = new cGameObject(L"MonsterBullet", L"MonsterBullet");

		D3DXVECTOR2 tempDir = lpPlayer->GetTransform().vPos - GetTransform().vPos;
		D3DXVec2Normalize(&tempDir, &tempDir);
		bullet->AddComponent<cMonsterBullet>()->SetBulletInfo(GetTransform().vPos, tempDir, 200, 1);
		bullet->GetComponent<cMonsterBullet>()->SetTexture(MyAddTexture(L"", L"./Resource/Texture/Bullet/MonsterBullet.png"));
		bullet->GetComponent<cMonsterBullet>()->SetCollider({0, 0, 20, 20});

		bulletDelay = 1.5f;
		OBJECTMANAGER->AddObject(bullet);
	}
	else
	{
		bulletDelay -= ElaspedTime;
	}
}
