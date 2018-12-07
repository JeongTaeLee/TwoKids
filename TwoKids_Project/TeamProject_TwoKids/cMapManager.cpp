#include "DXUT.h"
#include "cMapManager.h"
#include "cMap.h"
#include <random>
#include "cMiniMapAdmin.h"

int GetRandomNumber(int min, int max)
{
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_int_distribution<int> range(min, max);

	return range(rnd);
}

bool GetMapCast(int process, int size, bool isLeft)
{
	if (process % size == 0 && isLeft)
		return false;
	if (process % size == size - 1 && isLeft == false)
		return false;
	return true;
}

cMapManager::cMapManager()
	:lpNowMap(nullptr), lpNextMap(nullptr), lpMapArr(nullptr), lpMiniMapAdmin(nullptr)
{
	eStage = E_STAGE01;
}


cMapManager::~cMapManager()
{
	Release();
}

void cMapManager::Release()
{
	int size = vMaps.size();

	if (lpNowMap)
	{
		OBJECTMANAGER->PopObject(lpNowMap);
		lpNowMap->GetComponent<cMap>()->PopMapObject();
		lpNowMap = nullptr;
	}

	for (auto Iter : vMaps)
	{
		Iter->GetComponent<cMap>()->ReleaseMapObject();
		OBJECTMANAGER->PopObject(Iter);
		SAFE_DELETE(Iter);
	}
	vMaps.clear();
	
	for (int i = 0; i < size; i++)
		SAFE_DELETE_ARRAY(lpMapArr[i]);

	SAFE_DELETE_ARRAY(lpMapArr);

	
}

void cMapManager::Update()
{

	if (lpNextMap)
	{
		if (lpNowMap)
		{
			lpNowMap->GetComponent<cMap>()->PopMapObject();
			OBJECTMANAGER->PopObject(lpNowMap);
			lpNowMap = nullptr;
		}

		lpNowMap = lpNextMap;
		lpNowMap->GetComponent<cMap>()->PushMapObject();
		OBJECTMANAGER->PushObject(lpNowMap);

		lpNextMap = nullptr;
	}
}


void cMapManager::CreateRandomMap(MAP_STAGE _eStage, const wstring & path)
{
	Release();
	LoadStage(path);
	eStage = _eStage;

	lpMapArr = new cGameObject**[vMaps.size()];
	
	for (int i = 0; i < vMaps.size(); i++)
	{
		lpMapArr[i] = new cGameObject*[vMaps.size()];
	}

	for (int i = 0; i < vMaps.size(); ++i)
	{
		for (int j = 0; j < vMaps.size(); ++j)
			lpMapArr[i][j] = nullptr;
	}
	iCompleteMapSize = 0;

	int firstX = vMaps.size() / 2, firstY = vMaps.size() / 2;

	cGameObject * nowMap = nullptr;
	nowMap = lpMapArr[firstY][firstX] = vMaps[0];
	nowMap->GetComponent<cMap>()->SetMapPos(firstX, firstY);
	nowMap->GetComponent<cMap>()->SetCollocateComplete(true);
	iCompleteMapSize++;

	while (iCompleteMapSize != vMaps.size())
	{
		nowMap = GetCompleteMap();
		POINT nowMapPoint = nowMap->GetComponent<cMap>()->GetMapPos();
		MAP_DIRECTION direction = GetNoneDoor(nowMapPoint.x, nowMapPoint.y);
		if (direction == NONE)
			continue;

		cGameObject * object = GetNoneCompleteMap();
		MAP_DIRECTION objectDirection = NONE;
		object->GetComponent<cMap>()->SetCollocateComplete(true);

		switch (direction)
		{
		case LEFT:
			lpMapArr[nowMapPoint.y][nowMapPoint.x - 1] = object;
			objectDirection = RIGHT;
			object->GetComponent<cMap>()->SetMapPos(nowMapPoint.x - 1, nowMapPoint.y);
			break;
		case RIGHT:
			lpMapArr[nowMapPoint.y][nowMapPoint.x + 1] = object;
			objectDirection = LEFT;
			object->GetComponent<cMap>()->SetMapPos(nowMapPoint.x + 1, nowMapPoint.y);
			break;
		case TOP:
			lpMapArr[nowMapPoint.y - 1][nowMapPoint.x] = object;
			objectDirection = BOTTOM;
			object->GetComponent<cMap>()->SetMapPos(nowMapPoint.x, nowMapPoint.y - 1);
			break;
		case BOTTOM:
			lpMapArr[nowMapPoint.y + 1][nowMapPoint.x] = object;
			object->GetComponent<cMap>()->SetMapPos(nowMapPoint.x, nowMapPoint.y + 1);
			objectDirection = TOP;
			break;
		}

		nowMap->GetComponent<cMap>()->InsertDoor(direction, object);
		object->GetComponent<cMap>()->InsertDoor(objectDirection, nowMap);
		iCompleteMapSize++;
	}

	for (auto Iter : vMaps)
		Iter->GetComponent<cMap>()->SetAdjacent();
	
	vMaps[vMaps.size() - 1]->GetComponent<cMap>()->SetBossMap(true);

	if (lpMiniMapAdmin)
		lpMiniMapAdmin = nullptr;

	lpMiniMapAdmin = new cGameObject;
	lpMiniMapAdmin->AddComponent<cMiniMapAdmin>();
	OBJECTMANAGER->AddObject(lpMiniMapAdmin);

	ChangeMap({ firstX , firstY });
}
void cMapManager::ChangeMap(const POINT & pos)
{
	lpNextMap = lpMapArr[pos.y][pos.x];

	if (lpMiniMapAdmin)
		lpMiniMapAdmin->GetComponent<cMiniMapAdmin>()->UpdateMiniMap(lpNextMap);
}

