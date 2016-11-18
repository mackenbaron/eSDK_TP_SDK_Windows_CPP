#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTP_Native_AllSitesList dialog

class CTP_Native_AllSitesList : public CDialogEx
{
	DECLARE_DYNAMIC(CTP_Native_AllSitesList)

public:
	CTP_Native_AllSitesList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTP_Native_AllSitesList();

// Dialog Data
	enum { IDD = IDD_DIALOG_ALL_SITES_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listAllSites;
	list<SiteInfoEx> m_listChoosedSite;
	afx_msg void OnBnClickedButtonAddSites();
	vector<SiteInfoEx> m_allSitesInfo;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonQuerySiteStatus();
	CEdit m_editResultPanel;
	SYSTEMTIME m_LastQueryTime;
private:
	void GetChoosedSites();
	void initAllSiteInfo();
public:
	afx_msg void OnBnClickedButtonSyncSiteStatus();
	afx_msg void OnBnClickedButtonDeleteSiteInfo();
	afx_msg void OnBnClickedButtonGetAllSite();
};
