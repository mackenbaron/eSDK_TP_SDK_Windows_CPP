// TP_Native_AllSitesList.cpp : implementation file
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_AllSitesList.h"
#include "afxdialogex.h"
#include "TP_Tool.h"

// CTP_Native_AllSitesList dialog

IMPLEMENT_DYNAMIC(CTP_Native_AllSitesList, CDialogEx)

CTP_Native_AllSitesList::CTP_Native_AllSitesList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTP_Native_AllSitesList::IDD, pParent)
{
	m_LastQueryTime.wYear = 0;
	m_LastQueryTime.wMonth = 0;
	m_LastQueryTime.wDay = 0;
	m_LastQueryTime.wHour = 0;
	m_LastQueryTime.wMinute = 0;
	m_LastQueryTime.wSecond = 0;
}

CTP_Native_AllSitesList::~CTP_Native_AllSitesList()
{
}

void CTP_Native_AllSitesList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listAllSites);
	DDX_Control(pDX, IDC_EDIT1, m_editResultPanel);
}


BEGIN_MESSAGE_MAP(CTP_Native_AllSitesList, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SITES, &CTP_Native_AllSitesList::OnBnClickedButtonAddSites)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTP_Native_AllSitesList::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_SITE_STATUS, &CTP_Native_AllSitesList::OnBnClickedButtonQuerySiteStatus)
	ON_BN_CLICKED(IDC_BUTTON_SYNC_SITE_STATUS, &CTP_Native_AllSitesList::OnBnClickedButtonSyncSiteStatus)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SITE_INFO, &CTP_Native_AllSitesList::OnBnClickedButtonDeleteSiteInfo)
	ON_BN_CLICKED(IDC_BUTTON_GET_ALL_SITE, &CTP_Native_AllSitesList::OnBnClickedButtonGetAllSite)
END_MESSAGE_MAP()


// CTP_Native_AllSitesList message handlers


BOOL CTP_Native_AllSitesList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_listAllSites.ModifyStyle(0, LVS_REPORT);
	DWORD dwStyle = m_listAllSites.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_listAllSites.SetExtendedStyle(dwStyle); // 设置扩展风格 

	m_listAllSites.InsertColumn(0,"URI",LVCFMT_CENTER,80,NULL);
	m_listAllSites.InsertColumn(1,"名称",LVCFMT_CENTER,80,NULL);
	m_listAllSites.InsertColumn(2,"类型",LVCFMT_CENTER,80,NULL);
	m_listAllSites.InsertColumn(3,"来源",LVCFMT_CENTER,80,NULL);
	m_listAllSites.InsertColumn(4,"呼叫方式",LVCFMT_CENTER,80,NULL);
	m_listAllSites.InsertColumn(5,"速率",LVCFMT_CENTER,100,NULL);
	m_listAllSites.InsertColumn(6,"视频格式",LVCFMT_CENTER,100,NULL);
	m_listAllSites.InsertColumn(7,"视频协议",LVCFMT_CENTER,100,NULL);
	m_listAllSites.InsertColumn(8,"锁定视频源",LVCFMT_CENTER,100,NULL);
	m_listAllSites.InsertColumn(9,"与会类型",LVCFMT_CENTER,100,NULL);

	initAllSiteInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



void CTP_Native_AllSitesList::OnBnClickedButtonAddSites()
{
	// TODO: Add your control notification handler code here
	GetChoosedSites();
}

