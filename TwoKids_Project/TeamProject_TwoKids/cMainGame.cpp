#include "DXUT.h"
#include "cMainGame.h"

#include "cIngame.h"
#include "cMainMenu.h"
#include "cIntro.h"
#include "cLoseScene.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	SCENEMANAGER->AddScene(L"Ingame", make_shared<cIngame>());
	SCENEMANAGER->AddScene(L"MainMenu", make_shared<cMainMenu>());
	SCENEMANAGER->AddScene(L"Intro", make_shared<cIntro>());
	SCENEMANAGER->AddScene(L"LoseScene", make_shared<cLoseScene>());
	SCENEMANAGER->ChangeScene(L"Intro");
}
void cMainGame::Release()
{
	cSceneManager		::ReleaseInstance();
	cMapManager			::ReleaseInstance();
	cCollisionManager	::ReleaseInstance();
	cObjectManager		::ReleaseInstance();
	cTextureManager		::ReleaseInstance();
	cCameraManager		::ReleaseInstance();
	cInputManager		::ReleaseInstance();
	cSoundManager		::ReleaseInstance();
}
void cMainGame::Update()
{
	if (KEYDOWN(VK_F1))
		TEXTUREMANAGER->SetRenderCollider(!TEXTUREMANAGER->GetRenderCollider());

	INPUTMANAGER->Update();
	CAMERAMANAGER->Update();
	SCENEMANAGER->Update(DXUTGetElapsedTime());
}
void cMainGame::Render()
{
	CAMERAMANAGER->SetTransform();
	SCENEMANAGER->Render();	
}

void cMainGame::LostDevice()
{
	TEXTUREMANAGER->LostDevice();
}
void cMainGame::ResetDevice()
{
	TEXTUREMANAGER->ResetDevice();
}