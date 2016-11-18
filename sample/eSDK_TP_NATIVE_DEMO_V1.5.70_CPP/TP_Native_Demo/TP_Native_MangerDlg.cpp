// TP_Native_ConfControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_MangerDlg.h"
#include "afxdialogex.h"
#include "TP_Tool.h"

// CTP_Native_ConfControlDlg dialog

IMPLEMENT_DYNAMIC(CTP_Native_MangerDlg, CPropertyPage)

	CTP_Native_MangerDlg::CTP_Native_MangerDlg()
	: CPropertyPage(CTP_Native_MangerDlg::IDD)
	, m_searchID(_T(""))
	, m_searchPage(_T(""))
	, m_searchSum(_T(""))
	, m_addSite(_T(""))
	, m_videoFormat(_T(""))
	, m_siteName(_T(""))
	, m_siteMark(_T(""))
	, m_scUser(_T(""))
	, m_scPassword(_T(""))
	, m_siteID(_T(""))
	, m_value(_T(""))
	, m_subConfID(_T(""))
	, m_onConfID(_T(""))
	, m_begainTime(_T(""))
	, m_duration(_T(""))
{
	m_num = 0;
	m_siteNum = 0;
	m_subNum = 0;
}

CTP_Native_MangerDlg::~CTP_Native_MangerDlg()
{
}

void CTP_Native_MangerDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, m_showPan);
	DDX_Control(pDX, IDC_LIST1, m_searchList);
	DDX_Text(pDX, IDC_EDIT3, m_searchID);
	DDX_Text(pDX, IDC_EDIT5, m_searchPage);
	DDX_Text(pDX, IDC_EDIT4, m_searchSum);
	//DDX_Control(pDX, IDC_LIST2, m_siteList);
	//DDX_Text(pDX, IDC_EDIT14, m_addSite);
	//DDX_Text(pDX, IDC_EDIT19, m_videoFormat);
	DDX_Text(pDX, IDC_EDIT8, m_siteName);
	DDX_Text(pDX, IDC_EDIT9, m_siteMark);
	DDX_Text(pDX, IDC_EDIT12, m_scUser);
	DDX_Text(pDX, IDC_EDIT13, m_scPassword);
	DDX_Text(pDX, IDC_EDIT7, m_siteID);
	DDX_Text(pDX, IDC_EDIT20, m_value);
	DDX_Control(pDX, IDC_LIST4, m_subList);
	DDX_Text(pDX, IDC_EDIT23, m_subConfID);
	DDX_Text(pDX, IDC_EDIT16, m_begainTime);
	DDX_Text(pDX, IDC_EDIT17, m_duration);
	DDX_Control(pDX, IDC_LIST_ALL_MCU_INFO, m_listAllMcuInfo);
	DDX_Control(pDX, IDC_COMBO2, m_cmb);
	DDX_Control(pDX, IDC_COMBO_SITE_RATE, m_cmbSiteRate);
	DDX_Control(pDX, IDC_COMBO_CIRCUI_TYPE, m_cmbCircuitType);
	DDX_Control(pDX, IDC_COMBO_SORT_TYPE, m_cmbSortType);
	DDX_Control(pDX, IDC_COMBO_SORT_ITEM_INDEX, m_cmbSortItemIndex);
	DDX_Control(pDX, IDC_COMBO_FILTER_BASE_COLUMN, m_cmbFilterBaseColumnIndex);
	DDX_Control(pDX, IDC_COMBO_IS_SUB_SCRIB, m_cmbIsSubScribe);
	DDX_Control(pDX, IDC_COMBO_SUB_SCRIBE_INFO, m_cmbSubScribeInfo);
}


