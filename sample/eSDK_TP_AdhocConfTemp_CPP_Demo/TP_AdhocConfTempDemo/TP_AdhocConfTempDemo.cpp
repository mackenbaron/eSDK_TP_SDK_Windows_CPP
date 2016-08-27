
// TP_AdhocConfTempDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TP_AdhocConfTempDemo.h"
#include "TP_AdhocConfTempDemoDlg.h"
#include "TP_Native_Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTP_AdhocConfTempDemoApp

BEGIN_MESSAGE_MAP(CTP_AdhocConfTempDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTP_AdhocConfTempDemoApp construction

CTP_AdhocConfTempDemoApp::CTP_AdhocConfTempDemoApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTP_AdhocConfTempDemoApp object

CTP_AdhocConfTempDemoApp theApp;


// CTP_AdhocConfTempDemoApp initialization

BOOL CTP_AdhocConfTempDemoApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	/*
	CTP_AdhocConfTempDemoDlg dlg;
	CTP_Native_Sheet *pSheet = NULL;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		pSheet = new CTP_Native_Sheet(_T("TP Native"));
		nResponse = pSheet->DoModal();
		if (nResponse == IDOK)
		{
			if ( NULL != pSheet )
			{
				delete pSheet;
				pSheet = NULL;
			}
		}
		else if (nResponse == IDCANCEL)
		{
			if ( NULL != pSheet )
			{
				delete pSheet;
				pSheet = NULL;
			}
		}
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	*/
	CTP_AdhocConfTempDemoDlg *dlg = NULL;
	CTP_Native_Sheet *pSheet = NULL;
	dlg = new CTP_AdhocConfTempDemoDlg();
	INT_PTR nResponse = dlg->DoModal();

	if (nResponse == IDCANCEL)
	{
		if (pShellManager != NULL)
		{
			delete pShellManager;
		}

		if (dlg)
		{
			delete dlg;
			dlg = NULL;
		}
		return FALSE;
	}

	if (dlg)
	{
		delete dlg;
	}

	pSheet = new CTP_Native_Sheet(_T("TP Native"));
	nResponse = pSheet->DoModal();
	if (nResponse == IDOK)
	{
		if ( NULL != pSheet )
		{
			delete pSheet;
			pSheet = NULL;
		}
	}
	else if (nResponse == IDCANCEL)
	{
		if ( NULL != pSheet )
		{
			delete pSheet;
			pSheet = NULL;
		}
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

