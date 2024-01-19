#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"

#include "CScene.h"
#include "CUI.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Update()
{
	m_pFocusedUI = GetFocusedUI();

	if (m_pFocusedUI == nullptr)
	{
		return;
	}

	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	if (pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}

			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	if (_pUI == nullptr || m_pFocusedUI == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	vector<CObject*>::iterator TargetIter = vecUI.end();
	vector<CObject*>::iterator Iter = vecUI.begin();

	for (; Iter != vecUI.end(); ++Iter)
	{
		CUI* UI = (CUI*)*Iter;
		if (UI->IsMouseOn())
		{
			TargetIter = Iter;
		}
	}

	if (TargetIter == vecUI.end())
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*TargetIter;
	vecUI.erase(TargetIter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	static vector<CUI*> vecNoneTarget;
	static list<CUI*> queue;

	vecNoneTarget.clear();
	queue.clear();

	queue.push_back(_pParentUI);

	CUI* pTargetUI = nullptr;
	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMouseOn())
		{
			if (pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (CUI* Child : vecChild)
		{
			queue.push_back(Child);
		}
	}

	if (bLbtnAway)
	{
		for (CUI* NoneTarget : vecNoneTarget)
		{
			NoneTarget->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}
