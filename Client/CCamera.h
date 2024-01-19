#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2 m_vLookAt;

	Vec2 m_vCurLookAt;

	Vec2 m_vPrevLookAt;

	CObject* m_pTargetObj;

	Vec2 m_vBetweenCenterAndLookAt;

	float m_fTime;
	float m_fSpeed;
	float m_fAccTime;

	CAM_EFFECT m_eEffect;

	CTexture* m_pVeilTex;

	float m_fEffectDuration;

	float m_fCurTime;

public:
	void SetLookAt(Vec2 _vLook) 
	{ 
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.0f;
	}

	Vec2 GetLookAt() { return m_vCurLookAt; }

	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }

	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vBetweenCenterAndLookAt; }

	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vBetweenCenterAndLookAt; }

	void FadeIn()
	{

	}

	void FadeOut(float _fDuration)
	{
		m_eEffect = CAM_EFFECT::FADE_OUT;
		m_fEffectDuration = _fDuration;

		if (m_fEffectDuration == 0.f)
		{
			assert(nullptr);
		}
	}
	
public:
	void Init();

	void Update();

	void Render(HDC _dc);

private:
	void CalBetweenCenterAndLookAt();
};