BEGIN_MESSAGE_MAP(CTP_Native_MangerDlg, CPropertyPage)
	
	ON_BN_CLICKED(IDC_BUTTON1, &CTP_Native_MangerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTP_Native_MangerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTP_Native_MangerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CTP_Native_MangerDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON4, &CTP_Native_MangerDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON10, &CTP_Native_MangerDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON65, &CTP_Native_MangerDlg::OnBnClickedButton65)
	ON_BN_CLICKED(IDC_BUTTON9, &CTP_Native_MangerDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON16, &CTP_Native_MangerDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON15, &CTP_Native_MangerDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON13, &CTP_Native_MangerDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CTP_Native_MangerDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON8, &CTP_Native_MangerDlg::OnBnClickedButton8)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ALL_MCU_INFO, &CTP_Native_MangerDlg::OnNMClickListAllMcuInfo)
END_MESSAGE_MAP()


// CTP_Native_ConfControlDlg message handlers

BOOL CTP_Native_MangerDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_searchList.ModifyStyle(0,LVS_REPORT);
	DWORD dwStyle = m_searchList.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_searchList.SetExtendedStyle(dwStyle); // 设置扩展风格 
	m_searchList.InsertColumn( 0, "排序方式", LVCFMT_LEFT, 100 );    //插入列
	m_searchList.InsertColumn( 1, "查询条件的数据列标识", LVCFMT_LEFT, 100 );    //插入列
	m_searchList.InsertColumn( 2, "包含的字符串", LVCFMT_LEFT, 100 );    //插入列
	m_searchList.InsertColumn( 3, "过滤条件的数据列标识", LVCFMT_LEFT, 100 );    //插入列

	m_cmbCircuitType.AddString("自动获取");
	m_cmbCircuitType.AddString("E1(不支持)");
	m_cmbCircuitType.AddString("ISDN(不支持)");
	m_cmbCircuitType.AddString("H.323");
	m_cmbCircuitType.AddString("PSTN(不支持)");
	m_cmbCircuitType.AddString("4E1(不支持)");
	m_cmbCircuitType.AddString("SIP");
	m_cmbCircuitType.AddString("VoIP SIP");
	m_cmbCircuitType.AddString("VoIP H.323");
	m_cmbCircuitType.AddString("SIP智真三屏");
	m_cmbCircuitType.AddString("H.323智真三屏");
	m_cmbCircuitType.SetCurSel(3);

	m_cmbSiteRate.AddString("自动选择");
	m_cmbSiteRate.AddString("64k");
	m_cmbSiteRate.AddString("1920k");
	m_cmbSiteRate.AddString("8192k");
	m_cmbSiteRate.SetCurSel(0);

	m_cmbSortType.AddString("升序排列");
	m_cmbSortType.AddString("降序排列");
	m_cmbSortType.SetCurSel(0);

	m_cmbSortItemIndex.AddString("会场名称");
	m_cmbSortItemIndex.AddString("会场URI");
	m_cmbSortItemIndex.AddString("会场状态");
	m_cmbSortItemIndex.AddString("会场类型(暂不支持)");
	m_cmbSortItemIndex.AddString("会议模板名");
	m_cmbSortItemIndex.AddString("会议模板接入号");
	m_cmbSortItemIndex.AddString("MCU名称");
	m_cmbSortItemIndex.SetCurSel(0);

	m_cmbFilterBaseColumnIndex.AddString("会场名称");
	m_cmbFilterBaseColumnIndex.AddString("会场URI");
	m_cmbFilterBaseColumnIndex.AddString("会场状态");
	m_cmbFilterBaseColumnIndex.AddString("会场类型(暂不支持)");
	m_cmbFilterBaseColumnIndex.AddString("会议模板名");
	m_cmbFilterBaseColumnIndex.AddString("会议模板接入号");
	m_cmbFilterBaseColumnIndex.AddString("MCU名称");
	m_cmbFilterBaseColumnIndex.SetCurSel(0);

	m_subList.ModifyStyle(0,LVS_REPORT);
	dwStyle = m_subList.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_subList.SetExtendedStyle(dwStyle); // 设置扩展风格 
	m_subList.InsertColumn( 0, "订阅", LVCFMT_LEFT, 50 );    //插入列
	m_subList.InsertColumn( 1, "会议类型", LVCFMT_LEFT, 100 );    //插入列
	m_subList.InsertColumn( 2, "会议ID", LVCFMT_LEFT, 100 );    //插入列

	m_listAllMcuInfo.ModifyStyle(0,LVS_REPORT);
	m_listAllMcuInfo.SetExtendedStyle(dwStyle);
	m_listAllMcuInfo.InsertColumn(0,"MCU ID",LVCFMT_LEFT, 100 );
	m_listAllMcuInfo.InsertColumn(1,"名称",LVCFMT_LEFT, 100 );
	m_listAllMcuInfo.InsertColumn(2,"类型",LVCFMT_LEFT, 100 );

	m_cmb.AddString("NONE(关闭)");
	m_cmb.AddString("PULL(开启)");
	m_cmb.AddString("CALLBACK(暂不支持)");
	m_cmb.SetCurSel(1);

	GetDlgItem(IDC_EDIT3)->SetWindowText("1");      //焦点数据ID
	GetDlgItem(IDC_EDIT4)->SetWindowText("10");		//每页记录
	GetDlgItem(IDC_EDIT5)->SetWindowText("1");      //当前页数

	GetDlgItem(IDC_EDIT17)->SetWindowText("P0Y0M0DT2H0M0.000S");

	CTime m_time;
	CString strTime;
	m_time=CTime::GetCurrentTime();				//获取当前时间日期  
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //格式化日期时间 
	GetDlgItem(IDC_EDIT16)->SetWindowText(strTime);

	m_cmbIsSubScribe.AddString(_T("取消订阅"));
	m_cmbIsSubScribe.AddString(_T("订阅"));
	m_cmbIsSubScribe.SetCurSel(1);

	m_cmbSubScribeInfo.AddString("已预约会议");
	m_cmbSubScribeInfo.AddString("正召开会议");
	m_cmbSubScribeInfo.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTP_Native_MangerDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString cstrTemp;
	//排序方式
	cstrTemp.Format( "%d", m_cmbSortType.GetCurSel() );
	m_searchList.InsertItem(m_num, cstrTemp);
	//排序的数据列
	cstrTemp.Format( "%d", m_cmbSortItemIndex.GetCurSel() );
	m_searchList.SetItemText( m_num, 1, cstrTemp );
	//会场过滤条件
	m_searchList.SetItemText( m_num, 2, m_value.GetBuffer() );
	//会场过滤值
	cstrTemp.Format( "%d", m_cmbFilterBaseColumnIndex.GetCurSel() );
	m_searchList.SetItemText( m_num, 3, cstrTemp );
	m_num ++;
}


