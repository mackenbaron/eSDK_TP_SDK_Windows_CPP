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
// CTP_Native_ConnectSiteDlg dialog

class CTP_Native_ConnectSiteDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CTP_Native_ConnectSiteDlg)
private:
	CTP_Native_Sheet *m_sheet;
public:
	CTP_Native_ConnectSiteDlg();
	virtual ~CTP_Native_ConnectSiteDlg();
	void SetSheet(CTP_Native_Sheet* sheet) {m_sheet = sheet;}
// Dialog Data
	enum { IDD = IDD_CONNECT_SITE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_confId;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_joinedSiteInfo;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	TPSDKResponseEx<list<SiteStatusEx>> m_joinedSitesInfo;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	vector<SiteStatusEx> allSitesInfo;
	afx_msg void OnBnClickedButton2();
};
