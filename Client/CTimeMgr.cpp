#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llCurrCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.0f)
	, m_dAcc(0.0f)
	, m_iCallCount(0)
	, m_iFPS(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llCurrCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurrCount);

	m_dDT = (double)(m_llCurrCount.QuadPart - m_llPrevCount.QuadPart) / (double)(m_llFrequency.QuadPart);

	m_llPrevCount = m_llCurrCount;

#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif
}

void CTimeMgr::Render()
{
	++m_iCallCount;
	m_dAcc += m_dDT;

	if (m_dAcc >= 1.0f)
	{
		m_iFPS = m_iCallCount;

		m_dAcc = 0.0f;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};

		swprintf_s(szBuffer, L"FPS: %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
