#pragma once
#include "singleton.h"
class cCameraManager :
	public singleton<cCameraManager>
{
private:
	D3DXMATRIXA16 matProj, matView;

	D3DXVECTOR2 vEyePos;
	D3DXVECTOR2 vEyeSize;
	D3DXVECTOR3 vEyeScale;

	float		fAngle;
public:
	cCameraManager();
	virtual ~cCameraManager();

	void Update();
	void SetTransform();
};

#define CAMERAMANAGER cCameraManager::GetInstance()