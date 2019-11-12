#include "stdafx.h"
#include "CTargetProcess.h"
#include "hangmon.h"
#include "stdio.h"
#include "shellapi.h"
#include "psapi.h"


CTargetProcess::CTargetProcess()
	:m_dwPid(0)
	,m_hWnd(NULL)
	,m_strName(L"")
{
}


CTargetProcess::~CTargetProcess()
{
}


int CTargetProcess::GetWindowHandleByPid()
{
	HWND hWnd = GetTopWindow(NULL);
	do {
		if (GetWindowLong(hWnd, GWLP_HWNDPARENT) != 0 || !IsWindowVisible(hWnd)) {
			continue;
		}
		DWORD getPID;
		GetWindowThreadProcessId(hWnd, &getPID);
		if (m_dwPid == getPID)
		{
			m_hWnd = hWnd;
			return 0;
		}
	} while ((hWnd = GetNextWindow(hWnd, GW_HWNDNEXT)) != NULL);

	return -1;
}


USHORT CTargetProcess::IsLiving()
{
	DWORD_PTR pdwResult;

	if (!SendMessageTimeout(m_hWnd, WM_NULL, NULL, NULL, SMTO_ABORTIFHUNG, 5000, &pdwResult))
	{
		int ec = GetLastError();
		// it is observed ERROR_INVALID_PARAMETER is got while NotMyFault.exe can't be killed
		switch (ec)
		{
		case ERROR_INVALID_PARAMETER:
			return PROCESS_HANGING;
		case ERROR_TIMEOUT:
			return PROCESS_HANGING;
		case ERROR_INVALID_WINDOW_HANDLE:
			return PROCESS_DEAD;
		default:
			return PROCESS_LIVING;
		}
	}

	return PROCESS_LIVING;
}


// get pid from the first argument in the command line
DWORD CTargetProcess::GetPidFromCommandLine()
{
	int Argc;
	LPWSTR *Argv;

	Argv = CommandLineToArgvW(GetCommandLineW(), &Argc);
	
	if (Argc < 2)
	{
		return 0;
	}

	return _tstoi(Argv[1]);
}


int CTargetProcess::GetProcessName(wchar_t* szProcessName, USHORT size)
{
	if (m_strName.empty())
	{
		if (!m_dwPid)
			return -1;

		HANDLE hProcess = OpenProcess(GENERIC_ALL, FALSE, m_dwPid);
		int rc = 0;

		if (!hProcess)
			return -1;

		HMODULE hModule = NULL;
		DWORD dummy = 0;
		if (!EnumProcessModules(hProcess, &hModule, sizeof(HMODULE), &dummy))
		{
			CloseHandle(hProcess);
			return -1;
		}

		if (!GetModuleFileNameEx(hProcess, hModule, szProcessName, size))
		{
			CloseHandle(hProcess);
			return -1;
		}

		m_strName = szProcessName;
	}
	else
	{
		_tcscpy_s(szProcessName, size, m_strName.c_str());
	}

	return 0;
}


int CTargetProcess::Init(DWORD dwPid)
{
	m_dwPid = dwPid; 
	if (GetWindowHandleByPid())
	{
		return -1;
	}
	return 0;
}


int CTargetProcess::GetPid()
{
	return m_dwPid;
}
