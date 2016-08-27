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
// TEX0_Sheet.cpp : implementation file
//

#include "stdafx.h"
//#include "TEX0_Demo.h"
#include "TP_Native_Sheet.h"
#include "TP_Native_SDK.h"

// CTEX0_Sheet

IMPLEMENT_DYNAMIC(CTP_Native_Sheet, CPropertySheet)

CTP_Native_Sheet::CTP_Native_Sheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_run = false;
	m_thread = NULL;
	m_threadID = 0;
	AddPage(&m_scheduleConfPage);
	m_scheduleConfPage.SetSheet(this);
	m_scheduleConfPage.m_psp.dwFlags |= PSP_USETITLE;
	m_scheduleConfPage.m_psp.pszTitle = "预约会议";

	//AddPage(&m_addSiteToConfPage);
	//m_addSiteToConfPage.SetSheet(this);
	//m_addSiteToConfPage.m_psp.dwFlags |= PSP_USETITLE;
	//m_addSiteToConfPage.m_psp.pszTitle = "添加会场";

	//AddPage(&m_connectSitePage);
	//m_connectSitePage.SetSheet(this);
	//m_connectSitePage.m_psp.dwFlags |= PSP_USETITLE;
	//m_connectSitePage.m_psp.pszTitle = "呼叫会场";
	
	//AddPage(&m_broadcastSitePage);
	//m_broadcastSitePage.SetSheet(this);
	//m_broadcastSitePage.m_psp.dwFlags |= PSP_USETITLE;
	//m_broadcastSitePage.m_psp.pszTitle = "广播会场";

	//AddPage(&m_otherInterface);
	//m_otherInterface.SetSheet(this);
	//m_otherInterface.m_psp.dwFlags |= PSP_USETITLE;
	//m_otherInterface.m_psp.pszTitle = "其它接口验证";
	
	AddPage(&m_ConferenceControlPage);
	m_ConferenceControlPage.SetSheet(this);
	m_ConferenceControlPage.m_psp.dwFlags |= PSP_USETITLE;
	m_ConferenceControlPage.m_psp.pszTitle = "会议控制接口";
	
	AddPage(&m_adhocConfTempManagePage);
	m_adhocConfTempManagePage.SetSheet(this);
	m_adhocConfTempManagePage.m_psp.dwFlags |= PSP_USETITLE;
	m_adhocConfTempManagePage.m_psp.pszTitle = "Adhoc会议模板调度接口";

	AddPage(&m_ConferenceManagePage);
	m_ConferenceManagePage.SetSheet(this);
	m_ConferenceManagePage.m_psp.dwFlags |= PSP_USETITLE;
	m_ConferenceManagePage.m_psp.pszTitle = "会议调度";

	AddPage(&m_MangerPage);
	m_MangerPage.SetSheet(this);
	m_MangerPage.m_psp.dwFlags |= PSP_USETITLE;
	m_MangerPage.m_psp.pszTitle = "管理接口";

#if 0
	AddPage(&m_statusPage);
	AddPage(&m_callPage);
	AddPage(&m_conferencePage);
	m_statusPage.SetSheet(this);
	m_callPage.SetSheet(this);
	m_conferencePage.SetSheet(this);
	m_statusPage.m_psp.dwFlags |= PSP_USETITLE;
	m_statusPage.m_psp.pszTitle = "状态";
	m_callPage.m_psp.dwFlags |= PSP_USETITLE;
	m_callPage.m_psp.pszTitle = "呼叫";
	m_conferencePage.m_psp.dwFlags |= PSP_USETITLE;
	m_conferencePage.m_psp.pszTitle = "会议";
#endif
}

CTP_Native_Sheet::CTP_Native_Sheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_run = false;
	m_thread = NULL;
	m_threadID = 0;
	AddPage(&m_scheduleConfPage);
	m_scheduleConfPage.SetSheet(this);
	m_scheduleConfPage.m_psp.dwFlags |= PSP_USETITLE;
	m_scheduleConfPage.m_psp.pszTitle = "预约会议";

	//AddPage(&m_addSiteToConfPage);
	//m_addSiteToConfPage.SetSheet(this);
	//m_addSiteToConfPage.m_psp.dwFlags |= PSP_USETITLE;
	//m_addSiteToConfPage.m_psp.pszTitle = "添加会场";

	//AddPage(&m_connectSitePage);
	//m_connectSitePage.SetSheet(this);
	//m_connectSitePage.m_psp.dwFlags |= PSP_USETITLE;
	//m_connectSitePage.m_psp.pszTitle = "呼叫会场";

	//AddPage(&m_broadcastSitePage);
	//m_broadcastSitePage.SetSheet(this);
	//m_broadcastSitePage.m_psp.dwFlags |= PSP_USETITLE;
	//m_broadcastSitePage.m_psp.pszTitle = "广播会场";

	//AddPage(&m_otherInterface);
	//m_otherInterface.SetSheet(this);
	//m_otherInterface.m_psp.dwFlags |= PSP_USETITLE;
	//m_otherInterface.m_psp.pszTitle = "其它接口验证";

	AddPage(&m_ConferenceControlPage);
	m_ConferenceControlPage.SetSheet(this);
	m_ConferenceControlPage.m_psp.dwFlags |= PSP_USETITLE;
	m_ConferenceControlPage.m_psp.pszTitle = "会议控制接口";

	AddPage(&m_adhocConfTempManagePage);
	m_adhocConfTempManagePage.SetSheet(this);
	m_adhocConfTempManagePage.m_psp.dwFlags |= PSP_USETITLE;
	m_adhocConfTempManagePage.m_psp.pszTitle = "Adhoc会议模板调度接口";

	AddPage(&m_ConferenceManagePage);
	m_ConferenceManagePage.SetSheet(this);
	m_ConferenceManagePage.m_psp.dwFlags |= PSP_USETITLE;
	m_ConferenceManagePage.m_psp.pszTitle = "会议调度";

	AddPage(&m_MangerPage);
	m_MangerPage.SetSheet(this);
	m_MangerPage.m_psp.dwFlags |= PSP_USETITLE;
	m_MangerPage.m_psp.pszTitle = "管理接口";

