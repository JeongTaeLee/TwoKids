#include "DXUT.h"
#include "cBulletBase.h"
#include "cExplosions.h"

cBulletBase::cBulletBase()
{
}


cBulletBase::~cBulletBase()
{
}

void cBulletBase::Start()
{
	wpSpriteRenderer = AddComponent<cSpriteRenderer>();
}

void cBulletBase::Update(float ElapsedTime)
{
	GetTransform().translation(vDirection * (fSpeed * ElapsedTime));
	
	if (IsOutMap())
		gameObject->Destroy();
}
bool cBulletBase::IsOutMap()
{
	D3DXVECTOR2 pos = D3DXVECTOR2(GetTransform().GetWorldMatrix()._41, GetTransform().GetWorldMatrix()._42);

	return (pos.x < 0 || pos.x > 1280 ||
		pos.y < 0 || pos.y > 720);
}
void cBulletBase::SetBulletInfo(const D3DXVECTOR2 & pos, const D3DXVECTOR2 & _vDirection, float _fSpeed, int _fDamage)
{
	GetTransform().vPos = pos;

	vDirection	= _vDirection;
	fSpeed		= _fSpeed;
	iDamage = _fDamage;

	GetTransform().vScale = { _fDamage * 1.0f , _fDamage * 1.0f };
}

void cBulletBase::SetAnimation(shared_ptr<VecTexture> animations)
{
	AddComponent<cAnimater>()
		->AddAnimationClip(L"Idle", animations, 0.05);
	wpSpriteRenderer.lock()->SetMidCenter();
}

void cBulletBase::SetCollider(const RECT & reRect)
{
	shared_ptr<cCollider2D> collider = AddComponent<cCollider2D>();
	collider->SetTrigger(true);
	collider->SetColliderRect(reRect);
}

void cBulletBase::SetTexture(shared_ptr<sTexture> texture)
{
	wpSpriteRenderer.lock()->SetTexture(texture);
	wpSpriteRenderer.lock()->SetMidCenter();
}

void cBulletBase::OnTriggerStay(shared_ptr<cCollider2D> collider)
{
	if (collider->GetTag() != L"Player" && collider->GetTag() != L"Bullet" && collider->GetTag() != L"MonsterBullet")
	{
		cGameObject* object = OBJECTMANAGER->AddObject(new cGameObject);
		object->AddComponent<cExplosions>()
			->SetAnimation(MyAddVecTexture(L"BulletExplosion", L"./Resource/Texture/BulletExplosion/effect%d.png", 1, 3));
		object->GetTransform().vPos = D3DXVECTOR2(GetTransform().GetWorldMatrix()._41, 
			GetTransform().GetWorldMatrix()._42);

		gameObject->Destroy();
	}
}
