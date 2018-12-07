#pragma once
#include "cMonsterComponent.h"

class cLeaf
	:public cMonsterComponent
{
public:
	cLeaf();
	~cLeaf();

	virtual void Start()	override;
	virtual void Update(float ElaspedTime)	override;
};

