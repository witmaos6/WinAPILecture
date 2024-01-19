#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
    Safe_Delete_Map<wstring, CRes*>(m_mapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    CTexture* pTex = FindTexture(_strKey);
    if (pTex)
    {
        return pTex;
    }

    wstring strFilePath = CPathMgr::GetInst()->GetContentsPath();
    strFilePath += _strRelativePath;

    pTex = new CTexture;
    pTex->Load(strFilePath);
    pTex->SetKey(_strKey);
    pTex->SetRelativePath(_strRelativePath);

    m_mapTex[_strKey] = pTex;

    return pTex;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
    CTexture* pTex = FindTexture(_strKey);
    if (pTex)
    {
        return pTex;
    }

    pTex = new CTexture;
    pTex->Create(_iWidth, _iHeight);
    pTex->SetKey(_strKey);

    m_mapTex[_strKey] = pTex;

    return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
    map<wstring, CRes*>::iterator It = m_mapTex.find(_strKey);

    if (It == m_mapTex.end())
    {
        return nullptr;
    }
    return (CTexture*)It->second;
}
