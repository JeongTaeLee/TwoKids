#pragma once
#include "cComponent.h"
class cStageChange :
	public cComponent
{
private:
	weak_ptr<cSpriteRenderer> wpSpriteRenderer;

	bool isstage1;
public:
	cStageChange();
	virtual ~cStageChange();

public:
	virtual void Start() override;
	virtual void Update(float ElapsedTime)	override;

	virtual void OnTriggerStay(shared_ptr<cCollider2D> collider) override;
	void SetStage1(bool isend) { isstage1 = isend; }
};

