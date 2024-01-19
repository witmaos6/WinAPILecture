#pragma once
#include "Global.h"

#include "CMonFactory.h"

class CObject;

class CScene
{
public:
	CScene();
	virtual ~CScene();

private:
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END];
	wstring m_strNmae;

	UINT m_iTileX;
	UINT m_iTileY;

	CObject* m_pPlayer;

public:
	void SetName(const wstring& _strName) { m_strNmae = _strName; }
	const wstring& GetName() { return m_strNmae; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

	virtual	void Update();
	virtual	void FinalUpdate();
	virtual	void Render(HDC _dc);

	void RenderTile(HDC _dc);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	void RegisterPlayer(CObject* _pPlayer) { m_pPlayer = _pPlayer; }
	CObject* GetPlayer() { return m_pPlayer; }

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

	void DeleteGroup(GROUP_TYPE _eTarget);

	void DeleteAll();

	void CreateTile(UINT _iXCount, UINT _iYCount);

	void LoadTile(const wstring& _strRelativePath);
};
