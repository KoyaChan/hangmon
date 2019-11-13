#pragma once
#include "CMessageMaker.h"
#include <string>
using namespace std;

class CHangHandler
{
public:
	CHangHandler(CMessageMaker* pcMessageMaker);
	~CHangHandler();
	int Invoke();
private:
	// Invoke() invokes this command
	wstring m_strHandlerCmd;
	CMessageMaker* m_pcMessageMaker;
	// Find the path to the handler from the command line and set it to m_strHandlerCmd
	int FindHandler();
};

