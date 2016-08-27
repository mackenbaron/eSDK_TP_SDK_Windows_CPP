
// TP_AdhocConfTempDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CTP_AdhocConfTempDemoDlg dialog
class CTP_AdhocConfTempDemoDlg : public CDialogEx
{
// Construction
public:
	CTP_AdhocConfTempDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TP_ADHOCCONFTEMPDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_editUserName;
	CEdit m_editPassword;
};
