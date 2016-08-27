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

// TP_Native_ScheduleConfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_ScheduleConfDlg.h"
#include "afxdialogex.h"



// CTP_Native_ScheduleConfDlg dialog

IMPLEMENT_DYNAMIC(CTP_Native_ScheduleConfDlg, CPropertyPage)

CTP_Native_ScheduleConfDlg::CTP_Native_ScheduleConfDlg()
	: CPropertyPage(CTP_Native_ScheduleConfDlg::IDD)
	, m_confName(_T(""))
	, m_beginTime(_T(""))
	, m_confTime(_T(""))
	, m_confPwd(_T(""))
	, m_accessCode(_T(""))
	, m_chairmanPwd(_T(""))
{
	m_sheet = NULL;
}

CTP_Native_ScheduleConfDlg::~CTP_Native_ScheduleConfDlg()
{
}

void CTP_Native_ScheduleConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_sitesInfoList);
	DDX_Text(pDX, IDC_EDIT_CONFNAME, m_confName);
	DDX_Text(pDX, IDC_EDIT_BEGINTIME, m_beginTime);
	DDX_Text(pDX, IDC_EDIT_HOWLONG, m_confTime);
	DDX_Text(pDX, IDC_EDIT_PWD, m_confPwd);
	DDX_Text(pDX, IDC_EDIT_ACCESSCODE, m_accessCode);
	DDX_Text(pDX, IDC_EDIT_CHAIRMANPWD, m_chairmanPwd);
	DDX_Control(pDX, IDC_COMBO_RATE, m_cb_rate);
	DDX_Control(pDX, IDC_COMBO_PWDTYPE, m_cb_pwdtype);
	DDX_Control(pDX, IDC_COMBO_MULTI, m_cb_multi);
	DDX_Control(pDX, IDC_COMBO_VEDIOFM, m_cb_vediofm);
	DDX_Control(pDX, IDC_COMBO_VEDIOPR, m_cb_vediopr);
	DDX_Control(pDX, IDC_COMBO_FREQUENCY, m_cmbRecurrenceConfFrequency);
	DDX_Control(pDX, IDC_EDIT_RECURRENCE_COUNT, m_editRecurrenceConfCount);
	DDX_Control(pDX, IDC_EDIT_RECURRENCE_CONF_INTERVAL, m_editRecurrenceConfInterval);
}


BEGIN_MESSAGE_MAP(CTP_Native_ScheduleConfDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_QUERY_SITES, &CTP_Native_ScheduleConfDlg::OnBnClickedBtnQuerySites)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CTP_Native_ScheduleConfDlg::OnNMClickList2)
	ON_BN_CLICKED(IDC_BTN_CREATECONF, &CTP_Native_ScheduleConfDlg::OnBnClickedBtnCreateconf)
	ON_BN_CLICKED(IDC_CHECK_RECURRENCE_CONF, &CTP_Native_ScheduleConfDlg::OnBnClickedCheckRecurrenceConf)
	ON_BN_CLICKED(IDC_CHECK_ADHOC_CONF_TEMPLATE, &CTP_Native_ScheduleConfDlg::OnBnClickedCheckAdhocConfTemplate)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ADHOC_CONF_TEMPLATE, &CTP_Native_ScheduleConfDlg::OnBnClickedButtonAddAdhocConfTemplate)
END_MESSAGE_MAP()


// CTP_Native_ScheduleConfDlg message handlers

