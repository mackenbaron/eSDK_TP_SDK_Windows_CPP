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

// TP_Native_AddSiteTOConfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_AddSiteTOConfDlg.h"
#include "afxdialogex.h"


// TP_Native_AddSiteTOConfDlg dialog

IMPLEMENT_DYNAMIC(TP_Native_AddSiteTOConfDlg, CPropertyPage)

TP_Native_AddSiteTOConfDlg::TP_Native_AddSiteTOConfDlg()
	: CPropertyPage(TP_Native_AddSiteTOConfDlg::IDD)
	, m_confId(_T(""))
{
	m_sheet = NULL;
}

TP_Native_AddSiteTOConfDlg::~TP_Native_AddSiteTOConfDlg()
{
}

void TP_Native_AddSiteTOConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONFID, m_confId);
	DDX_Control(pDX, IDC_LIST2, m_allConfList);
	DDX_Control(pDX, IDC_LIST3, m_joinedList);
}


BEGIN_MESSAGE_MAP(TP_Native_AddSiteTOConfDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &TP_Native_AddSiteTOConfDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &TP_Native_AddSiteTOConfDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &TP_Native_AddSiteTOConfDlg::OnNMClickList2)
END_MESSAGE_MAP()


// TP_Native_AddSiteTOConfDlg message handlers


BOOL TP_Native_AddSiteTOConfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_allConfList.ModifyStyle(0,LVS_REPORT);

	DWORD dwStyle = m_allConfList.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_allConfList.SetExtendedStyle(dwStyle); // 设置扩展风格 

	m_allConfList.InsertColumn(0,"URI",LVCFMT_CENTER,80,NULL);
	m_allConfList.InsertColumn(1,"名称",LVCFMT_CENTER,80,NULL);
	m_allConfList.InsertColumn(2,"类型",LVCFMT_CENTER,80,NULL);
	m_allConfList.InsertColumn(3,"来源",LVCFMT_CENTER,80,NULL);
	m_allConfList.InsertColumn(4,"呼叫方式",LVCFMT_CENTER,80,NULL);
	m_allConfList.InsertColumn(5,"速率",LVCFMT_CENTER,100,NULL);
	m_allConfList.InsertColumn(6,"视频格式",LVCFMT_CENTER,100,NULL);
	m_allConfList.InsertColumn(7,"视频协议",LVCFMT_CENTER,100,NULL);
	m_allConfList.InsertColumn(8,"锁定视频源",LVCFMT_CENTER,100,NULL);
	m_allConfList.InsertColumn(9,"与会类型",LVCFMT_CENTER,100,NULL);

	
	m_joinedList.ModifyStyle(0,LVS_REPORT);

	dwStyle = m_joinedList.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	m_joinedList.SetExtendedStyle(dwStyle); // 设置扩展风格 

	m_joinedList.InsertColumn(0,"URI",LVCFMT_CENTER,80,NULL);
	m_joinedList.InsertColumn(1,"名称",LVCFMT_CENTER,80,NULL);
	m_joinedList.InsertColumn(2,"状态",LVCFMT_CENTER,80,NULL);
	m_joinedList.InsertColumn(3,"音量",LVCFMT_CENTER,80,NULL);
	m_joinedList.InsertColumn(4,"视频源",LVCFMT_CENTER,80,NULL);
	m_joinedList.InsertColumn(5,"闭音",LVCFMT_CENTER,100,NULL);
	m_joinedList.InsertColumn(6,"静音",LVCFMT_CENTER,100,NULL);
	m_joinedList.InsertColumn(7,"类型",LVCFMT_CENTER,100,NULL);

	return TRUE;
}

void TP_Native_AddSiteTOConfDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<SiteInfoEx>> siteList;

	siteList = querySitesEx();

	if (allSitesInfo.size()>0)
	{
		allSitesInfo.clear();
	}

	m_allConfList.DeleteAllItems();
	if (siteList.resultCode==0)
	{
		int j=0;
		list<SiteInfoEx>::iterator i; 
		for (i = siteList.result.begin(); i != siteList.result.end(); ++i) 
		{
			allSitesInfo.push_back(*i);
			m_allConfList.InsertItem(j,i->uri.c_str());
			m_allConfList.SetItemText(j,1,i->name.c_str());
			CString str;
			str.Format("%d",i->type);
			m_allConfList.SetItemText(j,2,str);
			str.Format("%d",i->from);
			m_allConfList.SetItemText(j,3,str);
			str.Format("%d",i->dialingMode);
			m_allConfList.SetItemText(j,4,str);
			m_allConfList.SetItemText(j,5,i->rate.c_str());
			str.Format("%d",i->videoFormat);
			m_allConfList.SetItemText(j,6,str);
			str.Format("%d",i->videoProtocol);
			m_allConfList.SetItemText(j,7,str);
			str.Format("%d",i->isLockVideoSource);
			m_allConfList.SetItemText(j,8,str);
			str.Format("%d",i->participantType);
			m_allConfList.SetItemText(j,9,str);
			j++;
		}
	}
}


