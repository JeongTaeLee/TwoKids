#pragma once

class cTransform;
class cGameObject;
class cCollider2D;

class cComponent
	:public enable_shared_from_this < cComponent >
{
private:
	bool		bEnable;

public:
	cGameObject * gameObject;
public:
	cComponent();
	virtual ~cComponent();

	virtual void Start()					{return;};
	virtual void Destroy()					{return;};
	virtual void Update(float ElapseTime)	{return;};
	virtual void Render() { };

	void SetEnable(bool enable);
	bool GetEnable();

	const wstring & GetTag();
	const wstring & GetObjectName();

	cTransform & GetTransform();
	cGameObject * GetParentObject();

	void SetOwner(cGameObject * _gameObject);

	virtual void Receive(const wstring & message) {}

	virtual void OnColliderStay(shared_ptr<cCollider2D> collider) {}
	virtual void OnTriggerStay(shared_ptr<cCollider2D> collider) {}

#pragma region ComponentFunc
	template<class component>
	shared_ptr<component> AddComponent()
	{
		return gameObject->AddComponent<component>();
	}
	template<class component>
	shared_ptr<component> GetComponent()
	{
		return gameObject->GetComponent<component>();
	}
#pragma endregion ComponentFunc
};

#define EGC(COM) GetComponent<##COM##>()
#define EAC(COM) AddComponent<##COM##>()