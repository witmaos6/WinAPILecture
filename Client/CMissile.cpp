#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_fTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f))
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

CMissile::~CMissile()
{
}

void CMissile::Update()
{
	Vec2 vPos = GetPos();

	vPos.X += 600.f * m_vDir.X * fDT;
	vPos.Y += 600.f * m_vDir.Y * fDT;
	// == 아래와 같음 
	//vPos.X += 600.f * cosf(m_fTheta) * fDT;
	//vPos.Y -= 600.f * sinf(m_fTheta) * fDT;

	SetPos(vPos);
}

void CMissile::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(_dc,
		(int)(vPos.X - vScale.X / 2.f),
		(int)(vPos.Y - vScale.Y / 2.f),
		(int)(vPos.X + vScale.X / 2.f),
		(int)(vPos.Y + vScale.Y / 2.f));

	ComponentRender(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}
