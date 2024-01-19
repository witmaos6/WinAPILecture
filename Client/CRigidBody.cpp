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
	// ���� ũ��
	float fForce = m_vForce.Length();
	if (fForce != 0.f)
	{
		// ���� ����
		m_vForce.Normalize();
		// ���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;
		// ���ӵ�
		m_vAccel = m_vForce * m_fAccel;
		// �ӵ�
		m_vVelocity += m_vAccel * fDT;
	}
	// ������ ����
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

	// �ӵ� ����
	if (m_vVelocity.Length() > m_fMaxSpeed)
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	Move();

	//�ʱ�ȭ
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
