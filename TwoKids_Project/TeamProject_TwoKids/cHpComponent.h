#pragma once
#include "cComponent.h"

class cHpComponent :
	public cComponent
{
private:
	cGameObject * player;
	vector<cGameObject*> vHp;

public:
	cHpComponent();
	virtual ~cHpComponent();

	virtual void Start()					override;
	virtual void Update(float ElapsedTime)	override;
	void Init(cGameObject *_player);
};

