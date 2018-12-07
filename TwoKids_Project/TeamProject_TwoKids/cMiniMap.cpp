#include "DXUT.h"
#include "cMiniMap.h"


cMiniMap::cMiniMap()
{
}


cMiniMap::~cMiniMap()
{
}

void cMiniMap::SetMiniMap(bool bBoss)
{
	shared_ptr<cSpriteRenderer> spRenderer = AddComponent<cSpriteRenderer>();

	switch (MAPMANAGER->GetStage())
	{
	case MAP_STAGE::E_STAGE01:
		if (bBoss)
			spRenderer->SetTexture(MyAddTexture(L"State01MiniMap_Boss", L"./Resource/Texture/MiniMap/Stage01Mini_Boss.png"));
		else
			spRenderer->SetTexture(MyAddTexture(L"State01MiniMap", L"./Resource/Texture/MiniMap/Stage01Mini.png"));
		break;
	case MAP_STAGE::E_STAGE02:
		if (bBoss)
			spRenderer->SetTexture(MyAddTexture(L"State02MiniMap_Boss", L"./Resource/Texture/MiniMap/Stage02Mini_Boss.png"));
		else
			spRenderer->SetTexture(MyAddTexture(L"State02MiniMap", L"./Resource/Texture/MiniMap/Stage02Mini.png"));
		break;

	default:
		break;
	}

	spRenderer->SetMidCenter();

	gameObject->SetDrawingOrder(4);
}
