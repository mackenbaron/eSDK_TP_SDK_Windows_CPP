#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

class CTP_Native_Sheet;
// CTP_Native_ConfControlDlg dialog
//会议控制接口
class CTP_Native_ConfControlDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CTP_Native_ConfControlDlg)
private:
	CTP_Native_Sheet *m_sheet;
public:
	CTP_Native_ConfControlDlg();
	virtual ~CTP_Native_ConfControlDlg();
	void SetSheet(CTP_Native_Sheet* sheet) {m_sheet = sheet;}

	// Dialog Data
	enum { IDD = IDD_CONF_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	CString m_confID;
	CString m_siteUri;
	CString m_videoSourceUri;
	CString m_swtichGate;
	CString m_broadcastSiteUri;
	CString m_chairmanUri;
	CString m_setSiteUri;
	CListCtrl m_siteList;
	CString m_target;
	CComboBox m_isSwitch;
	CComboBox m_isBroadcast;
	CComboBox m_moreIsBroadcast;
	CComboBox m_isMute;
	CComboBox m_isQuiet;
	int m_num;
	int m_numVolume;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	CString m_volume;
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton12();
	CString m_sitemarkUri;
	CString m_temp;
	CString m_tempVolume;
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton8();
//	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton10();
	CComboBox m_cmbContinuousPresenceMode;
};
