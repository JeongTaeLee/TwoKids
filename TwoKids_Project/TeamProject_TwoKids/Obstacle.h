#pragma once
#include "cComponent.h"
class Obstacle :
	public cComponent
{
private:
public:
	Obstacle();
	~Obstacle();

	virtual void Start()						override;
	virtual void Destroy()						override;
	virtual void Update(float ElapsedTime)		override;
	virtual void Receive(const wstring & key)	override;
};

