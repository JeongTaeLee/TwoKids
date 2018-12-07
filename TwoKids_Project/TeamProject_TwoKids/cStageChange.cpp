#include "DXUT.h"
#include "cStageChange.h"

#include "cIngame.h"

cStageChange::cStageChange()
{
}


cStageChange::~cStageChange()
{
}

void cStageChange::Start()
{
	AddComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"StageChange", L"./Resource/Texture/MapImage/Hellgate.png"));
	GetComponent<cSpriteRenderer>()->SetMidCenter();
	AddComponent<cCollider2D>()->SetColliderRect({0, 0, 70, 30});
	if(isstage1)
		MAPMANAGER->SetStage(E_STAGE02);
	else
		MAPMANAGER->SetStage(E_STAGE01);
}

void cStageChange::Update(float ElapsedTime)
{
}

void cStageChange::OnTriggerStay(shared_ptr<cCollider2D> collider)
{
	if (collider->GetTag() == L"Player")
	{
		if (isstage1)
			SCENEMANAGER->ChangeScene(L"Ingame");
		else
			SCENEMANAGER->ChangeScene(L"Intro");
	}
}
