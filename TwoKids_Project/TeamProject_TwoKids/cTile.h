#pragma once
#include "cComponent.h"
class cTile :
	public cComponent
{
private:
	int iArrX, iArrY;
public:
	cTile();
	virtual ~cTile();

	void SetTileInfo(shared_ptr<sTexture> texture, const D3DXVECTOR2 & pos, int iArrX, int iArrY);
};

