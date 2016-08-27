#pragma once
#include "afxwin.h"


// CTpLoginDlg dialog

class CTpLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTpLoginDlg)

public:
	CTpLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTpLoginDlg();

// Dialog Data
	enum { IDD = IDD_TPCONFERENCESCONTROLSAMPLE_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_editUserName;
	CEdit m_editPassword;
	virtual BOOL OnInitDialog();
};
