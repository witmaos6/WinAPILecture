#pragma once

class CMonster;
class CState;

class AI
{
public:
	AI();
	~AI();
	friend class CMonster;
private:
	map<MON_STATE, CState*> m_mapState;
	CState* m_pCurState;
	CMonster* m_pOwner;

public:
	void Update();

public:
	void AddState(CState* _pState);
	CState* GetState(MON_STATE _eState);

	void SetCurState(MON_STATE _eState);

	CMonster* GetOwner() { return m_pOwner; }

	void ChangeState(MON_STATE _eNextState);
};

