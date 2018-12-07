#include "DXUT.h"
#include "cLoseScene.h"

#include "Button.h"


cLoseScene::cLoseScene()
{
}


cLoseScene::~cLoseScene()
{
}

void goIntroScene()
{
	SCENEMANAGER->ChangeScene(L"Intro");
}

void cLoseScene::Init()
{
	lose = new cGameObject();
	lose->AddComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"lose", L"./Resource/Texture/Lose.png"));
	lose->GetComponent<cSpriteRenderer>()->SetMidCenter();
	lose->GetTransform().vPos = { WINSIZEX / 2, WINSIZEY / 2 };

	OBJECTMANAGER->AddObject(lose);

	cGameObject * xButton = new cGameObject(L"X_Lose");
	xButton->GetTransform().vPos = D3DXVECTOR2(WINSIZEX - 160, WINSIZEY - 100);
	xButton->AddComponent<Button>();
	xButton->GetComponent<Button>()->Init(L"./Resource/Texture/MainScene/HowtoX/Howto", goIntroScene);
	OBJECTMANAGER->AddObject(xButton);
}

void cLoseScene::Release()
{
	OBJECTMANAGER->Reset();
}

void cLoseScene::Update(float ElapseTime)
{
	OBJECTMANAGER->Update(ElapseTime);
}

void cLoseScene::Render()
{
	OBJECTMANAGER->Render();
}
