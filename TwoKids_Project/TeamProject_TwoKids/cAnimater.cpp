#include "DXUT.h"
#include "cAnimater.h"


cAnimater::cAnimater()
	:spNowAnimationClip(nullptr), spSpriteRenderer(nullptr),
	iNowCount(0), iNowAmount(0), fFrameTime(0.f),
	tcIdleKey(L"None"), bAnimationLock(false),
	bLooping(false), bFrameEnd(false)
{}


cAnimater::~cAnimater()
{
}

void cAnimater::Start()
{
	spSpriteRenderer = GetComponent<cSpriteRenderer>();
}
void cAnimater::Destroy()
{
	spSpriteRenderer.reset();
	spNowAnimationClip.reset();
	mapAnimationClips.clear();
}
void cAnimater::Update(float ElapseTime)
{
	if (!spNowAnimationClip)
		return;

	if (!spSpriteRenderer)
	{
		spSpriteRenderer = GetComponent<cSpriteRenderer>();
		return;
	}

	fFrameTime += ElapseTime;

	if (fFrameTime >= spNowAnimationClip->fFrameTime)
	{
		fFrameTime = 0;
	
		if (!spSpriteRenderer)
			return;

		spSpriteRenderer->SetTexture((*spNowAnimationClip)[iNowCount]);

		if (iNowCount < iNowAmount)
		{
			if (!bAnimationLock)
			{
				if (iNowCount == 0)
					bFrameEnd = false;
				iNowCount++;
			}
		}
		else
		{
			bFrameEnd = true;
			iNowCount = 0;
		}
	}
}

void cAnimater::AddAnimationClip(const wstring & key, shared_ptr<VecTexture> vecTexture, float _fFrameTime)
{
	auto find = mapAnimationClips.find(key);

	if (find != mapAnimationClips.end())
		return;
	
	shared_ptr<sAnimationClip> tempClip =
		mapAnimationClips.insert(make_pair(key, new sAnimationClip(key, vecTexture, _fFrameTime))).first->second;
	
	if (tcIdleKey == L"None")
	{
		tcIdleKey = key;
		spNowAnimationClip = tempClip;
		spSpriteRenderer->SetTexture((*tempClip)[0]);
	}

	iNowAmount = (*tempClip->spAnimations).size() - 1;
	iNowCount = 0;
}

void cAnimater::ChangeAnimation(const wstring & key)
{
	auto find = mapAnimationClips.find(key);

	if (find == mapAnimationClips.end())
	{
		spNowAnimationClip = mapAnimationClips.find(tcIdleKey)->second;
		iNowAmount = (*spNowAnimationClip->spAnimations).size() - 1;
		iNowCount = 0;
		return;
	}

	if (spNowAnimationClip)
	{
		if (spNowAnimationClip->tcClipKey == key)
			return;
	}

	spNowAnimationClip.reset();
	spNowAnimationClip = find->second;
		
	iNowAmount			= spNowAnimationClip->spAnimations->size() - 1;
	iNowCount			= 0;

	bAnimationLock		= false;

	spSpriteRenderer->SetTexture((*spNowAnimationClip)[0]);

	fFrameTime = 0.0f;
}

void cAnimater::SetLockAnimation(int lockFrame, bool _bAhimiationLock)
{
	spSpriteRenderer->SetTexture((*spNowAnimationClip)[lockFrame]);
	bAnimationLock = _bAhimiationLock;
}

void cAnimater::SetLockAnimation(bool _bAnimationlock)
{
	bAnimationLock = _bAnimationlock;
}

void cAnimater::SetAnimationFrame(int frame)
{
	spSpriteRenderer->SetTexture((*spNowAnimationClip)[frame]);
	fFrameTime = 0.0f;
}

void cAnimater::SetLooping(bool _bLooping)
{
	bLooping = _bLooping;
}

bool cAnimater::GetFrameEnd()
{
	return bFrameEnd;
}

const wstring & cAnimater::GetNowKey()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return spNowAnimationClip->tcClipKey;
}

shared_ptr<sTexture> sAnimationClip::operator[](int index)
{
	if (index < 0 || spAnimations->size() - 1 < index)
		return nullptr;

	return (*spAnimations)[index];
}
