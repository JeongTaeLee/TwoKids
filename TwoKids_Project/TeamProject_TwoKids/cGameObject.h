#pragma once

#include "cTransform.h"

class cComponent;
class cCollider2D;

class cGameObject
{
private:
	cTransform transform;
	
	cGameObject *					lpParentObject;
	
	list< cGameObject* >			liChildObjects;
	list< shared_ptr<cComponent> >	liComponents;
	
	wstring tcObjectName;
	wstring tcTag;

	bool	bDestroy;
	bool	bActive;

	int iDrawingOrder;
public: 
	cGameObject(cGameObject * parent = nullptr);
	cGameObject(const wstring & _tcObjectName, cGameObject * parent = nullptr);
	cGameObject(const wstring & _tcObjectName, const wstring & _tcTag, cGameObject * parent = nullptr);

	virtual ~cGameObject();

	void Release();
	void Update(float ElapseTime);
	void Render();

	cGameObject *	AddChild	(cGameObject * lpChild);
	void			DeleteChild	(cGameObject * lpChild);

	void	Send(const wstring & message);
	
	void	OnTriggerSend(shared_ptr<cCollider2D> collider);
	void	OnColliderSend(shared_ptr<cCollider2D> collider);

	void	CutParent();

	void	Destroy();
	inline bool	GetDestroy()							{ return bDestroy; }

	void	SetActive(bool _bActive);
	inline bool	GetActive()								{ return bActive; }

	void	SetDrawingOrder(int order);
	inline int		GetDrawingOrder()					{ return iDrawingOrder; }

	const inline wstring &		GetObjectName()			{ return tcObjectName; }
	const inline wstring &		GetTag()				{ return tcTag; }

	inline cTransform &	GetTransform()						{ return transform; }
	
	inline cGameObject *	GetParentObject()				{ return lpParentObject; }
	void			SetParentObject(cGameObject * object)	{ lpParentObject = object; }

	inline list< cGameObject* > & GetChildList()			{ return liChildObjects; }

#pragma region _ComponentFunc
	template<class component>
	shared_ptr<component> AddComponent()
	{
		static_assert(std::is_base_of<cComponent, component>::value, "AddComponentError : 컴포넌트를 상속받지 않은 객체입니다");

		shared_ptr<component> tempComponent(new component);

		tempComponent->SetOwner(this);
		tempComponent->Start();
		
		liComponents.push_back(tempComponent);

		return tempComponent;
	}
	template<class component>
	shared_ptr<component> GetComponent()
	{
		static_assert(std::is_base_of<cComponent, component>::value, "GetComponentError : 컴포넌트를 상속받지 않은 객체입니다");

		for (auto Iter : liComponents)
		{
			shared_ptr<component> get = dynamic_pointer_cast<component>(Iter);

			if (!get)
				continue;

			return get;
		}

		return {};
	}
	template<class component>
	void DeleteComponent() 
	{
		static_assert(std::is_base_of<cComponent, component>::value, "GetComponentError : 컴포넌트를 상속받지 않은 객체입니다");
	
		for (auto Iter = liComponents.begin(); Iter != liComponents.end();)
		{
			shared_ptr<component> get = dynamic_pointer_cast<component>((*Iter));

			if (!get)
				++Iter;
			else
			{
				get->Destroy();
				liComponents.erase(Iter);
				return;
			}
		}

	}
#pragma endregion _ComponentFunc
#pragma region _Sorting
	static bool YSort(cGameObject * object01, cGameObject * object02)
	{
		if (object01->GetDrawingOrder() == object02->GetDrawingOrder())
			return object01->GetTransform().matWorldMatrix._42 < object02->GetTransform().matWorldMatrix._42;
		else
			return false;
	}

	static bool OrderSort(cGameObject * object01, cGameObject * object02)
	{
		return object01->GetDrawingOrder() < object02->GetDrawingOrder();
	}
#pragma endregion _Sorting
};