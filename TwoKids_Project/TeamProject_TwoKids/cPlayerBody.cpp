#include "DXUT.h"
#include "cPlayerBody.h"

#include "cPlayerComponent.h"
#include "cBulletBase.h"

cPlayerBody::cPlayerBody()
{
}


cPlayerBody::~cPlayerBody()
{
}

void cPlayerBody::Start()
{
	GetTransform().vPos = D3DXVECTOR2(0, -13);

	wpSpriteRenderer	= AddComponent<cSpriteRenderer>();
	wpAnimater			= AddComponent<cAnimater>();

	shared_ptr<cCollider2D> collider = AddComponent<cCollider2D>();
	collider->SetColliderRect({ 0, 0, 40, 20 });
	collider->SetColliderPos(D3DXVECTOR2(0, 40));

	AddComponent<cRigidBody>();


	wpAnimater.lock()->AddAnimationClip(L"Idle", MyAddVecTexture(L"Player_Body_Idle", L"./Resource/Texture/Player/Body_Front/%d.png", 1, 2), 0.05);
	wpAnimater.lock()->AddAnimationClip(L"Front", MyAddVecTexture(L"Player_Body_Front", L"./Resource/Texture/Player/Body_Front/%d.png", 1, 4), 0.05);
	wpAnimater.lock()->AddAnimationClip(L"Back", MyAddVecTexture(L"Player_Body_Back", L"./Resource/Texture/Player/Body_Back/%d.png", 1, 4), 0.05);
	wpAnimater.lock()->AddAnimationClip(L"Left", MyAddVecTexture(L"Player_Body_Left", L"./Resource/Texture/Player/Body_Left/%d.png", 1, 4), 0.05);
	wpAnimater.lock()->AddAnimationClip(L"Right", MyAddVecTexture(L"Player_Body_Right", L"./Resource/Texture/Player/Body_Right/%d.png", 1, 4), 0.05);
	wpAnimater.lock()->SetLockAnimation(0, true);
	wpSpriteRenderer.lock()->SetMidCenter();
	


	wpPlayerComponent = gameObject->GetParentObject()
		->GetComponent<cPlayerComponent>();
}


void cPlayerBody::Update(float ElapsedTime)
{
	GetTransform().vPos = D3DXVECTOR2(0, -13);

	if (wpPlayerComponent.lock()->eCharState == CHARSTATE::E_CHARSTATE_IDLE)
	{
		wpAnimater.lock()->ChangeAnimation(L"Idle");
		wpAnimater.lock()->SetLockAnimation(0, true);
	}
	if (wpPlayerComponent.lock()->eCharState == CHARSTATE::E_CHARSTATE_UP)
		wpAnimater.lock()->ChangeAnimation(L"Back");
	if (wpPlayerComponent.lock()->eCharState == CHARSTATE::E_CHARSTATE_DOWN)
		wpAnimater.lock()->ChangeAnimation(L"Front");
	if (wpPlayerComponent.lock()->eCharState == CHARSTATE::E_CHARSTATE_LEFT)
	{
		// Left 동작을 이 될 경우 이미지 문제때문에 3픽셀을 밀어야 중앙으로 정렬됨
		GetTransform().vPos = D3DXVECTOR2(3, -13);
		wpAnimater.lock()->ChangeAnimation(L"Left");
	}

	if (wpPlayerComponent.lock()->eCharState == CHARSTATE::E_CHARSTATE_RIGHT)
		wpAnimater.lock()->ChangeAnimation(L"Right");
}
