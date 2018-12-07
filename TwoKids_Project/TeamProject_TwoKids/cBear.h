#pragma once
#include "cMonsterComponent.h"

class cBear
	:public cMonsterComponent
{
public:
	cBear();
	~cBear();

	virtual void Start()	override;
	virtual void Update(float ElaspedTime)	override;
};

