#pragma once
#include "CObject.h"

class CMissile : public CObject
{
private:
	float m_fTheta;

	Vec2 m_vDir;
public:
	CMissile();
	~CMissile();

public:
	void SetDir(float _fTheta){ m_fTheta = _fTheta; }
	void SetDir(Vec2 _vDir) 
	{ 
		m_vDir = _vDir; 
		m_vDir.Normalize();
	}

	virtual void Update();
	virtual void Render(HDC _dc);

	virtual void OnCollisionEnter(CCollider* _pOther);

	CLONE(CMissile);
};
