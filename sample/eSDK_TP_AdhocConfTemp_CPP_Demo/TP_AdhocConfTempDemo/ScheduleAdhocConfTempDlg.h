#pragma once
#include "afxcmn.h"

class CTP_Native_Sheet;
// CScheduleAdhocConfTempDlg dialog

class CScheduleAdhocConfTempDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CScheduleAdhocConfTempDlg)

public:
	CScheduleAdhocConfTempDlg();
	virtual ~CScheduleAdhocConfTempDlg();
	void SetSheet(CTP_Native_Sheet* sheet) {m_sheet = sheet;}

// Dialog Data
	enum { IDD = IDD_DIALOG_SCHEDULE_ADHOC_CONF_TEMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listAllAdhocConfTemp;
	list<AdhocConfTemplateParamEx> m_listAllAdhocConferencesTemplate;
private:
	CTP_Native_Sheet *m_sheet;
	int m_choosedAdhocConfTempItem;
	list<AdhocConfTemplateParamEx>::iterator getChoosedAdhocConfTemplate();
	void getAllAdhocConfTempList();
	void showAllAdhocConfTempList();
	int m_list2BeHit;
	int m_list2ItemSel;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
};
