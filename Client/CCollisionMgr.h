#pragma once

class CCollider;

union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	map<ULONGLONG, bool> m_mapColInfo;
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];

public:
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	void Update();

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);

public:
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }
};

