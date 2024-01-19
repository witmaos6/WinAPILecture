#include "pch.h"
#include "CEventMgr.h"

#include "CUIMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "AI.h"
#include "CState.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::Update()
{
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		CObject* pDeadObj = (CObject*)_eve.lParam;
		if (!pDeadObj->IsDead())
		{
			pDeadObj->SetDead();
			m_vecDead.push_back(pDeadObj);
		}
	}
		break;

	case EVENT_TYPE::SCENE_CHANGE:
	{
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
		break;
	case EVENT_TYPE::CHANGE_AI_STATE:
	{
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.wParam;
		pAI->ChangeState(eNextState);
	}
	default:
		break;
	}
}
