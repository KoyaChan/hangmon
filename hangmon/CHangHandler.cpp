#include "stdafx.h"
#include "CHangHandler.h"
#include <shellapi.h>
#include <shlwapi.h>
#include <process.h>


CHangHandler::CHangHandler(CMessageMaker* pcMessageMaker)
	:m_pcMessageMaker(pcMessageMaker)
{
	FindHandler();
}


CHangHandler::~CHangHandler()
{
}

// Invoke the handler command
int CHangHandler::Invoke()
{
	int ret = _wsystem(m_strHandlerCmd.c_str());

	wchar_t szMessage[MAX_PATH] = { 0 };
	swprintf_s(szMessage, sizeof(szMessage), L"%s returned %d", PathFindFileName(m_strHandlerCmd.c_str()), ret);
	m_pcMessageMaker->SetHandlerStatus(szMessage);

	return ret;
}


// // Find the path to the handler from the command line and set it to m_strHandlerCmd
int CHangHandler::FindHandler()
{
	int Argc;
	LPWSTR *Argv;
	Argv = CommandLineToArgvW(GetCommandLineW(), &Argc);
	
	wchar_t szHandlerPath[MAX_PATH];
	if (Argc < 3)
	{
		// handler name isn't given in the command line
		wchar_t szDefaultHandler[] = L"HangDump.bat";
		_tcsncpy_s(szHandlerPath, MAX_PATH, szDefaultHandler, wcslen(szDefaultHandler));
	}
	else
	{
		_tcsncpy_s(szHandlerPath, MAX_PATH, Argv[2], wcslen(Argv[2]));
	}

	const wchar_t* szPathList[] = { L".", NULL };
	if (!PathFindOnPathW(szHandlerPath, szPathList))
	{
		m_strHandlerCmd = szHandlerPath;

		wstring strMessage = L"Handler not found : ";
		strMessage += m_strHandlerCmd;
		m_pcMessageMaker->SetHandlerStatus((PTCHAR)strMessage.c_str());

		return 1;
	}

	m_strHandlerCmd = szHandlerPath;

	wstring strMessage = L"Handler : ";
	strMessage += m_strHandlerCmd;
	m_pcMessageMaker->SetHandlerStatus((PTCHAR)strMessage.c_str());
	m_strHandlerCmd = szHandlerPath;
	return 0;
}
