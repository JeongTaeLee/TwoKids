#pragma once
#include "cScene.h"
class cLoseScene :
	public cScene
{
private:
	cGameObject * lose;

public:
	cLoseScene();
	virtual ~cLoseScene();

	virtual void Init()		override;
	virtual void Release()	override;
	virtual void Update(float ElapseTime)	override;
	virtual void Render()	override;
};

