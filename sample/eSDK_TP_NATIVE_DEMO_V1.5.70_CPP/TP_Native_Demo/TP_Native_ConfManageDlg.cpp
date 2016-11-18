// TP_Native_ConfControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_ConfManageDlg.h"
#include "afxdialogex.h"
#include "TP_Native_AllSitesList.h"
#include "TP_Tool.h"

// CTP_Native_ConfControlDlg dialog

IMPLEMENT_DYNAMIC(CTP_Native_ConfManageDlg, CPropertyPage)

CTP_Native_ConfManageDlg::CTP_Native_ConfManageDlg()
	: CPropertyPage(CTP_Native_ConfManageDlg::IDD)
{
	m_iLastChoosedItem = -1;
}

CTP_Native_ConfManageDlg::~CTP_Native_ConfManageDlg()
{
}

void CTP_Native_ConfManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CONFERENCE, m_listConference);
	DDX_Control(pDX, IDC_LIST_CONF_SITES, m_listSitesInConf);
	DDX_Control(pDX, IDC_EDIT_RESULT_PANNEL, m_editResultPanel);
	DDX_Control(pDX, IDC_EDIT_PROLONG_CONF, m_editProlongConfTime);
	DDX_Control(pDX, IDC_COMBO_CONF_RATE, m_cmbRate);
	DDX_Control(pDX, IDC_COMBO_CONF_ENCRYPT_TYPE, m_cmbEncryptType);
	DDX_Control(pDX, IDC_COMBO_CONF_CPRESOUCE, m_cmbCpResouce);
	DDX_Control(pDX, IDC_COMBO_CONF_AUX_VIDEO_PROTOCOL, m_cmbAuxVideoProtocol);
	DDX_Control(pDX, IDC_COMBO_AUX_VIDEO_FORMAT, m_cmbAuxVideoFormat);
	DDX_Control(pDX, IDC_EDIT_CONF_NAME, m_editNewConfName);
	DDX_Control(pDX, IDC_EDIT_PROLONG_TIME, m_editNewProlongTime);
	DDX_Control(pDX, IDC_EDIT_CDR_QUERY_BEGIN_TIME, m_editCdrQueryBeginTime);
	DDX_Control(pDX, IDC_EDIT_CDR_QUERY_DURATION, m_editCdrQueryDuration);
	DDX_Control(pDX, IDC_EDIT_CDR_QUERY_SITE_URI, m_editCdrQuerySiteUri);
	DDX_Control(pDX, IDC_COMBO_CDR_QUERY_CALL_TYPE, m_cmbCdrQueryCallType);
	DDX_Control(pDX, IDC_COMBO_NEW_FREQUENCY, m_cmbNewRecurrenceFrequency);
	DDX_Control(pDX, IDC_EDIT_NEW_RECURRENCE_INTERVAL, m_editNewRecurrenceInterval);
	DDX_Control(pDX, IDC_EDIT_NEW_RECURRENCE_COUNT, m_editNewRecurrenceCount);
}


BEGIN_MESSAGE_MAP(CTP_Native_ConfManageDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CTP_Native_ConfManageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &CTP_Native_ConfManageDlg::OnBnClickedButton7)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CONFERENCE, &CTP_Native_ConfManageDlg::OnNMClickListConference)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_CONF, &CTP_Native_ConfManageDlg::OnBnClickedButtonDeleteConf)
	ON_BN_CLICKED(IDC_BUTTON_PROLONG_CONF, &CTP_Native_ConfManageDlg::OnBnClickedButtonProlongConf)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SITES, &CTP_Native_ConfManageDlg::OnBnClickedButtonAddSites)
	ON_BN_CLICKED(IDC_BUTTON12, &CTP_Native_ConfManageDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON_GET_CONF_SITES, &CTP_Native_ConfManageDlg::OnBnClickedButtonGetConfSites)
	ON_BN_CLICKED(IDC_BUTTON2, &CTP_Native_ConfManageDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CONF_SITES, &CTP_Native_ConfManageDlg::OnNMClickListConfSites)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT_SITES, &CTP_Native_ConfManageDlg::OnBnClickedButtonConnectSites)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_SITES, &CTP_Native_ConfManageDlg::OnBnClickedButtonDisconnectSites)
	ON_BN_CLICKED(IDC_BUTTON_DEL_SITE_FROM_CONF, &CTP_Native_ConfManageDlg::OnBnClickedButtonDelSiteFromConf)
//	ON_CBN_SELCHANGE(IDC_COMBO5, &CTP_Native_ConfManageDlg::OnCbnSelchangeCombo5)
ON_BN_CLICKED(IDC_BUTTON_EDIT_CONF_INFO, &CTP_Native_ConfManageDlg::OnBnClickedButtonEditConfInfo)
ON_BN_CLICKED(IDC_BUTTON_GET_CONTINUOUS_PRESNECE_INFO, &CTP_Native_ConfManageDlg::OnBnClickedButtonGetContinuousPresneceInfo)
ON_BN_CLICKED(IDC_BUTTON_GET_CONTINUOUS_PRESENCE_PARAM, &CTP_Native_ConfManageDlg::OnBnClickedButtonGetContinuousPresenceParam)
ON_BN_CLICKED(IDC_BUTTON_QUERY_CONF_SITE_MCU, &CTP_Native_ConfManageDlg::OnBnClickedButtonQueryConfSiteMcu)
ON_BN_CLICKED(IDC_BUTTON_QUERY_POINT_TO_POINT_CDR, &CTP_Native_ConfManageDlg::OnBnClickedButtonQueryPointToPointCdr)
ON_BN_CLICKED(IDC_BUTTON_QUERY_MULTI_POINT_CDR, &CTP_Native_ConfManageDlg::OnBnClickedButtonQueryMultiPointCdr)
ON_BN_CLICKED(IDC_BUTTON_EDIT_RECURRENCE_CONF, &CTP_Native_ConfManageDlg::OnBnClickedButtonEditRecurrenceConf)
ON_BN_CLICKED(IDC_BUTTON11, &CTP_Native_ConfManageDlg::OnBnClickedButton11)
END_MESSAGE_MAP()


