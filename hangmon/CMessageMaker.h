#pragma once
#include <string>
using namespace std;

#define HANDLER_STATUS_SIZE (MAX_PATH + 20)
class CMessageMaker
{
public:
	CMessageMaker();
	~CMessageMaker();
	void SetStatus(int iStatus);
	void SetHandlerStatus(PTCHAR szStatus);
	void SetPid(const DWORD dwPid);
	void SetProcessName(const PTCHAR pszProcessName);
	void SetExtraMessage(const wchar_t* szMessage);
	void DisplayMessage(const HDC hdc);

private:
	wstring m_strProcessName;
	wstring m_strPid;
	wstring m_strHandlerStatus;
	int m_iStatus;
	wstring m_strExtraMessage;
};

