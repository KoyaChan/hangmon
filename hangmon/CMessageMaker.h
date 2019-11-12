#pragma once
#include <string>
using namespace std;

class CMessageMaker
{
public:
	CMessageMaker();
	~CMessageMaker();
private:
	wstring m_strProcessName;
	wstring m_strPid;
	PTCHAR m_szStatus;
public:
	void SetPid(DWORD pid);
	void SetProcessName(PTCHAR pszProcessName);
	void SetStatus(PTCHAR pszStatus);
	PTCHAR MakeMessage(PTCHAR szMessage, USHORT size);
};

