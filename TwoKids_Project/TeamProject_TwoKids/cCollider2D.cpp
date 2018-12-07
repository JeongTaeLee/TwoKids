#include "DXUT.h"
#include "cCollider2D.h"

cCollider2D::cCollider2D()
{
	vColliderPos = D3DXVECTOR2(0, 0);
	
	SetRect(&reCollider, 0, 0, 0, 0);

	colliderWidth	= 0;
	colliderHeight	= 0;

	bIsTrigger = false; 
}
cCollider2D::~cCollider2D()
{
}
void cCollider2D::Start()
{
	COLLIDERMANAGER->AddCollider(dynamic_pointer_cast<cCollider2D>(shared_from_this()));
}
void cCollider2D::Destroy()
{
	COLLIDERMANAGER->DestroyCollider(dynamic_pointer_cast<cCollider2D>(shared_from_this()));
}
void cCollider2D::Update(float ElasedTime)
{
	D3DXMATRIXA16 matWorld			= GetTransform().GetWorldMatrix();
	D3DXVECTOR2 playerColliderPos	= D3DXVECTOR2(matWorld._41 + vColliderPos.x, matWorld._42 + vColliderPos.y);

	SetRect(&reCollider, playerColliderPos.x - colliderWidth / 2, playerColliderPos.y - colliderHeight / 2,
		playerColliderPos.x + colliderWidth / 2, playerColliderPos.y + colliderHeight / 2);

	SetVertex();
}
void cCollider2D::Render()
{
	if (!TEXTUREMANAGER->GetRenderCollider())
		return;

	TEXTUREMANAGER->GetD3DXLine()->Begin();
	TEXTUREMANAGER->GetD3DXLine()->Draw(vVertex, 5, D3DCOLOR_XRGB(255, 0, 0));
	TEXTUREMANAGER->GetD3DXLine()->End();
}
void cCollider2D::SetColliderPos(const D3DXVECTOR2 & colliderPos)
{
	vColliderPos = colliderPos;

	D3DXMATRIXA16 matWorld			= GetTransform().GetWorldMatrix();
	D3DXVECTOR2 playerColliderPos	= D3DXVECTOR2(matWorld._41 + vColliderPos.x, matWorld._42 + vColliderPos.y);

	SetRect(&reCollider, playerColliderPos.x - colliderWidth / 2, playerColliderPos.y - colliderHeight / 2,
		playerColliderPos.x + colliderWidth / 2, playerColliderPos.y + colliderHeight / 2);
	SetVertex();
}
void cCollider2D::SetColliderRect(const RECT & reRect)
{
	colliderWidth = reRect.right;
	colliderHeight = reRect.bottom;

	reCollider = reRect;

	SetVertex();
}
const RECT & cCollider2D::GetColliderRect()
{
	return reCollider;
}

void cCollider2D::SetVertex()
{
	vVertex[0] = D3DXVECTOR2((float)reCollider.left, (float)reCollider.top);
	vVertex[1] = D3DXVECTOR2((float)reCollider.right, (float)reCollider.top);
	vVertex[2] = D3DXVECTOR2((float)reCollider.right, (float)reCollider.bottom);
	vVertex[3] = D3DXVECTOR2((float)reCollider.left, (float)reCollider.bottom);
	vVertex[4] = D3DXVECTOR2((float)reCollider.left, (float)reCollider.top);
}

void cCollider2D::OnCollider(shared_ptr<cCollider2D> collider)
{
	if (collider->GetTrigger() || this->bIsTrigger)
	{
		gameObject->OnTriggerSend(collider);
		return;
	}
	else
	{
		shared_ptr<cRigidBody> spRigidBody = collider->GetComponent<cRigidBody>();

		if (spRigidBody)
		{
			// 부모가 있는지 체크
			cGameObject * object = collider->gameObject->GetParentObject();
			
			if (!object)
				object = collider->gameObject;
	
			// 교차 렉트와 상대 렉트.
			RECT reIntersect;
			RECT reOpponentCollider = collider->GetColliderRect();
			IntersectRect(&reIntersect, &reCollider,&reOpponentCollider);
	
			D3DXVECTOR2 vCollLength;
			vCollLength.x = (float)(reIntersect.right - reIntersect.left);
			vCollLength.y = (float)(reIntersect.bottom - reIntersect.top);
			
			// 자기의 콜리더 위치
			D3DXVECTOR2 vMyCollPos;
			vMyCollPos.x = (float)(reCollider.left + reCollider.right) / 2;
			vMyCollPos.y = (float)(reCollider.top + reCollider.bottom) / 2;
	
			// 상대 콜리더 위치
			D3DXVECTOR2 OpponentColliderPos;
			OpponentColliderPos.x = (float)(reOpponentCollider.left + reOpponentCollider.right) / 2;
			OpponentColliderPos.y = (float)(reOpponentCollider.top + reOpponentCollider.bottom) / 2;
	
			// 오른쪽 왼쪽 충돌 처리
			if (vCollLength.x < vCollLength.y)
			{
				if (vMyCollPos.x < OpponentColliderPos.x)
					object->GetTransform().vPos.x += vCollLength.x;
				else																	  
					object->GetTransform().vPos.x -= vCollLength.x;
			}
			// 아래쪽 위치.
			else
			{
				if (vMyCollPos.y < OpponentColliderPos.y)
					object->GetTransform().vPos.y += vCollLength.y;
				else
					object->GetTransform().vPos.y -= vCollLength.y;
			}
		}
		gameObject->OnColliderSend(collider);
	}
	
}
