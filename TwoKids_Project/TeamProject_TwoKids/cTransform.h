#pragma once
#include "cComponent.h"

class cTransform
	: public cComponent
{
public:
	D3DXVECTOR2 vPos;
	D3DXVECTOR2 vScale;
	float		fRotation;

	D3DXMATRIXA16 matPos;
	D3DXMATRIXA16 matRot;
	D3DXMATRIXA16 matScali;

	D3DXMATRIXA16 matLocalMatrix;
	D3DXMATRIXA16 matWorldMatrix;
public:
	cTransform();
	virtual ~cTransform();
	
	virtual void Update(float ElapsedTime)	override;
	
	void translation(const D3DXVECTOR2 & vTrans);

	void SetTransform();

	const D3DXMATRIXA16 & GetWorldMatrix();
	const D3DXMATRIXA16 & GetLocalMatrix();
};
