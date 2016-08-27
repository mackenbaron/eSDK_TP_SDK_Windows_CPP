
// TP_AdhocConfTempDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTP_AdhocConfTempDemoApp:
// See TP_AdhocConfTempDemo.cpp for the implementation of this class
//

class CTP_AdhocConfTempDemoApp : public CWinApp
{
public:
	CTP_AdhocConfTempDemoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTP_AdhocConfTempDemoApp theApp;