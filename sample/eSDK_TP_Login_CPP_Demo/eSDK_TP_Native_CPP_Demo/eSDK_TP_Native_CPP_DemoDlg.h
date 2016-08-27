
// eSDK_TP_Native_CPP_DemoDlg.h : header file
//

#pragma once


// CeSDK_TP_Native_CPP_DemoDlg dialog
class CeSDK_TP_Native_CPP_DemoDlg : public CDialogEx
{
// Construction
public:
	CeSDK_TP_Native_CPP_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ESDK_TP_NATIVE_CPP_DEMO_DIALOG };

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
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedLogin();
	void StartMsgRetrieval();
	void StopMsgRetrieval();
	void KeepAlive();
private:
	bool m_run;
	HANDLE m_thread;
	unsigned int m_threadID;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
