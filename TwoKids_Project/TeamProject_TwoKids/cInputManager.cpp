#include "DXUT.h"
#include "cInputManager.h"



cInputManager::cInputManager()
{
	memset(iNowKey, false, sizeof(iNowKey));
	memset(iOldKey, false, sizeof(iOldKey));
}


cInputManager::~cInputManager()
{
}

void cInputManager::Update()
{
	memcpy(iOldKey, iNowKey	, sizeof(iOldKey));
	memset(iNowKey, false	, sizeof(iNowKey));


	for (int i = 0; i < KEYMAX; i++)
	{
		if (GetAsyncKeyState(i))
			iNowKey[i] = true;
	}

	POINT point;
	GetCursorPos(&point);
	ScreenToClient(DXUTGetHWND(), &point);

	vMousePos = D3DXVECTOR2((float)point.x, (float)point.y);
}

bool cInputManager::GetKeyPress(int i)
{
	return (iOldKey[i] == true && iNowKey[i] == true);
}

bool cInputManager::GetKeyDown(int i)
{
	return (iOldKey[i] == false && iNowKey[i] == true);
}

bool cInputManager::GetKeyUp(int i)
{
	return (iOldKey[i] == true && iNowKey[i] == false);
}

const D3DXVECTOR2 & cInputManager::GetMousePos()
{
	return vMousePos;
}
