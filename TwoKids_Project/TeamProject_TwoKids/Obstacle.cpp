#include "DXUT.h"
#include "Obstacle.h"


Obstacle::Obstacle()
{
}


Obstacle::~Obstacle()
{
}

void Obstacle::Start()
{
	GetTransform().vPos = D3DXVECTOR2(WINSIZEX/2,WINSIZEY/2);

	shared_ptr<cSpriteRenderer> renderer = AddComponent<cSpriteRenderer>();
	renderer->SetTexture(MyAddTexture(L"Obstacle", L"./Resource/Texture/Obstacle.png"));
	renderer->SetMidCenter();

	shared_ptr<cCollider2D> collider = AddComponent<cCollider2D>();
	collider->SetColliderRect({ 0, 0, 110, 50});
	collider->SetColliderPos(D3DXVECTOR2(-1, 31));

	//AddComponent<cRigidBody>();
}

void Obstacle::Destroy()
{
}

void Obstacle::Update(float ElapsedTime)
{
}

void Obstacle::Receive(const wstring & key)
{
}
