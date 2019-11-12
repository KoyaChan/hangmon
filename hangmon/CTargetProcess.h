#pragma once
#include <string>
using namespace std;

#define PROCESS_LIVING 0
#define PROCESS_HANGING 1
#define PROCESS_DEAD   2

class CTargetProcess
{
public:
	CTargetProcess();
	~CTargetProcess();
private:
	HWND m_hWnd;
	int m_dwPid;
	wstring m_strName;
	int GetWindowHandleByPid();
public:
	USHORT IsLiving();
	static DWORD GetPidFromCommandLine();
	int GetProcessName(wchar_t* szProcessName, USHORT size);
	int Init(DWORD dwPid);
	int GetPid();
};

