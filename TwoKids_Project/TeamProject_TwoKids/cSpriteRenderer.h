#pragma once
#include "cComponent.h"
class cSpriteRenderer :
	public cComponent
{
private:
	shared_ptr<sTexture> spTexture;

	RECT		reSrc;
	D3DXVECTOR3 vCenterPos;

	D3DCOLOR	d3dColor;

	DWORD		dwBeginParameter = D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE;
public:
	cSpriteRenderer();
	virtual ~cSpriteRenderer();

	virtual void Render()					override;

	void SetBeginParameter(DWORD _dwBeginParameter);
	void SetMidCenter();
	void SetTexture(shared_ptr<sTexture> _spTexture);
	void SetCenter(const D3DXVECTOR3 & _vCenterPos);
	void SetColor(const D3DCOLOR & _d3dColor);
	void SetSrc(const RECT & _reSrc);

	D3DXIMAGE_INFO GetImageInfo() { return spTexture->info; }
};

