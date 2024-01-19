#pragma once
class AI;
class CMonster;

class CState
{
public:
	CState(MON_STATE _eState);
	virtual ~CState();

private:
	AI* m_pAI;
	MON_STATE m_eState;
public:
	AI* GetAI() { return m_pAI; }
	MON_STATE GetType() { return m_eState; }
	CMonster* GetMonster();

	friend class AI;

public:
	virtual void Update() = 0;

	virtual void Enter() = 0;

	virtual void Exit() = 0;
};

