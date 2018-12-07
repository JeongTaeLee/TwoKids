#pragma once
#include "cMonsterComponent.h"
class cBee :
	public cMonsterComponent
{
public:
	cBee();
	virtual ~cBee();

	virtual void Start()	override;
	virtual void Update(float ElaspedTime)	override;
};

