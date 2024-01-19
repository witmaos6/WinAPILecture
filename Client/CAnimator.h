#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
	friend class CObject;
public:
	CAnimator();
	~CAnimator();

private:
	CObject* m_pOwner;

	map<wstring, CAnimation*> m_mapAnim;

	CAnimation* m_pCurAnim;

	bool m_bRepeat;
public:
	CObject* GetObj() { return m_pOwner; }

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

	CAnimation* FindAnimation(const wstring& _strName);

	void Play(const wstring& _strName, bool _bRepeat);

	void Update();

	void FinalUpdate();

	void Render(HDC _dc);
};

