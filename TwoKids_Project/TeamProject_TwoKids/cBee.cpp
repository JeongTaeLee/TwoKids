#include "DXUT.h"
#include "cBee.h"


cBee::cBee()
{
}


cBee::~cBee()
{
}

void cBee::Start()
{
	cMonsterComponent::Start();

	fMonsterHp		= 5;
	fMonsterSpeed	= 100;

	wpCollider2D.lock()->SetColliderRect({ 0, 0, 50, 50 });
	wpAnimater.lock()->AddAnimationClip(L"front", MyAddVecTexture(L"Bee_front", L"./Resource/Texture/Monster/Stage01_Monster/Bee/front/bee_front%02d.png", 1, 4), 0.1);
	wpAnimater.lock()->AddAnimationClip(L"back", MyAddVecTexture(L"Bee_back", L"./Resource/Texture/Monster/Stage01_Monster/Bee/back/bee_back%02d.png", 1, 4), 0.1);
	wpAnimater.lock()->AddAnimationClip(L"left", MyAddVecTexture(L"Bee_left", L"./Resource/Texture/Monster/Stage01_Monster/Bee/left/bee_left%02d.png", 1, 4), 0.1);
	wpAnimater.lock()->AddAnimationClip(L"right", MyAddVecTexture(L"Bee_right", L"./Resource/Texture/Monster/Stage01_Monster/Bee/right/bee_right%02d.png", 1, 4), 0.1);

	wpSpriteRenderer.lock()->SetMidCenter();

	SetRandomDirection();
}

void cBee::Update(float ElapsedTime)
{
	cMonsterComponent::BasicMove(ElapsedTime);
	cMonsterComponent::BasicAttack(ElapsedTime);
}

