#include "DXUT.h"
#include "Button.h"

#include <string>

Button::Button()
{
	buttonState = E_BUTTONSTATE_IDLE;
}


Button::~Button()
{
}

void Button::Start()
{
	renderer = AddComponent<cSpriteRenderer>();
}

void Button::Update(float ElapsedTime)
{
	buttonState = E_BUTTONSTATE_IDLE;

	if (MouseIsOverIt())
	{
		buttonState = E_BUTTONSTATE_OVER;

		if(INPUTMANAGER->GetKeyPress(VK_LBUTTON))
			buttonState = E_BUTTONSTATE_DOWN;
		if (INPUTMANAGER->GetKeyUp(VK_LBUTTON))
		{
			buttonState = E_BUTTONSTATE_DOWN;

			Trigger();
		}
	}

	ChangeSpriteInState();
}



void Button::Init(const wstring &path, std::function<void()> func)
{
	renderer->SetTexture(MyAddTexture(gameObject->GetObjectName() + L"_idle", path + L"_idle.png"));
	renderer->SetTexture(MyAddTexture(gameObject->GetObjectName() + L"_over", path + L"_over.png"));
	renderer->SetTexture(MyAddTexture(gameObject->GetObjectName() + L"_down", path + L"_down.png"));	

	renderer->SetMidCenter();
	triggerFunction = func;
}

void Button::Trigger()
{
	triggerFunction();
}

bool Button::MouseIsOverIt()
{
	D3DXVECTOR2 mousePos = INPUTMANAGER->GetMousePos();
	D3DXVECTOR2 buttonPos = GetTransform().vPos;
	POINT buttonSize;
	buttonSize.x = renderer->GetImageInfo().Width;
	buttonSize.y = renderer->GetImageInfo().Height;

	if (mousePos.x > (buttonPos.x - buttonSize.x / 2) && mousePos.x < (buttonPos.x + buttonSize.x / 2))
	{
		if (mousePos.y > (buttonPos.y - buttonSize.y / 2) && mousePos.y < (buttonPos.y + buttonSize.y / 2))
		{
			return true;
		}
	}

	return false;
}

void Button::ChangeSpriteInState()
{
	wstring stateName = L"";

	switch (buttonState)
	{
	case E_BUTTONSTATE_IDLE:
		stateName += L"_idle";
		break;
	case E_BUTTONSTATE_DOWN:
		stateName += L"_down";
		break;
	case E_BUTTONSTATE_OVER:
		stateName += L"_over";
		break;
	}

	renderer->SetTexture(MyGetTexture(gameObject->GetObjectName() + stateName.c_str()));
	renderer->SetMidCenter();
	renderer->SetBeginParameter(D3DXSPRITE_ALPHABLEND);
}

bool Button::GetPressed()
{
	if (buttonState != E_BUTTONSTATE_IDLE)
		return true;

	return false;
}