void CTP_Native_MangerDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	for(int i = 0;i<m_searchList.GetItemCount();i++)
	{
		if(m_searchList.GetCheck(i))
		{
			m_searchList.DeleteItem(i);
			m_num--;
		}
	}
}


void CTP_Native_MangerDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<QuerySitesInfoExResponse> returnInfo;
	CString str;
	CString sort;
	CString itemIndex;
	CString strValue;
	CString columnIndex;
	QueryConfigEx queryConfig;
	SortItemEx sortItem;
	StringFilterEx sf;
	PageParamEx pageParam;
	UpdateData(TRUE);
	//排序条件组合，目前只支持单列排序
	for(int i = 0;i<m_searchList.GetItemCount();i++)
	{
		if(m_searchList.GetCheck(i))
		{
			sort = m_searchList.GetItemText(i,0);        //排序方式
			sortItem.sort = _ttoi(sort);
			itemIndex = m_searchList.GetItemText(i,1);
			sortItem.itemIndex = _ttoi(itemIndex);
			strValue = m_searchList.GetItemText(i,2);
			sf.value = strValue;
			columnIndex = m_searchList.GetItemText(i,3);
			sf.columnIndex = _ttoi(columnIndex);
			queryConfig.sortItems.push_back(sortItem);
			queryConfig.filters.push_back(sf);
		}
	}
	queryConfig.focusItem = _ttoi(m_searchID);
	queryConfig.pageParam.numberPerPage = _ttoi(m_searchSum);
	queryConfig.pageParam.currentPage = _ttoi(m_searchPage);

	returnInfo= querySitesInfoEx(queryConfig);
	if (returnInfo.resultCode==0)
	{
		char result[1024] = {0};
		char tempResult[1024] = {0};
		sprintf_s(result,1023,"查询会场信息成功:resultCode:%d,currentPage:%d,pageInfo:%d,totalRecord:%d. ",returnInfo.resultCode,returnInfo.result.pageInfo.currentPage,returnInfo.result.pageInfo.totalPages,returnInfo.result.pageInfo.totalRecords);
		list<TerminalInfoEx>::iterator it;
		for(it = returnInfo.result.sites.begin();it!=returnInfo.result.sites.end();it++)
		{
			sprintf_s(tempResult,1023,"name:%s,rate:%s,regUser:%s,type:%d. \n",it->name.c_str(),it->rate.c_str(),it->regUser.c_str(),it->uri.c_str(),it->type);
			str = tempResult +str;
		}
		str = result + str;
		m_showPan.SetWindowTextA(str);
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"查询会场信息失败；返回码：%d",returnInfo.resultCode);
		str = result;
		m_showPan.SetWindowTextA(str);
	}
}


