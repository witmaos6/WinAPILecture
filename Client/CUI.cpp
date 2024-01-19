#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"
#include "CCamera.h"
#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	:m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{

}

CUI::CUI(const CUI& _origin)
	: CObject(_origin)
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
	for (CUI* Child : _origin.m_vecChildUI)
	{
		AddChild(Child->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::Update()
{
	UpdateChild();
}

void CUI::FinalUpdate()
{
	CObject::FinalUpdate();

	m_vFinalPos = GetPos();

	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	MouseOnCheck();

	FinalUpdateChild();
}

void CUI::Render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc
			, (int)vPos.X
			, (int)vPos.Y
			, (int)(vPos.X + vScale.X)
			, (int)(vPos.Y + vScale.Y));
	}
	else
	{
		Rectangle(_dc
			, (int)vPos.X
			, (int)vPos.Y
			, (int)(vPos.X + vScale.X)
			, (int)(vPos.Y + vScale.Y));
	}	

	RenderChild(_dc);
}

void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{
}

void CUI::UpdateChild()
{
	for (CUI* ChildUI : m_vecChildUI)
	{
		ChildUI->Update();
	}
}

void CUI::FinalUpdateChild()
{
	for (CUI* ChildUI : m_vecChildUI)
	{
		ChildUI->FinalUpdate();
	}
}

void CUI::RenderChild(HDC _dc)
{
	for (CUI* ChildUI : m_vecChildUI)
	{
		ChildUI->Render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (m_vFinalPos.X <= vMousePos.X && vMousePos.X <= m_vFinalPos.X + vScale.X
		&& m_vFinalPos.Y <= vMousePos.Y && vMousePos.Y <= m_vFinalPos.Y + vScale.Y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}
