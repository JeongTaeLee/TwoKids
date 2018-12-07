#pragma once
#include "cComponent.h"
class cHpUI :
	public cComponent
{
private:
	weak_ptr<cSpriteRenderer> wpSpriteRenderer;

public:
	cHpUI();
	virtual ~cHpUI();

	virtual void Start()					override;
	virtual void Update(float ElapsedTime)	override;

	void SetHp(int hp);
};

