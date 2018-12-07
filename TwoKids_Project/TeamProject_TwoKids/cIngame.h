#pragma once
#include "cScene.h"

class cGameObject;


class cIngame :
	public cScene
{
private:
	cGameObject * gameObject;

	cGameObject * pauseScreen;
public:
	cIngame();
	virtual ~cIngame();

	virtual void Init()		override;
	virtual void Release()	override;
	virtual void Update(float ElapseTime)	override;
	virtual void Render()	override;

	void AddPlayer();
};

void Quit();
void Restart(cGameObject *popUp);

