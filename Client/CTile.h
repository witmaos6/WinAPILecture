#pragma once

#include "CObject.h"

class CTexture;
class CTile : public CObject
{
public:
	CTile();
	~CTile();

private:
	CTexture* m_pTileTex;

	const int TextureDist = 33;

	int m_iIdx;

public:
	void SetTexture(CTexture* _pTex) { m_pTileTex = _pTex; }

	int GetTexDist() { return TextureDist; }

	void AddImgIdx() { m_iIdx++; }

private:
	virtual void Update();
	virtual void Render(HDC _dc);

public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

	CLONE(CTile);
};

