#pragma once

#include "AddAdhocConfTempDlg.h"
#include "ScheduleAdhocConfTempDlg.h"
// CTP_Native_Sheet

class CTP_Native_Sheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CTP_Native_Sheet)

public:
	CTP_Native_Sheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CTP_Native_Sheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CTP_Native_Sheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	bool m_run;
	HANDLE m_thread;
	unsigned int m_threadID;
	CAddAdhocConfTempDlg m_addAdhocConfTempDlg;
	CScheduleAdhocConfTempDlg m_scheduleAdhocTempDlg;
	void startMsgRetrieval();
	void StopMsgRetrieval();
public:
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnIdok();
	void tpNativeKeepAlive();
};


