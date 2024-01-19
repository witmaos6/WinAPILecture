#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_bAlive(true)
{
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_bAlive(true)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}

	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}

	if (_origin.m_pRigidBody)
	{
		m_pRigidBody = new CRigidBody(*_origin.m_pRigidBody);
		m_pRigidBody->m_pOwner = this;
	}
}

CObject::~CObject()
{
	if (m_pCollider)
	{
		delete m_pCollider;
	}

	if (m_pAnimator)
	{
		delete m_pAnimator;
	}

	if (m_pRigidBody)
	{
		delete m_pRigidBody;
	}
}

void CObject::FinalUpdate()
{
	if (m_pCollider)
	{
		m_pCollider->FinalUpdate();
	}

	if (m_pAnimator)
	{
		m_pAnimator->FinalUpdate();
	}

	if (m_pRigidBody)
	{
		m_pRigidBody->FinalUpdate();
	}
}

void CObject::Render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	Rectangle(_dc, 
	(int)(vRenderPos.X - m_vScale.X / 2.f),
	(int)(vRenderPos.Y - m_vScale.Y / 2.f),
	(int)(vRenderPos.X + m_vScale.X / 2.f),
	(int)(vRenderPos.Y + m_vScale.Y / 2.f));

	ComponentRender(_dc);
}

void CObject::ComponentRender(HDC _dc)
{
	if (m_pCollider)
	{
		m_pCollider->Render(_dc);
	}

	if (m_pAnimator)
	{
		m_pAnimator->Render(_dc);
	}
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}