void CTP_Native_AllSitesList::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMItemActivate->iItem != -1) 
	{ 
		if(m_listAllSites.GetCheck(pNMItemActivate->iItem)) 
		{ 
			m_listAllSites.SetItemState(pNMItemActivate->iItem, 0, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listAllSites.SetCheck(pNMItemActivate->iItem,FALSE); 
		} 
		else
		{
			m_listAllSites.SetItemState(pNMItemActivate->iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listAllSites.SetCheck(pNMItemActivate->iItem,TRUE);
		} 
	}
	*pResult = 0;
}


void CTP_Native_AllSitesList::OnBnClickedButtonQuerySiteStatus()
{
	// TODO: Add your control notification handler code here
	list<std::string> siteUris;
	GetChoosedSites();
	for ( list<SiteInfoEx>::iterator iter = m_listChoosedSite.begin(); iter != m_listChoosedSite.end(); iter++ )
	{
		siteUris.push_back(iter->uri);
	}
	m_listChoosedSite.clear();
	if ( siteUris.size() > 0 )
	{
		CString cstrResult;
		SYSTEMTIME beginTime;
		CTime m_time;
		m_time=CTime::GetCurrentTime();//获取当前时间日期  
		m_time.GetAsSystemTime(beginTime);
		m_LastQueryTime = beginTime;
		TPSDKResponseEx<map<std::string,list<FreeBusyStateEx>>> response = querySiteStatusEx( siteUris, beginTime, "P0Y0M0DT6H0M0.000S"); 
		if ( 0 == response.resultCode )
		{
			cstrResult = _T("查询会场忙闲状态成功：");
			for ( map<std::string,list<FreeBusyStateEx>>::iterator iter = response.result.begin(); iter != response.result.end(); iter++ )
			{
				CString cstrTemp;
				cstrTemp.Format( "会场URI:%s ",iter->first.c_str() );
				for ( list<FreeBusyStateEx>::iterator iter1 = iter->second.begin(); iter1 != iter->second.end(); iter1++ )
				{
					CString cstrTemp1;
					cstrTemp1.Format("开始时间:%04d-%02d-%02dT%02d:%02d:%02d%s,持续时间:%s,忙闲状态:%d,会议ID:%s,会议名:%s", iter1->startTime.wYear, 
						             iter1->startTime.wMonth, iter1->startTime.wDay, iter1->startTime.wHour, iter1->startTime.wMinute, iter1->startTime.wSecond,
						             TP_Tool::GetLocalTimeZone().c_str(), iter1->span.c_str(), iter1->state, iter1->confId.c_str(), iter1->confName.c_str() );
					cstrTemp = cstrTemp +" " + cstrTemp1;
				}
				cstrResult = cstrResult + "   " + cstrTemp;
			}
		} 
		else
		{
			CString cstrResult= _T("查询会场忙闲状态失败：");
		}
		m_editResultPanel.SetWindowText( cstrResult ); 
	}
	else
	{
		m_editResultPanel.SetWindowText( _T("请选择要查询的会场") ); 
	}
}

void CTP_Native_AllSitesList::GetChoosedSites()
{
	m_listChoosedSite.clear();
	for (int i=0; i<m_listAllSites.GetItemCount(); i++)
	{
		if(m_listAllSites.GetCheck(i)) 
		{ 
			m_listChoosedSite.push_back( m_allSitesInfo[i] );
		}
	}
}

void CTP_Native_AllSitesList::OnBnClickedButtonSyncSiteStatus()
{
	// TODO: Add your control notification handler code here
	list<std::string> siteUris;
	GetChoosedSites();
	for ( list<SiteInfoEx>::iterator iter = m_listChoosedSite.begin(); iter != m_listChoosedSite.end(); iter++ )
	{
		siteUris.push_back(iter->uri);
	}
	m_listChoosedSite.clear();
	if ( siteUris.size() > 0 )
	{
		CString cstrResult;
		SYSTEMTIME beginTime;
		CTime m_time;
		m_time=CTime::GetCurrentTime();//获取当前时间日期  
		m_time.GetAsSystemTime(beginTime);
		if ( m_LastQueryTime.wYear != 0 )
		{
			beginTime = m_LastQueryTime;
		}
		TPSDKResponseEx<map<std::string,list<FreeBusyStateEx>>> response = synchSiteStatusEx( siteUris, beginTime, "P0Y0M0DT6H0M0.000S"); 
		if ( 0 == response.resultCode )
		{
			cstrResult = _T("同步会场忙闲状态成功：");
			for ( map<std::string,list<FreeBusyStateEx>>::iterator iter = response.result.begin(); iter != response.result.end(); iter++ )
			{
				CString cstrTemp;
				cstrTemp.Format( "会场URI:%s ",iter->first.c_str() );
				for ( list<FreeBusyStateEx>::iterator iter1 = iter->second.begin(); iter1 != iter->second.end(); iter1++ )
				{
					CString cstrTemp1;
					cstrTemp1.Format("开始时间:%04d-%02d-%02dT%02d:%02d:%02d%s,持续时间:%s,忙闲状态:%d,会议ID:%s,会议名:%s", iter1->startTime.wYear, 
						iter1->startTime.wMonth, iter1->startTime.wDay, iter1->startTime.wHour, iter1->startTime.wMinute, iter1->startTime.wSecond,
						TP_Tool::GetLocalTimeZone().c_str(), iter1->span.c_str(), iter1->state, iter1->confId.c_str(), iter1->confName.c_str() );
					cstrTemp = cstrTemp +" " + cstrTemp1;
				}
				cstrResult = cstrResult + "   " + cstrTemp;
			}
		} 
		else
		{
			CString cstrResult= _T("同步会场忙闲状态失败：");
		}
		m_editResultPanel.SetWindowText( cstrResult ); 
	}
	else
	{
		m_editResultPanel.SetWindowText( _T("请选择要查询的会场") ); 
	}
}


void CTP_Native_AllSitesList::OnBnClickedButtonDeleteSiteInfo()
{
	// TODO: Add your control notification handler code here
	list<std::string> siteUris;
	GetChoosedSites();
	if ( m_listChoosedSite.size() > 0 )
	{
		list<std::string> siteUris;
		for ( list<SiteInfoEx>::iterator iter = m_listChoosedSite.begin(); iter != m_listChoosedSite.end(); iter++ )
		{
			siteUris.push_back(iter->uri);
		}
		m_listChoosedSite.clear();
		int iRet = deleteSiteInfoEx( siteUris );
		if ( 0 == iRet )
		{
			m_editResultPanel.SetWindowText( _T("删除会场信息成功") ); 
		} 
		else
		{
			CString cstrMsg;
			cstrMsg.Format( "删除会场信息失败，返回码: %d", iRet );
			m_editResultPanel.SetWindowText( cstrMsg ); 
		}
	} 
	else
	{
		m_editResultPanel.SetWindowText( _T("请选择要删除的会场") ); 
	}

}

void CTP_Native_AllSitesList::initAllSiteInfo()
{
	TPSDKResponseEx<list<SiteInfoEx>> siteList = querySitesEx();
	m_listAllSites.DeleteAllItems();
	m_allSitesInfo.clear();
	if (siteList.resultCode==0)
	{
		int j=0;
		list<SiteInfoEx>::iterator i; 
		for (i = siteList.result.begin(); i != siteList.result.end(); ++i) 
		{
			m_allSitesInfo.push_back(*i);
			m_listAllSites.InsertItem(j,i->uri.c_str());
			m_listAllSites.SetItemText(j,1,i->name.c_str());
			CString str;
			str.Format("%d",i->type);
			m_listAllSites.SetItemText(j,2,str);
			str.Format("%d",i->from);
			m_listAllSites.SetItemText(j,3,str);
			str.Format("%d",i->dialingMode);
			m_listAllSites.SetItemText(j,4,str);
			m_listAllSites.SetItemText(j,5,i->rate.c_str());
			str.Format("%d",i->videoFormat);
			m_listAllSites.SetItemText(j,6,str);
			str.Format("%d",i->videoProtocol);
			m_listAllSites.SetItemText(j,7,str);
			str.Format("%d",i->isLockVideoSource);
			m_listAllSites.SetItemText(j,8,str);
			str.Format("%d",i->participantType);
			m_listAllSites.SetItemText(j,9,str);
			j++;
		}
	}
	else
	{
		CString cstrMsg;
		cstrMsg.Format( "获得会场列表失败，返回码: %d", siteList.resultCode );
		m_editResultPanel.SetWindowText( cstrMsg ); 
	}
}

void CTP_Native_AllSitesList::OnBnClickedButtonGetAllSite()
{
	// TODO: Add your control notification handler code here
	initAllSiteInfo();
}
