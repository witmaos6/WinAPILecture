#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCore.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

CPlayer::CPlayer()
{
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"Texture\\Player.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(30.f, 40.f));

	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"Texture\\Link_0.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", m_pTex, Vec2(0.f, 260.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	GetAnimator()->Play(L"WALK_DOWN", true);

	CreateRigidBody();

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");

	for (int i = 0; i < pAnim->GetMaxFrame(); i++)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Update()
{
	CRigidBody* pRigid = GetRigidBody();	

	if (KEY_HOLD(KEY::W))
	{
		pRigid->AddForce(Vec2(0.f, -200.f));
	}	
	if (KEY_HOLD(KEY::S))
	{
		pRigid->AddForce(Vec2(0.f, 200.f));
	}
	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));	
	}
	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}

	if (KEY_TAP(KEY::W))
	{
		pRigid->AddVelocity(Vec2(0.f, -100.f));
	}
	if (KEY_TAP(KEY::S))
	{
		pRigid->AddVelocity(Vec2(0.f, 100.f));
	}
	if (KEY_TAP(KEY::A))
	{
		pRigid->AddVelocity(Vec2(-100.f, 0.f));
	}
	if (KEY_TAP(KEY::D))
	{
		pRigid->AddVelocity(Vec2(100.f, 0.f));
	}

	if (KEY_TAP(KEY::SPACE))
	{
		LaunchMissile();
	}

	GetAnimator()->Update();
}

void CPlayer::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CPlayer::LaunchMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.Y -= GetScale().Y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}