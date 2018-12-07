#include "DXUT.h"
#include "cIngame.h"

#include "PopUpScreen.h"

#include "cPlayerComponent.h"
#include "cPlayerHead.h"
#include "cPlayerBody.h"
#include "cPlayerShadow.h"
#include "Obstacle.h"
#include "cHpComponent.h"
#include "cMainMenu.h"
#include "cItem.h"



cIngame::cIngame()
{
}


cIngame::~cIngame()
{
}

void cIngame::Init()
{
	AddPlayer();

	MAPMANAGER->Release();
	

	switch (MAPMANAGER->GetStage())
	{
	case E_STAGE01:
		MAPMANAGER->CreateRandomMap(E_STAGE01, L"./Resource/Map/Stage01/");
		SOUNDMANAGER->AddSound(L"Stage1", L"./Resource/Sound/happy.mp3", true);
		SOUNDMANAGER->PlayerSound(L"Stage1", 0.5);
		break;
	case E_STAGE02:
		MAPMANAGER->CreateRandomMap(E_STAGE02, L"./Resource/Map/Stage02/");
		SOUNDMANAGER->AddSound(L"Stage2", L"./Resource/Sound/battleThemeA.mp3", true);
		SOUNDMANAGER->PlayerSound(L"Stage2", 0.5);
		break;
	}
	//AddMonster();

	//cGameObject * object = new cGameObject(L"Obstacle");
	//object->AddComponent<Obstacle>();
	//OBJECTMANAGER->AddObject(object);

	cGameObject * object = new cGameObject(L"hpbar");
	object->AddComponent<cHpComponent>()->Init(OBJECTMANAGER->FindObject(L"Player"));
	OBJECTMANAGER->AddObject(object);

	pauseScreen = new cGameObject(L"PauseScreen");
	pauseScreen->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2);
	pauseScreen->AddComponent<PopUpScreen>()->Init(1, L"./Resource/Texture/UI/Pause/Pause.png");
	pauseScreen->GetComponent<PopUpScreen>()->ButtonInit(0, L"./Resource/Texture/UI/Pause/exit", L"exit", 650, 390, Quit);
	pauseScreen->GetComponent<PopUpScreen>()->ButtonInit(1, L"./Resource/Texture/MainScene/HowtoX/Howto", L"Howto_Pause", 900, 550, [&]() {Restart(pauseScreen); });
	pauseScreen->GetComponent<cSpriteRenderer>()->SetMidCenter();
	pauseScreen->SetDrawingOrder(1);
	pauseScreen->SetActive(false);
	OBJECTMANAGER->AddObject(pauseScreen);

}
void cIngame::Release()
{
	MAPMANAGER->Release();
	OBJECTMANAGER->Reset();
	SOUNDMANAGER->StopSound(L"Stage1");
	SOUNDMANAGER->StopSound(L"Stage2");
}
void cIngame::Update(float ElapseTime)
{
	if (KEYDOWN(VK_ESCAPE))
	{
		pauseScreen->SetActive(true);
		pauseScreen->GetComponent<PopUpScreen>()->ButtonSetActive(true);
	}
	if(pauseScreen->GetActive())
		ElapseTime = 0;

	OBJECTMANAGER->Update(ElapseTime);
	COLLIDERMANAGER->Update();
	MAPMANAGER->Update();
}
void cIngame::Render()
{
	OBJECTMANAGER->Render();
}

void cIngame::AddPlayer()
{
	cGameObject* Player(new cGameObject(L"Player", L"Player"));
	OBJECTMANAGER->AddObject(Player);
	Player->AddComponent<cPlayerComponent>();

	cGameObject* PlayerShadow(new cGameObject(L"PlayerShadow", L"Player", Player));
	OBJECTMANAGER->AddObject(PlayerShadow);
	PlayerShadow->AddComponent<cPlayerShadow>();

	cGameObject* PlayerBody(new cGameObject(L"PlayerBody", L"Player", Player));
	OBJECTMANAGER->AddObject(PlayerBody);
	PlayerBody->AddComponent<cPlayerBody>();

	cGameObject* PlayerHead(new cGameObject(L"PlayerHead", L"Player", Player));
	OBJECTMANAGER->AddObject(PlayerHead);
	PlayerHead->AddComponent<cPlayerHead>();

	Player->GetComponent<cPlayerComponent>()->SetHeadBodyObject(PlayerHead, PlayerBody);

}
void Quit()
{
	SCENEMANAGER->ChangeScene(L"MainMenu");
}

void Restart(cGameObject *popUp)
{
	popUp->GetComponent<PopUpScreen>()->ButtonSetActive(false);
	popUp->SetActive(false);
}
