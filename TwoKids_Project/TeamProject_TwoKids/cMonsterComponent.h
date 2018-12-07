#pragma once
#include "cComponent.h"

enum MONSTERDIRECTION
{
	E_MDIR_NONE,
	E_MDIR_UP,
	E_MDIR_DOWN,
	E_MDIR_LEFT,
	E_MDIR_RIGHT,
};

class cMonsterComponent :
	public cComponent
{
protected:
	cGameObject*			lpNowMap;
	cGameObject*			lpPlayer;

	weak_ptr<cSpriteRenderer>	wpSpriteRenderer;
	weak_ptr<cAnimater>			wpAnimater;
	weak_ptr<cCollider2D>		wpCollider2D;
	weak_ptr<cRigidBody>		wpRigidBody;

	MONSTERDIRECTION		eMonsterDir;
	D3DXVECTOR2				vDirection;

	float					fAttackElapsed;
	float					fAttackDelay;

	float					fMonsterHp;
	float					fMonsterSpeed;
public:
	cMonsterComponent();
	virtual ~cMonsterComponent();

	virtual void Start()	override;
	virtual void Update(float ElapsedTime)	override;

	virtual void BasicMove(float ElapsedTime);
	virtual void BasicAttack(float ElapsedTime);
		
	virtual void OnColliderStay(shared_ptr<cCollider2D> collider) override;
	virtual void OnTriggerStay(shared_ptr<cCollider2D> collider) override;
	
	void SetRandomDirection();
	void SetMonster(const D3DXVECTOR2 & vStartPos, cGameObject * _lpNowMap);
};

