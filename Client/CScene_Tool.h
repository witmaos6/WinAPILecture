#pragma once
#include "CScene.h"

class CUI;

class CScene_Tool : public CScene
{
public:
	CScene_Tool();
	~CScene_Tool();
private:
	CUI* m_pUI;
public:
	virtual void Update();

	virtual void Enter();

	virtual void Exit();

public:
	void SetTileIdx();

	void SaveTileData();
	void SaveTile(const wstring& _strFilePath);

	void LoadTileData();
};
