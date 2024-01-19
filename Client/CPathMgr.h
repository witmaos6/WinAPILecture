#pragma once
#include "pch.h"
class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t m_szContentPath[255];
	wchar_t m_szRelativePath[255];

public:
	void Init();

	const wchar_t* GetContentsPath() { return m_szContentPath; }

	wstring GetRelativePath(const wchar_t* _filePath);
};

