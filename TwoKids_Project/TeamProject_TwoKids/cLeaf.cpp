#include "DXUT.h"
#include "cLeaf.h"


cLeaf::cLeaf()
{
}


cLeaf::~cLeaf()
{
}

void cLeaf::Start()
{
	cMonsterComponent::Start();

	fMonsterHp = 5;
	fMonsterSpeed = 100;

	wpCollider2D.lock()->SetColliderRect({ 0, 0, 50, 50 });
	wpAnimater.lock()->AddAnimationClip(L"front", MyAddVecTexture(L"Leaf_front", L"./Resource/Texture/Monster/Stage02_Monster/Leaf/front/leaf_front%02d.png", 1, 4), 0.1);

	wpSpriteRenderer.lock()->SetMidCenter();

	SetRandomDirection();
}

void cLeaf::Update(float ElaspedTime)
{
	cMonsterComponent::BasicAttack(ElaspedTime);
}