void CTP_Native_MangerDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	TerminalInfoEx siteInfo;
	CString str;
	CString temp;
	list<VideoCapbilityItemEx> videoCapbility;
	char result[1024] = {0};
	CString strResult = "";
	UpdateData(TRUE);

	//会场名称
	siteInfo.name = m_siteName;
	//会场标识
	siteInfo.uri = m_siteMark;
	//会场类型
	siteInfo.type = m_cmbCircuitType.GetCurSel() + 1;
	//速率。格式为“速率值k/M”，如“1920k”。默认由系统自动选择
	CString strRate;
	m_cmbSiteRate.GetLBText(m_cmbSiteRate.GetCurSel(),strRate);
	siteInfo.rate = strRate;
	//（可选）H.323、SIP协议会场注册SC的用户名
	siteInfo.regUser = m_scUser;
	//（可选）H.323、SIP协议会场注册SC的密码
	siteInfo.regPassword = m_scPassword;

	siteInfo.videoCapbility = videoCapbility;
	int resultCode=   addSiteInfoEx(m_siteID.GetBuffer(), siteInfo);
	if (resultCode==0)
	{
		sprintf_s(result,1023,"resultCode:%d",resultCode);
		strResult = strResult + result;
		m_showPan.SetWindowTextA(result);
	} 
	else
	{
		CString s; 
		sprintf_s(result,1023,"添加会场信息失败；返回码：%d",resultCode);
		strResult = result;
		m_showPan.SetWindowTextA(strResult);
	}
}