void TP_Native_AddSiteTOConfDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	vector<int> indexTemp;
	for (int i=0;i<m_allConfList.GetItemCount();i++)
	{
		if(m_allConfList.GetCheck(i)) 
		{ 
			indexTemp.push_back(i);
		} 
	}

	if (indexTemp.size()>0)
	{
		UpdateData(TRUE);
		//会议ID
		std::string  confId = m_confId.GetBuffer();
		 bool falg = true;
		if (getConfSiteList(confId) == 0)
		{
			for (int j=0;j<indexTemp.size();j++)
			{
				allSitesInfo[indexTemp[j]].rate="1920k";
				allSitesInfo[indexTemp[j]].type = 4;
				allSitesInfo[indexTemp[j]].videoProtocol = 1;

				falg = true;

				list<SiteStatusEx>::iterator i; 
				for (i = joinedSitesInfo.result.begin(); i != joinedSitesInfo.result.end(); ++i) 
				{
					if (allSitesInfo[indexTemp[j]].uri==i->uri)
					{
						falg = false;
						break;
					}
				}
				if (falg)
				{
					SYSTEMTIME beginTime;
					memset(&beginTime,0,sizeof(SYSTEMTIME));
					TPSDKResponseEx<list<SiteAccessInfoEx>> addSiteReturn=addSiteToConfEx(confId, allSitesInfo[indexTemp[j]], beginTime);

					if (addSiteReturn.resultCode != 0)
					{
						SetDlgItemText(IDC_STATIC_ADDCONF_REST, _T("添加会场失败，返回码："+addSiteReturn.resultCode));
					}
				}
			}


			getConfSiteList(confId);

			m_joinedList.DeleteAllItems();
			int j=0;
			list<SiteStatusEx>::iterator i; 
			for (i = joinedSitesInfo.result.begin(); i != joinedSitesInfo.result.end(); ++i) 
			{
				m_joinedList.InsertItem(j,i->uri.c_str());
				m_joinedList.SetItemText(j,1,i->name.c_str());
				CString str;
				str.Format("%d",i->status);
				m_joinedList.SetItemText(j,2,str);
				str.Format("%d",i->volume);
				m_joinedList.SetItemText(j,3,str);
				m_joinedList.SetItemText(j,4,i->videoSource.c_str());
				str.Format("%d",i->isQuiet);
				m_joinedList.SetItemText(j,5,str);
				str.Format("%d",i->isMute);
				m_joinedList.SetItemText(j,6,str);
				str.Format("%d",i->type);
				m_joinedList.SetItemText(j,7,str);
				j++;
			}
			SetDlgItemText(IDC_STATIC_ADDCONF_REST, _T("添加会场成功"));

		}
		else
		{
			CString s; 
			s.Format("获取已参会的会场列表失败，返回码：%d",joinedSitesInfo.resultCode);
			SetDlgItemText(IDC_STATIC_ADDCONF_REST,s.GetBuffer());
		}
	}
	else
	{
		SetDlgItemText(IDC_STATIC_ADDCONF_REST, _T("请先勾选要添加的会场"));
	}
	
}


void TP_Native_AddSiteTOConfDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	if(pNMItemActivate->iItem != -1) 
	{ 
		if(m_allConfList.GetCheck(pNMItemActivate->iItem)) 
		{ 
			m_allConfList.SetItemState(pNMItemActivate->iItem, 0, LVIS_SELECTED|LVIS_FOCUSED); 
			m_allConfList.SetCheck(pNMItemActivate->iItem,FALSE); 
		} 
		else
		{
			m_allConfList.SetItemState(pNMItemActivate->iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
			m_allConfList.SetCheck(pNMItemActivate->iItem,TRUE);
		} 
	}

	*pResult = 0;
}


//获取会议中的会场
int TP_Native_AddSiteTOConfDlg::getConfSiteList(string confId)
{
	list<std::string> siteUris;
	if (joinedSitesInfo.result.size()>0)
	{
		joinedSitesInfo.result.clear();
	}
	joinedSitesInfo=queryConfSitesStatusEx(confId,siteUris);
	return joinedSitesInfo.resultCode;
}