BOOL CTP_Native_ScheduleConfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_sitesInfoList.ModifyStyle(0,LVS_REPORT);

	DWORD dwStyle = m_sitesInfoList.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_sitesInfoList.SetExtendedStyle(dwStyle); // 设置扩展风格 

	m_sitesInfoList.InsertColumn(0,"URI",LVCFMT_CENTER,80,NULL);
	m_sitesInfoList.InsertColumn(1,"名称",LVCFMT_CENTER,80,NULL);
	m_sitesInfoList.InsertColumn(2,"类型",LVCFMT_CENTER,80,NULL);
	m_sitesInfoList.InsertColumn(3,"来源",LVCFMT_CENTER,80,NULL);
	m_sitesInfoList.InsertColumn(4,"呼叫方式",LVCFMT_CENTER,80,NULL);
	m_sitesInfoList.InsertColumn(5,"速率",LVCFMT_CENTER,100,NULL);
	m_sitesInfoList.InsertColumn(6,"视频格式",LVCFMT_CENTER,100,NULL);
	m_sitesInfoList.InsertColumn(7,"视频协议",LVCFMT_CENTER,100,NULL);
	m_sitesInfoList.InsertColumn(8,"锁定视频源",LVCFMT_CENTER,100,NULL);
	m_sitesInfoList.InsertColumn(9,"与会类型",LVCFMT_CENTER,100,NULL);

	SetDlgItemText(IDC_EDIT_CONFNAME, _T("New Conf"));

	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,30, 0);
	m_time=CTime::GetCurrentTime();//获取当前时间日期  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //格式化日期时间 

	SetDlgItemText(IDC_EDIT_BEGINTIME,strTime);
	SetDlgItemText(IDC_EDIT_HOWLONG, _T("120"));
	SetDlgItemText(IDC_EDIT_ACCESSCODE, _T(""));

	m_cb_rate.AddString(_T("64k"));
	m_cb_rate.AddString(_T("1920k"));
	m_cb_rate.AddString(_T("8192k"));
	m_cb_rate.SetCurSel(1);

	m_cb_pwdtype.AddString(_T("AutoEncrypt"));
	m_cb_pwdtype.AddString(_T("ForceEncrypt"));
	m_cb_pwdtype.AddString(_T("None"));
	m_cb_pwdtype.SetCurSel(0);

	m_cb_multi.AddString(_T("1"));
	m_cb_multi.AddString(_T("2"));
	m_cb_multi.AddString(_T("3"));
	m_cb_multi.AddString(_T("4"));
	m_cb_multi.AddString(_T("5"));
	m_cb_multi.AddString(_T("6"));
	m_cb_multi.AddString(_T("7"));
	m_cb_multi.AddString(_T("8"));
	m_cb_multi.SetCurSel(1);

	m_cb_vediopr.AddString(_T("Auto"));
	m_cb_vediopr.AddString(_T("H.261"));
	m_cb_vediopr.AddString(_T("H.263"));
	m_cb_vediopr.AddString(_T("H.264"));
	m_cb_vediopr.SetCurSel(0);

	m_cb_vediofm.AddString(_T("Auto"));
	m_cb_vediofm.AddString(_T("4CIF"));
	m_cb_vediofm.AddString(_T("720P30(720P)"));
	m_cb_vediofm.AddString(_T("1080P30(1080P)"));
	m_cb_vediofm.AddString(_T("480P"));
	m_cb_vediofm.AddString(_T("720P60"));
	m_cb_vediofm.AddString(_T("1080P60"));
	m_cb_vediofm.AddString(_T("QCIF"));
	m_cb_vediofm.AddString(_T("CIF"));
	m_cb_vediofm.AddString(_T("SQCIF"));
	m_cb_vediofm.AddString(_T("CIF2"));
	m_cb_vediofm.AddString(_T("I108"));
	m_cb_vediofm.AddString(_T("I480"));
	m_cb_vediofm.SetCurSel(0);

	m_cmbRecurrenceConfFrequency.AddString(_T("每天"));
	m_cmbRecurrenceConfFrequency.AddString(_T("每周"));
	m_cmbRecurrenceConfFrequency.AddString(_T("每月"));
	m_cmbRecurrenceConfFrequency.SetCurSel(1);
	m_cmbRecurrenceConfFrequency.EnableWindow(FALSE);
	m_editRecurrenceConfCount.EnableWindow(FALSE);
	m_editRecurrenceConfInterval.EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ACCESSCODE)->EnableWindow(FALSE);

	m_editRecurrenceConfInterval.SetWindowText("1");
	m_editRecurrenceConfCount.SetWindowText("2");

	return TRUE;
}