void CTP_Native_MangerDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	m_allMcu.clear();
	m_listAllMcuInfo.DeleteAllItems();
	TPSDKResponseEx<QueryMCUInfoExResponse> returnInfo;
	CString sort;
	CString itemIndex;
	CString strValue;
	CString columnIndex;
	QueryConfigEx queryConfig;
	SortItemEx sortItem;
	StringFilterEx sf;
	PageParamEx pageParam;
	char result[1024] = {0};
	CString str = "";
	UpdateData(TRUE);
	//排序条件组合，目前只支持单列排序
	for(int i = 0;i<m_searchList.GetItemCount();i++)
	{
		if(m_searchList.GetCheck(i))
		{
			sort = m_searchList.GetItemText(i,0);
			sortItem.sort = _ttoi(sort);
			itemIndex = m_searchList.GetItemText(i,1);
			sortItem.itemIndex = _ttoi(itemIndex);
			strValue = m_searchList.GetItemText(i,2);
			sf.value = strValue;
			columnIndex = m_searchList.GetItemText(i,3);
			sf.columnIndex = _ttoi(columnIndex);
			queryConfig.sortItems.push_back(sortItem);
			queryConfig.filters.push_back(sf);
		}
	}
	queryConfig.focusItem = _ttoi(m_searchID);
	queryConfig.pageParam.numberPerPage = _ttoi(m_searchSum);
	queryConfig.pageParam.currentPage = _ttoi(m_searchPage);

	returnInfo=queryMCUInfoEx(queryConfig);
	if (returnInfo.resultCode==0)
	{
		int iCount = m_listAllMcuInfo.GetItemCount();
		for ( list<MCUInfoEx>::iterator iter = returnInfo.result.mcus.begin(); iter != returnInfo.result.mcus.end();iter++ )
		{
			m_allMcu.push_back(*iter);
			m_listAllMcuInfo.InsertItem( iCount, TP_Tool::Int2String(iter->id).c_str() );
			m_listAllMcuInfo.SetItemText( iCount, 1, iter->name.c_str() );
			m_listAllMcuInfo.SetItemText( iCount, 2, TP_Tool::Int2String(iter->type).c_str() );
			sprintf_s(result,1023,"id:%d,name:%s,type:%d\n",TP_Tool::Int2String(iter->id).c_str(),iter->name.c_str() ,TP_Tool::Int2String(iter->type).c_str());
			str = str + result;
		}
		m_showPan.SetWindowTextA(str);
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"查询MCU信息列表失败；返回码：%d",returnInfo.resultCode);
		m_showPan.SetWindowTextA(str);
	}
}


void CTP_Native_MangerDlg::OnBnClickedButton10()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString cstrTemp;
	//订阅还是取消订阅
	cstrTemp.Format( "%d", m_cmbIsSubScribe.GetCurSel() );
	m_subList.InsertItem( m_subNum, cstrTemp );
	//会议类型
	cstrTemp.Format( "%d", m_cmbSubScribeInfo.GetCurSel() );
	m_subList.SetItemText( m_subNum, 1, cstrTemp );
	//会议ID
	m_subList.SetItemText(m_subNum,2,m_subConfID.GetBuffer());
	m_subNum++;
}


void CTP_Native_MangerDlg::OnBnClickedButton65()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	for(int i = 0;i<m_subList.GetItemCount();i++)
	{
		if(m_subList.GetCheck(i))
		{
			m_subList.DeleteItem(i);
			m_subNum--;
		}
	}
}


