#pragma once
#include "pch.h"

class CObject;

class CRigidBody
{
	friend class CObject;
private:
	CObject* m_pOwner;
	
	Vec2 m_vForce;
	Vec2 m_vAccel;
	Vec2 m_vVelocity;

	float m_fMass;
	float m_fFricCoeff; // ¸¶Âû °è¼ö
	float m_fMaxSpeed;
	
public:
	CRigidBody();
	~CRigidBody();	
	
	void FinalUpdate();

public:
	void AddForce(Vec2 _vF) { m_vForce += _vF; }

	float GetMass() { return m_fMass; }
	void SetMass(float _fMass) { m_fMass = _fMass; }

	Vec2 GetVelocity() { return m_vVelocity; }
	void SetVelocity(Vec2 _InVelocity) { m_vVelocity = _InVelocity; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }

	float GetMaxVelocity() { return m_fMaxSpeed; }
	void SetMaxVelocity(float _InMaxSpeed) { m_fMaxSpeed = _InMaxSpeed; }

private:
	void Move();
};

