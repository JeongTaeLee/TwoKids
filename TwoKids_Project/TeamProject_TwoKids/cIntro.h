#pragma once
#include "cScene.h"

enum INTRO_STATE
{
	NONE_BACK,
	CHAR_MOVE,
	MONSTER_MOVE,
	ACTIVE_LIGHT,
	ACTIVE_LOGO
};

class cIntro :
	public cScene
{
private:
	cGameObject * background;
	cGameObject * character;
	cGameObject * monster_Left;
	cGameObject * monster_Right;
	cGameObject * spotLight;
	cGameObject * logo;

	INTRO_STATE intro_State;

	float timeDelay;
	float charSpeed;
	float lightAlpha;
	float logoScale;

public:
	cIntro();
	virtual ~cIntro();

public:
	virtual void Init()		override;
	virtual void Release()	override;
	virtual void Update(float ElapseTime)	override;
	virtual void Render()	override;

};

template<typename T>
void Lerp(T *transform, T p, float scale)
{
	*transform = *transform + (p - *transform) * scale;
}
