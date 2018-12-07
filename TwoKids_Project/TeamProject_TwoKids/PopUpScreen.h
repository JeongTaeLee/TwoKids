#pragma once
#include "cGameObject.h"

#include <functional>

class PopUpScreen :
	public cComponent
{
private:
	shared_ptr<cSpriteRenderer> background;

	cGameObject ** buttons;
	int iButtonCount;
	int index;
public:
	PopUpScreen();
	virtual ~PopUpScreen();


	virtual void Start()						override;
	virtual void Update(float ElapsedTime)		override;
	virtual void Destroy()						override;

	virtual void Init(int buttonNum, wstring path);
	virtual void ButtonInit(int index, wstring path, wstring name, int xPos, int yPos, std::function<void()> func);
	virtual void ButtonSetActive(bool state);
};

