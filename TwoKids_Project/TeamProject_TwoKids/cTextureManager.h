#pragma once
#include "singleton.h"

struct sTexture
{
	LPDIRECT3DTEXTURE9	lpTexture;
	D3DXIMAGE_INFO		info;

	sTexture(LPDIRECT3DTEXTURE9 _lpTexture, D3DXIMAGE_INFO _info)
		:lpTexture(_lpTexture), info(_info){}
	~sTexture() {
		SAFE_RELEASE(lpTexture);
	}
};

using VecTexture = vector< shared_ptr<sTexture> >;

class cTextureManager :
	public singleton<cTextureManager>
{
private:
	map<wstring, shared_ptr<sTexture> >		spTextures;
	map<wstring, shared_ptr<VecTexture> >	spVecTextures;

	LPD3DXSPRITE	lpD3DXSprite;
	LPD3DXLINE		lpD3DXLine;

	bool			bRenderCollider = false;
public:
	cTextureManager();
	virtual ~cTextureManager();

	shared_ptr<sTexture> AddTexture(const wstring & key, const wstring &path);
	shared_ptr<VecTexture> AddVecTexture(const wstring & key, const wstring & path, int min, int max);

	shared_ptr<sTexture> GetTexture(const wstring & key);
	shared_ptr<VecTexture> GetVecTexture(const wstring & key);

	const LPD3DXSPRITE & GetD3DXSprite();
	const LPD3DXLINE & GetD3DXLine();

	void LostDevice();
	void ResetDevice();

	void SetRenderCollider(bool _SetRenderCheck);
	bool GetRenderCollider();
};

#define TEXTUREMANAGER cTextureManager::GetInstance()

#define MyAddTexture(key, path) TEXTUREMANAGER->AddTexture(key, path)
#define MyAddVecTexture(key, path, min, max) TEXTUREMANAGER->AddVecTexture(key, path, min, max)

#define MyGetTexture(key,path) TEXTUREMANAGER->GetTexture(key)
#define MyGetVecTexture(key,path, min, max) TEXTUREMANAGER->GetVecTexture(key)