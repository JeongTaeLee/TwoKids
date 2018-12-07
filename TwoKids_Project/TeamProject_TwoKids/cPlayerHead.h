#pragma once
#include "cComponent.h"

class cPlayerComponent;

class cPlayerHead :
	public cComponent
{
private:
	weak_ptr<cSpriteRenderer>	wpSpriteRenderer;
	weak_ptr<cAnimater>			wpAnimater;

	weak_ptr<cPlayerComponent>	wpPlayerComponent;

	DWORD FireTime;
public:
	cPlayerHead();
	virtual ~cPlayerHead();

	virtual void Start()							override;
	virtual void Update(float ElapsedTime)			override;
	
	void CreateBullet(const D3DXVECTOR2 & Direction, const D3DXVECTOR2 & Position);
public:
	float bulletSpeed;
	float fireDelay;
	float filreDamage;
};