void CTP_Native_MangerDlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	list<SubscribeInfoEx *> listsubscribeInfos;
	CString isSubscribe;
	CString type;
	CString confID;

	for(int i = 0;i<m_subList.GetItemCount();i++)
	{
		if(m_subList.GetCheck(i))
		{			
			type = m_subList.GetItemText(i, 1);
			if ( "0" == type )
			{
				ScheduledConfSubscribeEx *pScheduledConfSubscribeEx = new ScheduledConfSubscribeEx;
				if ( NULL == pScheduledConfSubscribeEx )
				{
					return;
				}
				isSubscribe = m_subList.GetItemText(i,0);
				pScheduledConfSubscribeEx->isSubscribe = _ttoi(isSubscribe);	//订阅or取消订阅
				confID = m_subList.GetItemText(i, 2);
				pScheduledConfSubscribeEx->confIds = confID.GetBuffer();
				//SubscribeInfoEx *pSubscribeInfoEx = (SubscribeInfoEx*)pScheduledConfSubscribeEx;
				listsubscribeInfos.push_back( (SubscribeInfoEx*)pScheduledConfSubscribeEx );
				pScheduledConfSubscribeEx = NULL;
			}
			else if ( "1" == type )
			{
				OngoingConfSubscribeEx *pOngoingConfSubscribeEx = new OngoingConfSubscribeEx;
				if ( NULL == pOngoingConfSubscribeEx )
				{
					return;
				}
				isSubscribe = m_subList.GetItemText(i,0);
				pOngoingConfSubscribeEx->isSubscribe = _ttoi(isSubscribe);	//订阅or取消订阅
				confID = m_subList.GetItemText(i, 2);
				pOngoingConfSubscribeEx->confIds = confID.GetBuffer();
				//SubscribeInfoEx *pSubscribeInfoEx = (SubscribeInfoEx*)pOngoingConfSubscribeEx;
				listsubscribeInfos.push_back( (SubscribeInfoEx*)pOngoingConfSubscribeEx );
				pOngoingConfSubscribeEx = NULL;
			}
		}
	}

	int result = subscribeEx(listsubscribeInfos);
	if ( 0 == result )
	{
		SetDlgItemText(IDC_EDIT1,_T("修改推送消息的过滤条件成功"));
	} 
	else
	{
		CString s; 
		s.Format("修改推送消息的过滤条件失败；返回码：%d",result);
		SetDlgItemText(IDC_EDIT1,s.GetBuffer());
	}
	for ( list<SubscribeInfoEx *>::iterator iter = listsubscribeInfos.begin(); iter != listsubscribeInfos.end(); iter++ )
	{
		delete (*iter);
		(*iter) = NULL;
	}
	listsubscribeInfos.clear();
	return;
}


void CTP_Native_MangerDlg::OnBnClickedButton16()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char tempResult[1024] = {0};
	CString str = "";
	int iPushMode = m_cmb.GetCurSel();
	std::string strExtendParameter;
	int result = enablePushEx(iPushMode, strExtendParameter);
	if ( 0 == result )
	{
		sprintf_s(tempResult,1023,"resultCode:%d",result);
		str = tempResult + str;
		m_showPan.SetWindowTextA(str);
	} 
	else
	{
		sprintf_s(tempResult,1023,"开启推送功能失败；返回码：%d",result);
		str = tempResult + str;
		m_showPan.SetWindowTextA(str);
	}
}


