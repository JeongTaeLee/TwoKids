#pragma once
#include "cComponent.h"

class cRigidBody :
	public cComponent
{
private:
	D3DXVECTOR2 vForce;

	bool		bInertia;
public:
	cRigidBody();
	virtual ~cRigidBody();

	virtual void Update(float ElapasedTime);

	void AddForce(const D3DXVECTOR2 _vForce, bool _bInertia = false);
	const D3DXVECTOR2 & GetForce();
};

