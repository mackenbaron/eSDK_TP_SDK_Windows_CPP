// TP_Native_Sheet.cpp : implementation file
//

#include "stdafx.h"
#include "TP_AdhocConfTempDemo.h"
#include "TP_Native_Sheet.h"

unsigned int __stdcall ThreadFunc(void* para)
{
	if (NULL == para)
	{
		return TP_E_RET_CODE_FAIL;
	}

	CTP_Native_Sheet* instance = (CTP_Native_Sheet*)para;
	instance->tpNativeKeepAlive();
	return TP_E_RET_CODE_SUCCESS;
}

// CTP_Native_Sheet

IMPLEMENT_DYNAMIC(CTP_Native_Sheet, CPropertySheet)

CTP_Native_Sheet::CTP_Native_Sheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_run = false;
	m_thread = NULL ;
	m_threadID = NULL;

	AddPage(&m_addAdhocConfTempDlg);
	m_addAdhocConfTempDlg.SetSheet(this);
	m_addAdhocConfTempDlg.m_psp.dwFlags |= PSP_USETITLE;
	m_addAdhocConfTempDlg.m_psp.pszTitle = "保存模板";

	AddPage(&m_scheduleAdhocTempDlg);
	m_scheduleAdhocTempDlg.SetSheet(this);
	m_scheduleAdhocTempDlg.m_psp.dwFlags |= PSP_USETITLE;
	m_scheduleAdhocTempDlg.m_psp.pszTitle = "预约会议";
}

CTP_Native_Sheet::CTP_Native_Sheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_run = false;
	m_thread = NULL ;
	m_threadID = NULL;

	AddPage(&m_addAdhocConfTempDlg);
	m_addAdhocConfTempDlg.SetSheet(this);
	m_addAdhocConfTempDlg.m_psp.dwFlags |= PSP_USETITLE;
	m_addAdhocConfTempDlg.m_psp.pszTitle = "保存模板";

	AddPage(&m_scheduleAdhocTempDlg);
	m_scheduleAdhocTempDlg.SetSheet(this);
	m_scheduleAdhocTempDlg.m_psp.dwFlags |= PSP_USETITLE;
	m_scheduleAdhocTempDlg.m_psp.pszTitle = "预约会议";
}

CTP_Native_Sheet::~CTP_Native_Sheet()
{
	//停止保活
	StopMsgRetrieval();
	//账号登出
	logout();
}


BEGIN_MESSAGE_MAP(CTP_Native_Sheet, CPropertySheet)
	ON_WM_NCCREATE()
	ON_WM_TIMER()
	ON_COMMAND(IDOK, &CTP_Native_Sheet::OnIdok)
END_MESSAGE_MAP()


// CTP_Native_Sheet message handlers


BOOL CTP_Native_Sheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  Add your specialized code here
	GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDOK,_T("登出"));
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_APPLY_NOW)->ShowWindow(SW_HIDE);

	SetTimer( 1, 19000, NULL );

	return bResult;
}


BOOL CTP_Native_Sheet::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!CPropertySheet::OnNcCreate(lpCreateStruct))
		return FALSE;

	// TODO:  Add your specialized creation code here

	return TRUE;
}


void CTP_Native_Sheet::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	startMsgRetrieval();
	CPropertySheet::OnTimer(nIDEvent);
}

void CTP_Native_Sheet::startMsgRetrieval()
{
	m_run = true;
	m_thread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)this, 0, &m_threadID);
}

void CTP_Native_Sheet::tpNativeKeepAlive()
{
	int ret = keepAlive();
	if ( TP_E_RET_CODE_SUCCESS == ret )
	{
		//AfxMessageBox("保活成功");
	} 
	else
	{
		//char result[1024]={0};
		//sprintf_s(result, 1023, "保活失败； 返回码 ：%d",ret);
		//AfxMessageBox(result);
	}
}

void CTP_Native_Sheet::OnIdok()
{
	// TODO: Add your command handler code here
	KillTimer( 1 );
	CPropertySheet::EndDialog(IDOK);
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