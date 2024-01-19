#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
public:
	CPlayer();
	~CPlayer();

private:

public:
	virtual void Update();

	virtual void Render(HDC _dc);

	CLONE(CPlayer);

private:
	void LaunchMissile();
};

