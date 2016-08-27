
// TP_KeepAlive_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TP_KeepAlive_Demo.h"
#include "TP_KeepAlive_DemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
public:
	afx_msg void OnIdclose();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(IDCLOSE, &CAboutDlg::OnIdclose)
END_MESSAGE_MAP()


unsigned int __stdcall ThreadFunc(void* para)
{
	if (NULL == para)
	{
		return TP_E_RET_CODE_FAIL;
	}

	CTP_KeepAlive_DemoDlg* instance = (CTP_KeepAlive_DemoDlg*)para;
	instance->KeepAliveLoop();
	return TP_E_RET_CODE_SUCCESS;
}

// CTP_KeepAlive_DemoDlg dialog




CTP_KeepAlive_DemoDlg::CTP_KeepAlive_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTP_KeepAlive_DemoDlg::IDD, pParent)
	,m_iKeepAliveCount(0)
	,m_threadID(0)
	,m_thread(0)
	,m_bOnLine(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTP_KeepAlive_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTP_KeepAlive_DemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTP_KeepAlive_DemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTP_KeepAlive_DemoDlg::OnBnClickedCancel)
	ON_COMMAND(IDCLOSE, &CTP_KeepAlive_DemoDlg::OnIdclose)
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTP_KeepAlive_DemoDlg message handlers

BOOL CTP_KeepAlive_DemoDlg::OnInitDialog()
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
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTP_KeepAlive_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTP_KeepAlive_DemoDlg::OnPaint()
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
HCURSOR CTP_KeepAlive_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTP_KeepAlive_DemoDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	std::string strUserName = "esdk_user";
	std::string strPassword = "Huawei@123";
	int iRet = login( strUserName, strPassword );
	if ( 0 == iRet)
	{
		SetDlgItemText(IDC_STATIC, _T("登录成功"));
		GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
		m_bOnLine = true;
		//开始保活
		SetTimer( 1, 39000, NULL );
	} 
	else
	{
		SetDlgItemText(IDC_STATIC, _T("登录失败，用户名或密码错误"));
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	}
	
	//CDialogEx::OnOK();
}


void CTP_KeepAlive_DemoDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	KillTimer(1);
	WaitForSingleObject(m_thread, INFINITE);
	int iRet = logout();
	if ( 0 == iRet )
	{
		m_bOnLine = false;
		SetDlgItemText(IDC_STATIC, _T("注销成功"));
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
		SetDlgItemText(IDC_STATIC, _T("注销失败"));
		GetDlgItem(IDOK)->EnableWindow(FALSE);
	}
	//CDialogEx::OnCancel();
}


void CAboutDlg::OnIdclose()
{
	// TODO: Add your command handler code here
	CDialogEx::OnCancel();
}


void CTP_KeepAlive_DemoDlg::OnIdclose()
{
	// TODO: Add your command handler code here
	CDialogEx::OnCancel();
}


void CTP_KeepAlive_DemoDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if ( true == m_bOnLine )
	{
		OnBnClickedCancel();
	}
	CDialogEx::OnCancel();
}

void CTP_KeepAlive_DemoDlg::KeepAliveLoop()
{

		//keepAlive需要每60秒之内调用一次，建议40秒一次，以防止网络延迟
		int ret = keepAlive();
		if ( 0 == ret )
		{
			m_iKeepAliveCount++;
			CString cstrMsg;
			cstrMsg.Format("保活成功，保活计数：%d", m_iKeepAliveCount);
			SetDlgItemText(IDC_STATIC, cstrMsg);
		} 
		else
		{
			CString cstrMsg;
			cstrMsg.Format("保活失败，保活计数：%d", m_iKeepAliveCount);
			SetDlgItemText(IDC_STATIC, cstrMsg);
		}

}


void CTP_KeepAlive_DemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	
	m_thread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)this, 0, &m_threadID);
	CDialogEx::OnTimer(nIDEvent);
}
