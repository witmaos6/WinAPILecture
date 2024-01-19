#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurrCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;
	
	double m_dDT;
	double m_dAcc;
	UINT m_iCallCount;
	UINT m_iFPS;

public:
	void Init();
	void Update();
	void Render();

	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

