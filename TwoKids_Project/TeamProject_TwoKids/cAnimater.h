#pragma once
#include "cComponent.h"

struct sAnimationClip
{
	wstring tcClipKey;

	shared_ptr<VecTexture>	spAnimations;
	float					fFrameTime;

	sAnimationClip(const wstring & _tcClipKey, shared_ptr<VecTexture> _spAnimations, float _fFrameTime)
		:tcClipKey(_tcClipKey), spAnimations(_spAnimations), fFrameTime(_fFrameTime) {}

	~sAnimationClip(){
		spAnimations.reset();
	}

	shared_ptr<sTexture> operator [](int index);
};

class cAnimater :
	public cComponent
{
private:
	map<wstring, shared_ptr<sAnimationClip> > mapAnimationClips;

	wstring	tcIdleKey;

	shared_ptr<sAnimationClip>		spNowAnimationClip;
	shared_ptr<cSpriteRenderer>		spSpriteRenderer;

	int		iNowCount;
	int		iNowAmount;

	float	fFrameTime;

	bool	bAnimationLock;

	bool	bLooping;
	bool	bFrameEnd;
public:
	cAnimater();
	virtual ~cAnimater();

	virtual void Start()					override;
	virtual void Destroy()					override;
	virtual void Update(float ElapseTime)	override;

	void AddAnimationClip(const wstring & key, shared_ptr<VecTexture> vecTexture, float fFrameTime);
	void ChangeAnimation(const wstring & key);

	void SetLockAnimation(int lockFrame, bool _bAhimiationLock);
	void SetLockAnimation(bool _bAnimationlock);
	void SetAnimationFrame(int frame);

	void SetLooping(bool _bLooping);

	bool GetFrameEnd();

	const wstring & GetNowKey();
};

