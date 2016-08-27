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

// TP_Native_BroadcastSiteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_BroadcastSiteDlg.h"
#include "afxdialogex.h"


// CTP_Native_BroadcastSiteDlg dialog

IMPLEMENT_DYNAMIC(CTP_Native_BroadcastSiteDlg, CPropertyPage)

CTP_Native_BroadcastSiteDlg::CTP_Native_BroadcastSiteDlg(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CTP_Native_BroadcastSiteDlg::IDD)
	, m_confId(_T(""))
{
	m_curSite="";
}

CTP_Native_BroadcastSiteDlg::~CTP_Native_BroadcastSiteDlg()
{
}

void CTP_Native_BroadcastSiteDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_confId);
	DDX_Control(pDX, IDC_LIST1, m_joinedSiteInfo);
}


BEGIN_MESSAGE_MAP(CTP_Native_BroadcastSiteDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON2, &CTP_Native_BroadcastSiteDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CTP_Native_BroadcastSiteDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTP_Native_BroadcastSiteDlg::OnNMClickList1)
END_MESSAGE_MAP()

BOOL CTP_Native_BroadcastSiteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_joinedSiteInfo.ModifyStyle(0,LVS_REPORT);

	DWORD dwStyle = m_joinedSiteInfo.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	m_joinedSiteInfo.SetExtendedStyle(dwStyle); // 设置扩展风格 

	m_joinedSiteInfo.InsertColumn(0,"URI",LVCFMT_CENTER,80,NULL);
	m_joinedSiteInfo.InsertColumn(1,"名称",LVCFMT_CENTER,80,NULL);
	m_joinedSiteInfo.InsertColumn(2,"状态",LVCFMT_CENTER,80,NULL);
	m_joinedSiteInfo.InsertColumn(3,"音量",LVCFMT_CENTER,80,NULL);
	m_joinedSiteInfo.InsertColumn(4,"视频源",LVCFMT_CENTER,80,NULL);
	m_joinedSiteInfo.InsertColumn(5,"闭音",LVCFMT_CENTER,100,NULL);
	m_joinedSiteInfo.InsertColumn(6,"静音",LVCFMT_CENTER,100,NULL);
	m_joinedSiteInfo.InsertColumn(7,"类型",LVCFMT_CENTER,100,NULL);

	return TRUE;
}

// CTP_Native_BroadcastSiteDlg message handlers


void CTP_Native_BroadcastSiteDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	if (m_curSite=="")
	{
		SetDlgItemText(IDC_STATIC_BROADCAST_REST, _T("请先选则要终止广播的会场"));
	} 
	else
	{
		UpdateData(TRUE);
		std::string  confId = m_confId.GetBuffer();
		int result =setBroadcastSiteEx(confId,m_curSite,1);

		if (result == 0)
		{
			SetDlgItemText(IDC_STATIC_CONNECT_REST, _T("终止广播成功"));
		}
		else
		{
			CString s; 
			s.Format("终止广播失败，返回码：%d",result);
			SetDlgItemText(IDC_STATIC_CONNECT_REST,s.GetBuffer());

		}

	}
}


void CTP_Native_BroadcastSiteDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if (m_curSite=="")
	{
		SetDlgItemText(IDC_STATIC_BROADCAST_REST, _T("请先选则要广播的会场"));
	} 
	else
	{
		UpdateData(TRUE);
		std::string  confId = m_confId.GetBuffer();
		int result =setBroadcastSiteEx(confId,m_curSite,0);

		if (result == 0)
		{
			SetDlgItemText(IDC_STATIC_BROADCAST_REST, _T("广播成功"));
		}
		else
		{
			CString s; 
			s.Format("广播失败，返回码：%d",result);
			SetDlgItemText(IDC_STATIC_BROADCAST_REST,s.GetBuffer());
		}
		
	}
}


BOOL CTP_Native_BroadcastSiteDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	if (WM_KEYDOWN   ==   pMsg-> message && 13   ==   pMsg-> wParam)
	{
		if (  GetDlgItem(IDC_EDIT1) == GetFocus())
		{
			UpdateData(TRUE);
			std::string  confId = m_confId.GetBuffer();
			list<std::string> siteUris;
			if (joinedSitesInfo.result.size()>0)
			{
				joinedSitesInfo.result.clear();
			}
			joinedSitesInfo=queryConfSitesStatusEx(confId,siteUris);

			if (joinedSitesInfo.resultCode==0)
			{
				m_joinedSiteInfo.DeleteAllItems();
				int j=0;
				list<SiteStatusEx>::iterator i; 
				for (i = joinedSitesInfo.result.begin(); i != joinedSitesInfo.result.end(); ++i) 
				{
					m_joinedSiteInfo.InsertItem(j,i->uri.c_str());
					m_joinedSiteInfo.SetItemText(j,1,i->name.c_str());
					CString str;
					str.Format("%d",i->status);
					m_joinedSiteInfo.SetItemText(j,2,str);
					str.Format("%d",i->volume);
					m_joinedSiteInfo.SetItemText(j,3,str);
					m_joinedSiteInfo.SetItemText(j,4,i->videoSource.c_str());
					str.Format("%d",i->isQuiet);
					m_joinedSiteInfo.SetItemText(j,5,str);
					str.Format("%d",i->isMute);
					m_joinedSiteInfo.SetItemText(j,6,str);
					str.Format("%d",i->type);
					m_joinedSiteInfo.SetItemText(j,7,str);
					j++;
				}
			}

			return TRUE;

		}

	}

	return CPropertyPage::PreTranslateMessage(pMsg);
}


void CTP_Native_BroadcastSiteDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	if(pNMItemActivate->iItem != -1) 
	{ 
		CString s=m_joinedSiteInfo.GetItemText(pNMItemActivate->iItem,0); 
		m_curSite=s.GetBuffer();
	}


	*pResult = 0;
}
