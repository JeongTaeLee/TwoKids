#include "DXUT.h"
#include "cCameraManager.h"


cCameraManager::cCameraManager()
{
	vEyePos		= D3DXVECTOR2((float)WINSIZEX / 2, (float)WINSIZEY / 2);
	vEyeSize	= D3DXVECTOR2((float)WINSIZEX, (float)WINSIZEY);
	vEyeScale	= D3DXVECTOR3(1.f, 1.f, 1.f);

	fAngle		= 0.f;

	D3DXMatrixOrthoLH(&matProj, vEyeSize.x, -vEyeSize.y, 0, 1);
}


cCameraManager::~cCameraManager()
{
}

void cCameraManager::Update()
{
	
	
	if (KEYPRESS('Q'))
		vEyeScale -= D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	if (KEYPRESS('E'))
		vEyeScale += D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	if (KEYPRESS('W'))
		vEyePos.y -= 1.f;
	if (KEYPRESS('S'))
		vEyePos.y += 1.f;
	if (KEYPRESS('A'))
		vEyePos.x -= 1.f;
	if (KEYPRESS('D'))
		vEyePos.x += 1.f;
	if (KEYPRESS('R'))
		fAngle += D3DXToRadian(10);
	
	
	matView = D3DXMATRIXA16(
		vEyeScale.x * cosf(fAngle), vEyeScale.x * sinf(fAngle), 0, 0,
		-vEyeScale.y * sinf(fAngle), vEyeScale.y * cosf(fAngle), 0, 0,
		0, 0, vEyeScale.z, 0,
		-vEyePos.x * vEyeScale.x * cosf(fAngle) + vEyePos.y * vEyeScale.y * sinf(fAngle),
		-vEyePos.x * vEyeScale.x * sinf(fAngle) - vEyePos.y * vEyeScale.y * cosf(fAngle), 0, 1);
	
	
	/*
	matView = D3DXMATRIXA16(
		vEyeScale.x * cosf(fAngle), vEyeScale.x * sinf(fAngle), 0, 0,
		-vEyeScale.y * sinf(fAngle), vEyeScale.y * cosf(fAngle), 0, 0,
		0, 0, vEyeScale.z, 0,
		-vEyePos.x * vEyeScale.y, -vEyePos.y * vEyeScale.x, 0, 1);
	*/
}
void cCameraManager::SetTransform()
{
	g_device->SetTransform(D3DTS_VIEW		, &matView);
	g_device->SetTransform(D3DTS_PROJECTION	, &matProj);
}