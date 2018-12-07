#include "DXUT.h"


cSpriteRenderer::cSpriteRenderer()
	:spTexture(nullptr), reSrc({0, 0, 0, 0}), vCenterPos(0.0f,0.0f,0.0f), d3dColor(D3DCOLOR_XRGB(255, 255, 255))
{
}


cSpriteRenderer::~cSpriteRenderer()
{
}

void cSpriteRenderer::Render()
{
	TEXTUREMANAGER->GetD3DXSprite()->Begin(dwBeginParameter);
	TEXTUREMANAGER->GetD3DXSprite()->Draw(spTexture->lpTexture,&reSrc , &vCenterPos, nullptr, d3dColor);
	TEXTUREMANAGER->GetD3DXSprite()->End();
}


void cSpriteRenderer::SetBeginParameter(DWORD _dwBeginParameter)
{
	dwBeginParameter = _dwBeginParameter;
}

void cSpriteRenderer::SetMidCenter()
{
	vCenterPos = D3DXVECTOR3(spTexture->info.Width / 2, spTexture->info.Height / 2, 0.0f);
}

void cSpriteRenderer::SetTexture(shared_ptr<sTexture> _spTexture)
{
	spTexture = _spTexture;
	SetRect(&reSrc, 0, 0, spTexture->info.Width, spTexture->info.Height);
}


void cSpriteRenderer::SetCenter(const D3DXVECTOR3 & _vCenterPos)
{
	vCenterPos = _vCenterPos;
}
void cSpriteRenderer::SetColor(const D3DCOLOR & _d3dColor)
{
	d3dColor = _d3dColor;
}
void cSpriteRenderer::SetSrc(const RECT & _reSrc)
{
	reSrc = _reSrc;
}