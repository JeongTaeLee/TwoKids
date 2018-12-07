#include "DXUT.h"
#include "cPlayerHead.h"
#include "cPlayerComponent.h"

#include "cBulletBase.h"

cPlayerHead::cPlayerHead()
{
}


cPlayerHead::~cPlayerHead()
{
}

void cPlayerHead::Start()
{
	GetTransform().vPos = D3DXVECTOR2(0, -10);

	wpSpriteRenderer	=	AddComponent<cSpriteRenderer>();
	wpAnimater			=	AddComponent<cAnimater>();
	
	wpAnimater.lock()->AddAnimationClip(L"Front", MyAddVecTexture(L"Player_Head_Front", L"./Resource/Texture/Player/Head/%d.png", 1, 2)	, 0.4);
	wpAnimater.lock()->AddAnimationClip(L"Left"	, MyAddVecTexture(L"Player_Head_Left", L"./Resource/Texture/Player/Head/%d.png", 3, 4)	, 0.4);
	wpAnimater.lock()->AddAnimationClip(L"Back"	, MyAddVecTexture(L"Player_Head_Back", L"./Resource/Texture/Player/Head/%d.png", 5, 6)	, 0.4);
	wpAnimater.lock()->AddAnimationClip(L"Right", MyAddVecTexture(L"Player_Head_Right", L"./Resource/Texture/Player/Head/%d.png", 7, 8)	, 0.4);

	wpSpriteRenderer.lock()->SetMidCenter();

	wpPlayerComponent.lock() = gameObject->GetParentObject()
		->GetComponent<cPlayerComponent>();

	FireTime = 0;
	bulletSpeed = 400;
	fireDelay = 300;
	filreDamage = 1;
}

void cPlayerHead::Update(float ElapsedTime)
{
	if (KEYDOWN('U'))
		gameObject->Destroy();

	bool bBehavior = false;


	if (KEYPRESS(VK_UP) || KEYPRESS(VK_DOWN) || KEYPRESS(VK_LEFT) || KEYPRESS(VK_RIGHT))
	{
		D3DXVECTOR2 Position;
		
		bBehavior = true;

		if (KEYPRESS(VK_UP))
		{
			Position.x = GetTransform().GetWorldMatrix()._41;
			Position.y = GetTransform().GetWorldMatrix()._42 - 40;

			wpAnimater.lock()->ChangeAnimation(L"Back");
			CreateBullet(D3DXVECTOR2(0, -1), Position);
		}
		if (KEYPRESS(VK_DOWN))
		{
			Position.x = GetTransform().GetWorldMatrix()._41;
			Position.y = GetTransform().GetWorldMatrix()._42 + 40;

			wpAnimater.lock()->ChangeAnimation(L"Front");
			CreateBullet(D3DXVECTOR2(0, 1), Position);
		}
		if (KEYPRESS(VK_LEFT))
		{
			Position.x = GetTransform().GetWorldMatrix()._41 - 30;
			Position.y = GetTransform().GetWorldMatrix()._42;

			wpAnimater.lock()->ChangeAnimation(L"Left");
			CreateBullet(D3DXVECTOR2(-1, 0), Position);
		}
		if (KEYPRESS(VK_RIGHT))
		{
			Position.x = GetTransform().GetWorldMatrix()._41 + 30;
			Position.y = GetTransform().GetWorldMatrix()._42;

			wpAnimater.lock()->ChangeAnimation(L"Right");
			CreateBullet(D3DXVECTOR2(1, 0), Position);

		}
	}

	if (!bBehavior)
		wpAnimater.lock()->ChangeAnimation(L"Front");

}

void cPlayerHead::CreateBullet(const D3DXVECTOR2 & Direction, const D3DXVECTOR2 & Position)
{
	if (FireTime > timeGetTime())
		return;

	FireTime = timeGetTime() + fireDelay;

	cGameObject * object = OBJECTMANAGER->AddObject(new cGameObject(L"Bullet" , L"PlayerBullet", nullptr));

	shared_ptr<cBulletBase> bullet = object->AddComponent<cBulletBase>();

	bullet->SetBulletInfo(Position, Direction, bulletSpeed, filreDamage);
	bullet->SetAnimation(MyAddVecTexture(L"Bullet01", L"./Resource/Texture/Bullet/clover%d.png", 1, 8));
	bullet->SetCollider({ 0,0, 20, 20 });
}
