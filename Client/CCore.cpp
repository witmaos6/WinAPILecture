#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CUIMgr.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "SelectGDI.h"
#include "resource.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	for (UINT i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		if (m_arrPen[i])
		{
			DeleteObject(m_arrPen[i]);
		}
	}

	DestroyMenu(m_hMenu);
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	Vec2 Temp((float)_ptResolution.x, (float) _ptResolution.y);
	ChangeWindowSize(Temp, false);

	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	m_hDC = GetDC(m_hWnd);

	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	CreateBrushPen();

	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CCamera::GetInst()->Init();
	CSceneMgr::GetInst()->Init();

	return S_OK;
}

void CCore::Progress()
{
	CTimeMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update();
	CCamera::GetInst()->Update();

	CSceneMgr::GetInst()->Update();

	CCollisionMgr::GetInst()->Update();

	CUIMgr::GetInst()->Update();

	Clear();

	CSceneMgr::GetInst()->Render(m_pMemTex->GetDC());
	CCamera::GetInst()->Render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->Render();

	CEventMgr::GetInst()->Update();
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);

	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1); // window clear
}

void CCore::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);

	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT Rect = { 0, 0, (long)_vResolution.X, (long)_vResolution.Y };
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 100, 100, Rect.right - Rect.left, Rect.bottom - Rect.top, 0);
}
