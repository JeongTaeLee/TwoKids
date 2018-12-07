#pragma once
#include "cComponent.h"
#include "cItem.h"

class cTile;
class cDoor;
class cMap :
	public cComponent
{
private:
	int iMapCode; // 맵의 이름을 string으로 하지말고 int로 코드를 만들자.

	int iPosX, iPosY;
	int iSizeW, iSizeH;

	D3DXVECTOR2 vMapPos;
	D3DXVECTOR2 vMapStartPos;

	list<cGameObject*>	liTiles;
	list<cGameObject*>	liColliders;
	list<cGameObject*>	liMonsters;
	map<MAP_DIRECTION, cGameObject*>	mDoors;

	list<cGameObject*>  litem;

	bool bCollocateComplete = false;
	bool bBossMap = false;
public:
	cMap();
	virtual ~cMap();
	
	void ReleaseMapObject();

	virtual void Update(float ElapsedTime) override;

	void PushMapObject();
	void PopMapObject();

	void SetMapPos(int _iPosX, int _iPosY);
	void SetMapInfo(const D3DXVECTOR2 & pos, int _iSizeW, int _iSizeH);
	void SetAdjacent();

	void InsertTile(shared_ptr<sTexture> texture, const D3DXVECTOR2 & pos, int _iArrX, int _iArrY);
	void InsertCollider(const D3DXVECTOR2 & pos,int iWidth, int iHeight);
	void InsertMonster(const wstring &name, const D3DXVECTOR2 & pos);
	void InsertDoor(MAP_DIRECTION eDirection, cGameObject * connectMap);
	void InsertItem();

	inline void SetCollocateComplete(bool _bCollocateComplete) { bCollocateComplete = _bCollocateComplete; };
	inline bool GetCollocateComplete() { return bCollocateComplete;}

	void DestroyMonster(cGameObject *gameObject);
	void Destroyitem(cGameObject *gameObject);
	bool IsAllMonsterDie();

	void SetBossMap(bool _bBossMap) { bBossMap = _bBossMap; }
	bool GetBossMap() { return bBossMap; }

	inline const POINT		 & GetMapPos() { return { iPosX, iPosY }; }
	inline const D3DXVECTOR2 & GetMapStartPos() { return vMapStartPos; }
};

