#include "DXUT.h"
#include "cExplosions.h"


cExplosions::cExplosions()
	:dwDestroyType(0)
{
}


cExplosions::~cExplosions()
{
}

void cExplosions::Start()
{
	wpSpriteRenderer = AddComponent<cSpriteRenderer>();
}

void cExplosions::Destroy()
{
}

void cExplosions::Update(float ElapsedTime)
{
	if (wpAnimater.lock()->GetFrameEnd())
		gameObject->Destroy();
}

void cExplosions::SetAnimation(shared_ptr<VecTexture> vecTexture)
{
	wpAnimater = AddComponent<cAnimater>();
	wpAnimater.lock()->AddAnimationClip(L"Idle", vecTexture, 0.01);
	wpSpriteRenderer.lock()->SetMidCenter();

}
