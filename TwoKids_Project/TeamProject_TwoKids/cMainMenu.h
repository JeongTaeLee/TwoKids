#pragma once
#include "cScene.h"
class cMainMenu :
	public cScene
{
private:

	cGameObject * background;
	cGameObject * clover;
	cGameObject * howto;
	cGameObject * credit;

	enum MAINMENUSTATE {
		IDLE,
		SETTING,

	};
	int state;
	float cloverSpeed;


public:
	cMainMenu();
	virtual ~cMainMenu();

	virtual void Init()	override;
	virtual void Release()	override;
	virtual void Update(float ElapsedTime)	override;
	virtual void Render()	override;


};

	void ClickHowto(cGameObject *howto);
	void OpenSettings(cGameObject *credit);
	void Exit();
