#include "DXUT.h"
#include "cMap.h"
#include "cDoor.h"
#include "cTile.h"

#include "cBee.h"
#include "cBear.h"
#include "cLeaf.h"
#include "cSlime.h"
#include "cDog.h"
#include "cGhost.h"
#include "cFinalboss.h"

cMap::cMap()
{
	mDoors.clear();
}


cMap::~cMap()
{
	
}

void cMap::ReleaseMapObject()
{
	PopMapObject();

	for (auto Iter : liTiles)
		SAFE_DELETE(Iter);

	for (auto Iter : liColliders)
		SAFE_DELETE(Iter);

	for (auto Iter : liMonsters)
		SAFE_DELETE(Iter);
	
	for (auto Iter : mDoors)
		SAFE_DELETE(Iter.second);

	for (auto Iter : litem)
		SAFE_DELETE(Iter);
}

void cMap::Update(float ElapsedTime)
{
	if (KEYDOWN(VK_F1))
	{
	}

}

void cMap::PushMapObject()
{
	for (auto Iter : liTiles)
		OBJECTMANAGER->PushObject(Iter);

	for (auto Iter : liColliders)
	{
		OBJECTMANAGER->PushObject(Iter);
		COLLIDERMANAGER->PushCollider(Iter->GetComponent<cCollider2D>());
	}

	for (auto Iter : liMonsters)
	{
		COLLIDERMANAGER->PushCollider(Iter->GetComponent<cCollider2D>());
		OBJECTMANAGER->PushObject(Iter);
	}

	for (auto Iter : mDoors)
	{
		OBJECTMANAGER->PushObject(Iter.second);
		COLLIDERMANAGER->PushCollider(Iter.second->GetComponent<cCollider2D>());
	}

	for (auto Iter : litem)
	{
		COLLIDERMANAGER->PushCollider(Iter->GetComponent<cCollider2D>());
		OBJECTMANAGER->PushObject(Iter);
	}
}

void cMap::PopMapObject()
{
	for (auto Iter : liTiles)
		OBJECTMANAGER->PopObject(Iter);

	for (auto Iter : liColliders)
	{
		COLLIDERMANAGER->PopCollfider(Iter->GetComponent<cCollider2D>());
		OBJECTMANAGER->PopObject(Iter);
	}

	for (auto Iter : liMonsters)
	{
		COLLIDERMANAGER->PopCollfider(Iter->GetComponent<cCollider2D>());
		OBJECTMANAGER->PopObject(Iter);
	}

	for (auto Iter : mDoors)
	{
		OBJECTMANAGER->PopObject(Iter.second);
		COLLIDERMANAGER->PopCollfider(Iter.second->GetComponent<cCollider2D>());
	}

	for (auto Iter : litem)
	{
		COLLIDERMANAGER->PopCollfider(Iter->GetComponent<cCollider2D>());
		OBJECTMANAGER->PopObject(Iter);
	}
}
void cMap::SetMapInfo(const D3DXVECTOR2 & pos, int _iSizeW, int _iSizeH)
{
	iSizeW = _iSizeW;
	iSizeH = _iSizeH;

	vMapPos = pos;

	vMapStartPos = D3DXVECTOR2((pos.x - iSizeW * 32) + 32, (pos.y - iSizeH * 32) + 32);
}
void cMap::SetMapPos(int _iPosX, int _iPosY)
{
	iPosX = _iPosX, iPosY = _iPosY;
}
void cMap::SetAdjacent()
{
	//left
	if (iPosX - 1 >= 0)
	{
		auto find = mDoors.find(LEFT);
		if (find == mDoors.end())
		{
		 	cGameObject * object = MAPMANAGER->GetMapArray()[iPosY][iPosX - 1];
		 	if (object != nullptr)
				InsertDoor(LEFT, object);
		}
	}
	//right
	if (iPosX + 1 < MAPMANAGER->GetMaps().size())
	{
		auto find = mDoors.find(RIGHT);
		if (find == mDoors.end())
		{
			cGameObject * object = MAPMANAGER->GetMapArray()[iPosY][iPosX + 1];
			if (object != nullptr)
				InsertDoor(RIGHT, object);
		}
	}
	//top
	if (iPosY - 1 >= 0)
	{
		auto find = mDoors.find(TOP);
		if (find == mDoors.end())
		{
			cGameObject * object = MAPMANAGER->GetMapArray()[iPosY - 1][iPosX];
			if (object != nullptr)
				InsertDoor(TOP, object);
		}
	}
	//bottom
	if (iPosY + 1 < MAPMANAGER->GetMaps().size())
	{
		auto find = mDoors.find(BOTTOM);
		if (find == mDoors.end())
		{
			cGameObject * object = MAPMANAGER->GetMapArray()[iPosY + 1][iPosX];
			if (object != nullptr)
				InsertDoor(BOTTOM, object);
		}
	}
}
void cMap::InsertTile(shared_ptr<sTexture> texture, const D3DXVECTOR2 & pos, int _iArrX, int _iArrY)
{
	cGameObject * object = new cGameObject(L"Tile", L"Tiles", this->gameObject);
	object->AddComponent<cTile>()->SetTileInfo(texture, vMapStartPos + pos, _iArrX, _iArrY);
	object->SetDrawingOrder(-2);
	
	liTiles.push_back(object);
}
void cMap::InsertCollider(const D3DXVECTOR2 & pos, int iWidth, int iHeight)
{	
	cGameObject * object = new cGameObject(L"Collider", L"Colliders", this->gameObject);
	object->GetTransform().vPos = vMapStartPos + pos;
	object->AddComponent<cCollider2D>()->SetColliderRect({ 0, 0, iWidth, iHeight });

	liColliders.push_back(object);
}

