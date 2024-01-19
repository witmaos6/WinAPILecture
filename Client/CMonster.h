#pragma once
#include "CObject.h"

struct tMonInfo
{
	float m_fHP;
	float m_fSpeed;
	float m_fRecogRange;
	float m_fAttRange;
	float m_fAtt;
};

class CTexture;
class AI;

class CMonster : public CObject
{
public:
	CMonster();
	~CMonster();

	friend class CMonFactory;

private:
	tMonInfo m_tInfo;

	CTexture* m_pTex;
	AI* m_pAI;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	virtual void OnCollisionEnter(CCollider* _pOther);

	CLONE(CMonster)

public:
	float GetSpeed() { return m_tInfo.m_fSpeed; }
	void SetSpeed(float _f) { m_tInfo.m_fSpeed = _f; }

	void SetAI(AI* _AI);

	const tMonInfo& GetInfo() { return m_tInfo; }

private:
	void SetMonInfo(const tMonInfo& _info)
	{
		m_tInfo = _info;
	}
};

