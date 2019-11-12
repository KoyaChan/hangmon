#pragma once
#include "CMessageMaker.h"
#include "CTargetProcess.h"

class CStatusChecker
{
public:
	CStatusChecker();
	~CStatusChecker();
	int StartMonitor();
private:
	CTargetProcess* m_pcTargetProcess;
	HWND m_hWnd;
	CMessageMaker* m_pcMessageMaker;
public:
	void Init(HWND& hWnd, CTargetProcess* pcTargetProcess, CMessageMaker* pcMessageMaker);
	int DisplayStatus(PTCHAR szStatus);
};

