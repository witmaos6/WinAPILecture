#include "pch.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CObject.h"
#include "CCamera.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for (int i = 0; i < (int)_iFrameCount; i++)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * i;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Update()
{
	if (m_bFinish)
	{
		return;
	}

	m_fAccTime += fDT;

	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		++m_iCurFrm;
		if (m_iCurFrm >= (int)m_vecFrm.size())
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.0f;
			return;
		}

		m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;
	}
}

void CAnimation::Render(HDC _dc)
{
	if (m_bFinish)
	{
		return;
	}

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	tAnimFrm CurFrm = m_vecFrm[m_iCurFrm];
	vPos += CurFrm.vOffset;
	
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	int x = (int)(vPos.X - CurFrm.vSlice.X / 2.f);
	int y = (int)(vPos.Y - CurFrm.vSlice.Y / 2.f);
	int cx = (int)(CurFrm.vSlice.X);
	int cy = (int)(CurFrm.vSlice.Y);

	TransparentBlt(_dc, x, y, cx, cy, m_pTex->GetDC()
		, (int)CurFrm.vLT.X
		, (int)CurFrm.vLT.Y
		, (int)CurFrm.vSlice.X
		, (int)CurFrm.vSlice.Y
		, RGB(255, 0, 255));
}
