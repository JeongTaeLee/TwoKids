#pragma once
#include "cComponent.h"
class cBulletBase :
	public cComponent
{
protected:
	weak_ptr<cSpriteRenderer> wpSpriteRenderer;
	D3DXVECTOR2 vDirection;

	int iDamage;
	float fSpeed;
public:
	cBulletBase();
	virtual ~cBulletBase();

	virtual void Start()					override;
	virtual void Update(float ElapsedTime)	override;

	bool IsOutMap();

	void SetBulletInfo(const D3DXVECTOR2 & pos, const D3DXVECTOR2 & vDirection, float _fSpeed, int _fDamage);
	void SetAnimation(shared_ptr<VecTexture> animations);
	void SetCollider(const RECT & reRect);
	void SetTexture(shared_ptr<sTexture> texture);

	int GetDamage() {	return iDamage;}

	virtual void OnTriggerStay(shared_ptr<cCollider2D> collider);
};

