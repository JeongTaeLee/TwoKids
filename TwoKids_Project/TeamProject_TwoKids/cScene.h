#pragma once
class cScene
{
public:
	cScene();
	virtual ~cScene();

	virtual void Init()		PURE;
	virtual void Release()	PURE;
	virtual void Update(float ElapseTime)	PURE;
	virtual void Render()	PURE;
};

