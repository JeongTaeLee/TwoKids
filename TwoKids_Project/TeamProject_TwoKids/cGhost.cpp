#include "DXUT.h"
#include "cGhost.h"


cGhost::cGhost()
{
}


cGhost::~cGhost()
{
}

void cGhost::Start()
{
	cMonsterComponent::Start();

	fMonsterHp = 5;
	fMonsterSpeed = 100;

	wpCollider2D.lock()->SetColliderRect({ 0, 0, 50, 50 });
	wpAnimater.lock()->AddAnimationClip(L"front", MyAddVecTexture(L"Ghost_front", L"./Resource/Texture/Monster/Stage03_Monster/Ghost/front/Ghost_front%02d.png", 1, 4), 0.1);
	wpAnimater.lock()->AddAnimationClip(L"back", MyAddVecTexture(L"Ghost_back", L"./Resource/Texture/Monster/Stage03_Monster/Ghost/back/Ghost_back%02d.png", 1, 4), 0.1);


	wpSpriteRenderer.lock()->SetMidCenter();

	SetRandomDirection();
}

void cGhost::Update(float ElaspedTime)
{
	cMonsterComponent::BasicMove(ElaspedTime);
	cMonsterComponent::BasicAttack(ElaspedTime);
}
