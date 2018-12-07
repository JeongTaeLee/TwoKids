#include "DXUT.h"
#include "cItem.h"

#include "cMap.h"

#include "cPlayerComponent.h"

cItem::cItem()
{
}


cItem::~cItem()
{
}

void cItem::Start()
{
	moveY = -1;
	pastRange = 0;
	AddComponent<cCollider2D>()->SetColliderRect({ 0, 0, 20, 20 });
}

void cItem::Update(float ElapseTime)
{
	if (pastRange < -20)
	{
		moveY = -moveY;
		pastRange = -20;
	}
	else if (pastRange > 20)
	{
		moveY = -moveY;
		pastRange = 20;
	}
	GetTransform().vPos.y += moveY * ElapseTime * 40;
	pastRange += moveY * ElapseTime * 40;
}

void cItem::OnTriggerStay(shared_ptr<cCollider2D> collider)
{
	if (collider->GetTag() == L"Player")
	{
		gameObject->GetParentObject()->GetComponent<cMap>()->Destroyitem(gameObject);
		collider->GetComponent<cPlayerComponent>()->SetItemAbility(itemKind);
	}
}

void cItem::SetItemKind(ITEM_KIND kind)
{
	switch (kind)
	{
	case CLOVER:
		AddComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"Clover", L"./Resource/Texture/Item/Clover.png"));
		break;
	case COFFE:
		AddComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"Coffe", L"./Resource/Texture/Item/Coffe.png"));
		break;
	case SHOES:
		AddComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"Shoes", L"./Resource/Texture/Item/Shoes.png"));
		break;
	case MILK:
		AddComponent<cSpriteRenderer>()->SetTexture(MyAddTexture(L"Milk", L"./Resource/Texture/Item/Milk.png"));
		break;
	default:
		break;
	}
	GetComponent<cSpriteRenderer>()->SetMidCenter();
	itemKind = kind;
}
