#include "stdafx.h"
#include "CStatusChecker.h"
#include "CTargetProcess.h"
#include "CHangHandler.h"

DWORD WINAPI StatusCheckerThread(LPVOID vdParam)
{
	CStatusChecker* pcStatusChecker = (CStatusChecker*)vdParam;
	pcStatusChecker->StartMonitor();
	return 0;
}

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

	// give PID and Process name to MessageMaker to print them in the message
	m_pcMessageMaker->SetPid(m_pcTargetProcess->GetPid());

	TCHAR szProcessName[MAX_PATH] = { 0 };
	m_pcTargetProcess->GetProcessName(szProcessName, MAX_PATH);
	m_pcMessageMaker->SetProcessName((PTCHAR)szProcessName);

	CHangHandler cHangHandler(m_pcMessageMaker);

	int iStatus = PROCESS_LIVING;
	while (iStatus == PROCESS_LIVING)
	{
		iStatus = m_pcTargetProcess->IsLiving();
		DisplayStatus(iStatus);

		if (iStatus == PROCESS_HANGING)
		{
			cHangHandler.Invoke();
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


void CStatusChecker::DisplayStatus(int iStatus)
{
	m_pcMessageMaker->SetStatus(iStatus);	 // This status is used in WinProc WM_PAINT

	DisplayMessage();
}


void CStatusChecker::DisplayMessage(const wchar_t* szMessage)
{
	m_pcMessageMaker->SetExtraMessage(szMessage);
	DisplayMessage();

}

void CStatusChecker::DisplayMessage()
{
	// Display message to the main window
	HDC hDC = GetDC(m_hWnd);
	m_pcMessageMaker->DisplayMessage(hDC);
	ReleaseDC(m_hWnd, hDC);
}
