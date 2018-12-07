#pragma once
#include "cComponent.h"

#include "cItem.h"
enum CHARSTATE {
	E_CHARSTATE_IDLE,
	E_CHARSTATE_LEFT,
	E_CHARSTATE_RIGHT,
	E_CHARSTATE_DOWN,
	E_CHARSTATE_UP,
};

struct HURT_DIRECTION {
	D3DXVECTOR2 Left   = { -1,  0 };
	D3DXVECTOR2 Right  = {  1,  0 };
	D3DXVECTOR2 Top	   = {  0, -1 };
	D3DXVECTOR2 Bottom = {  0,  1 };
};

class cPlayerHead;
class cPlayerBody;
class cGameObject;

class cPlayerComponent :
	public cComponent
{
private:
	cGameObject* lpHeadObject;
	cGameObject* lpBodyObject;

	weak_ptr<cPlayerHead> wpPlayerHead;
	weak_ptr<cPlayerBody> wpPlayerBody;

	DWORD					dwPortalDelay;
	bool					bOnPortal;
	bool					isNoneDie;
	float speed ;
private:
	
	int hp;
	int maxHp;
	float hurtDelay;
	float fixupDelay;

public:
	CHARSTATE eCharState;

public:
	cPlayerComponent();
	virtual ~cPlayerComponent();

	virtual void Start()							override;
	virtual void Update(float ElapsedTime)			override;
	virtual void OnTriggerStay(shared_ptr<cCollider2D> collider) override;

	void InputKey(float ElapsedTime);

	virtual void SetHeadBodyObject(cGameObject* _spHeadObject, cGameObject* _spBodyObject);

public:
	void AddHurt(int damage, D3DXVECTOR2 direction);

public:
	int GetHp() { return hp; }
	int SetHp(int _hp) { hp = _hp; }
	int GetMaxHp() { return maxHp; }
	int SetMaxHp(int _maxHp) { maxHp = _maxHp; }

	float GetHurtDelay() { return hurtDelay; };
	float GetFixupDelay() { return fixupDelay; };
	void SetItemAbility(ITEM_KIND kind);

	bool GetOnPortal() { return bOnPortal; }
	void OnPortal();
};