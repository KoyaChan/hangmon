#include "stdafx.h"
#include "CMessageMaker.h"

static TCHAR szNoStatus[] = L"Status Not Set";

CMessageMaker::CMessageMaker()
	:m_strPid(wstring(L"0"))
	,m_strProcessName(wstring(L""))
	,m_szStatus((PTCHAR)szNoStatus)
{
}


CMessageMaker::~CMessageMaker()
{
}


void CMessageMaker::SetPid(const DWORD pid)
{
	wchar_t szPid[21] = { 0 };
	_itow_s(pid, szPid, sizeof(szPid), 10);
	m_strPid = szPid;
}


void CMessageMaker::SetProcessName(const PTCHAR pszProcessName)
{
	m_strProcessName = pszProcessName;
}


void CMessageMaker::SetStatus(const PTCHAR pszStatus)
{
	m_szStatus = pszStatus;
}


PTCHAR CMessageMaker::MakeMessage(PTCHAR szMessage, USHORT size)
{
	swprintf_s(szMessage, size, _T("%s  PID[%s]  %s"), m_szStatus, m_strPid.c_str(), m_strProcessName.c_str());
	return szMessage;
}


void CMessageMaker::SetHandlerStatus(PTCHAR szStatus)
{
	wcscpy_s(m_szHandlerStatus, HANDLER_STATUS_SIZE, szStatus);
}
