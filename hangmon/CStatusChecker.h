#pragma once
#include "CMessageMaker.h"
#include "CTargetProcess.h"

DWORD WINAPI StatusCheckerThread(LPVOID vdParam);

class CStatusChecker
{
public:
	CStatusChecker();
	~CStatusChecker();
	int StartMonitor();
	void Init(HWND& hWnd, CTargetProcess* pcTargetProcess, CMessageMaker* pcMessageMaker);
	void DisplayMessage(const wchar_t* szMessage);

private:
	CTargetProcess* m_pcTargetProcess;
	HWND m_hWnd;
	CMessageMaker* m_pcMessageMaker;

	void DisplayMessage();
	void DisplayStatus(int iStatus);
};

