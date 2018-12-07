#include "DXUT.h"
#include "cRigidBody.h"


cRigidBody::cRigidBody()
	:vForce(0, 0)
{
	bInertia = false;
}

cRigidBody::~cRigidBody()
{
}



void cRigidBody::Update(float ElapasedTime)
{
	if (bInertia)
	{
		if (vForce.x > 0 || vForce.x < 0)
			GetTransform().vPos.x += vForce.x;
		if (vForce.y > 0 || vForce.y < 0)
			GetTransform().vPos.y += vForce.y;
	
		vForce = D3DXVECTOR2(0, 0);
	}
}

void cRigidBody::AddForce(const D3DXVECTOR2 _vForce, bool _bInertia)
{
	vForce	+= _vForce;

	bInertia = _bInertia;

	if (!bInertia)
	{
		if (vForce.x > 0 || vForce.x < 0)
			GetTransform().vPos.x += vForce.x;
		if (vForce.y > 0 || vForce.y < 0)
			GetTransform().vPos.y += vForce.y;

		vForce = D3DXVECTOR2(0, 0);
	}
}

const D3DXVECTOR2 & cRigidBody::GetForce()
{
	return vForce;
}
