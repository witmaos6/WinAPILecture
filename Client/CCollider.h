#pragma once

class CObject;

class CCollider
{
	friend class CObject;
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

private:
	static UINT g_iNextID;

	CObject* m_pOwner;

	Vec2 m_vOffsetPos;

	Vec2 m_vFinalPos;

	Vec2 m_vScale;

	UINT m_iID;

	int m_iCol;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	UINT GetID() { return m_iID; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }
	
public:
	void FinalUpdate();

	void Render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther);
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator = (CCollider& _origin) = delete;
};
