#include "DXUT.h"
#include "cIntro.h"


cIntro::cIntro()
{
}


cIntro::~cIntro()
{
}


void cIntro::Init()
{
	timeDelay = 0.3f;
	charSpeed = 50;
	logoScale = 5;
	lightAlpha = 0.0f;

	intro_State = NONE_BACK;

	background = new cGameObject();
	background->GetTransform().vPos = { WINSIZEX / 2, WINSIZEY / 2 };
	background->AddComponent<cSpriteRenderer>()->SetTexture(
		MyAddTexture(L"Main_Background", L"./Resource/Texture/MainScene/Main_Background.png"));
	background->GetComponent<cSpriteRenderer>()->SetMidCenter();
	background->SetDrawingOrder(0);
	OBJECTMANAGER->AddObject(background);

	character = new cGameObject();
	character->GetTransform().vPos = { WINSIZEX / 2, -WINSIZEY / 2 };
	character->AddComponent<cSpriteRenderer>()->SetTexture(
		MyAddTexture(L"Main_Character", L"./Resource/Texture/MainScene/Character.png"));
	character->GetComponent<cSpriteRenderer>()->SetMidCenter();
	character->SetDrawingOrder(3);
	OBJECTMANAGER->AddObject(character);

	monster_Left = new cGameObject();
	monster_Left->GetTransform().vPos = { -WINSIZEX / 2, WINSIZEY / 2 };
	monster_Left->AddComponent<cSpriteRenderer>()->SetTexture(
		MyAddTexture(L"Main_Monster_Left", L"./Resource/Texture/MainScene/Monster_Left.png"));
	monster_Left->GetComponent<cSpriteRenderer>()->SetMidCenter();
	monster_Left->SetDrawingOrder(1);
	OBJECTMANAGER->AddObject(monster_Left);

	monster_Right = new cGameObject();
	monster_Right->GetTransform().vPos = { WINSIZEX + WINSIZEX / 2, WINSIZEY / 2 };
	monster_Right->AddComponent<cSpriteRenderer>()->SetTexture(
		MyAddTexture(L"Main_Monster_Right", L"./Resource/Texture/MainScene/Monster_Right.png"));
	monster_Right->GetComponent<cSpriteRenderer>()->SetMidCenter();
	monster_Right->SetDrawingOrder(1);
	OBJECTMANAGER->AddObject(monster_Right);

	spotLight = new cGameObject();
	spotLight->GetTransform().vPos = { WINSIZEX / 2, WINSIZEY / 2 };
	spotLight->AddComponent<cSpriteRenderer>()->SetTexture(
		MyAddTexture(L"Main_Spotlight", L"./Resource/Texture/MainScene/Spotlight.png"));
	spotLight->GetComponent<cSpriteRenderer>()->SetMidCenter();
	spotLight->GetComponent<cSpriteRenderer>()->SetColor(D3DCOLOR_RGBA(255, 255, 255, 0));
	spotLight->SetDrawingOrder(2);
	OBJECTMANAGER->AddObject(spotLight);

	logo = new cGameObject();
	logo->GetTransform().vPos = { WINSIZEX / 2, WINSIZEY / 2 };
	logo->AddComponent<cSpriteRenderer>()->SetTexture(
		MyAddTexture(L"Main_Logo", L"./Resource/Texture/MainScene/Logo.png"));
	logo->GetComponent<cSpriteRenderer>()->SetMidCenter();
	logo->GetTransform().vScale = { logoScale, logoScale };
	logo->SetDrawingOrder(4);
	logo->SetActive(false);
	OBJECTMANAGER->AddObject(logo);
}

void cIntro::Update(float ElapseTime)
{
	OBJECTMANAGER->Update(ElapseTime);

	switch (intro_State)
	{
	case NONE_BACK:
		if (timeDelay > 0)
			timeDelay -= ElapseTime;
		else
		{
			timeDelay = 0;
			intro_State = CHAR_MOVE;
		}
		break;
	case CHAR_MOVE:
		character->GetTransform().vPos += { 0, charSpeed * ElapseTime };
		charSpeed += 50;
		if (character->GetTransform().vPos.y >= WINSIZEY / 2)
		{
			character->GetTransform().vPos.y = WINSIZEY / 2;
			intro_State = MONSTER_MOVE;
			timeDelay = 1.7f;
		}
		break;
	case MONSTER_MOVE:
		Lerp<D3DXVECTOR2>(&monster_Left->GetTransform().vPos,  D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2), 0.05f);
		Lerp<D3DXVECTOR2>(&monster_Right->GetTransform().vPos, D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2), 0.05f);
		if (timeDelay > 0)
			timeDelay -= ElapseTime;
		else
		{
			timeDelay = 1.0f;
			intro_State = ACTIVE_LIGHT;
		}
		break;
	case ACTIVE_LIGHT:
		Lerp<float>(&lightAlpha, 255, 0.1f);
		spotLight->GetComponent<cSpriteRenderer>()->SetColor(D3DCOLOR_RGBA(255, 255, 255, (int)lightAlpha));
		if (timeDelay > 0)
			timeDelay -= ElapseTime;
		else
		{
			intro_State = ACTIVE_LOGO;
			logo->SetActive(true);
		}
		break;
	case ACTIVE_LOGO:
		Lerp<float>(&logoScale, 1, 0.1f);
		logo->GetTransform().vScale = { logoScale, logoScale };
		
		
		break;
	default:
		break;
	}

	if(INPUTMANAGER->GetKeyDown(VK_LBUTTON))
		SCENEMANAGER->ChangeScene(L"MainMenu");

}

void cIntro::Release()
{
	OBJECTMANAGER->Reset();
}

void cIntro::Render()
{
	OBJECTMANAGER->Render();
}
