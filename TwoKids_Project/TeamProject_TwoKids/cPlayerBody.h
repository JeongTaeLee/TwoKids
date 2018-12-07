#pragma once
#include "cComponent.h"

class cPlayerComponent;

class cPlayerBody :
	public cComponent
{
private:
	weak_ptr<cSpriteRenderer>	wpSpriteRenderer;
	weak_ptr<cAnimater>			wpAnimater;

	weak_ptr<cPlayerComponent>	wpPlayerComponent;
public:
	cPlayerBody();
	virtual ~cPlayerBody();

	virtual void Start()							override;
	virtual void Update(float ElapsedTime)			override;
};

