/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/


// TP_Native_Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_DemoDlg.h"
#include "TP_Native_Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTP_Native_DemoApp

BEGIN_MESSAGE_MAP(CTP_Native_DemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTP_Native_DemoApp construction

CTP_Native_DemoApp::CTP_Native_DemoApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTP_Native_DemoApp object

CTP_Native_DemoApp theApp;


// CTP_Native_DemoApp initialization

BOOL CTP_Native_DemoApp::InitInstance()
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



	CTP_Native_DemoDlg *dlg = NULL;
	CTP_Native_Sheet *sheet = NULL;
	while(true)
	{

		dlg = new CTP_Native_DemoDlg();
		//dlg->Create(IDD_TEX0_DEMO_DIALOG, this);

		//m_pMainWnd = &dlg;
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

		sheet = new CTP_Native_Sheet(_T("TP Native"));
		//CTEX0_Sheet sheet(_T("TEX0 Control"));
		//GetNextDlgTabItem(GetFocus())->GetNextWindow()->SetFocus();
		//	m_pMainWnd = &sheet;
		nResponse = sheet->DoModal();
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
			//sheet.StopMsgRetrieval();
			//CDialogEx::OnOK();

		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
			//sheet.StopMsgRetrieval();
			//CDialogEx::OnClose();
			if (sheet)
			{
				delete sheet;
				sheet = NULL;
			}
			if (pShellManager != NULL)
			{
				delete pShellManager;
			}


			return FALSE;
		}

		if (sheet)
		{
			delete sheet;
		}
	}

#if 0
	CTP_Native_DemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
#endif
	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

