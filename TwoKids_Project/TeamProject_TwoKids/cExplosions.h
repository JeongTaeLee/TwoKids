#pragma once
#include "cComponent.h"
class cExplosions :
	public cComponent
{
private:
	DWORD dwDestroyType;

	weak_ptr<cSpriteRenderer>	wpSpriteRenderer;
	weak_ptr<cAnimater>			wpAnimater;
public:
	cExplosions();
	virtual ~cExplosions();

	virtual void Start()					override;
	virtual void Destroy()					override;
	virtual void Update(float ElapsedTime)	override;
	
	void SetAnimation(shared_ptr<VecTexture> vecTexture);
};

