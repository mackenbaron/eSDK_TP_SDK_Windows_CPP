
// HoldMultiConfDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CHoldMultiConfDlg dialog
class CHoldMultiConfDlg : public CDialogEx
{
// Construction
public:
	CHoldMultiConfDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HOLDMULTICONF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	void StartMsgRetrieval();

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
	CString m_strUsername;
	CString m_strPassword;
	afx_msg void OnBnClickedLogin();
	afx_msg void OnBnClickedLogout();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void MainLoop();
	ConferenceStatusEx GetChoosedConferencesItem();

private:
	unsigned int m_threadID;
	int m_iLastChoosedItem;
	int m_listConfBeHit;
	int m_listConfItemSel;
public:
	CComboBox m_cmbSortItemIndex;
	CListCtrl m_searchList;
	int m_num;
	afx_msg void OnBnClickedAddSearchCondition();
	CComboBox m_cmbFilterBaseColumnIndex;
	CComboBox m_cmbSortType;
	CString m_value;
	afx_msg void OnBnClickedButtonClearSearchCondition();
	CString m_searchID;
	CString m_searchSum;
	CString m_searchPage;
	afx_msg void OnBnClickedButtonQuerySitesInfo();
	CEdit m_showPan;
	afx_msg void OnBnClickedButtonQueryConfStatus();
	CListCtrl m_listConference;
	vector<ConferenceStatusEx> m_conferenceList;
	vector<ConferenceStatusEx> m_ChoosedConferences;
	afx_msg void OnBnClickedButtonGetConfSites();
	CListCtrl m_listSitesInConf;
	afx_msg void OnBnClickedBtnQuerySites();
	void UpdateSiteList();
	CString m_confName;
	CString m_beginTime;
	CString m_confTime;
	CComboBox m_cmbRecurrenceConfFrequency;
	CEdit m_editRecurrenceConfCount;
	CEdit m_editRecurrenceConfInterval;
	CListCtrl m_sitesInfoList;
	CString m_chairmanPwd;
	CComboBox m_cb_rate;
	CComboBox m_cb_pwdtype;
	CComboBox m_cb_multi;
	CComboBox m_cb_vediofm;
	CComboBox m_cb_vediopr;
	afx_msg void OnBnClickedBtnCreateconf();
	CString m_confPwd;
	CString m_accessCode;
	vector<SiteInfoEx> m_allSitesInfo;
	vector<SiteInfoEx> m_joinConfSitesInfo;
	afx_msg void OnNMClickListConf(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckRecurrenceConf();
	afx_msg void OnNMRClickListConf(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListConf(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnNMDblclkListConf(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRDblclkListConf(NMHDR *pNMHDR, LRESULT *pResult);
};
