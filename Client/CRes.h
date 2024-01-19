#pragma once
#include "Global.h"

class CRes
{
private:
	wstring m_strKey;
	wstring m_strRelativePath;

public:
	CRes();
	virtual ~CRes();

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetPath() { return m_strRelativePath; }
};
