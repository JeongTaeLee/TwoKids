#include "DXUT.h"
#include "cMonsterDeath.h"

#include "cIntro.h"

cMonsterDeath::cMonsterDeath()
{
}


cMonsterDeath::~cMonsterDeath()
{
}

void cMonsterDeath::Start()
{
	AddComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"MonsteDeath", L"./Resource/Texture/MonsterDeath.png"));
	GetComponent<cSpriteRenderer>()->SetMidCenter();
	GetComponent<cSpriteRenderer>()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 0));
	gameObject->SetDrawingOrder(2);
	alpha = 0;

	delay = 1.0f;
}

void cMonsterDeath::Update(float ElapsedTime)
{
	if (delay <= 0)
		gameObject->Destroy();
	else
		delay -= ElapsedTime;
	Lerp<float>(&alpha, 255.0f, 0.1f);
	GetComponent<cSpriteRenderer>()->SetColor(D3DCOLOR_RGBA(255, 255, 255, (int)alpha));
}
