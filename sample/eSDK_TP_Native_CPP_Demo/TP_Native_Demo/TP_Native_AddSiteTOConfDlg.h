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
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"

class CTP_Native_Sheet;
// TP_Native_AddSiteTOConfDlg dialog

class TP_Native_AddSiteTOConfDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(TP_Native_AddSiteTOConfDlg)
private:
	CTP_Native_Sheet *m_sheet;
	int getConfSiteList(string confId);
public:
	TP_Native_AddSiteTOConfDlg();
	virtual ~TP_Native_AddSiteTOConfDlg();
	void SetSheet(CTP_Native_Sheet* sheet) {m_sheet = sheet;}
// Dialog Data
	enum { IDD = IDD_ADD_SITE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_confId;
	CListCtrl m_allConfList;
	CListCtrl m_joinedList;
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	vector<SiteInfoEx> allSitesInfo;
	TPSDKResponseEx<list<SiteStatusEx>> joinedSitesInfo;
};