void cMap::InsertMonster(const wstring & name, const D3DXVECTOR2 & pos)
{
	if (name == L"Bee.png")
	{
		cGameObject * object = new cGameObject(L"Monster", L"Monsters");
		object->AddComponent<cBee>()->SetMonster(pos, gameObject);
		
		liMonsters.push_back(object);
	}
	if (name == L"Bear.png")
	{
		cGameObject * object = new cGameObject(L"Monster", L"Monsters");
		object->AddComponent<cBear>()->SetMonster(pos, gameObject);
		
		liMonsters.push_back(object);
	}
	if (name == L"Leaf.png")
	{
		cGameObject * object = new cGameObject(L"Monster", L"Monsters");
		object->AddComponent<cLeaf>()->SetMonster(pos, gameObject);

		liMonsters.push_back(object);
	}
	if (name == L"slime_front01.png")
	{
		cGameObject * object = new cGameObject(L"Monster", L"Monsters");
		object->AddComponent<cSlime>()->SetMonster(pos, gameObject);

		liMonsters.push_back(object);
	}
	if (name == L"Dog.png")
	{
		cGameObject * object = new cGameObject(L"Monster", L"Monsters");
		object->AddComponent<cDog>()->SetMonster(pos, gameObject);

		liMonsters.push_back(object);
	}
	if (name == L"ghost_front01.png")
	{
		cGameObject * object = new cGameObject(L"Monster", L"Monsters");
		object->AddComponent<cGhost>()->SetMonster(pos, gameObject);

		liMonsters.push_back(object);
	}
	if (name == L"Finalboss_front01.png")
	{
		cGameObject * object = new cGameObject(L"Monster", L"Monsters");
		object->AddComponent<cFinalboss>()->SetMonster(pos, gameObject);

		liMonsters.push_back(object);
	}
	
}

void cMap::InsertDoor(MAP_DIRECTION eDirection, cGameObject * connectMap)
{
	auto find = mDoors.find(eDirection);
	if (find != mDoors.end())
		return;

	cGameObject * object = new cGameObject(gameObject);
	//object->AddComponent<cDoor>()->SetDoorInfo(gameObject, connectMap, eDirection);
	object->AddComponent<cDoor>()->SetDoorInfo(GetMapPos(), connectMap->GetComponent<cMap>()->GetMapPos(), eDirection);

	//Collider√ﬂ∞°
	shared_ptr<cCollider2D> collider = object->AddComponent<cCollider2D>();
	collider->SetColliderRect({ 0, 0, 50, 50 });
	COLLIDERMANAGER->PopCollfider(collider);

	switch (eDirection)
	{
	case MAP_DIRECTION::LEFT:
		object->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2 - 64 * 9 - 20, WINSIZEY / 2);
		break;
	case MAP_DIRECTION::RIGHT:
		object->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2 + 64 * 9 + 20, WINSIZEY / 2);
		break;
	case MAP_DIRECTION::TOP:
		object->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2 - 64 * 4 - 20);
		break;
	case MAP_DIRECTION::BOTTOM:
		object->GetTransform().vPos = D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2 + 64 * 4 + 20);
		break;
	}

	mDoors.insert(make_pair(eDirection, object));
}

void cMap::InsertItem()
{
	cGameObject * item = new cGameObject(L"item", gameObject);
	item->AddComponent<cItem>()->SetItemKind((ITEM_KIND)GetRandomNumber(0, 3));
	item->GetTransform().vPos = { 1000, 200 };
	
	litem.push_back(item);
}

void cMap::DestroyMonster(cGameObject* gameObject)
{
	for (auto Iter = liMonsters.begin(); Iter != liMonsters.end();)
	{
		if ((*Iter) == gameObject)
		{
			liMonsters.erase(Iter);
			break;
		}
		else
			++Iter;
	}

	gameObject->Destroy();
}

void cMap::Destroyitem(cGameObject * gameObject)
{
	for (auto Iter = litem.begin(); Iter != litem.end();)
	{
		if ((*Iter) == gameObject)
		{
			litem.erase(Iter);
			break;
		}
		else
			++Iter;
	}

	gameObject->Destroy();
}

bool cMap::IsAllMonsterDie()
{
	if (liMonsters.size() == 0) return true;
	return false;
}

