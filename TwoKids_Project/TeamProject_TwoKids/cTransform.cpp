#include "DXUT.h"
#include "cTransform.h"


cTransform::cTransform()
	:vPos(D3DXVECTOR2(0, 0)), vScale(D3DXVECTOR2(1, 1)), fRotation(0.0f)
{
}


cTransform::~cTransform()
{
}

void cTransform::Update(float ElapsedTime)
{
	D3DXMatrixTranslation(&matPos, GetTransform().vPos.x, GetTransform().vPos.y, 0.0f);
	D3DXMatrixRotationZ(&matRot, GetTransform().fRotation);
	D3DXMatrixScaling(&matScali, GetTransform().vScale.x, GetTransform().vScale.y, 0.0f);

	matLocalMatrix = matScali * matRot * matPos;

	if (GetParentObject())
	{
		D3DXMATRIXA16 parentMat = GetParentObject()->GetTransform().matWorldMatrix;

		matWorldMatrix = parentMat * matLocalMatrix;
	}
	else
		matWorldMatrix = matLocalMatrix;
}

void cTransform::translation(const D3DXVECTOR2 & vTrans)
{
	vPos += vTrans;
}

void cTransform::SetTransform()
{
	TEXTUREMANAGER->GetD3DXSprite()->SetTransform(&matWorldMatrix);
}

const D3DXMATRIXA16 & cTransform::GetWorldMatrix()
{
	return matWorldMatrix;
}

const D3DXMATRIXA16 & cTransform::GetLocalMatrix()
{
	return matLocalMatrix;
}
