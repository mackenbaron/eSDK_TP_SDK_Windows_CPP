
// tpConferencesControlSampleDlg.h : header file
//

#pragma once


// CtpConferencesControlSampleDlg dialog
class CtpConferencesControlSampleDlg : public CDialogEx
{
// Construction
public:
	CtpConferencesControlSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TPCONFERENCESCONTROLSAMPLE_DIALOG };

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
};