#if 0
	AddPage(&m_statusPage);
	AddPage(&m_callPage);
	AddPage(&m_conferencePage);
	m_statusPage.SetSheet(this);
	m_callPage.SetSheet(this);
	m_conferencePage.SetSheet(this);
	m_statusPage.m_psp.dwFlags |= PSP_USETITLE;
	m_statusPage.m_psp.pszTitle = "状态";
	m_callPage.m_psp.dwFlags |= PSP_USETITLE;
	m_callPage.m_psp.pszTitle = "呼叫";
	m_conferencePage.m_psp.dwFlags |= PSP_USETITLE;
	m_conferencePage.m_psp.pszTitle = "会议";
#endif
}

CTP_Native_Sheet::~CTP_Native_Sheet()
{
	//停止保活
	StopMsgRetrieval();

	//账号登出
	logout();

#if 0
	if (NULL != m_incomingCall)
	{
		delete m_incomingCall;
		m_incomingCall = NULL;
	}
#endif
}


BEGIN_MESSAGE_MAP(CTP_Native_Sheet, CPropertySheet)
	ON_WM_NCCREATE()
	ON_WM_TIMER()
	ON_COMMAND(IDOK, &CTP_Native_Sheet::OnIdok)
END_MESSAGE_MAP()


// CTEX0_Sheet message handlers


BOOL CTP_Native_Sheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  Add your specialized code here
	//隐藏属性页默认按钮
	//GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDOK,_T("登出"));
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_APPLY_NOW)->ShowWindow(SW_HIDE);

	//调整窗体大小隐藏默认按钮区域
	CRect btnRect;
	GetDlgItem(IDOK)->GetWindowRect(&btnRect);
	CRect wndRect; 
	GetWindowRect(&wndRect);  
	::SetWindowPos(this->m_hWnd, HWND_TOP, 0, 0, wndRect.Width(), wndRect.Height(), SWP_NOMOVE | SWP_NOZORDER); 

	//开始保活
	//StartMsgRetrieval();
	SetTimer( 1, 19000, NULL );

	return bResult;
}


BOOL CTP_Native_Sheet::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!CPropertySheet::OnNcCreate(lpCreateStruct))
		return FALSE;

	// TODO:  Add your specialized creation code here
	//显示最小化按钮
	ModifyStyle(0, WS_SYSMENU | WS_MINIMIZEBOX, SWP_NOZORDER);

	return TRUE;
}


unsigned int __stdcall ThreadFunc(void* para)
{
	if (NULL == para)
	{
		return TP_E_RET_CODE_FAIL;
	}

	CTP_Native_Sheet* instance = (CTP_Native_Sheet*)para;
	instance->MainLoop();
	return TP_E_RET_CODE_SUCCESS;
}


void CTP_Native_Sheet::MainLoop()
{
	//int confType = 0;
	//while (m_run)
	//{
		int ret = keepAlive();
		//Sleep(60000);
#if 0
		if (TP_E_RET_CODE_SUCCESS != ret)
		{
			continue;
		}
#endif

	//}
}


void CTP_Native_Sheet::StartMsgRetrieval()
{
	//if (NULL == m_thread)
	//{
		m_run = true;
		m_thread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)this, 0, &m_threadID);
	//}
}


void CTP_Native_Sheet::StopMsgRetrieval()
{
	if (NULL == m_thread)
	{
		return;
	}

	m_run = false;
	DWORD i = WaitForSingleObject(m_thread, INFINITE);
	m_thread = NULL;
}


void CTP_Native_Sheet::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	StartMsgRetrieval();
	CPropertySheet::OnTimer(nIDEvent);
}

void CTP_Native_Sheet::OnIdok()
{
	// TODO: Add your command handler code here
	KillTimer( 1 );
	CPropertySheet::EndDialog(IDOK);
}
