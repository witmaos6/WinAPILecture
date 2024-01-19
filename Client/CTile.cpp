#include "pch.h"
#include "CTile.h"

#include "CTexture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iIdx(2)
{
	SetScale(Vec2((float)(TextureDist), (float)(TextureDist)));
}

CTile::~CTile()
{
}

void CTile::Update()
{
}

void CTile::Render(HDC _dc)
{
	if (m_pTileTex == nullptr || m_iIdx == -1)
	{
		return;
	}

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = iWidth / TextureDist;
	UINT iMaxRow = iHeight / TextureDist;

	UINT iCurRow = (UINT)m_iIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iIdx % iMaxCol;

	if (iMaxRow <= iCurRow)
	{
		assert(nullptr);
	}

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();
	
	BitBlt(_dc
		, (int)(vRenderPos.X)
		, (int)(vRenderPos.Y)
		, (int)(vScale.X)
		, (int)(vScale.Y)
		, m_pTileTex->GetDC()
		, (int)(iCurCol * TextureDist)
		, (int)(iCurRow * TextureDist)
		, SRCCOPY);
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iIdx, sizeof(int), 1, _pFile);
}
