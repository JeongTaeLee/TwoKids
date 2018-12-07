#pragma once
#include "cComponent.h"
#include <functional>


enum BUTTONSTATE {
	E_BUTTONSTATE_IDLE,
	E_BUTTONSTATE_DOWN,
	E_BUTTONSTATE_OVER,

};

class cGameObject;

class Button :
	public cComponent
{
private:
	shared_ptr<cSpriteRenderer> renderer;

	BUTTONSTATE buttonState;

	std::function<void()> triggerFunction;
public: 
	Button();
	virtual ~Button();


	virtual void Start()						override;
	virtual void Update(float ElapsedTime)		override;

	virtual void Init(const wstring &path, std::function<void()> func);

	virtual void Trigger();
	virtual bool MouseIsOverIt();
	virtual void ChangeSpriteInState();

	virtual bool GetPressed();
};

