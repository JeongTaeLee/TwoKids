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
	// 파일 로더를 위한 객체
	wifstream ifLoader;

	// 로드한 맵들을 모아두는 벡터(현재 스테이ㅇ지 맵만 저장함)
	// 시작할때 1, 2, 3, 스테이지 전체를 로드하는게 아닌 (1스테이지 맵들만 로드함)
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

	// 랜덤맵!
	// 맵 폴더 안에 스테이지 별로 폴더를 나누는 것이 좋을것 같음 예) map/stage01, map/stage02, map/stage03
	// path경로에 있는 모든 파일을 불러옴.
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
