#pragma once
#include "singleton.h"

int GetRandomNumber(int min, int max);

class cMap;
class cMiniMapAdmin;
enum MAP_DIRECTION
{
	NONE = -1,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

enum MAP_STAGE
{
	E_STAGE01,
	E_STAGE02,
	E_STAGE03,
};

class cMapManager :
	public singleton<cMapManager>
{
private:
	// ���� �δ��� ���� ��ü
	wifstream ifLoader;

	// �ε��� �ʵ��� ��Ƶδ� ����(���� �����̤��� �ʸ� ������)
	// �����Ҷ� 1, 2, 3, �������� ��ü�� �ε��ϴ°� �ƴ� (1�������� �ʵ鸸 �ε���)
	vector<cGameObject*>	vMaps;
	MAP_STAGE				eStage;

	cGameObject * lpNowMap;
	cGameObject * lpNextMap;

	cGameObject ***	     lpMapArr;
	vector<cGameObject*> vNotCompleteMap;
	int					 iCompleteMapSize;

	cGameObject*		 lpMiniMapAdmin;

public:
	cMapManager();
	virtual ~cMapManager();
	
	void Release();
	void Update();

	// ������!
	// �� ���� �ȿ� �������� ���� ������ ������ ���� ������ ���� ��) map/stage01, map/stage02, map/stage03
	// path��ο� �ִ� ��� ������ �ҷ���.
	void CreateRandomMap(MAP_STAGE _eStage, const wstring & key);
	void ChangeMap(const POINT & pos);
	
	void LoadMapName(vector<wstring> &vNames, const wstring & path);
	void LoadStage(const wstring & path);
public:
	MAP_DIRECTION	GetNoneDoor(int arrX, int arrY);
	cGameObject***	GetMapArray() { return lpMapArr; }
	cGameObject*	GetCompleteMap();
	cGameObject*	GetNoneCompleteMap();
	cGameObject*	GetNowMap()			{ return lpNowMap; }
	const vector<cGameObject*> & GetMaps()	{ return vMaps; }
	void  SetStage(MAP_STAGE stage) { eStage = stage; }
	const MAP_STAGE & GetStage()			{ return eStage; }
};

#define MAPMANAGER cMapManager::GetInstance()