// CTP_Native_ConfControlDlg message handlers

//查询所有会议
void CTP_Native_ConfManageDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
	m_listConference.DeleteAllItems();

	list<std::string> confIds;
	m_ChoosedConferences.clear();
	m_conferenceList.clear();
	TPSDKResponseEx<list<ConferenceStatusEx>> returnInfo = queryConferencesStatusEx(confIds);

	if (returnInfo.resultCode==0)
	{
		int i = 0;
		for ( list<ConferenceStatusEx>::iterator iter = returnInfo.result.begin(); iter != returnInfo.result.end(); iter++)
		{
			//m_ChoosedConferences.push_back(*iter);
			m_conferenceList.push_back(*iter);
			m_listConference.InsertItem(i,iter->id.c_str());
			m_listConference.SetItemText(i, 1, iter->name.c_str());
			CString cstrTemp;
			if ( 2 == iter->status )
			{
				cstrTemp=_T("待召开");
			}
			if ( 3 ==  iter->status )
			{
				cstrTemp=_T("正在召开");
			}
			m_listConference.SetItemText(i, 2, cstrTemp);
			cstrTemp.Format( "%d-%d-%d %d:%d:%d", iter->beginTime.wYear, iter->beginTime.wMonth, iter->beginTime.wDay, iter->beginTime.wHour, iter->beginTime.wMinute, iter->beginTime.wSecond);
			m_listConference.SetItemText(i, 3, cstrTemp);
		}
		m_editResultPanel.SetWindowText(_T("查询已调度会议的状态成功"));
	} 
	else
	{
		CString s; 
		s.Format("查询已调度会议的状态失败；返回码：%d",returnInfo.resultCode);
		m_editResultPanel.SetWindowText(s);
	}
}


