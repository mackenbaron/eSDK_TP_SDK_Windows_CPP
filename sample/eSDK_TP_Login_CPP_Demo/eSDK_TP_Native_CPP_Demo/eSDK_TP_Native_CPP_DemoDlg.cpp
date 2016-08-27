
// eSDK_TP_Native_CPP_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eSDK_TP_Native_CPP_Demo.h"
#include "eSDK_TP_Native_CPP_DemoDlg.h"
#include "afxdialogex.h"
#include "TP_Native_SDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

unsigned int __stdcall ThreadFunc(void* para)
{
	if (NULL == para)
	{
		return TP_E_RET_CODE_FAIL;
	}

	CeSDK_TP_Native_CPP_DemoDlg* instance = (CeSDK_TP_Native_CPP_DemoDlg*)para;
	instance->KeepAlive();
	return TP_E_RET_CODE_SUCCESS;
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CeSDK_TP_Native_CPP_DemoDlg dialog




CeSDK_TP_Native_CPP_DemoDlg::CeSDK_TP_Native_CPP_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CeSDK_TP_Native_CPP_DemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_run = true;
	m_thread = NULL;
	m_threadID = NULL;
}

void CeSDK_TP_Native_CPP_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CeSDK_TP_Native_CPP_DemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CeSDK_TP_Native_CPP_DemoDlg::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_BUTTON2, &CeSDK_TP_Native_CPP_DemoDlg::OnBnClickedLogin)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CeSDK_TP_Native_CPP_DemoDlg message handlers

BOOL CeSDK_TP_Native_CPP_DemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CeSDK_TP_Native_CPP_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CeSDK_TP_Native_CPP_DemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CeSDK_TP_Native_CPP_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CeSDK_TP_Native_CPP_DemoDlg::OnBnClickedLogout()
{
	// TODO: Add your control notification handler code here
	StopMsgRetrieval();
	KillTimer(1);
	int ret = TP_E_RET_CODE_FAIL;
	ret = logout();
	if (TP_E_RET_CODE_SUCCESS == ret)
	{
		AfxMessageBox("µÇ³ö³É¹¦");
	}
	else
	{
		char result[1024]={0};
		sprintf_s(result, 1023, "µÇ³öÊ§°Ü£» ·µ»ØÂë £º%d",ret);
		AfxMessageBox(result);
	}
}


void CeSDK_TP_Native_CPP_DemoDlg::OnBnClickedLogin()
{
	int ret = TP_E_RET_CODE_FAIL;
	ret = login("esdk_user","Huawei@123");
	if (TP_E_RET_CODE_SUCCESS == ret)
	{
		AfxMessageBox("µÇÂ¼³É¹¦");
		SetTimer(1, 19000, NULL);
	}
	else
	{
		char result[1024]={0};
		sprintf_s(result, 1023, "µÇÂ¼Ê§°Ü£» ·µ»ØÂë £º%d",ret);
		AfxMessageBox(result);
	}
}

void CeSDK_TP_Native_CPP_DemoDlg::StartMsgRetrieval()
{
	m_run = true;
	m_thread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)this, 0, &m_threadID);
}

void CeSDK_TP_Native_CPP_DemoDlg::StopMsgRetrieval()
{
	if (NULL == m_thread)
	{
		return;
	}

	m_run = false;
	DWORD i = WaitForSingleObject(m_thread, INFINITE);
	m_thread = NULL;
}

void CeSDK_TP_Native_CPP_DemoDlg::KeepAlive()
{
	int ret = keepAlive();
}


void CeSDK_TP_Native_CPP_DemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	StartMsgRetrieval();
	CDialogEx::OnTimer(nIDEvent);
}
