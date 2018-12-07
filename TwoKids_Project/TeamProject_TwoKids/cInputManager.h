#pragma once
#include "singleton.h"


class cInputManager :
	public singleton<cInputManager>
{
private:
	enum KEYSTATE
	{
		E_KEY_DOWN,
		E_KEY_UP,
		E_KEY_PRESS,
		E_KEY_NONE,
	};
private:
	bool iNowKey[KEYMAX];
	bool iOldKey[KEYMAX];	

	D3DXVECTOR2 vMousePos;
public:
	cInputManager();
	virtual ~cInputManager();

	void Update();

	bool GetKeyPress(int i);
	bool GetKeyDown(int i);
	bool GetKeyUp(int i);

	const D3DXVECTOR2 & GetMousePos();
};

#define INPUTMANAGER cInputManager::GetInstance()

#define KEYDOWN(i) INPUTMANAGER->GetKeyDown(i)
#define KEYUP(i) INPUTMANAGER->GetKeyUp(i)
#define KEYPRESS(i) INPUTMANAGER->GetKeyPress(i)

