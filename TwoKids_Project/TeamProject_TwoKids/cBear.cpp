#include "DXUT.h"
#include "cBear.h"


cBear::cBear()
{
}


cBear::~cBear()
{
}

void cBear::Start()
{
	cMonsterComponent::Start();

	fMonsterHp = 10;
	fMonsterSpeed = 50;

	wpCollider2D.lock()->SetColliderRect({ 0, 0, 50, 100});
	wpAnimater.lock()->AddAnimationClip(L"front", MyAddVecTexture(L"Bear_front", L"./Resource/Texture/Monster/Stage01_Monster/Bear/front/Bear_front%02d.png", 1, 4), 0.1);
	wpAnimater.lock()->AddAnimationClip(L"back", MyAddVecTexture(L"Bear_back", L"./Resource/Texture/Monster/Stage01_Monster/Bear/back/Bear_back%02d.png", 1, 4), 0.1);
	wpAnimater.lock()->AddAnimationClip(L"left", MyAddVecTexture(L"Bear_left", L"./Resource/Texture/Monster/Stage01_Monster/Bear/left/Bear_left%02d.png", 1, 4), 0.1);
	wpAnimater.lock()->AddAnimationClip(L"right", MyAddVecTexture(L"Bear_right", L"./Resource/Texture/Monster/Stage01_Monster/Bear/right/Bear_right%02d.png", 1, 4), 0.1);

	wpSpriteRenderer.lock()->SetMidCenter();

	SetRandomDirection();
}

void cBear::Update(float ElaspedTime)
{
	cMonsterComponent::BasicMove(ElaspedTime);
	cMonsterComponent::BasicAttack(ElaspedTime);
}
