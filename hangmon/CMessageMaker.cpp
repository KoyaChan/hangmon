#include "stdafx.h"
#include "CTargetProcess.h"
#include "CMessageMaker.h"
#include <vector>
#include <map>

CMessageMaker::CMessageMaker()
	:m_strPid(wstring(L"0"))
	,m_strProcessName(wstring(L""))
	,m_iStatus(PROCESS_DEAD)
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


void CMessageMaker::SetStatus(const int iStatus)
{
	m_iStatus = iStatus;
}

void CMessageMaker::SetHandlerStatus(PTCHAR szStatus)
{
	m_strHandlerStatus = szStatus;
}


typedef map<int, wchar_t*> StatusMap;
void CMessageMaker::DisplayMessage(HDC hdc)
{
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);

	StatusMap mpStatus;
	mpStatus.insert(StatusMap::value_type(PROCESS_LIVING, (wchar_t*)L"Living"));
	mpStatus.insert(StatusMap::value_type(PROCESS_HANGING, (wchar_t*)L"Hanging"));
	mpStatus.insert(StatusMap::value_type(PROCESS_DEAD, (wchar_t*)L"Process Window Not Found"));

	size_t mergin = 5;
	size_t y = 0;
	if (!m_strExtraMessage.empty())
	{
		y += tm.tmHeight + mergin;
		SetTextColor(hdc, RGB(0xff, 0, 0));
		TextOut(hdc, 10, y, m_strExtraMessage.c_str(), m_strExtraMessage.size());
		y += tm.tmHeight;
	}

	y += tm.tmHeight + mergin;
	if (m_iStatus == PROCESS_HANGING)
	{
		SetTextColor(hdc, RGB(0xFF, 0, 0));
	}
	else if (m_iStatus == PROCESS_DEAD)
	{
		SetTextColor(hdc, RGB(0xFF, 0, 0xFF));
	}
	else
	{
		SetTextColor(hdc, RGB(0, 0, 0xFF));
	}
	TextOut(hdc, 10, y, mpStatus[m_iStatus], wcslen(mpStatus[m_iStatus]));

	SetTextColor(hdc, RGB(0, 0, 0));

	y += tm.tmHeight + mergin;
	wstring strLine = L"PID : ";
	strLine += m_strPid;
	TextOut(hdc, 10, y, strLine.c_str(), strLine.size());

	y += tm.tmHeight + mergin;
	strLine = L"";
	strLine += m_strProcessName;
	TextOut(hdc, 10, y, strLine.c_str(), strLine.size());

	y += tm.tmHeight * 2 + mergin;
	TextOut(hdc, 10, y, m_strHandlerStatus.c_str(), m_strHandlerStatus.size());

}


void CMessageMaker::SetExtraMessage(const wchar_t* szMessage)
{
	m_strExtraMessage = szMessage;
}
