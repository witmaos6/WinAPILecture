#pragma once
#include "Global.h"

#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CObject
{
	friend class CEventMgr;
public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

private:
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	CRigidBody* m_pRigidBody;

	bool m_bAlive;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }

	bool IsDead() { return !m_bAlive; }

public:
	virtual CObject* Clone() = 0;

	virtual void Update() = 0;
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

	void ComponentRender(HDC _dc);

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();

private:
	void SetDead() { m_bAlive = false; }
};

