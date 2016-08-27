#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTpControlConferenceDlg dialog

class CTpControlConferenceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTpControlConferenceDlg)

public:
	CTpControlConferenceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTpControlConferenceDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONTROL_CONFERENCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CEdit m_editConfId;
	CEdit m_editSiteUri;
	CEdit m_editVideoSourceUri;
	CEdit m_editTarget;
	CComboBox m_cbbPresenceMode;
	CComboBox m_cbbIsBroadcast;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	list<SiteStatusEx> getConfAllSitesStatusEx(std::string strConfId);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void StartMsgRetrieval();
	void StopMsgRetrieval();
	void KeepAlive();
	void showSitesStatus(list<SiteStatusEx> &siteStatusList);
private:
	bool m_run;
	HANDLE m_thread;
	unsigned int m_threadID;
public:
	CListCtrl m_listSitesStatus;
	afx_msg void OnBnClickedButton4();
};
