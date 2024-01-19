#pragma once
#include "CObject.h"

class CUI : public CObject
{
public:
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();

    friend class CUIMgr;

private:
    vector<CUI*> m_vecChildUI;
    CUI* m_pParentUI;

    Vec2 m_vFinalPos;

    bool m_bCamAffected;
    bool m_bMouseOn;
    bool m_bLbtnDown;

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }

    CUI* GetParent() { return m_pParentUI; }
    void AddChild(CUI* _pUI)
    { 
        m_vecChildUI.push_back(_pUI);
        _pUI->m_pParentUI = this;
    }

    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }
    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

public:
    virtual void Update();
    virtual void FinalUpdate();
    virtual void Render(HDC _dc);

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    virtual CUI* Clone() = 0;

private:
    void UpdateChild();
    void FinalUpdateChild();
    void RenderChild(HDC _dc);

    void MouseOnCheck();
};

