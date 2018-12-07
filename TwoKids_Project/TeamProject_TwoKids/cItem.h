#pragma once
#include "cComponent.h"

enum ITEM_KIND
{
	CLOVER,
	COFFE,
	SHOES,
	MILK
};
class cItem :
	public cComponent
{
private:
	weak_ptr<cSpriteRenderer>	wpSpriteRenderer;

	ITEM_KIND itemKind;

	float moveY;
	float pastRange;
public:
	cItem();
	virtual ~cItem();
	
public:
	virtual void Start() override;
	virtual void Update(float ElapseTime) override;

	virtual void OnTriggerStay(shared_ptr<cCollider2D> collider) override;

	void SetItemKind(ITEM_KIND kind);
};

