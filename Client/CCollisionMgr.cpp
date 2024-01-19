#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	:m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	UINT ColBitset = (1 << iCol);
	if (m_arrCheck[iRow] & ColBitset)
	{
		m_arrCheck[iRow] &= ~ColBitset;
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

void CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; iRow++)
	{
		for (UINT iCol = 0; iCol < (UINT)GROUP_TYPE::END; iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (size_t L = 0; L < vecLeft.size(); L++)
	{
		if (vecLeft[L]->GetCollider() == nullptr)
			continue;

		for (size_t R = 0; R < vecRight.size(); R++)
		{
			if (vecRight[R]->GetCollider() == nullptr || vecLeft[L] == vecRight[R])
				continue;

			CCollider* pLeftCol = vecLeft[L]->GetCollider();
			CCollider* pRightCol = vecRight[R]->GetCollider();

			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			
			if (m_mapColInfo.find(ID.ID) == m_mapColInfo.end())
			{
				m_mapColInfo[ID.ID] = false;
			}

			map<const ULONGLONG, bool>::iterator It = m_mapColInfo.find(ID.ID);

			if (IsCollision(pLeftCol, pRightCol))
			{
				if (It->second)
				{
					if (vecLeft[L]->IsDead() || vecRight[R]->IsDead())
					{
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						It->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					if (!vecLeft[L]->IsDead() && !vecRight[R]->IsDead())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						It->second = true;
					}
				}
			}
			else
			{
				if (It->second)
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					It->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.X - vLeftPos.X) < (vLeftScale.X + vRightScale.X) / 2.f
		&& abs(vRightPos.Y - vLeftPos.Y) < (vLeftScale.Y + vRightScale.Y) / 2.f)
	{
		return true;
	}

	return false;
}
