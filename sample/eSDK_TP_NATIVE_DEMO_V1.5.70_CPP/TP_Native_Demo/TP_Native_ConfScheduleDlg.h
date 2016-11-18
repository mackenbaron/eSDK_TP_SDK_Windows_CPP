#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

class CTP_Native_Sheet;
// CTP_Native_ConfControlDlg dialog

class CTP_Native_ConfScheduleDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CTP_Native_ConfScheduleDlg)
private:
	CTP_Native_Sheet *m_sheet;
public:
	CTP_Native_ConfScheduleDlg();
	virtual ~CTP_Native_ConfScheduleDlg();
	void SetSheet(CTP_Native_Sheet* sheet) {m_sheet = sheet;}

// Dialog Data
	enum { IDD = IDD_DIALOG_CONF_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListCtrl m_listConference;
	list<ConferenceStatusEx> m_conferenceList;
	virtual BOOL OnInitDialog();
};