void CTP_Native_MangerDlg::OnBnClickedButton15()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<NotificationEx *>> result = queryNotificationEx();
	if ( 0 == result.resultCode )
	{
		CString cstrResultMsg;
		cstrResultMsg.Format("读取通知消息成功。");
		for ( list<NotificationEx *>::iterator iter = result.result.begin(); iter != result.result.end(); iter++ )
		{
			if ( (*iter)->type == TP_D_OVERFLOW_NOTIFICATION_TYPE )
			{
				OverflowNotificationEx *pOverflowNtf = (OverflowNotificationEx *)*iter;
				CString cstrTemp;
				cstrTemp.Format("消息队列溢出.");
				cstrResultMsg = cstrResultMsg + cstrTemp;
				pOverflowNtf = NULL;
			} 
			else if ( (*iter)->type == TP_D_SCHEDULED_CONF_NOTIFICATION_TYPE )
			{
				ScheduledConfNotificationEx *pScheduledConfNtf = (ScheduledConfNotificationEx *)*iter;
				CString cstrTemp;
				cstrTemp.Format("通知类型：%d, 会议ID: %s, 会议开始时间: %04d-%02d-%02dT%02d:%02d:%02d%s。", pScheduledConfNtf->event,
					             pScheduledConfNtf->confId.c_str(), pScheduledConfNtf->beginTime.wYear, pScheduledConfNtf->beginTime.wMonth, 
								 pScheduledConfNtf->beginTime.wDay, pScheduledConfNtf->beginTime.wHour, pScheduledConfNtf->beginTime.wMilliseconds,
								 pScheduledConfNtf->beginTime.wSecond, TP_Tool::GetLocalTimeZone().c_str() );
				pScheduledConfNtf = NULL;
				cstrResultMsg = cstrResultMsg + cstrTemp;
			}
			else if ( (*iter)->type == TP_D_ONGOING_CONF_NOTIFICATION_TYPE )
			{
				OngoingConfNotificationEx *pOngoingConfNtf = (OngoingConfNotificationEx *)*iter;
				CString cstrTemp;
				cstrTemp.Format("通知类型: %d, 会议ID: %s, 开始时间: %04d-%02d-%02dT%02d:%02d:%02d%s, 会场URI: %s, ", pOngoingConfNtf->event,
					             pOngoingConfNtf->confId.c_str(), pOngoingConfNtf->beginTime.wYear, pOngoingConfNtf->beginTime.wMonth,
								 pOngoingConfNtf->beginTime.wDay, pOngoingConfNtf->beginTime.wHour, pOngoingConfNtf->beginTime.wMinute,
								 pOngoingConfNtf->beginTime.wSecond, TP_Tool::GetLocalTimeZone().c_str(), pOngoingConfNtf->siteUri.c_str());
				for ( list<NotificationStatusEx *>::iterator ite = pOngoingConfNtf->changes.begin(); ite != pOngoingConfNtf->changes.end(); ite++ )
				{
					if ( TP_D_CONFERENCE_STATUS_TYPE == (*ite)->structtype )
					{
						ConferenceStatusEx *pConferenceStatusEx = (ConferenceStatusEx *)*ite;
						CString cstrTemp1;
						cstrTemp1.Format("会议ID: %s, 会议名称: %s, 会议状态: %d .", pConferenceStatusEx->id.c_str(), pConferenceStatusEx->name.c_str(),
							              pConferenceStatusEx->status);
						cstrTemp = cstrTemp + cstrTemp1;
						pConferenceStatusEx = NULL;
					} 
					else if ( TP_D_SITE_STATUS_TYPE == (*ite)->structtype )
					{
						SiteStatusEx *pSiteStatusEx = (SiteStatusEx *)*ite;
						CString cstrTemp1;
						cstrTemp1.Format("会场URI: %s, 会场名称: %s, 会场状态: %d .", pSiteStatusEx->uri.c_str(), pSiteStatusEx->name.c_str(),
							             pSiteStatusEx->status);
						cstrTemp = cstrTemp + cstrTemp1;
						pSiteStatusEx = NULL;
					}
				}
				cstrResultMsg = cstrResultMsg + cstrTemp;
			}
		}
		releasequeryNotificationMemery(result.result);
		m_showPan.SetWindowTextA(cstrResultMsg);
	}
	else
	{
		CString s; 
		s.Format("读取通知消息失败；返回码：%d",result.resultCode);
		m_showPan.SetWindowTextA(s);
	}
}


