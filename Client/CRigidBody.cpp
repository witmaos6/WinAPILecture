#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.0f)
	, m_fFricCoeff(100.0f)
	, m_fMaxSpeed(200.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::FinalUpdate()
{
	// 힘의 크기
	float fForce = m_vForce.Length();
	if (fForce != 0.f)
	{
		// 힘의 방향
		m_vForce.Normalize();
		// 가속도의 크기
		float m_fAccel = fForce / m_fMass;
		// 가속도
		m_vAccel = m_vForce * m_fAccel;
		// 속도
		m_vVelocity += m_vAccel * fDT;
	}
	// 마찰력 적용
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;
		if (vFriction.Length() >= m_vVelocity.Length())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// 속도 제한
	if (m_vVelocity.Length() > m_fMaxSpeed)
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	Move();

	//초기화
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	float fSpeed = m_vVelocity.Length();
	if (fSpeed != 0.f)
	{
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT;
		m_pOwner->SetPos(vPos);
	}
}
