#pragma once

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY
};

enum class KEY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,

	Q,
	W,
	E,
	R,
	T,
	Y,
	A,
	S,
	D,
	F,

	ALT,
	CTRL,
	LSHIFT,
	ENTER,
	ESC,
	SPACE,

	LBTN,
	RBTN,

	THE_END // It means the end
};

struct tKeyInfo
{
	KEY_STATE eState;

	bool bPrevPress;
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;
	Vec2 m_vCurMousePos;

public:
	void Init();
	void Update();

	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}

	Vec2 GetMousePos() { return m_vCurMousePos; }
};

