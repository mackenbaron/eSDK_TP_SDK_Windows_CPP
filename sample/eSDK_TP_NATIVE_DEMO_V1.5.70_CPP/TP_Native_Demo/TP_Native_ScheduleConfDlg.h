/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#pragma once
//#include "TP_Native_Sheet.h"
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

class CTP_Native_Sheet;
// CTP_Native_ScheduleConfDlg dialog

class CTP_Native_ScheduleConfDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CTP_Native_ScheduleConfDlg)
private:
	CTP_Native_Sheet *m_sheet;
public:
	CTP_Native_ScheduleConfDlg();   // standard constructor
	virtual ~CTP_Native_ScheduleConfDlg();
	void SetSheet(CTP_Native_Sheet* sheet) {m_sheet = sheet;}
	void UpdateSiteList();
// Dialog Data
	enum { IDD = IDD_SCHEDULE_CONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnQuerySites();
	CListCtrl m_sitesInfoList;
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_confName;
	CString m_beginTime;
	CString m_confTime;
	CString m_confPwd;
	CString m_accessCode;
	CString m_chairmanPwd;
	CComboBox m_cb_rate;
	CComboBox m_cb_pwdtype;
	CComboBox m_cb_multi;
	CComboBox m_cb_vediofm;
	CComboBox m_cb_vediopr;
	afx_msg void OnBnClickedBtnCreateconf();
	vector<SiteInfoEx> m_allSitesInfo;
	vector<SiteInfoEx> m_joinConfSitesInfo;
	CComboBox m_cmbRecurrenceConfFrequency;
	afx_msg void OnBnClickedCheckRecurrenceConf();
	afx_msg void OnBnClickedCheckAdhocConfTemplate();
	afx_msg void OnBnClickedButtonAddAdhocConfTemplate();
	CEdit m_editRecurrenceConfCount;
	CEdit m_editRecurrenceConfInterval;
};
