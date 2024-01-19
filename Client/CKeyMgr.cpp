#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

int g_arrVK[(int)KEY::THE_END] =
{
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'A',
	'S',
	'D',
	'F',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_RETURN,
	VK_ESCAPE,
	VK_SPACE,

	VK_LBUTTON,
	VK_RBUTTON
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::THE_END; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update()
{
	HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();

	if (hWnd)
	{
		for (int i = 0; i < (int)KEY::THE_END; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPress)
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPress = true;
			}
			else
			{
				if (m_vecKey[i].bPrevPress)
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPress = false;
			}
		}

		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);
		m_vCurMousePos = Vec2((float)(ptPos.x), (float)(ptPos.y));
	}
	else
	{
		for (int i = 0; i < (int)KEY::THE_END; i++)
		{
			m_vecKey[i].bPrevPress = false;

			if (m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}
