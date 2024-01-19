#pragma once

#include "CScene.h"

class CScene_Start : public CScene
{
private:
	Vec2 m_vForcePos;
	float m_fForceRadius;
	float m_fCurRadius;
	float m_fForce;
	bool m_bUseForce;

public:
	CScene_Start();
	~CScene_Start();

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	virtual void Enter();

	virtual void Exit();

private:
	void CreateForce();
};
