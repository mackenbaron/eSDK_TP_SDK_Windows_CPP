
// TP_KeepAlive_DemoDlg.h : header file
//

#pragma once


// CTP_KeepAlive_DemoDlg dialog
class CTP_KeepAlive_DemoDlg : public CDialogEx
{
// Construction
public:
	CTP_KeepAlive_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TP_KEEPALIVE_DEMO_DIALOG };

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
	afx_msg void OnBnClickedCancel();
	afx_msg void OnIdclose();
	afx_msg void OnClose();

public:	//function
	void KeepAliveLoop();

private:	//member
	HANDLE m_thread;
	unsigned int m_threadID;
	int    m_iKeepAliveCount;
	bool   m_bOnLine;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