void CTP_Native_ScheduleConfDlg::OnBnClickedBtnQuerySites()
{
	// TODO: Add your control notification handler code here
	UpdateSiteList();
}


void CTP_Native_ScheduleConfDlg::UpdateSiteList()
{
	TPSDKResponseEx<list<SiteInfoEx>> siteList;

	siteList = querySitesEx();

	if (m_allSitesInfo.size()>0)
	{
		m_allSitesInfo.clear();
	}

	m_sitesInfoList.DeleteAllItems();
	if (siteList.resultCode==0)
	{
		int j=0;
		list<SiteInfoEx>::iterator i; 
		for (i = siteList.result.begin(); i != siteList.result.end(); ++i) 
		{
			m_allSitesInfo.push_back(*i);
			m_sitesInfoList.InsertItem(j,i->uri.c_str());
			m_sitesInfoList.SetItemText(j,1,i->name.c_str());
			CString str;
			str.Format("%d",i->type);
			m_sitesInfoList.SetItemText(j,2,str);
			str.Format("%d",i->from);
			m_sitesInfoList.SetItemText(j,3,str);
			str.Format("%d",i->dialingMode);
			m_sitesInfoList.SetItemText(j,4,str);
			m_sitesInfoList.SetItemText(j,5,i->rate.c_str());
			str.Format("%d",i->videoFormat);
			m_sitesInfoList.SetItemText(j,6,str);
			str.Format("%d",i->videoProtocol);
			m_sitesInfoList.SetItemText(j,7,str);
			str.Format("%d",i->isLockVideoSource);
			m_sitesInfoList.SetItemText(j,8,str);
			str.Format("%d",i->participantType);
			m_sitesInfoList.SetItemText(j,9,str);
			j++;
		}
	}
}

void CTP_Native_ScheduleConfDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	if(pNMItemActivate->iItem != -1) 
	{ 
		if(m_sitesInfoList.GetCheck(pNMItemActivate->iItem)) 
		{ 
			m_sitesInfoList.SetItemState(pNMItemActivate->iItem, 0, LVIS_SELECTED|LVIS_FOCUSED); 
			m_sitesInfoList.SetCheck(pNMItemActivate->iItem,FALSE); 
		} 
		else
		{
			m_sitesInfoList.SetItemState(pNMItemActivate->iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
			m_sitesInfoList.SetCheck(pNMItemActivate->iItem,TRUE);
		} 
	}

	*pResult = 0;
}


