#pragma once
#include "afxcmn.h"
#include "afxcmn.h"
#include "afxwin.h"

class CTP_Native_Sheet;
// CTP_Native_AdhocConfTempManage dialog

class CTP_Native_AdhocConfTempManage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTP_Native_AdhocConfTempManage)

public:
	CTP_Native_AdhocConfTempManage();
	virtual ~CTP_Native_AdhocConfTempManage();
	void SetSheet(CTP_Native_Sheet* sheet) {m_sheet = sheet;}
	void GetChoosedAdhocConferenceList();
	void getChoosedAdhocConfTemplateList();
// Dialog Data
	enum { IDD = IDD_DIALOG_ADHOC_CONF_TEMPLATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listAllAdhocConfTemplate;
	CListCtrl m_listAllAdhocConference;
	virtual BOOL OnInitDialog();
private:
	CTP_Native_Sheet *m_sheet;
	int m_iLastChoosedAdhocTemplateItem;
	list<AdhocConfTemplateParamEx> m_listAllAdhocConferencesTemplate;
	AdhocConfTemplateParamEx m_choosedConfTemplate;
	std::string m_choosedConfTemplateId;
	list<AdhocConferenceEx> m_listChoosedAdhocConferences;
	list<AdhocConferenceEx> m_listAllAdhocConferences;
	void clearChoosedConfTemplate();
public:
	afx_msg void OnBnClickedButtonGetadhocConfTemplate();
	CEdit m_editResultPanel;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGetAdhocConferences();
	CEdit m_editNewAdhocConfTempName;
	CEdit m_editNewAdhocTempDuration;
	CComboBox m_cmbNewAdhocTemplateRate;
	CComboBox m_cmbNewAdhocTemplateMediaEncrytType;
	CEdit m_editNewAdhocTemplateAccessCode;
	CComboBox m_cmbNewAdhocTemplatePresentationVideo;
	CComboBox m_cmbNewAdhocTemplateCpResouce;
	afx_msg void OnBnClickedButtonEditAdhocConfTemplate();
	afx_msg void OnBnClickedButtonDeleteAdhocTemplate();
	afx_msg void OnBnClickedButtonQueryAdhocConfFreeBusy();
	afx_msg void OnNMClickList5(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_editQueryBeginTime;
	CEdit m_editQueryAdhocDuration;
	afx_msg void OnBnClickedButtonSynchAdhocConfFreeBusy();
	afx_msg void OnBnClickedButtonQueryPointToPointCdr();
	CComboBox m_cmbQueryAdhocTempType;
	CEdit m_editQueryAdhocTempKeyValue;
};
