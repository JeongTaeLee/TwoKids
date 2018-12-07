#include "DXUT.h"
#include "cMiniMapAdmin.h"
#include "cMap.h"
#include "cMiniMap.h"

cMiniMapAdmin::cMiniMapAdmin()
{
}


cMiniMapAdmin::~cMiniMapAdmin()
{
}

void cMiniMapAdmin::Start()
{
	GetTransform().vPos = D3DXVECTOR2(1150, 150);

	shared_ptr<cSpriteRenderer> spriteRenderer = AddComponent<cSpriteRenderer>();
	spriteRenderer->SetTexture(MyAddTexture(L"MiniMapGuide", L"./Resource/Texture/MiniMap/MiniMapGuid.png"));	
	spriteRenderer->SetMidCenter();
	gameObject->SetDrawingOrder(3);
}

void cMiniMapAdmin::Destroy()
{
}

void cMiniMapAdmin::ResetMiniMap()
{
	for (auto Iter : gameObject->GetChildList())
		Iter->Destroy();

	gameObject->GetChildList().clear();
}

void cMiniMapAdmin::UpdateMiniMap(cGameObject * lpNowMap)
{
	ResetMiniMap();
	
	cGameObject *** mapArr = MAPMANAGER->GetMapArray();

	shared_ptr<cMap> mapComponent = lpNowMap->GetComponent<cMap>();
	POINT mapPos = mapComponent->GetMapPos();

	if (lpNowMap != nullptr)
		CreateMiniMap(D3DXVECTOR2(0, 0), mapComponent->GetBossMap(), true);

	for (int i = 0; i < 9; ++i)
	{
		POINT checkPos;
		switch (i)
		{
		case 0:
			checkPos = {-1, -1 };
			break;
		case 1:
			checkPos = { 0, -1 };
			break;
		case 2:
			checkPos = { 1, -1 };
			break;
		case 3:
			checkPos = {-1, 0};
			break;
		case 4:
			continue;
			break;
		case 5:
			checkPos = { 1, 0};
			break;
		case 6:
			checkPos = {-1, 1};
			break;
		case 7:
			checkPos = { 0, 1};
			break;
		case 8:
			checkPos = { 1, 1};
			break;
		}

		if (mapPos.x + checkPos.x >= 0 && mapPos.x + checkPos.x < MAPMANAGER->GetMaps().size() &&
			mapPos.y + checkPos.y >= 0 && mapPos.y + checkPos.y < MAPMANAGER->GetMaps().size())
		{
			if (mapArr[mapPos.y + checkPos.y][mapPos.x + checkPos.x] != nullptr)
				CreateMiniMap(D3DXVECTOR2(60 * checkPos.x, 50 * checkPos.y), 
					mapArr[mapPos.y + checkPos.y][mapPos.x + checkPos.x]->GetComponent<cMap>()->GetBossMap(), false);
		}
	}
}

cGameObject* cMiniMapAdmin::CreateMiniMap(const D3DXVECTOR2 & pos, bool boss, bool NowMap)
{
	cGameObject * object = new cGameObject(gameObject);
	object->GetTransform().vPos = pos;
	object->AddComponent<cMiniMap>()->SetMiniMap(boss);

	if (!NowMap)
		object->GetComponent<cSpriteRenderer>()->SetColor(D3DCOLOR_ARGB(255, 150, 150, 150));


	return OBJECTMANAGER->AddObject(object);
}
