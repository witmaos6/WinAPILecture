#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	:m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.0f)
	, m_fAccTime(0.5f)
	, m_eEffect(CAM_EFFECT::NONE)
	, m_pVeilTex(nullptr)
	, m_fEffectDuration(0.f)
	, m_fCurTime(0.f)
{
}

CCamera::~CCamera()
{
}

void CCamera::Init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.X, (UINT)vResolution.Y);
}

void CCamera::Update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
	{
		m_vLookAt.Y -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		m_vLookAt.Y += 500.f * fDT;
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		m_vLookAt.X -= 500.f * fDT;
	}
	if (KEY_HOLD(KEY::RIGHT))
	{
		m_vLookAt.X += 500.f * fDT;
	}

	CalBetweenCenterAndLookAt();
}

void CCamera::Render(HDC _dc)
{
	if (m_eEffect == CAM_EFFECT::NONE)
	{
		return;
	}

	float fRatio = 0.f;

	if (m_eEffect == CAM_EFFECT::FADE_OUT)
	{
		m_fCurTime += fDT;
		
		if (m_fEffectDuration < m_fCurTime)
		{
			m_eEffect = CAM_EFFECT::NONE;
			return;
		}

		fRatio = m_fCurTime / m_fEffectDuration;
	}

	int iAlpha = (int)(255.f * fRatio);

	BLENDFUNCTION BF = {};
	BF.BlendOp = AC_SRC_OVER;
	BF.BlendFlags = 0;
	BF.AlphaFormat = 0;
	BF.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc
		, 0
		, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, BF);
}

void CCamera::CalBetweenCenterAndLookAt()
{
	m_fAccTime += fDT;

	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vBetweenCenterAndLookAt = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
