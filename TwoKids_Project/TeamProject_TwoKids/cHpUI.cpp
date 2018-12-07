#include "DXUT.h"
#include "cHpUI.h"


cHpUI::cHpUI()
{
}


cHpUI::~cHpUI()
{
}

void cHpUI::Start()
{
	wpSpriteRenderer = AddComponent<cSpriteRenderer>();
	wpSpriteRenderer.lock()->SetTexture(MyAddTexture(L"hp", L"./Resource/Texture/UI/HP/hp.png"));
	gameObject->SetDrawingOrder(10);
}

void cHpUI::Update(float ElapsedTime)
{
}

void cHpUI::SetHp(int hp)
{
	switch (hp)
	{
	case 0:
		wpSpriteRenderer.lock()->SetTexture(MyAddTexture(L"hpNone", L"./Resource/Texture/UI/HP/none.png"));
		break;
	case 1:
		wpSpriteRenderer.lock()->SetTexture(MyAddTexture(L"hpHalf", L"./Resource/Texture/UI/HP/half.png"));
		break;
	case 2:
		wpSpriteRenderer.lock()->SetTexture(MyAddTexture(L"hp", L"./Resource/Texture/UI/HP/hp.png"));
		break;
	default:
		break;
	}
}
