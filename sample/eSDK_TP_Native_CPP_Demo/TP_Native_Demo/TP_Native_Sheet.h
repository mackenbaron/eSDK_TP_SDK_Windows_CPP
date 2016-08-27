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
#if 0
#include "TEX0_CallPage.h"
#include "TEX0_StatusPage.h"
#include "TEX0_ConferencePage.h"
#include "TEX0_IncomingCall.h"
#include "TEX0_CheckConfCtrlPWD.h"
#include "TEX0_SDK.h"
#endif
#include "TP_Native_ScheduleConfDlg.h"
#include "TP_Native_AddSiteTOConfDlg.h"
#include "TP_Native_ConnectSiteDlg.h"
#include "TP_Native_BroadcastSiteDlg.h"
#include "TP_Native_OtherInterface.h"
#include "TP_Native_ConfManageDlg.h"
#include "TP_Native_ConfControl.h"
#include "TP_Native_AdhocConfTempManage.h"
#include "TP_Native_MangerDlg.h"
// CTEX0_Sheet


class CTP_Native_Sheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CTP_Native_Sheet)

public:
	CTP_Native_Sheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CTP_Native_Sheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CTP_Native_Sheet();

protected:
	DECLARE_MESSAGE_MAP()

private:
	bool m_run;
	HANDLE m_thread;
	unsigned int m_threadID;
	int m_confType;
	CTP_Native_ScheduleConfDlg m_scheduleConfPage;
	//TP_Native_AddSiteTOConfDlg m_addSiteToConfPage;
	//CTP_Native_ConnectSiteDlg m_connectSitePage;
	//CTP_Native_BroadcastSiteDlg m_broadcastSitePage;
	CTP_Native_OtherInterface  m_otherInterface;
	CTP_Native_ConfManageDlg m_ConferenceManagePage;
	CTP_Native_ConfControlDlg m_ConferenceControlPage;

	CTP_Native_AdhocConfTempManage m_adhocConfTempManagePage;
	CTP_Native_MangerDlg m_MangerPage;
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	void ShowTitleMsg(CString msg) {SetWindowText(msg);}
	void MainLoop();
	void StartMsgRetrieval();
	void StopMsgRetrieval();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnIdok();
};


