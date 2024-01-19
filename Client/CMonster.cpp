#include "pch.h"
#include "CMonster.h"

#include "AI.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_tInfo{}
	, m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"Texture\\Monster.bmp");

	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (m_pAI)
	{
		delete m_pAI;
	}
}

void CMonster::Update()
{
	m_pAI->Update();
}

void CMonster::Render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	BitBlt(_dc,
		(int)(vPos.X - (float)(iWidth / 2)),
		(int)(vPos.Y - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, SRCCOPY);

	ComponentRender(_dc);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		
	}
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}
