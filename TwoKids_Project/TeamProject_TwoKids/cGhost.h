#pragma once
#include "cMonsterComponent.h"
class cGhost :
	public cMonsterComponent
{
public:
	cGhost();
	virtual ~cGhost();

	virtual void Start()	override;
	virtual void Update(float ElaspedTime)	override;
};

