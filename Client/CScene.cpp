#include "pch.h"
#include "CScene.h"

#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CCore.h"

CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
	, m_pPlayer(nullptr)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (m_arrObj[i][j])
			{
				delete m_arrObj[i][j];
			}
		}
	}
}

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->Update();
			}
		}
	}
}

void CScene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); j++)
		{
			if (m_arrObj[i][j])
			{
				m_arrObj[i][j]->FinalUpdate();
			}
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		if((UINT)GROUP_TYPE::TILE == i)
		{
			RenderTile(_dc);
			continue;
		}

		vector<CObject*>::iterator It = m_arrObj[i].begin();

		for (; It != m_arrObj[i].end();)
		{
			if (!(*It)->IsDead())
			{
				(*It)->Render(_dc);
				++It;
			}
			else
			{
				It = m_arrObj[i].erase(It);
			}
		}
	}
}

void CScene::RenderTile(HDC _dc)
{
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	Vec2 vCameraLook = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vLeftTop = vCameraLook - vResolution / 2.f;

	int iTileSize = 33;

	int iLTCol = (int)vLeftTop.X / iTileSize;
	int iLTRow = (int)vLeftTop.Y / iTileSize;

	int iClientWidth = ((int)vResolution.X / iTileSize) + 1;
	int iClientHeight = ((int)vResolution.Y / iTileSize) + 1;

	for(int iCurRow = iLTRow; iCurRow < (iLTRow + iClientHeight); iCurRow++)
	{
		for(int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); iCurCol++)
		{
			if(iCurCol < 0 || m_iTileX <= (UINT)iCurCol
				|| iCurRow < 0 || m_iTileY <= (UINT)iCurRow)
			{
				continue;
			}

			int iIdx = (m_iTileX * iCurRow) + iCurCol;

			vecTile[iIdx]->Render(_dc);
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"Texture//Tile//TILE.bmp");

	for (int i = 0; i < (int)_iYCount; i++)
	{
		for (int j = 0; j < (int)_iXCount; j++)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)(j * pTile->GetTexDist()), (float)(i * pTile->GetTexDist())));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentsPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	for (CObject* Tile : vecTile)
	{
		((CTile*)Tile)->Load(pFile);
	}

	fclose(pFile);
}