void cMapManager::LoadMapName(vector<wstring> &vNames, const wstring & searchPath)
{
	_wfinddata_t fd;
	long handle = _wfindfirst(searchPath.c_str(), &fd);

	if (handle == -1)
		return;

	int result = 0;
	do
	{
		vNames.push_back(fd.name);
		result = _wfindnext(handle, &fd);
	} while (result != -1);
}
void cMapManager::LoadStage(const wstring & path)
{
	for (auto Iter : vMaps)
		Iter->Destroy();
	vMaps.clear();

	wstring searchPath = path + L"*.MSF";

	vector<wstring> fileNames;
	LoadMapName(fileNames, searchPath);

	for (auto Iter : fileNames)
	{
		wstring tcFilePath = path + Iter;

		ifLoader.open(tcFilePath.c_str(), ios::in);

		int iMapWidth = 0, iMapHeight = 0;
		ifLoader >> iMapWidth >> iMapHeight;

		cGameObject *		createMap = new cGameObject(L"Map", L"Mpas");
		shared_ptr<cMap>	map = createMap->AddComponent<cMap>();
		map->SetMapInfo(D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2), iMapWidth, iMapHeight);

		if (Iter == L"1.MSF")
		{
			createMap->GetComponent<cMap>()->InsertItem();
		}

		while (!ifLoader.eof())
		{
			wstring type;
			ifLoader >> type;

			if (type == L"Tile")
			{
				int iPosX = 0, iPosY = 0;

				ifLoader >> type >> iPosX >> iPosY;

				wstring imagePath = L"./Resource/Texture/MapImage/" + type;
				map->InsertTile(MyAddTexture(imagePath, imagePath), D3DXVECTOR2(iPosX, iPosY), iPosX / 64, iPosY / 64);
			}
			else if (type == L"Collider")
			{
				int iPosX = 0, iPosY = 0;
				int iSizeX = 0, iSizeY = 0;
				ifLoader >> iPosX >> iPosY >> iSizeX >> iSizeY;

				map->InsertCollider(D3DXVECTOR2(iPosX, iPosY), iSizeX, iSizeY);
			}
			else if (type == L"Monster")
			{
				int iPosX = 0, iPosY = 0;

				ifLoader >> type >> iPosX >> iPosY;

				map->InsertMonster(type, D3DXVECTOR2(iPosX, iPosY));
			}
		}

		map->PopMapObject();

		vMaps.push_back(createMap);

		ifLoader.close();
	}
}

MAP_DIRECTION cMapManager::GetNoneDoor(int arrX, int arrY)
{
	bool bCheck = false;

	for (int i = 0; i < 4; i++)
	{
		if (i == 0){
			if (arrX - 1 < 0)
				continue;
			if (lpMapArr[arrY][arrX - 1] != nullptr)
				continue;

			bCheck = true;
		}
		if (i == 1){
			if (arrX + 1 > vMaps.size() - 1)
				continue;
			if (lpMapArr[arrY][arrX + 1] != nullptr)
				continue;

			bCheck = true;
		}
		if (i == 2){
			if (arrY - 1 < 0)
				continue;
			if (lpMapArr[arrY - 1][arrX] != nullptr)
				continue;

			bCheck = true;
		}
		if (i == 3){
			if (arrY + 1 > vMaps.size() - 1)
				continue;
			if (lpMapArr[arrY + 1][arrX] != nullptr)
				continue;

			bCheck = true;
		}
	}

	if (!bCheck)
		return NONE;

	MAP_DIRECTION random;

	while (true)
	{
		MAP_DIRECTION randomDirection = (MAP_DIRECTION)GetRandomNumber(0, 3);

		switch (randomDirection)
		{
		case LEFT:
			if ((arrX - 1) < 0)
				continue;
			if (lpMapArr[arrY][arrX - 1] != nullptr)
				continue;
			
			random = randomDirection;
			return random;
			break;
		case RIGHT:
			if ((arrX + 1) > (vMaps.size() - 1))
				continue;
			if (lpMapArr[arrY][arrX + 1] != nullptr)
				continue;

			random = randomDirection;
			return random;
			break;
		case TOP:
			if ((arrY - 1) < 0)
				continue;
			if (lpMapArr[arrY-1][arrX] != nullptr)
				continue;

			random = randomDirection;
			return random;
			break;
		case BOTTOM:
			if ((arrY + 1) > (vMaps.size() - 1))
				continue;
			if (lpMapArr[arrY + 1][arrX] != nullptr)
				continue;

			random = randomDirection;
			return random;
			break;

		}
	}
}
cGameObject * cMapManager::GetCompleteMap()
{
	if (vMaps.size() == iCompleteMapSize)
		return nullptr;

	while (true)
	{
		int randomIndex = GetRandomNumber(0, vMaps.size() - 1);

		if (vMaps[randomIndex]->GetComponent<cMap>()->GetCollocateComplete())
			return vMaps[randomIndex];
	}

	return nullptr;
}
cGameObject * cMapManager::GetNoneCompleteMap()
{
	return vMaps[iCompleteMapSize];
}
