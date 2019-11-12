#include "stdafx.h"
#include "CStatusChecker.h"
#include "CTargetProcess.h"


CStatusChecker::CStatusChecker()
	:m_hWnd(NULL)
	,m_pcMessageMaker(NULL)
	,m_pcTargetProcess(NULL)
{
}


CStatusChecker::~CStatusChecker()
{
}

int CStatusChecker::StartMonitor()
{
	static TCHAR szLiving[] = L"Process Window Living";
	static TCHAR szDead[] = L"Process Window not found";
	static TCHAR szHang[] = L"!!!!! PROCESS HANGING !!!!!";

	m_pcMessageMaker->SetPid(m_pcTargetProcess->GetPid());
	TCHAR szProcessName[MAX_PATH] = { 0 };
	m_pcTargetProcess->GetProcessName(szProcessName, MAX_PATH);
	m_pcMessageMaker->SetProcessName((PTCHAR)szProcessName);

	USHORT usStatus = PROCESS_LIVING;
	while (usStatus == PROCESS_LIVING)
	{
		usStatus = m_pcTargetProcess->IsLiving();
		switch (usStatus)
		{
		case PROCESS_LIVING:
			DisplayStatus(szLiving);
			break;
		case PROCESS_DEAD:
			DisplayStatus(szDead);
			break;
		case PROCESS_HANGING:
			DisplayStatus(szHang);
			break;
		default:
			break;
		}
		Sleep(1000);
	}
	return 0;
}


void CStatusChecker::Init(HWND& hWnd, CTargetProcess* pcTargetProcess, CMessageMaker* pcMessageMaker )
{
	m_hWnd = hWnd;
	m_pcTargetProcess = pcTargetProcess;
	m_pcMessageMaker = pcMessageMaker;
}


int CStatusChecker::DisplayStatus(PTCHAR pszStatus)
{
	m_pcMessageMaker->SetStatus(pszStatus);

	HDC hDC = GetDC(m_hWnd);
	TCHAR szMessage[MAX_PATH] = { 0 };
	TextOut(hDC, 10, 30, m_pcMessageMaker->MakeMessage(szMessage, MAX_PATH), MAX_PATH);
	ReleaseDC(m_hWnd, hDC);

	return 0;
}
