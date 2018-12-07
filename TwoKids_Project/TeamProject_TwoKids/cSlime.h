#pragma once
#include "cMonsterComponent.h"
class cSlime :
	public cMonsterComponent
{
private:
	float bulletDelay;

public:
	cSlime();
	virtual ~cSlime();

public:
	virtual void Start()	override;
	virtual void Update(float ElaspedTime)	override;
};