BOOL CTP_Native_ConfManageDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_listConference.ModifyStyle(0,LVS_REPORT);
	DWORD dwStyle = m_listConference.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_listConference.SetExtendedStyle(dwStyle); // 设置扩展风格 
	m_listConference.InsertColumn(0,"会议ID",LVCFMT_CENTER,80,NULL);
	m_listConference.InsertColumn(1,"会议名称",LVCFMT_CENTER,80,NULL);
	m_listConference.InsertColumn(2,"会议状态",LVCFMT_CENTER,80,NULL);
	m_listConference.InsertColumn(3,"开始时间",LVCFMT_CENTER,80,NULL);

	m_listSitesInConf.ModifyStyle(0,LVS_REPORT);
	dwStyle = m_listSitesInConf.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_listSitesInConf.SetExtendedStyle(dwStyle);
	m_listSitesInConf.InsertColumn(0,"URI",LVCFMT_CENTER,80,NULL);
	m_listSitesInConf.InsertColumn(1,"名称",LVCFMT_CENTER,80,NULL);
	m_listSitesInConf.InsertColumn(2,"类型",LVCFMT_CENTER,80,NULL);
	m_listSitesInConf.InsertColumn(3,"来源",LVCFMT_CENTER,80,NULL);
	m_listSitesInConf.InsertColumn(4,"呼叫方式",LVCFMT_CENTER,80,NULL);
	m_listSitesInConf.InsertColumn(5,"速率",LVCFMT_CENTER,100,NULL);
	m_listSitesInConf.InsertColumn(6,"视频格式",LVCFMT_CENTER,100,NULL);
	m_listSitesInConf.InsertColumn(7,"视频协议",LVCFMT_CENTER,100,NULL);
	m_listSitesInConf.InsertColumn(8,"锁定视频源",LVCFMT_CENTER,100,NULL);
	m_listSitesInConf.InsertColumn(9,"与会类型",LVCFMT_CENTER,100,NULL);

	m_editProlongConfTime.SetWindowText("P0Y0M0DT1H0M0.000S");
	m_editNewConfName.SetWindowText("Edit Conference");

	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,30, 0);
	m_time=CTime::GetCurrentTime();				//获取当前时间日期  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //格式化日期时间 
	m_editNewProlongTime.SetWindowText(strTime);

	m_cmbRate.AddString(_T("64k"));
	m_cmbRate.AddString(_T("1920k"));
	m_cmbRate.AddString(_T("8192k"));
	m_cmbRate.SetCurSel(1);

	m_cmbEncryptType.AddString(_T("AutoEncrypt"));
	m_cmbEncryptType.AddString(_T("ForceEncrypt"));
	m_cmbEncryptType.AddString(_T("None"));
	m_cmbEncryptType.SetCurSel(2);

	m_cmbCpResouce.AddString(_T("1"));
	m_cmbCpResouce.AddString(_T("2"));
	m_cmbCpResouce.AddString(_T("3"));
	m_cmbCpResouce.AddString(_T("4"));
	m_cmbCpResouce.AddString(_T("5"));
	m_cmbCpResouce.AddString(_T("6"));
	m_cmbCpResouce.AddString(_T("7"));
	m_cmbCpResouce.AddString(_T("8"));
	m_cmbCpResouce.SetCurSel(2);

	m_cmbAuxVideoFormat.AddString(_T("Auto"));
	m_cmbAuxVideoFormat.AddString(_T("H.261"));
	m_cmbAuxVideoFormat.AddString(_T("H.263"));
	m_cmbAuxVideoFormat.AddString(_T("H.264"));
	m_cmbAuxVideoFormat.SetCurSel(0);

	m_cmbAuxVideoProtocol.AddString(_T("Auto"));
	m_cmbAuxVideoProtocol.AddString(_T("4CIF"));
	m_cmbAuxVideoProtocol.AddString(_T("720P30(720P)"));
	m_cmbAuxVideoProtocol.AddString(_T("1080P30(1080P)"));
	m_cmbAuxVideoProtocol.AddString(_T("480P"));
	m_cmbAuxVideoProtocol.AddString(_T("720P60"));
	m_cmbAuxVideoProtocol.AddString(_T("1080P60"));
	m_cmbAuxVideoProtocol.AddString(_T("QCIF"));
	m_cmbAuxVideoProtocol.AddString(_T("CIF"));
	m_cmbAuxVideoProtocol.AddString(_T("SQCIF"));
	m_cmbAuxVideoProtocol.AddString(_T("CIF2"));
	m_cmbAuxVideoProtocol.AddString(_T("I108"));
	m_cmbAuxVideoProtocol.AddString(_T("I480"));
	m_cmbAuxVideoProtocol.SetCurSel(0);

	m_cmbNewRecurrenceFrequency.AddString("每天");
	m_cmbNewRecurrenceFrequency.AddString("每周");
	m_cmbNewRecurrenceFrequency.AddString("每月");
	m_cmbNewRecurrenceFrequency.SetCurSel(1);

	m_editNewRecurrenceInterval.SetWindowText("1");
	m_editNewRecurrenceCount.SetWindowText("3");

	CTimeSpan delta1(0, 0,-240, 0);
	m_time=CTime::GetCurrentTime();				//获取当前时间日期  
	m_time+=delta1;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));
	m_editCdrQueryBeginTime.SetWindowText(strTime);
	m_editCdrQueryDuration.SetWindowText(_T("P0Y0M0DT4H0M0.000S"));
	m_cmbCdrQueryCallType.AddString("呼叫主叫方");   //calling主叫方
	m_cmbCdrQueryCallType.AddString("呼叫被叫方");	 //calling被叫方
	m_cmbCdrQueryCallType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTP_Native_ConfManageDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	CTP_Native_AllSitesList *pdlgAllSitesList = new CTP_Native_AllSitesList();
	if ( NULL != pdlgAllSitesList )
	{
		INT_PTR nResponse = pdlgAllSitesList->DoModal();
		m_listChoosedSite.clear();
		m_listChoosedSite = pdlgAllSitesList->m_listChoosedSite;
		for ( list<SiteInfoEx>::iterator iter = m_listChoosedSite.begin(); iter != m_listChoosedSite.end(); iter++)
		{
			int iSitesCount = m_listSitesInConf.GetItemCount();
			bool blnUriInList = false;
			for ( int i = 0; i < iSitesCount; i++ )
			{
				CString cstrTemp = m_listSitesInConf.GetItemText(i, 0);
				std::string strTempSiteUri = cstrTemp.GetBuffer();
				if ( strTempSiteUri == iter->uri )
				{
					blnUriInList = true;
					break;
				}
				if ( false == blnUriInList && i == (iSitesCount - 1) )		//当URI不在列表中，则添加进来
				{
					m_listSitesInConf.InsertItem( iSitesCount, iter->uri.c_str());
					m_listSitesInConf.SetItemText( iSitesCount, 1, iter->name.c_str());
					CString cstrTemp;
					cstrTemp.Format( "%d", iter->type );
					m_listSitesInConf.SetItemText( iSitesCount, 2, cstrTemp );	//类型
					cstrTemp.Format( "%d", iter->from );
					m_listSitesInConf.SetItemText( iSitesCount, 3, cstrTemp );
					cstrTemp.Format( "%d", iter->dialingMode );
					m_listSitesInConf.SetItemText( iSitesCount, 4, cstrTemp );
					m_listSitesInConf.SetItemText( iSitesCount, 5, iter->rate.c_str() );
					cstrTemp.Format( "%d", iter->videoFormat );
					m_listSitesInConf.SetItemText( iSitesCount, 6, cstrTemp );
					cstrTemp.Format( "%d", iter->videoProtocol );
					m_listSitesInConf.SetItemText( iSitesCount, 7, cstrTemp );
					cstrTemp.Format( "%d", iter->isLockVideoSource );
					m_listSitesInConf.SetItemText( iSitesCount, 8, cstrTemp );
					cstrTemp.Format( "%d", iter->participantType );
					m_listSitesInConf.SetItemText( iSitesCount, 9, cstrTemp );
				}
			}
		}
		delete pdlgAllSitesList;
		pdlgAllSitesList = NULL;
	}

}


