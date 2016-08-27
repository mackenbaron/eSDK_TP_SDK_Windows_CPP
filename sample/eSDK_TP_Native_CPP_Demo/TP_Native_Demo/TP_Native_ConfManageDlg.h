#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

class CTP_Native_Sheet;
// CTP_Native_ConfControlDlg dialog
//会议调度
class CTP_Native_ConfManageDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CTP_Native_ConfManageDlg)
private:
	CTP_Native_Sheet *m_sheet;
public:
	CTP_Native_ConfManageDlg();
	virtual ~CTP_Native_ConfManageDlg();
	void SetSheet(CTP_Native_Sheet* sheet) {m_sheet = sheet;}

// Dialog Data
	enum { IDD = IDD_DIALOG_CONF_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListCtrl m_listConference;
	vector<ConferenceStatusEx> m_conferenceList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton7();
	CListCtrl m_listSitesInConf;
	afx_msg void OnNMClickListConference(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDeleteConf();
	vector<ConferenceStatusEx> m_ChoosedConferences;
	ConferenceStatusEx m_nowChoosedConference;
	CEdit m_editResultPanel;
	afx_msg void OnBnClickedButtonProlongConf();
	CEdit m_editProlongConfTime;
	afx_msg void OnBnClickedButtonAddSites();
	afx_msg void OnBnClickedButton12();
private:
	int m_iLastChoosedItem;
	list<SiteInfoEx> m_listChoosedSite;
	void GetChoosedConferencesItem();
	void getNowChoosedConference();
public:
	afx_msg void OnBnClickedButtonGetConfSites();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnNMClickListConfSites(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonConnectSites();
	afx_msg void OnBnClickedButtonDisconnectSites();
	afx_msg void OnBnClickedButtonDelSiteFromConf();
//	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnBnClickedButtonEditConfInfo();
	CComboBox m_cmbRate;
	CComboBox m_cmbEncryptType;
	CComboBox m_cmbCpResouce;
	CComboBox m_cmbAuxVideoProtocol;
	CComboBox m_cmbAuxVideoFormat;
	CEdit m_editNewConfName;
	CEdit m_editNewProlongTime;
	afx_msg void OnBnClickedButtonGetContinuousPresneceInfo();
	afx_msg void OnBnClickedButtonGetContinuousPresenceParam();
	afx_msg void OnBnClickedButtonQueryConfSiteMcu();
	CEdit m_editCdrQueryBeginTime;
	CEdit m_editCdrQueryDuration;
	CEdit m_editCdrQuerySiteUri;
	afx_msg void OnBnClickedButtonQueryPointToPointCdr();
	CComboBox m_cmbCdrQueryCallType;
	afx_msg void OnBnClickedButtonQueryMultiPointCdr();
	afx_msg void OnBnClickedButtonEditRecurrenceConf();
	CComboBox m_cmbNewRecurrenceFrequency;
	CEdit m_editNewRecurrenceInterval;
	CEdit m_editNewRecurrenceCount;
	afx_msg void OnBnClickedButton11();
};
