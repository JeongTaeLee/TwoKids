#include "DXUT.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
	D3DXCreateSprite(g_device, &lpD3DXSprite);
	D3DXCreateLine(g_device, &lpD3DXLine);
	
}


cTextureManager::~cTextureManager()
{
	spTextures.clear();
	SAFE_RELEASE(lpD3DXSprite);
	SAFE_RELEASE(lpD3DXLine);
}

shared_ptr<sTexture> cTextureManager::AddTexture(const wstring & key, const wstring & path)
{
	auto find = spTextures.find(key);

	if (find != spTextures.end())
		return find->second;

	LPDIRECT3DTEXTURE9	lpTexture;
	D3DXIMAGE_INFO		info;

	if (D3DXCreateTextureFromFileEx(g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 
		0, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &lpTexture) == S_OK)
	{
		return spTextures.insert(make_pair(key, make_shared<sTexture>(lpTexture, info))).first->second;
	}

#pragma region FAILEDLOAD
	DEBUG_LOGW(L"Failed : " << key.c_str() << L" Path : " << path.c_str());
#pragma endregion FAILEDLOAD
	return nullptr;
}

shared_ptr<VecTexture> cTextureManager::AddVecTexture(const wstring & key, const wstring & path, int min, int max)
{
	auto find = spVecTextures.find(key);

	if (find != spVecTextures.end())
		return find->second;

	shared_ptr<VecTexture> textures = make_shared<VecTexture>();

	for (int i = min; i <= max; i++)
	{
		TCHAR ch[256];
		wsprintf(ch, path.c_str(), i);

		LPDIRECT3DTEXTURE9	lpTexture;
		D3DXIMAGE_INFO		info;

		if (D3DXCreateTextureFromFileEx(g_device, ch, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &lpTexture) == S_OK)
			(*textures).push_back(make_shared<sTexture>(lpTexture, info));
		else
		{
#pragma region FAILEDLOAD
			DEBUG_LOGW(L"Failed : " << key.c_str() << L" Path : " << ch);
#pragma endregion FAILEDLOAD

			textures->clear();
			textures.reset();

			return nullptr;
		}
	}

	return spVecTextures.insert(make_pair(key, textures)).first->second;
}

shared_ptr<sTexture>	cTextureManager::GetTexture(const wstring & key)
{
	auto find = spTextures.find(key);

	if (find == spTextures.end())
		return nullptr;

	return find->second;
}
shared_ptr<VecTexture>	cTextureManager::GetVecTexture(const wstring & key)
{
	auto find = spVecTextures.find(key);

	if (find == spVecTextures.end())
		return nullptr;

	return find->second;
}

const LPD3DXSPRITE & cTextureManager::GetD3DXSprite()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return lpD3DXSprite;
}

const LPD3DXLINE & cTextureManager::GetD3DXLine()
{
	return lpD3DXLine;
}

void cTextureManager::LostDevice()
{
	lpD3DXSprite->OnLostDevice();
}

void cTextureManager::ResetDevice()
{
	lpD3DXSprite->OnResetDevice();
}

void cTextureManager::SetRenderCollider(bool _SetRenderCheck)
{
	bRenderCollider = _SetRenderCheck;
}

bool cTextureManager::GetRenderCollider()
{
	return bRenderCollider;
}