void CTP_Native_ConfManageDlg::OnNMClickListConference(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMItemActivate->iItem != -1) 
	{ 
		if(m_listConference.GetCheck(pNMItemActivate->iItem)) 
		{ 
			m_listConference.SetItemState(pNMItemActivate->iItem, 0, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listConference.SetCheck(pNMItemActivate->iItem,FALSE); 
			m_iLastChoosedItem = -1;
		} 
		else
		{
			if ( -1 != m_iLastChoosedItem )
			{
				m_listConference.SetItemState( m_iLastChoosedItem, 0, LVIS_SELECTED|LVIS_FOCUSED ); 
				m_listConference.SetCheck( m_iLastChoosedItem,FALSE );
			}
			m_listConference.SetItemState(pNMItemActivate->iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listConference.SetCheck(pNMItemActivate->iItem,TRUE);
			m_iLastChoosedItem = pNMItemActivate->iItem;
		} 
	}
	*pResult = 0;
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonDeleteConf()
{
	// TODO: Add your control notification handler code here
	GetChoosedConferencesItem();
	SYSTEMTIME beginTime;
	beginTime.wDay=0;
	beginTime.wDayOfWeek = 0;
	beginTime.wHour = 0;
	beginTime.wMilliseconds = 0;
	beginTime.wMinute = 0;
	beginTime.wMonth = 0;
	beginTime.wSecond = 0;
	beginTime.wYear = 0;
	if ( m_ChoosedConferences.size() > 0 )
	{
		for ( int i = 0; i < m_ChoosedConferences.size(); i++ )
		{
			int iRet = delScheduledConfEx( m_ChoosedConferences[i].id, beginTime );
			if ( 0 == iRet )
			{
				CString cstrTemp;
				cstrTemp.Format("删除会议成功，返回值 = %d", iRet);
				m_editResultPanel.SetWindowText(cstrTemp);
			}
			else
			{
				CString cstrTemp;
				cstrTemp.Format("删除会议失败，返回值 = %d", iRet);
				m_editResultPanel.SetWindowText(cstrTemp);
			}
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请选择会议"));
	}


}


void CTP_Native_ConfManageDlg::OnBnClickedButtonProlongConf()
{
	// TODO: Add your control notification handler code here
	if ( m_listConference.GetItemCount() >0 )
	{
		GetChoosedConferencesItem();
		if ( m_ChoosedConferences.size() > 0 )
		{
			for ( int i = 0; i < m_ChoosedConferences.size(); i++ )
			{
				CString cstrTemp;
				m_editProlongConfTime.GetWindowText(cstrTemp);
				std::string strProlongTime = cstrTemp;
				int iRet = prolongScheduledConfEx( m_ChoosedConferences[i].id, m_ChoosedConferences[i].beginTime, strProlongTime);
				if ( 0 == iRet )
				{
					CString cstrTemp;
					cstrTemp.Format("延长会议成功，返回值 = %d", iRet);
					m_editResultPanel.SetWindowText(cstrTemp);
				} 
				else
				{
					CString cstrTemp;
					cstrTemp.Format("延长会议失败，返回值 = %d", iRet);
					m_editResultPanel.SetWindowText(cstrTemp);
				}
			}

		}
		else
		{
			m_editResultPanel.SetWindowText(_T("请选择会议"));
		}
	} 
	else
	{
		m_editResultPanel.SetWindowText(_T("会议列表为空"));
	}

}


void CTP_Native_ConfManageDlg::OnBnClickedButtonAddSites()
{
	// TODO: Add your control notification handler code here

	getNowChoosedConference();
	if ( m_nowChoosedConference.id !="" )
	{
		if ( m_listChoosedSite.size() > 0 )
		{
			for ( list<SiteInfoEx>::iterator ite = m_listChoosedSite.begin(); ite != m_listChoosedSite.end(); ite++ )
			{
				TPSDKResponseEx<list<SiteAccessInfoEx>> response = addSiteToConfEx( m_nowChoosedConference.id, *ite, m_nowChoosedConference.beginTime );
				if ( 0 == response.resultCode )
				{
					CString cstrShowMsg;
					cstrShowMsg.Format("添加会场成功，返回码=%d", response.resultCode);
					CString cstrTemp;
					for ( list<SiteAccessInfoEx>::iterator itera = response.result.begin();itera != response.result.end(); itera++ )
					{
						cstrTemp.Format("会场URI:%s,会议接入号:%s,会场名称:%s,会议开始时间:%04d-%02d-%02dT%02d:%02d:%02d%s,MCU_URI:%s",
							            itera->uri.c_str(), itera->confAccessCode.c_str(), itera->name.c_str(),itera->beginTime.wYear,
										itera->beginTime.wMonth, itera->beginTime.wDay, itera->beginTime.wHour, itera->beginTime.wMinute, itera->beginTime.wSecond,
										TP_Tool::GetLocalTimeZone().c_str(), itera->mcuUri.c_str());
						cstrShowMsg = cstrShowMsg + "  " + cstrTemp;
					}
					m_editResultPanel.SetWindowText(cstrShowMsg);
				} 
				else
				{
					CString cstrShowMsg;
					cstrShowMsg.Format("添加会场失败，失败码=%d", response.resultCode);
					m_editResultPanel.SetWindowText(cstrShowMsg);
				}
			}
			m_listChoosedSite.clear();
		}
		else
		{
			m_editResultPanel.SetWindowText(_T("请先选择要添加的会场"));
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择会议"));
	}
}

//查询会议状态
void CTP_Native_ConfManageDlg::OnBnClickedButton12()
{
	// TODO: Add your control notification handler code here

	list<std::string> confIds;
	if ( -1 != m_iLastChoosedItem )
	{
		int iSerNum = m_listConference.GetItemCount() -1;
		for ( int i = 0; i < m_listConference.GetItemCount(); i++ )
		{
			if ( m_listConference.GetCheck(i) )
			{
				confIds.push_back(m_conferenceList[iSerNum - i].id);
			}
		}
		TPSDKResponseEx<list<ConferenceStatusEx>> returnInfo = queryConferencesStatusEx(confIds);
		if ( 0 == returnInfo.resultCode )
		{
			int i = 0;
			for ( list<ConferenceStatusEx>::iterator iter = returnInfo.result.begin(); iter != returnInfo.result.end(); iter++ )
			{
				CString cstrShowMsg;
				cstrShowMsg.Format("查询会议状态，返回码=%d", returnInfo.resultCode);
				CString cstrTemp;
				for ( list<ConferenceStatusEx>::iterator itera = returnInfo.result.begin();itera != returnInfo.result.end(); itera++ )
				{
					cstrTemp.Format("会议ID:%s,会议名称:%s,会议状态:%d,会议开始时间:%04d-%02d-%02dT%02d:%02d:%02d%s",
						itera->id.c_str(), itera->name.c_str(), itera->status,itera->beginTime.wYear,
						itera->beginTime.wMonth, itera->beginTime.wDay, itera->beginTime.wHour, itera->beginTime.wMinute, itera->beginTime.wSecond,
						TP_Tool::GetLocalTimeZone().c_str());
					cstrShowMsg = cstrShowMsg + "  " + cstrTemp;
				}
				m_editResultPanel.SetWindowText(cstrShowMsg);
			}
		} 
		else
		{
			CString cstrShowMsg;
			cstrShowMsg.Format("查询会议失败，失败码=%d", returnInfo.resultCode);
			m_editResultPanel.SetWindowText(cstrShowMsg);
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请选择要查询的会议"));
	}
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonGetConfSites()
{
	// TODO: Add your control notification handler code here
		GetChoosedConferencesItem();
		if ( m_ChoosedConferences.size() > 0 )
		{
			for ( int i = 0; i < m_ChoosedConferences.size(); i++ )
			{
				list<std::string> siteUris;
				TPSDKResponseEx<list<SiteStatusEx>> response = queryConfSitesStatusEx( m_ChoosedConferences[i].id, siteUris );
				if ( 0 == response.resultCode )
				{
					m_listSitesInConf.DeleteAllItems();
					int i = 0;
					for ( list<SiteStatusEx>::iterator iter = response.result.begin(); iter != response.result.end(); iter++ )
					{
						m_listSitesInConf.InsertItem(0,iter->uri.c_str());
						m_listSitesInConf.SetItemText( i, 1, iter->name.c_str());
						CString cstrTemp;
						cstrTemp.Format( "%d", iter->type );
						m_listSitesInConf.SetItemText( i, 2, cstrTemp );	//类型
						cstrTemp.Format( "%d", iter->participantType );
						m_listSitesInConf.SetItemText( i, 9, cstrTemp );
					}
					m_editResultPanel.SetWindowText(_T("查询会议的会场成功"));
				} 
				else
				{
					CString cstrShowMsg;
					cstrShowMsg.Format("查询会议的会场失败，失败码=%d", response.resultCode);
					m_editResultPanel.SetWindowText(cstrShowMsg);
				}
			}
		}
		else
		{
			m_editResultPanel.SetWindowText(_T("请选择要查询的会议"));
		}

}


void CTP_Native_ConfManageDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}


void CTP_Native_ConfManageDlg::OnNMClickListConfSites(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMItemActivate->iItem != -1) 
	{ 
		if(m_listSitesInConf.GetCheck(pNMItemActivate->iItem)) 
		{ 
			m_listSitesInConf.SetItemState(pNMItemActivate->iItem, 0, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listSitesInConf.SetCheck(pNMItemActivate->iItem,FALSE); 
		} 
		else
		{
			m_listSitesInConf.SetItemState(pNMItemActivate->iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listSitesInConf.SetCheck(pNMItemActivate->iItem,TRUE);
		} 
	}
	*pResult = 0;
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonConnectSites()
{
	// TODO: Add your control notification handler code here

	getNowChoosedConference();
	if ( m_nowChoosedConference.id != "" )
	{
		list<std::string> siteUris;
		for ( int i = 0; i < m_listSitesInConf.GetItemCount(); i++ )
		{
			if ( m_listSitesInConf.GetCheck(i) == TRUE )
			{
				CString cstrSiteUri = m_listSitesInConf.GetItemText(i, 0);
				std::string strSiteUri = cstrSiteUri;
				siteUris.push_back(strSiteUri);
			}
		}
		if ( siteUris.size() == 0 )
		{
			m_editResultPanel.SetWindowText(_T("请先选择会场"));
		}
		else
		{
			int iRet = connectSitesEx( m_nowChoosedConference.id, siteUris );
			if ( 0 == iRet )
			{
				CString cstrResultMsg;
				cstrResultMsg.Format( "呼叫会场成功，返回码=%d", iRet );
				m_editResultPanel.SetWindowText( cstrResultMsg );
			} 
			else
			{
				CString cstrResultMsg;
				cstrResultMsg.Format( "呼叫会场失败，返回码=%d", iRet );
				m_editResultPanel.SetWindowText( cstrResultMsg );
			}
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择会议"));
	}
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonDisconnectSites()
{
	// TODO: Add your control notification handler code here
	getNowChoosedConference();
	if ( m_nowChoosedConference.id != "" )
	{
		list<std::string> siteUris;
		for ( int i = 0; i < m_listSitesInConf.GetItemCount(); i++ )
		{
			if ( m_listSitesInConf.GetCheck(i) == TRUE )
			{
				CString cstrSiteUri = m_listSitesInConf.GetItemText(i, 0);
				std::string strSiteUri = cstrSiteUri;
				siteUris.push_back(strSiteUri);
			}
		}
		if ( siteUris.size() == 0 )
		{
			m_editResultPanel.SetWindowText(_T("请先选择会场"));
		}
		else
		{
			int iRet = disconnectSitesEx( m_nowChoosedConference.id, siteUris );
			if ( 0 == iRet )
			{
				CString cstrResultMsg;
				cstrResultMsg.Format( "断开会场成功，返回码=%d", iRet );
				m_editResultPanel.SetWindowText( cstrResultMsg );
			} 
			else
			{
				CString cstrResultMsg;
				cstrResultMsg.Format( "断开会场失败，返回码=%d", iRet );
				m_editResultPanel.SetWindowText( cstrResultMsg );
			}
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择会议"));
	}
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonDelSiteFromConf()
{
	// TODO: Add your control notification handler code here
	getNowChoosedConference();
	if ( m_nowChoosedConference.id != "" )
	{
		list<std::string> siteUris;
		for ( int i = 0; i < m_listSitesInConf.GetItemCount(); i++ )
		{
			if ( m_listSitesInConf.GetCheck(i) == TRUE )
			{
				CString cstrSiteUri = m_listSitesInConf.GetItemText(i, 0);
				std::string strSiteUri = cstrSiteUri;
				siteUris.push_back(strSiteUri);
			}
		}
		if ( siteUris.size() == 0 )
		{
			m_editResultPanel.SetWindowText(_T("请先选择会场"));
		}
		else
		{
			for ( list<std::string>::iterator ite = siteUris.begin(); ite != siteUris.end(); ite++ )
			{
				int iRet = delSiteFromConfEx( m_nowChoosedConference.id, *ite, m_nowChoosedConference.beginTime );
				if ( 0 == iRet )
				{
					CString cstrResultMsg;
					cstrResultMsg.Format( "删除会场成功，返回码=%d", iRet );
					m_editResultPanel.SetWindowText( cstrResultMsg );
				} 
				else
				{
					CString cstrResultMsg;
					cstrResultMsg.Format( "删除会场失败，返回码=%d", iRet );
					m_editResultPanel.SetWindowText( cstrResultMsg );
				}
			}
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择会议"));
	}
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonEditConfInfo()
{
	// TODO: Add your control notification handler code here
	getNowChoosedConference();
	if ( m_nowChoosedConference.id != "" )
	{
		if ( 2 == m_nowChoosedConference.status )
		{
			ConferenceInfoEx scheduleConf;
			//会议Id
			scheduleConf.confId = m_nowChoosedConference.id;
			CString cstrTemp;
			//name
			m_editNewConfName.GetWindowText(cstrTemp);
			scheduleConf.name = cstrTemp;
			//会议开始时间
			m_editNewProlongTime.GetWindowText( cstrTemp );
			COleDateTime tT;
			tT.ParseDateTime( cstrTemp );
			tT.GetAsSystemTime( scheduleConf.beginTime );
			//会议时长
			m_editProlongConfTime.GetWindowText( cstrTemp );
			scheduleConf.duration = cstrTemp.GetBuffer();
			//加密方式
			scheduleConf.mediaEncryptType = m_cmbEncryptType.GetCurSel();
			//多画面模式
			scheduleConf.cpResouce = m_cmbCpResouce.GetCurSel() + 1;
			//辅流视频格式
			scheduleConf.auxVideoFormat = m_cmbAuxVideoFormat.GetCurSel();
			//视频协议
			scheduleConf.auxVideoProtocol = m_cmbAuxVideoProtocol.GetCurSel();
			//速率
			m_cmbRate.GetLBText(m_cmbRate.GetCurSel(),cstrTemp);
			scheduleConf.rate = cstrTemp.GetBuffer();
			//会场
			for ( list<SiteInfoEx>::iterator ite = m_listChoosedSite.begin(); ite != m_listChoosedSite.end(); ite++ )
			{
				scheduleConf.sites.push_back(*ite);
			}
			TPSDKResponseEx<ConferenceInfoEx> response = editScheduledConfEx( scheduleConf );
			if ( 0 == response.resultCode )
			{
				CString cstrResultMsg;
				cstrResultMsg.Format( "修改会议成功，会议ID：%s，会议接入号：%s。", response.result.confId.c_str(), response.result.accessCode.c_str());
				m_editResultPanel.SetWindowText( cstrResultMsg );
			} 
			else
			{
				CString cstrResultMsg;
				cstrResultMsg.Format( "修改会议失败，返回码=%d", response.resultCode );
				m_editResultPanel.SetWindowText( cstrResultMsg );
			}
		}
		else
		{
			m_editResultPanel.SetWindowText(_T("会议不存在，或已结束，或已经开始,不能编辑"));
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择会议"));
	}
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonGetContinuousPresneceInfo()
{
	// TODO: Add your control notification handler code here
	getNowChoosedConference();
	if ( m_nowChoosedConference.id != "" )
	{
		TPSDKResponseEx<GetContinuousPresenceInfoResponseEx> response = getContinuousPresenceInfoEx(m_nowChoosedConference.id);
		if ( 0 == response.resultCode )
		{
			CString cstrResultMsg;
			cstrResultMsg.Format("读取多画面模式资源数成功:");
			for ( list<std::string>::iterator iter = response.result.targets.begin(); iter != response.result.targets.end(); iter++ )
			{
				CString cstrTarget;
				cstrTarget.Format("多画面类型：%s", iter->c_str());
				cstrResultMsg = cstrResultMsg + " " + cstrTarget;
			}
			CString cstrCpResource;
			cstrCpResource.Format("%d",response.result.cpResource);
			cstrResultMsg = cstrResultMsg + " " + cstrCpResource;
			cstrResultMsg = cstrResultMsg + "，支持的多画面模式列表：";
			for ( list<int>::iterator iter = response.result.supportCPModes.begin(); iter != response.result.supportCPModes.end(); iter++ )
			{
				CString cstrCpModes;
				cstrCpModes.Format("%d", *iter);
				cstrResultMsg = cstrResultMsg + cstrCpModes;
			}
			m_editResultPanel.SetWindowText( cstrResultMsg );
		} 
		else
		{
			CString cstrResultMsg;
			cstrResultMsg.Format( "读取多画面模式资源数失败，返回码=%d", response.resultCode );
			m_editResultPanel.SetWindowText( cstrResultMsg );
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择会议"));
	}
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonGetContinuousPresenceParam()
{
	// TODO: Add your control notification handler code here
	getNowChoosedConference();
	if ( m_nowChoosedConference.id != "" )
	{
		TPSDKResponseEx<GetContinuousPresenceParamResponseEx> response = getContinuousPresenceParamEx( m_nowChoosedConference.id, "0" );
		if ( 0 == response.resultCode )
		{
			CString cstrResultMsg;
			cstrResultMsg.Format( "读取指定会议的多画面参数成功，多画面模式：%d， ",response.result.presenceMode);
			for ( list<std::string>::iterator iter = response.result.subPics.begin(); iter != response.result.subPics.end(); iter++ )
			{
				CString cstrTemp;
				cstrTemp.Format("%d", *iter);
				cstrResultMsg = cstrResultMsg + cstrTemp;
			}
			m_editResultPanel.SetWindowText( cstrResultMsg );
		} 
		else
		{
			CString cstrResultMsg;
			cstrResultMsg.Format( "读取指定会议的多画面参数失败，返回码=%d", response.resultCode );
			m_editResultPanel.SetWindowText( cstrResultMsg );
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择会议"));
	}
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonQueryConfSiteMcu()
{
	// TODO: Add your control notification handler code here
    getNowChoosedConference();
	if ( m_nowChoosedConference.id != "")
	{
		list<std::string> siteUris;
		for ( int i = 0; i < m_listSitesInConf.GetItemCount(); i++ )
		{
			if ( m_listSitesInConf.GetCheck(i) == TRUE )
			{
				CString cstrSiteUri = m_listSitesInConf.GetItemText(i, 0);
				std::string strSiteUri = cstrSiteUri;
				siteUris.push_back(strSiteUri);
			}
		}
		if ( siteUris.size() == 0 )
		{
			m_editResultPanel.SetWindowText(_T("请先选择会场"));
		}
		else
		{
			TPSDKResponseEx<list<SiteMCUEx>> response = queryConfSiteMCUEx( m_nowChoosedConference.id, siteUris, m_nowChoosedConference.beginTime );
			if ( 0 == response.resultCode )
			{
				CString cstrResultMsg;
				cstrResultMsg.Format( "查询会场所属MCU成功, " );
				for ( list<SiteMCUEx>::iterator itera = response.result.begin(); itera != response.result.end(); itera++ )
				{
					CString cstrTemp;
					cstrTemp.Format("会场URI:%s,MCU:%d ", itera->siteUri.c_str(), itera->mcuId);
					cstrResultMsg = cstrResultMsg + " " + cstrTemp;
				}
				m_editResultPanel.SetWindowText( cstrResultMsg );
			} 
			else
			{
				CString cstrResultMsg;
				cstrResultMsg.Format( "查询会场所属MCU失败，返回码=%d", response.resultCode );
				m_editResultPanel.SetWindowText( cstrResultMsg );
			}
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择会议"));
	}
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonQueryPointToPointCdr()
{
	// TODO: Add your control notification handler code here
	PointToPointCDRQueryConfigEx queryConfig;
	//查询开始时间
	CString cstrTemp;
	m_editCdrQueryBeginTime.GetWindowText(cstrTemp);
	COleDateTime tT;
	tT.ParseDateTime(cstrTemp);
	tT.GetAsSystemTime( queryConfig.beginTime );
	//查询间隔时间
	m_editCdrQueryDuration.GetWindowText(cstrTemp);
	queryConfig.duration = cstrTemp.GetBuffer();
	//查询的会场URI
	m_editCdrQuerySiteUri.GetWindowText(cstrTemp);
	queryConfig.endPoint.siteUri = cstrTemp.GetBuffer();
	//呼叫类型
	queryConfig.endPoint.type = m_cmbCdrQueryCallType.GetCurSel();
	//页码定位参数
	queryConfig.pageParam.numberPerPage = 10;
	queryConfig.pageParam.currentPage = 1;
	TPSDKResponseEx<QueryPointToPointCDRExResponse> response = queryPointToPointCDREx( queryConfig );
	if ( 0 == response.resultCode )
	{
		CString cstrResultMsg = "查询CDR点对点话单成功。 ";
		for ( list<PointToPointCDREx>::iterator iter = response.result.cdr.begin(); iter != response.result.cdr.end(); iter++ )
		{
			cstrTemp.Format("主叫URI：%s，主叫协议：%d，被叫URI：%s，被叫协议：%d，带宽：%s，开始时间：%04d-%02d-%02dT%02d:%02d:%02d%s，结束时间：%04d-%02d-%02dT%02d:%02d:%02d%s",
				             iter->callingUri.c_str(), iter->callingProtocol, iter->calledUri.c_str(), iter->calledProtocol,iter->rate.c_str(),
							 iter->startTime.wYear, iter->startTime.wMonth, iter->startTime.wDay, iter->startTime.wHour, iter->startTime.wMinute,
							 iter->startTime.wSecond, TP_Tool::GetLocalTimeZone().c_str(), iter->endTime.wYear, iter->endTime.wMonth, iter->endTime.wDay,
							 iter->endTime.wHour, iter->endTime.wMinute, iter->endTime.wSecond, TP_Tool::GetLocalTimeZone().c_str());
			cstrResultMsg = cstrResultMsg + cstrTemp;
		}
		m_editResultPanel.SetWindowText( cstrResultMsg );
	} 
	else
	{
		CString cstrResultMsg;
		cstrResultMsg.Format( "查询CDR点对点话单失败，返回码=%d", response.resultCode );
		m_editResultPanel.SetWindowText( cstrResultMsg );
	}
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonQueryMultiPointCdr()
{
	// TODO: Add your control notification handler code here
	MultiPointCDRQueryConfigEx  queryConfig;
	//查询开始时间
	CString cstrTemp;
	m_editCdrQueryBeginTime.GetWindowText(cstrTemp);
	COleDateTime tT;
	tT.ParseDateTime(cstrTemp);
	tT.GetAsSystemTime( queryConfig.beginTime );
	//查询间隔时间
	m_editCdrQueryDuration.GetWindowText(cstrTemp);
	queryConfig.duration = cstrTemp.GetBuffer();
	//查询的会场URI
	m_editCdrQuerySiteUri.GetWindowText(cstrTemp);
	queryConfig.siteUri = cstrTemp.GetBuffer();
	//页码定位参数
	queryConfig.pageParam.numberPerPage = 10;
	queryConfig.pageParam.currentPage = 1;
	TPSDKResponseEx<QueryMultiPointCDRExResponse> response = queryMultiPointCDREx( queryConfig );
	if ( 0 == response.resultCode )
	{
		CString cstrResultMsg = "查询CDR多点话单成功。 ";
		for ( list<MultiPointCDREx>::iterator iter = response.result.cdr.begin(); iter != response.result.cdr.end(); iter++ )
		{
			cstrTemp.Format("会场名称:%s,会场标识:%s,会场类型:%d,会场与会类型:%d,速率:%s,开始时间:%04d-%02d-%02dT%02d:%02d:%02d%s,结束时间:%04d-%02d-%02dT%02d:%02d:%02d%s,会议名称:%s,会议ID:%s,会议创建者:%s,会议计费码:%s",
				             iter->siteName.c_str(), iter->siteUri.c_str(), iter->siteType, iter->participantType, iter->rate.c_str(),
							 iter->startTime.wYear, iter->startTime.wMonth, iter->startTime.wDay, iter->startTime.wHour, iter->startTime.wMinute,
							 iter->startTime.wSecond, TP_Tool::GetLocalTimeZone().c_str(), iter->endTime.wYear, iter->endTime.wMonth, iter->endTime.wDay,
							 iter->endTime.wHour, iter->endTime.wMinute, iter->endTime.wSecond, TP_Tool::GetLocalTimeZone().c_str(), iter->conferenceName.c_str(), iter->conferenceId.c_str(),
							 iter->conferenceCreater.c_str(), iter->billCode.c_str());
			cstrResultMsg = cstrResultMsg + cstrTemp;
		}
		m_editResultPanel.SetWindowText( cstrResultMsg );
	} 
	else
	{
		CString cstrResultMsg;
		cstrResultMsg.Format( "查询CDR多点话单失败，返回码=%d", response.resultCode );
		m_editResultPanel.SetWindowText( cstrResultMsg );
	}
}


void CTP_Native_ConfManageDlg::OnBnClickedButtonEditRecurrenceConf()
{
	// TODO: Add your control notification handler code here
	getNowChoosedConference();
	if ( m_nowChoosedConference.id != "")
	{
		list<std::string> siteUris;
		RecurrenceConfInfoEx scheduleConf;
		scheduleConf.base_info.confId = m_nowChoosedConference.id;
		//name
		CString cstrTemp;
		m_editNewConfName.GetWindowText(cstrTemp);
		scheduleConf.base_info.name = cstrTemp;
		//会议时长
		m_editNewProlongTime.GetWindowText( cstrTemp );
		COleDateTime tT;
		tT.ParseDateTime( cstrTemp );
		tT.GetAsSystemTime( scheduleConf.base_info.beginTime );
		//会议开始时间
		m_editProlongConfTime.GetWindowText( cstrTemp );
		scheduleConf.base_info.duration = cstrTemp.GetBuffer();
		//加密方式
		scheduleConf.base_info.mediaEncryptType = m_cmbEncryptType.GetCurSel();
		//多画面模式
		scheduleConf.base_info.cpResouce = m_cmbCpResouce.GetCurSel() + 1;
		//辅流视频格式
		scheduleConf.base_info.auxVideoFormat = m_cmbAuxVideoFormat.GetCurSel();
		//视频协议
		scheduleConf.base_info.auxVideoProtocol = m_cmbAuxVideoProtocol.GetCurSel();
		//速率
		m_cmbRate.GetLBText(m_cmbRate.GetCurSel(),cstrTemp);
		scheduleConf.base_info.rate = cstrTemp.GetBuffer();
		//重复类型
		scheduleConf.frequency = m_cmbNewRecurrenceFrequency.GetCurSel();
		//重复周期
		m_editNewRecurrenceInterval.GetWindowText(cstrTemp);
		scheduleConf.interval = atoi(cstrTemp);
		//重复次数
		m_editNewRecurrenceCount.GetWindowText(cstrTemp);
		scheduleConf.count = atoi(cstrTemp.GetBuffer());
		//会场
		for ( list<SiteInfoEx>::iterator ite = m_listChoosedSite.begin(); ite != m_listChoosedSite.end(); ite++ )
		{
			scheduleConf.base_info.sites.push_back(*ite);
		}
		//
		scheduleConf.weekDays.push_back(1);
		scheduleConf.weekDay = 0;
		scheduleConf.monthDay = 0;
		TPSDKResponseEx<RecurrenceConfInfoEx> response = editRecurrenceConferenceEx( scheduleConf, m_nowChoosedConference.beginTime );
		if ( 0 == response.resultCode )
		{
			CString cstrResultMsg;
			cstrResultMsg.Format( "修改周期会议成功，返回码=%d", response.resultCode );
			m_editResultPanel.SetWindowText( cstrResultMsg );
		} 
		else
		{
			CString cstrResultMsg;
			cstrResultMsg.Format( "修改周期会议失败，返回码=%d", response.resultCode );
			m_editResultPanel.SetWindowText( cstrResultMsg );
		}
	}
}

void CTP_Native_ConfManageDlg::GetChoosedConferencesItem()
{
	m_ChoosedConferences.clear();
	if ( m_listConference.GetItemCount() > 0 )
	{
		for ( int i = 0; i < m_listConference.GetItemCount(); i++ )
		{
			int iMaxCount = m_conferenceList.size() - 1;
			if ( m_listConference.GetCheck(i) )
			{
				m_ChoosedConferences.push_back(m_conferenceList[iMaxCount - i]);
			}
		}
	}
}

void CTP_Native_ConfManageDlg::getNowChoosedConference()
{
	m_nowChoosedConference.id = "";
	if ( m_listConference.GetItemCount() > 0 )
	{
		for ( int i = 0; i < m_listConference.GetItemCount(); i++ )
		{
			int iMaxCount = m_conferenceList.size() - 1;
			if ( m_listConference.GetCheck(i) )
			{
				m_nowChoosedConference = m_conferenceList[iMaxCount - i];
			}
		}
	}
}

void CTP_Native_ConfManageDlg::OnBnClickedButton11()
{
	// TODO: Add your control notification handler code here
}
