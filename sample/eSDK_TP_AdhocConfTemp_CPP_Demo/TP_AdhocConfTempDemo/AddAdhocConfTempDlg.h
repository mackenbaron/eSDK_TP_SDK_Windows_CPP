#pragma once
#include "afxwin.h"
#include "afxcmn.h"

class CTP_Native_Sheet;
// CAddAdhocConfTempDlg dialog

class CAddAdhocConfTempDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CAddAdhocConfTempDlg)

public:
	CAddAdhocConfTempDlg();
	virtual ~CAddAdhocConfTempDlg();
	void SetSheet(CTP_Native_Sheet* sheet) {m_sheet = sheet;}

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_ADHOC_TEMPLATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CTP_Native_Sheet *m_sheet;
	void UpdateSiteList();
	vector<SiteInfoEx> m_allSitesInfo;
public:
	CEdit m_editAdhocConfTempName;
	CEdit m_editAdhocConfTempAccessCode;
	CEdit m_editAdhocConfTempDuration;
	CEdit m_editAdhocConfTempBillCode;
	CEdit m_editAdhocConfTempPassword;
	CEdit m_editAdhocConfTempMaxSitesCount;
	CEdit m_editAdhocConfTempMainSiteUri;
	CEdit m_editAdhocConfTempChairmanPassword;
	CEdit m_editAdhocConfTempEmail;
	CEdit m_editAdhocConfTempContent;
	CEdit m_editAdhocConfTempTelephone;
	CEdit m_editAdhocConfTempReservedCsdPorts;
	CComboBox m_cbbAdhocConfTempCpResouce;
	CComboBox m_cbbAdhocConfTempMediaEncryptType;
	CComboBox m_cbbAdhocConfTempRate;
	CComboBox m_cbbAdhocConfTempIsLiveBroadcast;
	CComboBox m_cbbAdhocConfTempIsRecording;
	CComboBox m_cbbAdhocConfTempPresentation;
	CComboBox m_cbbAdhocConfTempVideoFormat;
	CComboBox m_cbbAdhocConfTempVideoProtocol;
	CComboBox m_cbbAdhocConfTempState;
	virtual BOOL OnInitDialog();
	CListCtrl m_listAllSites;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
