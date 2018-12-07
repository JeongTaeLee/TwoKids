#include "DXUT.h"
#include "PopUpScreen.h"

#include "Button.h"

PopUpScreen::PopUpScreen()
{
}


PopUpScreen::~PopUpScreen()
{
}

void PopUpScreen::Start()
{
	background = AddComponent<cSpriteRenderer>();
	index = 0;
}

void PopUpScreen::Update(float ElapsedTime)
{
}

void PopUpScreen::Destroy()
{
	//SAFE_DELETE_ARRAY(buttons);
}

void PopUpScreen::Init(int buttonNum, wstring path)
{
	background->SetTexture(MyAddTexture(gameObject->GetObjectName(), path ));
	background->SetMidCenter();
	background->SetBeginParameter(D3DXSPRITE_ALPHABLEND);

	buttons = new cGameObject*[buttonNum];
	iButtonCount = buttonNum;

}

void PopUpScreen::ButtonInit(int index, wstring path, wstring name, int xPos, int yPos, std::function<void()> func)
{
	buttons[index] = new cGameObject(name);
	buttons[index]->GetTransform().vPos = D3DXVECTOR2(xPos, yPos);
	buttons[index]->AddComponent<Button>();
	buttons[index]->GetComponent<Button>()->Init(path, func);
	buttons[index]->SetDrawingOrder(2);
	buttons[index]->SetActive(false);
	OBJECTMANAGER->AddObject(buttons[index]);
	++this->index;
}

void PopUpScreen::ButtonSetActive(bool state)
{
	for (int i = 0; i < index; i++)
	{
		buttons[i]->SetActive(state);
	}
}
