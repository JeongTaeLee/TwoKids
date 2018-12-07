#include "DXUT.h"
#include "cPlayerShadow.h"


cPlayerShadow::cPlayerShadow()
{
}


cPlayerShadow::~cPlayerShadow()
{
}

void cPlayerShadow::Start()
{
	GetTransform().vPos = D3DXVECTOR2(0, 30);
	
	shared_ptr<cSpriteRenderer> renderer = AddComponent<cSpriteRenderer>();

	renderer->SetTexture(MyAddTexture(L"PlayerShadow", L"./Resource/Texture/Player/PlayerShadow.png"));
	renderer->SetMidCenter();

	gameObject->SetDrawingOrder(-1);
}
