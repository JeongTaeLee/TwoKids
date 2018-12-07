#pragma once
#include "cComponent.h"
#include "cBulletBase.h"

class cMonsterBullet :
	public cBulletBase
{
public:
	cMonsterBullet();
	virtual ~cMonsterBullet();

public:
	virtual void Start()					override;
	virtual void Update(float ElapsedTime)	override;

public:
	virtual void OnTriggerStay(shared_ptr<cCollider2D> collider) override;
};

