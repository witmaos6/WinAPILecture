#pragma once


#include "pch.h"
#include "Define.h"

class CTexture;

class CCore
{
	SINGLE(CCore)

private:
	HWND m_hWnd;
	POINT m_ptResolution;
	HDC m_hDC;	

	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

	CTexture* m_pMemTex;

	HMENU m_hMenu;

public:
	int Init(HWND _hWnd, POINT _ptResolution);

	void Progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};
