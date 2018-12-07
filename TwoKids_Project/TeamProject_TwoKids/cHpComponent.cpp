#include "DXUT.h"
#include "cHpComponent.h"

#include "cHpUI.h"
#include "cPlayerComponent.h"



cHpComponent::cHpComponent()
{
}


cHpComponent::~cHpComponent()
{
	vHp.clear();
}

void cHpComponent::Start()
{
	GetTransform().vPos = { 100, 30 };

	cGameObject* obj = OBJECTMANAGER->AddObject(new cGameObject(gameObject));
	obj->AddComponent<cHpUI>();
	obj->GetTransform().vPos = { -50, 0 };
	vHp.push_back(obj);

	obj = OBJECTMANAGER->AddObject(new cGameObject(gameObject));
	obj->AddComponent<cHpUI>();
	obj->GetTransform().vPos = { 0, 0 };
	vHp.push_back(obj);

	obj = OBJECTMANAGER->AddObject(new cGameObject(gameObject));
	obj->AddComponent<cHpUI>();
	obj->GetTransform().vPos = { 50, 0 };
	vHp.push_back(obj);
}

void cHpComponent::Update(float ElapsedTime)
{
	int hp	  = player->GetComponent<cPlayerComponent>()->GetHp();
	int maxHp = player->GetComponent<cPlayerComponent>()->GetMaxHp();
	
	if (ceil(float(maxHp) / 2) > vHp.size())
	{
		cGameObject* obj = OBJECTMANAGER->AddObject(new cGameObject(gameObject));
		obj->AddComponent<cHpUI>();
		obj->GetTransform().vPos = { float(vHp.size() * 50 - 50), 0 };
		vHp.push_back(obj);
	}

	for (int i = 0; i < vHp.size(); i++)
	{
		if (hp > 1)
		{
			vHp[i]->GetComponent<cHpUI>()->SetHp(2);
			hp -= 2;
		}
		else if (hp == 1)
		{
			vHp[i]->GetComponent<cHpUI>()->SetHp(1);
			hp -= 1;
		}
		else if (hp == 0)
		{
			vHp[i]->GetComponent<cHpUI>()->SetHp(0);
			break;
		}
	}
}

void cHpComponent::Init(cGameObject * _player)
{
	player = _player;
}