void CTP_Native_ScheduleConfDlg::OnBnClickedBtnCreateconf()
{
	// TODO: Add your control notification handler code here
	vector<int> indexTemp;
	for (int i=0;i<m_sitesInfoList.GetItemCount();i++)
	{
		if(m_sitesInfoList.GetCheck(i)) 
		{ 
			indexTemp.push_back(i);
		} 
	}

	if (indexTemp.size()>0)
	{
		TPSDKResponseEx<ConferenceInfoEx> confInfoReturn;

		ConferenceInfoEx scheduleConf;

		UpdateData(TRUE);
		//会议名称
		scheduleConf.name = m_confName.GetBuffer();


		COleDateTime tT;
		tT.ParseDateTime(m_beginTime);
		SYSTEMTIME st;
		tT.GetAsSystemTime(st);
		
		scheduleConf.beginTime = st;

		//会议时长
		int minutes = atoi(m_confTime.GetBuffer());
		int hours = minutes / 60;
		minutes = minutes - hours * 60;
		CString s; 
		s.Format("P0Y0M0DT%dH%dM0.000S", hours,minutes);
		scheduleConf.duration = s.GetBuffer();
		//接入码
		if ( BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_ADHOC_CONF_TEMPLATE))->GetCheck() )
		{
			scheduleConf.accessCode = m_accessCode.GetBuffer();
		}
		else
		{
			scheduleConf.accessCode = "";
		}
		//密码
		if (m_confPwd.GetLength()>0)
		{
			scheduleConf.password = m_confPwd.GetBuffer();
			scheduleConf.chairmanPassword = m_chairmanPwd.GetBuffer();
		}
		//加密方式
		scheduleConf.mediaEncryptType = m_cb_pwdtype.GetCurSel();
		//多画面模式
		scheduleConf.cpResouce = m_cb_multi.GetCurSel() + 1;
		//辅流视频格式
		scheduleConf.auxVideoFormat = m_cb_vediofm.GetCurSel();
		//视频协议
		scheduleConf.auxVideoProtocol = m_cb_vediopr.GetCurSel();
		//速率
		CString strRate;
		m_cb_rate.GetLBText(m_cb_rate.GetCurSel(),strRate);
		scheduleConf.rate = strRate.GetBuffer();
		//演示方式
		scheduleConf.presentation = 0;

		scheduleConf.isLiveBroadcast=0;
		scheduleConf.isRecording=0;
		scheduleConf.status=0;
		scheduleConf.maxSitesCount = 3;

		for (int j=0;j<indexTemp.size();j++)
		{
			scheduleConf.sites.push_back(m_allSitesInfo[indexTemp[j]]);
		}
		m_joinConfSitesInfo = scheduleConf.sites;
		if ( BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK_RECURRENCE_CONF))->GetCheck() )
		{   
			//创建普通会议
			confInfoReturn=scheduleConfEx(scheduleConf);
			if (confInfoReturn.resultCode==0)
			{
				CString s; 
				s.Format("创建会议成功；会议ID：%s",confInfoReturn.result.confId.c_str());
				SetDlgItemText(IDC_STATIC_RESULT,s.GetBuffer());
			} 
			else
			{
				CString s; 
				s.Format("创建会议失败；返回码：%d",confInfoReturn.resultCode);
				SetDlgItemText(IDC_STATIC_RESULT,s.GetBuffer());
			}
		} 
		else
		{
			//创建周期会议
			RecurrenceConfInfoEx recurrenceConf;
			recurrenceConf.base_info = scheduleConf;
			recurrenceConf.frequency = m_cmbRecurrenceConfFrequency.GetCurSel();   //每周
			CString cstrTemp;
			m_editRecurrenceConfInterval.GetWindowText(cstrTemp);
			recurrenceConf.interval = atoi(cstrTemp.GetBuffer());	//间隔
			recurrenceConf.weekDays.push_back(1);
			recurrenceConf.weekDay = 0;
			recurrenceConf.monthDay = 0;
			m_editRecurrenceConfCount.GetWindowText(cstrTemp);
			recurrenceConf.count = atoi(cstrTemp.GetBuffer());
			TPSDKResponseEx<RecurrenceConfInfoEx> response = scheduleRecurrenceConferenceEx( recurrenceConf ); 
			if ( 0 == response.resultCode )
			{
				CString s; 
				s.Format("创建会议成功；会议ID：%s",response.result.base_info.confId.c_str());
				SetDlgItemText(IDC_STATIC_RESULT,s.GetBuffer());
			} 
			else
			{
				CString s; 
				s.Format("创建会议失败；返回码：%d",response.resultCode);
				SetDlgItemText(IDC_STATIC_RESULT,s.GetBuffer());
			}
		}


	}
	else
	{
		SetDlgItemText(IDC_STATIC_RESULT, _T("请先勾选要参与会议的会场"));
	}
	
}


void CTP_Native_ScheduleConfDlg::OnBnClickedCheckRecurrenceConf()
{
	// TODO: Add your control notification handler code here
	if(BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK_RECURRENCE_CONF))->GetCheck())
	{
		m_cmbRecurrenceConfFrequency.EnableWindow(FALSE);
		//((CButton*)GetDlgItem(IDC_CHECK_ADHOC_CONF_TEMPLATE))->SetCheck(TRUE);
		m_editRecurrenceConfCount.EnableWindow(FALSE);
		m_editRecurrenceConfInterval.EnableWindow(FALSE);
	}
	else
	{
		m_cmbRecurrenceConfFrequency.EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_ADHOC_CONF_TEMPLATE))->SetCheck(FALSE);
		GetDlgItem(IDC_EDIT_ACCESSCODE)->EnableWindow(FALSE);
		m_editRecurrenceConfCount.EnableWindow(TRUE);
		m_editRecurrenceConfInterval.EnableWindow(TRUE);
	}
}


