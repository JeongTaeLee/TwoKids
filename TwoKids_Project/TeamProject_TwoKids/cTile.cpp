#include "DXUT.h"
#include "cTile.h"


cTile::cTile()
{
}


cTile::~cTile()
{
}

void cTile::SetTileInfo(shared_ptr<sTexture> texture, const D3DXVECTOR2 & pos, int _iArrX, int _iArrY)
{	
	GetTransform().vPos = pos;

	shared_ptr<cSpriteRenderer> renderer = AddComponent<cSpriteRenderer>();
	renderer->SetTexture(texture);
	renderer->SetMidCenter();

	iArrX = _iArrX;
	iArrY = _iArrY;
}
