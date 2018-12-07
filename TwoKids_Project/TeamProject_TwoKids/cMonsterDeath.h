#pragma once
#include "cComponent.h"
class cMonsterDeath :
	public cComponent
{
private:
	float delay;
	float alpha;

public:
	cMonsterDeath();
	virtual ~cMonsterDeath();

public:
	virtual void Start()					override;
	virtual void Update(float ElapsedTime)	override;
};

