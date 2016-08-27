#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

class CTP_Native_Sheet;
// CTP_Native_ConfControlDlg dialog

class CTP_Native_MangerDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CTP_Native_MangerDlg)
private:
	CTP_Native_Sheet *m_sheet;
	list<VideoCapbilityItemEx> m_listSiteVideoCapbility;
public:
	CTP_Native_MangerDlg();
	virtual ~CTP_Native_MangerDlg();
	void SetSheet(CTP_Native_Sheet* sheet) {m_sheet = sheet;}

	// Dialog Data
	enum { IDD = IDD_DIALOG_MANGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_showPan;
	CListCtrl m_searchList;
	CString m_searchID;
	CString m_searchPage;
	CString m_searchSum;
	int m_num;
	int m_siteNum;
	int m_subNum;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CListCtrl m_siteList;
	afx_msg void OnBnClickedButton7();
	CString m_addSite;
	CString m_videoFormat;
	CString m_siteName;
	CString m_siteMark;
	CString m_scUser;
	CString m_scPassword;
	CString m_siteID;
	CString m_value;
	afx_msg void OnBnClickedButton4();
	CListCtrl m_subList;
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton65();
	afx_msg void OnBnClickedButton9();
	CString m_subConfID;
	CString m_onConfID;
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton15();
	CString m_begainTime;
	CString m_duration;
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton8();
	CListCtrl m_listAllMcuInfo;
	vector<MCUInfoEx> m_allMcu;
	afx_msg void OnNMClickListAllMcuInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton12();
	CComboBox m_cmb;
	CComboBox m_cmbSiteRate;
	CComboBox m_cmbCircuitType;
	CComboBox m_cmbSortType;
	CComboBox m_cmbSortItemIndex;
	CComboBox m_cmbFilterBaseColumnIndex;
	CComboBox m_cmbIsSubScribe;
	CComboBox m_cmbSubScribeInfo;
};