void CTP_Native_ScheduleConfDlg::OnBnClickedCheckAdhocConfTemplate()
{
	// TODO: Add your control notification handler code here
	if(BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK_ADHOC_CONF_TEMPLATE))->GetCheck())
	{
		//((CButton*)GetDlgItem(IDC_CHECK_RECURRENCE_CONF))->SetCheck(TRUE);
		//m_cmbRecurrenceConfFrequency.EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ACCESSCODE)->EnableWindow(FALSE);

	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_RECURRENCE_CONF))->SetCheck(FALSE);
		m_cmbRecurrenceConfFrequency.EnableWindow(FALSE);
		m_editRecurrenceConfCount.EnableWindow(FALSE);
		m_editRecurrenceConfInterval.EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ACCESSCODE)->EnableWindow(TRUE);
	}
}


void CTP_Native_ScheduleConfDlg::OnBnClickedButtonAddAdhocConfTemplate()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	std::string strOrgId = "1";
	AdhocConfTemplateParamEx adhocConfTemplate;
	adhocConfTemplate.adhocConfTemplateId = "0";
	adhocConfTemplate.name = m_confName.GetBuffer();
	CString cstrTemp;
	//会议激活码
	adhocConfTemplate.accessCode = m_accessCode.GetBuffer();
	//会议时长
	int minutes = atoi(m_confTime.GetBuffer());
	int hours = minutes / 60;
	minutes = minutes - hours * 60;
    //cstrTemp = "";
	cstrTemp.Format("P0Y0M0DT%dH%dM0.000S", hours,minutes);
	adhocConfTemplate.duration = cstrTemp.GetBuffer();
	//密码
	if (m_confPwd.GetLength()>0)
	{
		adhocConfTemplate.password = m_confPwd.GetBuffer();
		adhocConfTemplate.chairmanPassword = m_chairmanPwd.GetBuffer();
	}
	//加密方式
	adhocConfTemplate.mediaEncryptType = m_cb_pwdtype.GetCurSel();
	//多画面模式
	adhocConfTemplate.cpResouce = m_cb_multi.GetCurSel() + 1;
	//速率
	CString strRate;
	m_cb_rate.GetLBText(m_cb_rate.GetCurSel(),strRate);
	adhocConfTemplate.rate = strRate.GetBuffer();
	//演示方式
	adhocConfTemplate.presentation = 0;

	adhocConfTemplate.isLiveBroadcast=0;
	adhocConfTemplate.isRecording=0;
	adhocConfTemplate.maxSitesCount = 3;

	vector<int> indexTemp;
	for (int i=0;i<m_sitesInfoList.GetItemCount();i++)
	{
		if(m_sitesInfoList.GetCheck(i)) 
		{ 
			indexTemp.push_back(i);
		} 
	}
	for (int j=0;j<indexTemp.size();j++)
	{
		adhocConfTemplate.sites.push_back(m_allSitesInfo[indexTemp[j]]);
	}

	TPSDKResponseEx<std::string> response = addAdhocConfTemplateEx( strOrgId, adhocConfTemplate );
	if ( 0 == response.resultCode )
	{
		CString s; 
		s.Format("创建会议模板成功；模板ID：%s",response.result.c_str());
		SetDlgItemText(IDC_STATIC_RESULT,s.GetBuffer());
	} 
	else
	{
		CString s; 
		s.Format("创建会议模板失败；返回码：%d",response.resultCode);
		SetDlgItemText(IDC_STATIC_RESULT,s.GetBuffer());
	}
}