void CTP_Native_MangerDlg::OnBnClickedButton13()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<MCUResourceEx>> returnInfo;
	char result[1024] = {0};
	CString str;
	UpdateData(TRUE);
	//待查询资源的MCU ID列表
	list<int> mcus;
	for (int i=0;i<m_listAllMcuInfo.GetItemCount();i++)
	{
		if(m_listAllMcuInfo.GetCheck(i)) 
		{ 
			mcus.push_back(m_allMcu[i].id);
		} 
	}

	//查询开始时间
	COleDateTime tT;
	tT.ParseDateTime(m_begainTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);

	string duration = m_duration;
	//调用MCU服务中的queryMCUFutureResourceEx方法，查询未来时间MCU的资源占用情况
	returnInfo= queryMCUFutureResourceEx(mcus,st,  duration);
	if (returnInfo.resultCode==0)
	{
		sprintf_s(result,1023,"查询未来时间MCU的资源占用情况成功:resultCode:%d",returnInfo.resultCode);
		str = str + result+ " ";
		list<MCUResourceEx>::iterator it;
		for(it = returnInfo.result.begin();it!=returnInfo.result.end();it++)
		{
			sprintf_s(result,1023,"mcuID:%d",it->mcuId);
			str = str + result;
			list<MCUResourceItemEx>::iterator item;
			for(item = it->resourceList.begin();item!=it->resourceList.end();item++)
			{
				sprintf_s(result,1023,"resouceType:%d",item);
				str = str + result + " ";
				list<ResourceOccupiedStatusEx>::iterator itor;
				for(itor = item->resourceStatus.begin();itor!=item->resourceStatus.end();itor++)
				{
					sprintf_s(result,1023,"duration:%s,freeCount:%d,totalcount:%d",itor->duration.c_str(),itor->freeCount,itor->totalcount);
					str = str + result + " ";
				}
			}
		}
		m_showPan.SetWindowTextA(str);
	} 
	else
	{
		CString s; 
		sprintf_s(result,1023,"查询未来时间MCU的资源占用情况失败；返回码：%d",returnInfo.resultCode);
		m_showPan.SetWindowTextA(str);
	}
}


void CTP_Native_MangerDlg::OnBnClickedButton14()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<OrganizationItemEx>>  returnInfo;
	char result[1024] = {0};
	CString str ="";
	returnInfo=queryOrganizationEx();
	if (returnInfo.resultCode==0)
	{
		sprintf_s(result,1023,"resultCode:%d",returnInfo);
		str = str + result;
		m_showPan.SetWindowTextA(str);
	} 
	else
	{
		sprintf_s(result,1023,"查询系统的组织节点失败；返回码：%d",returnInfo.resultCode);
		str = str + result;
		m_showPan.SetWindowTextA(str);
	}
}

//编辑会场信息
void CTP_Native_MangerDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	TerminalInfoEx siteInfo;
	CString str;
	CString temp;
	CString strResult;
	char result[1024] = {0};
	list<VideoCapbilityItemEx> videoCapbility;
	UpdateData(TRUE);

	//会场名称
	siteInfo.name = m_siteName;
	//会场标识
	siteInfo.uri = m_siteMark;
	//会场类型
	siteInfo.type = m_cmbCircuitType.GetCurSel() + 1;
	//速率。格式为“速率值k/M”，如“1920k”。默认由系统自动选择
	CString strRate;
	m_cmbSiteRate.GetLBText(m_cmbSiteRate.GetCurSel(),strRate);
	siteInfo.rate = strRate;
	//（可选）H.323、SIP协议会场注册SC的用户名
	siteInfo.regUser = m_scUser;
	//（可选）H.323、SIP协议会场注册SC的密码
	siteInfo.regPassword = m_scPassword;

	siteInfo.videoCapbility = m_listSiteVideoCapbility;
	int resultCode = editSiteInfoEx (siteInfo);
	if (resultCode==0)
	{
		sprintf_s(result,1023,"resultCode:%d",resultCode);
		strResult = strResult + result;
		m_showPan.SetWindowTextA(strResult);
	} 
	else
	{
		sprintf_s(result,1023,"编辑会场信息失败；返回码：%d",resultCode);
		strResult = strResult + result;
		m_showPan.SetWindowTextA(strResult);
	}

}


void CTP_Native_MangerDlg::OnNMClickListAllMcuInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMItemActivate->iItem != -1) 
	{ 
		if(m_listAllMcuInfo.GetCheck(pNMItemActivate->iItem)) 
		{ 
			m_listAllMcuInfo.SetItemState(pNMItemActivate->iItem, 0, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listAllMcuInfo.SetCheck(pNMItemActivate->iItem,FALSE); 
		} 
		else
		{
			m_listAllMcuInfo.SetItemState(pNMItemActivate->iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listAllMcuInfo.SetCheck(pNMItemActivate->iItem,TRUE);
		} 
	}
	*pResult = 0;
}