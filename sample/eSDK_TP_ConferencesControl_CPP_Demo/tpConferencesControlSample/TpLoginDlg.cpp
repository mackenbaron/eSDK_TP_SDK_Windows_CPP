// TpLoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tpConferencesControlSample.h"
#include "TpLoginDlg.h"
#include "afxdialogex.h"


// CTpLoginDlg dialog

IMPLEMENT_DYNAMIC(CTpLoginDlg, CDialogEx)

CTpLoginDlg::CTpLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTpLoginDlg::IDD, pParent)
{

}

CTpLoginDlg::~CTpLoginDlg()
{
}

void CTpLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editUserName);
	DDX_Control(pDX, IDC_EDIT2, m_editPassword);
}


BEGIN_MESSAGE_MAP(CTpLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTpLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTpLoginDlg message handlers


void CTpLoginDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int ret = TP_E_RET_CODE_FAIL;
	CString strUsername;
	m_editUserName.GetWindowText(strUsername);
	CString strPassword;
	m_editPassword.GetWindowText(strPassword);
	ret = login(strUsername.GetBuffer(), strPassword.GetBuffer());
	if (TP_E_RET_CODE_SUCCESS == ret)
	{
		CDialogEx::OnOK();
	}
	else
	{
		AfxMessageBox("用户名或密码错误");
	}
}


BOOL CTpLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_editUserName.SetWindowText("esdk_user");
	m_editPassword.SetWindowText("Huawei@123");
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
