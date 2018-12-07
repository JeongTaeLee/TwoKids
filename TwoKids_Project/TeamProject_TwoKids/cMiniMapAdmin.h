#pragma once
#include "cComponent.h"

class cMiniMapAdmin :
	public cComponent
{
private:

public:
	cMiniMapAdmin();
	virtual ~cMiniMapAdmin();

	virtual void Start()	override;
	virtual void Destroy()	override;
	void ResetMiniMap();
	void UpdateMiniMap(cGameObject * lpNowMap);

	cGameObject* CreateMiniMap(const D3DXVECTOR2 & pos, bool boss, bool NowMap);
};

