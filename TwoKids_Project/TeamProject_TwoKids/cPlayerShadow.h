#pragma once
#include "cComponent.h"
class cPlayerShadow :
	public cComponent
{
public:
	cPlayerShadow();
	virtual ~cPlayerShadow();

	virtual void Start()	override;
};

