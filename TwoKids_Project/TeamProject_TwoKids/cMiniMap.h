#pragma once
#include "cComponent.h"
class cMiniMap :
	public cComponent
{
public:
	cMiniMap();
	virtual ~cMiniMap();

	void SetMiniMap(bool bBoss);
};

