#include "DXUT.h"
#include "cMainMenu.h"

#include "Button.h"

cMainMenu::cMainMenu()
{
}


cMainMenu::~cMainMenu()
{
}

void cMainMenu::Init()
{
	state = 1;

	background = new cGameObject(L"MainMenuBackground");
	background->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2);
	background->AddComponent<cSpriteRenderer>();
	background->GetComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"MainMenuBackGround", L"./Resource/Texture/MainScene/Main_Menu.png"));
	background->GetComponent<cSpriteRenderer>()->SetMidCenter();
	background->GetComponent<cSpriteRenderer>()->SetBeginParameter(D3DXSPRITE_ALPHABLEND);
	OBJECTMANAGER->AddObject(background);

	/*background = AddComponent<cSpriteRenderer>();
	background->SetTexture(MyAddTexture(L"MainMenu", L"./Resource/Texture/MainMenu.png"));
	background->SetMidCenter();
	background->SetBeginParameter(D3DXSPRITE_ALPHABLEND);*/

	cGameObject * settingButton = new cGameObject(L"Credit");
	settingButton->GetTransform().vPos = D3DXVECTOR2(WINSIZEX - 160, WINSIZEY - 100);
	settingButton->AddComponent<Button>();
	settingButton->GetComponent<Button>()->Init(L"./Resource/Texture/MainScene/Credit/Credit", [&]() { OpenSettings(credit); });
	OBJECTMANAGER->AddObject(settingButton);

	cGameObject * bHowto = new cGameObject(L"Howto");
	bHowto->GetTransform().vPos = D3DXVECTOR2(160, WINSIZEY - 100);
	bHowto->AddComponent<Button>();
	bHowto->GetComponent<Button>()->Init(L"./Resource/Texture/MainScene/Howto/Howto", [&]() { ClickHowto(howto); });
	OBJECTMANAGER->AddObject(bHowto);

	cGameObject * exitButton = new cGameObject(L"HowtoX");
	exitButton->GetTransform().vPos = D3DXVECTOR2(WINSIZEX - 80, 50);
	exitButton->AddComponent<Button>();
	exitButton->GetComponent<Button>()->Init(L"./Resource/Texture/MainScene/MainX/X", Exit);
	exitButton->SetDrawingOrder(1);
	OBJECTMANAGER->AddObject(exitButton);

	clover = new cGameObject(L"clover");
	clover->GetTransform().vPos = D3DXVECTOR2( WINSIZEX / 2, WINSIZEY / 2);
	clover->AddComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"Main_Clover", L"./Resource/Texture/MainScene/Clover.png"));
	clover->GetComponent<cSpriteRenderer>()->SetMidCenter();
	clover->SetDrawingOrder(1);
	OBJECTMANAGER->AddObject(clover);

	howto = new cGameObject(L"howto_howto");
	howto->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2);
	howto->AddComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"Howto", L"./Resource/Texture/MainScene/HowtoX/Howto.png"));
	howto->GetComponent<cSpriteRenderer>()->SetMidCenter();
	howto->SetDrawingOrder(2);
	OBJECTMANAGER->AddObject(howto);
	howto->SetActive(false);

	credit = new cGameObject(L"Credit_Credit");
	credit->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2);
	credit->AddComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"Credit", L"./Resource/Texture/MainScene/Credit.png"));
	credit->GetComponent<cSpriteRenderer>()->SetMidCenter();
	credit->SetDrawingOrder(2);
	OBJECTMANAGER->AddObject(credit);
	credit->SetActive(false);

	cloverSpeed = -1;

	SOUNDMANAGER->AddSound(L"MainMenu", L"./Resource/Sound/Rise of spirit.mp3", true);
	SOUNDMANAGER->PlayerSound(L"MainMenu", 0.5);
}

void cMainMenu::Release()
{
	OBJECTMANAGER->Reset();
	SOUNDMANAGER->StopSound(L"MainMenu");
}

void cMainMenu::Update(float ElapseTime)
{
	OBJECTMANAGER->Update(ElapseTime);

	if (KEYDOWN(VK_ESCAPE))
		PostQuitMessage(0);

	if (clover->GetTransform().vPos.y < WINSIZEY / 2 - 40 || clover->GetTransform().vPos.y > WINSIZEY / 2 + 20)
		cloverSpeed = -cloverSpeed;
	clover->GetTransform().vPos.y += cloverSpeed;
	if (KEYDOWN(VK_LBUTTON))
	{
		if (howto->GetActive())
			howto->SetActive(false);
		else if (credit->GetActive())
			credit->SetActive(false);
		else if (!OBJECTMANAGER->FindObject(L"Credit")->GetComponent<Button>()->GetPressed() &&
			!OBJECTMANAGER->FindObject(L"Howto")->GetComponent<Button>()->GetPressed()	&&
			!OBJECTMANAGER->FindObject(L"HowtoX")->GetComponent<Button>()->GetPressed())
		SCENEMANAGER->ChangeScene(L"Ingame");
	}
}

void cMainMenu::Render()
{
	OBJECTMANAGER->Render();
}

void ClickHowto(cGameObject *howto)
{
	howto->SetActive(true);
}

void OpenSettings(cGameObject *credit)
{
	credit->SetActive(true);
}

void Exit()
{	
	PostQuitMessage(0);
}

