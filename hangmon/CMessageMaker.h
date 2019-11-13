#pragma once
#include <string>
using namespace std;

#define HANDLER_STATUS_SIZE (MAX_PATH + 20)
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
private:
	wchar_t m_szHandlerStatus[HANDLER_STATUS_SIZE];
public:
	void SetHandlerStatus(PTCHAR szStatus);
};

