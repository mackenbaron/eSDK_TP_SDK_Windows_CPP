// TP_Native_AdhocConfTempManage.cpp : implementation file
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_AdhocConfTempManage.h"
#include "afxdialogex.h"
#include "TP_Tool.h"

// CTP_Native_AdhocConfTempManage dialog

IMPLEMENT_DYNAMIC(CTP_Native_AdhocConfTempManage, CPropertyPage)

CTP_Native_AdhocConfTempManage::CTP_Native_AdhocConfTempManage()
	: CPropertyPage(CTP_Native_AdhocConfTempManage::IDD)
{
	m_iLastChoosedAdhocTemplateItem = -1;
}

CTP_Native_AdhocConfTempManage::~CTP_Native_AdhocConfTempManage()
{
}

void CTP_Native_AdhocConfTempManage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listAllAdhocConfTemplate);
	DDX_Control(pDX, IDC_LIST5, m_listAllAdhocConference);
	//DDX_Control(pDX, IDC_LIST2, m_listSitesInAdhocConfTemplate);
	DDX_Control(pDX, IDC_EDIT3, m_editResultPanel);
	DDX_Control(pDX, IDC_EDIT_NEW_ADHOC_CONF_TEMPLATE_NAME, m_editNewAdhocConfTempName);
	DDX_Control(pDX, IDC_EDIT_NEW_ADHOC_TEMPLATE_DURATION, m_editNewAdhocTempDuration);
	DDX_Control(pDX, IDC_COMBO_NEW_ADHOC_TEMPLATE_RATE, m_cmbNewAdhocTemplateRate);
	DDX_Control(pDX, IDC_COMBO_NEW_ADHOC_TEMP_MEDIA_ENCRYPT_TYPE, m_cmbNewAdhocTemplateMediaEncrytType);
	DDX_Control(pDX, IDC_EDIT_NEW_ADHOC_TEMP_ACCESS_CODE, m_editNewAdhocTemplateAccessCode);
	DDX_Control(pDX, IDC_COMBO_NEW_PRESENTATION_VIDEO, m_cmbNewAdhocTemplatePresentationVideo);
	DDX_Control(pDX, IDC_COMBO_NEW_ADHOC_TEMP_CPRESOUCE, m_cmbNewAdhocTemplateCpResouce);
	DDX_Control(pDX, IDC_EDIT_QUERY_BEGIN_TIME, m_editQueryBeginTime);
	DDX_Control(pDX, IDC_EDIT_QUERY_DURATION, m_editQueryAdhocDuration);
	DDX_Control(pDX, IDC_COMBO1, m_cmbQueryAdhocTempType);
	DDX_Control(pDX, IDC_EDIT1, m_editQueryAdhocTempKeyValue);
}


BEGIN_MESSAGE_MAP(CTP_Native_AdhocConfTempManage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_GETADHOC_CONF_TEMPLATE, &CTP_Native_AdhocConfTempManage::OnBnClickedButtonGetadhocConfTemplate)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTP_Native_AdhocConfTempManage::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON_GET_ADHOC_CONFERENCES, &CTP_Native_AdhocConfTempManage::OnBnClickedButtonGetAdhocConferences)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_ADHOC_CONF_TEMPLATE, &CTP_Native_AdhocConfTempManage::OnBnClickedButtonEditAdhocConfTemplate)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ADHOC_TEMPLATE, &CTP_Native_AdhocConfTempManage::OnBnClickedButtonDeleteAdhocTemplate)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_ADHOC_CONF_FREE_BUSY, &CTP_Native_AdhocConfTempManage::OnBnClickedButtonQueryAdhocConfFreeBusy)
	ON_NOTIFY(NM_CLICK, IDC_LIST5, &CTP_Native_AdhocConfTempManage::OnNMClickList5)
	ON_BN_CLICKED(IDC_BUTTON_SYNCH_ADHOC_CONF_FREE_BUSY, &CTP_Native_AdhocConfTempManage::OnBnClickedButtonSynchAdhocConfFreeBusy)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_POINT_TO_POINT_CDR, &CTP_Native_AdhocConfTempManage::OnBnClickedButtonQueryPointToPointCdr)
END_MESSAGE_MAP()


// CTP_Native_AdhocConfTempManage message handlers


BOOL CTP_Native_AdhocConfTempManage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	m_listAllAdhocConfTemplate.ModifyStyle(0,LVS_REPORT);
	DWORD dwStyle = m_listAllAdhocConfTemplate.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_listAllAdhocConfTemplate.SetExtendedStyle(dwStyle); // 设置扩展风格 
	m_listAllAdhocConfTemplate.InsertColumn(0,"模板ID",LVCFMT_CENTER,80,NULL);
	m_listAllAdhocConfTemplate.InsertColumn(1,"模板名称",LVCFMT_CENTER,80,NULL);
	m_listAllAdhocConfTemplate.InsertColumn(2,"会议激活码",LVCFMT_CENTER,80,NULL);
	m_listAllAdhocConfTemplate.InsertColumn(3,"会议时长",LVCFMT_CENTER,80,NULL);

	m_listAllAdhocConference.ModifyStyle(0,LVS_REPORT);
	dwStyle = m_listAllAdhocConference.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_listAllAdhocConference.SetExtendedStyle(dwStyle); // 设置扩展风格 
	m_listAllAdhocConference.InsertColumn(0,"Adhoc会议名称",LVCFMT_CENTER,120,NULL);
	m_listAllAdhocConference.InsertColumn(1,"Adhoc会议接入号",LVCFMT_CENTER,160,NULL);

	m_cmbQueryAdhocTempType.AddString("会场名称");
	m_cmbQueryAdhocTempType.AddString("会场URI");
	m_cmbQueryAdhocTempType.AddString("会场状态");
	m_cmbQueryAdhocTempType.AddString("会场类型");
	m_cmbQueryAdhocTempType.AddString("会议模板名称");
	m_cmbQueryAdhocTempType.AddString("会议模板接入号");
	m_cmbQueryAdhocTempType.AddString("MCU名称");
	m_cmbQueryAdhocTempType.SetCurSel(4);
	m_editQueryAdhocTempKeyValue.SetWindowText("Adhoc");

	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,-120, 0);
	m_time=CTime::GetCurrentTime();				//获取当前时间日期  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //格式化日期时间 

	m_editQueryBeginTime.SetWindowText(strTime);
	m_editQueryAdhocDuration.SetWindowText(_T("P0Y0M0DT2H0M0.000S"));

	m_editNewAdhocConfTempName.SetWindowText("Edit_Adhoc_Temp");
	m_editNewAdhocTemplateAccessCode.SetWindowText("123456");
	m_editNewAdhocTempDuration.SetWindowText(_T("P0Y0M0DT2H0M0.000S"));

	m_cmbNewAdhocTemplateRate.AddString(_T("64k"));
	m_cmbNewAdhocTemplateRate.AddString(_T("1920k"));
	m_cmbNewAdhocTemplateRate.AddString(_T("8192k"));
	m_cmbNewAdhocTemplateRate.SetCurSel(1);

	m_cmbNewAdhocTemplateMediaEncrytType.AddString(_T("AutoEncrypt"));
	m_cmbNewAdhocTemplateMediaEncrytType.AddString(_T("ForceEncrypt"));
	m_cmbNewAdhocTemplateMediaEncrytType.AddString(_T("None"));
	m_cmbNewAdhocTemplateMediaEncrytType.SetCurSel(2);

	m_cmbNewAdhocTemplateCpResouce.AddString(_T("1"));
	m_cmbNewAdhocTemplateCpResouce.AddString(_T("2"));
	m_cmbNewAdhocTemplateCpResouce.AddString(_T("3"));
	m_cmbNewAdhocTemplateCpResouce.AddString(_T("4"));
	m_cmbNewAdhocTemplateCpResouce.AddString(_T("5"));
	m_cmbNewAdhocTemplateCpResouce.AddString(_T("6"));
	m_cmbNewAdhocTemplateCpResouce.AddString(_T("7"));
	m_cmbNewAdhocTemplateCpResouce.AddString(_T("8"));
	m_cmbNewAdhocTemplateCpResouce.SetCurSel(1);

	//m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("Auto"));
	//m_cmbAuxVideoFormat.AddString(_T("H.261"));
	//m_cmbAuxVideoFormat.AddString(_T("H.263"));
	//m_cmbAuxVideoFormat.AddString(_T("H.264"));
	//m_cmbAuxVideoFormat.SetCurSel(0);

	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("Auto"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("4CIF"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("720P30(720P)"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("1080P30(1080P)"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("480P"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("720P60"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("1080P60"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("QCIF"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("CIF"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("SQCIF"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("CIF2"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("I108"));
	m_cmbNewAdhocTemplatePresentationVideo.AddString(_T("I480"));
	m_cmbNewAdhocTemplatePresentationVideo.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTP_Native_AdhocConfTempManage::OnBnClickedButtonGetadhocConfTemplate()
{
	// TODO: Add your control notification handler code here
	m_listAllAdhocConfTemplate.DeleteAllItems();
	m_listAllAdhocConferencesTemplate.clear();

	QueryConfigEx queryConfig;
	SortItemEx sortItemEx;
	sortItemEx.itemIndex = 4;		//按会议模板的名称排序
	sortItemEx.sort = 0;
	queryConfig.sortItems.push_back(sortItemEx);
	queryConfig.focusItem = 1;
	queryConfig.pageParam.currentPage = 1;
	queryConfig.pageParam.numberPerPage = 10;

	StringFilterEx stringFilterEx;
	stringFilterEx.columnIndex = m_cmbQueryAdhocTempType.GetCurSel();
	CString cstrTemp;
	m_editQueryAdhocTempKeyValue.GetWindowText(cstrTemp);
	stringFilterEx.value = cstrTemp.GetBuffer();
	queryConfig.filters.push_back(stringFilterEx);
	TPSDKResponseWithPageEx<list<AdhocConfTemplateParamEx>> response = queryAdhocConfTemplateListEx( queryConfig );
	if ( 0 == response.resultCode )
	{
		m_listAllAdhocConferencesTemplate = response.result;
		int iTemplateCount = m_listAllAdhocConfTemplate.GetItemCount();
		for ( list<AdhocConfTemplateParamEx>::iterator iter = response.result.begin(); iter != response.result.end(); iter++ )
		{
			m_listAllAdhocConfTemplate.InsertItem( iTemplateCount, iter->adhocConfTemplateId.c_str() );
			m_listAllAdhocConfTemplate.SetItemText( iTemplateCount, 1, iter->name.c_str() );
			m_listAllAdhocConfTemplate.SetItemText( iTemplateCount, 2, iter->accessCode.c_str() );
			m_listAllAdhocConfTemplate.SetItemText( iTemplateCount, 3, iter->duration.c_str() );
		}
		CString cstrMsg;
		cstrMsg.Format("查询Adhoc会议模板成功");
		m_editResultPanel.SetWindowText(cstrMsg);
	} 
	else
	{
		CString cstrMsg;
		cstrMsg.Format("查询Adhoc会议模板错误，返回码：%d", response.resultCode);
		m_editResultPanel.SetWindowText(cstrMsg);
	}
}


void CTP_Native_AdhocConfTempManage::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMItemActivate->iItem != -1) 
	{ 
		if(m_listAllAdhocConfTemplate.GetCheck(pNMItemActivate->iItem)) 
		{ 
			m_listAllAdhocConfTemplate.SetItemState(pNMItemActivate->iItem, 0, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listAllAdhocConfTemplate.SetCheck(pNMItemActivate->iItem,FALSE); 
			m_iLastChoosedAdhocTemplateItem = -1;
		} 
		else
		{
			if ( -1 != m_iLastChoosedAdhocTemplateItem )
			{
				m_listAllAdhocConfTemplate.SetItemState( m_iLastChoosedAdhocTemplateItem, 0, LVIS_SELECTED|LVIS_FOCUSED ); 
				m_listAllAdhocConfTemplate.SetCheck( m_iLastChoosedAdhocTemplateItem,FALSE );
			}
			m_listAllAdhocConfTemplate.SetItemState(pNMItemActivate->iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listAllAdhocConfTemplate.SetCheck(pNMItemActivate->iItem,TRUE);
			m_iLastChoosedAdhocTemplateItem = pNMItemActivate->iItem;
		} 
	}

	*pResult = 0;
}


void CTP_Native_AdhocConfTempManage::OnBnClickedButtonGetAdhocConferences()
{
	// TODO: Add your control notification handler code here
	m_listAllAdhocConference.DeleteAllItems();

	QueryConfigEx queryConfig;
	//排序条件组合，目前只支持单列排序
	SortItemEx s;
	s.sort = 0;
	s.itemIndex = 4;
	queryConfig.sortItems.push_back(s);

	//页码定位参数
	queryConfig.pageParam.numberPerPage = 10;
	queryConfig.pageParam.currentPage = 1;
	queryConfig.focusItem = 1;
	//焦点数据ID。指定当前查询优先返回包含指定ID的数据页面
	queryConfig.focusItem = 0;
	TPSDKResponseEx<QueryAdhocConferenceExResponse> response = queryAdhocConferencesEx( queryConfig );
	if ( 0 == response.resultCode )
	{
		m_listAllAdhocConferences = response.result.adhocConferences;
		int iAdhocConfCount = m_listAllAdhocConference.GetItemCount();
		for ( list<AdhocConferenceEx>::iterator iter = response.result.adhocConferences.begin(); iter != response.result.adhocConferences.end(); iter++ )
		{
			m_listAllAdhocConference.InsertItem( iAdhocConfCount, iter->name.c_str() );
			m_listAllAdhocConference.SetItemText( iAdhocConfCount, 1, iter->confAccessCode.c_str() );
		}
		CString cstrMsg;
		cstrMsg.Format("查询Adhoc会议列表成功");
		m_editResultPanel.SetWindowText(cstrMsg);
	} 
	else
	{
		CString cstrMes;
		cstrMes.Format("查询Adhoc会议列表失败，返回码：%d", response.resultCode);
		m_editResultPanel.SetWindowText(cstrMes);
	}
}


void CTP_Native_AdhocConfTempManage::OnBnClickedButtonEditAdhocConfTemplate()
{
	// TODO: Add your control notification handler code here
	getChoosedAdhocConfTemplateList();
	if ( m_choosedConfTemplateId != "" )
	{
		AdhocConfTemplateParamEx adhocConfTemplate;
		adhocConfTemplate.adhocConfTemplateId = m_choosedConfTemplateId;
		//会议模板名称
		CString cstrTemp;
		m_editNewAdhocConfTempName.GetWindowText(cstrTemp);
		adhocConfTemplate.name = cstrTemp.GetBuffer();
		//会议激活码
		m_editNewAdhocTemplateAccessCode.GetWindowText(cstrTemp);
		adhocConfTemplate.accessCode = cstrTemp.GetBuffer();
		//会议时长
		m_editNewAdhocTempDuration.GetWindowText(cstrTemp);
		//int minutes = atoi( cstrTemp.GetBuffer() );
		//int hours = minutes / 60;
		//minutes = minutes - hours * 60;
		////cstrTemp = "";
		//cstrTemp.Format("P0Y0M0DT%dH%dM0.000S", hours,minutes);
		adhocConfTemplate.duration = cstrTemp.GetBuffer();
		//加密方式
		adhocConfTemplate.mediaEncryptType = m_cmbNewAdhocTemplateMediaEncrytType.GetCurSel();
		//多画面模式
		adhocConfTemplate.cpResouce = m_cmbNewAdhocTemplateCpResouce.GetCurSel() + 1;
		//速率
		m_cmbNewAdhocTemplateRate.GetLBText(m_cmbNewAdhocTemplateRate.GetCurSel(),cstrTemp);
		adhocConfTemplate.rate = cstrTemp.GetBuffer();
		int iRet = editAdhocConfTemplateEx( adhocConfTemplate );
		if ( 0 == iRet )
		{
			m_editResultPanel.SetWindowText(_T("修改会议模板成功"));
		} 
		else
		{
			CString cstrMsg;
			cstrMsg.Format("修改会议模板失败，返回码：%d", iRet);
			m_editResultPanel.SetWindowText(cstrMsg);
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择Adhoc会议模板"));
	}
}


void CTP_Native_AdhocConfTempManage::OnBnClickedButtonDeleteAdhocTemplate()
{
	// TODO: Add your control notification handler code here
	getChoosedAdhocConfTemplateList();
	if ( m_choosedConfTemplateId != "")
	{
		int iRet = delAdhocConfTemplateEx( m_choosedConfTemplateId );
		if ( 0 == iRet )
		{
			m_editResultPanel.SetWindowText(_T("删除会议模板成功"));
		} 
		else
		{
			CString cstrMsg;
			cstrMsg.Format("删除会议模板失败，返回码：%d", iRet);
			m_editResultPanel.SetWindowText(cstrMsg);
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择Adhoc会议模板"));
	}
}


void CTP_Native_AdhocConfTempManage::OnBnClickedButtonQueryAdhocConfFreeBusy()
{
	// TODO: Add your control notification handler code here
	GetChoosedAdhocConferenceList();
	if ( m_listChoosedAdhocConferences.size() > 0 )
	{	
		list<std::string> confAccessCodes;
		for ( list<AdhocConferenceEx>::iterator iter = m_listChoosedAdhocConferences.begin(); iter != m_listChoosedAdhocConferences.end(); iter++ )
		{
			confAccessCodes.push_back(iter->confAccessCode);
		}
		//查询开始时间
		CString cstrTemp;
		m_editQueryBeginTime.GetWindowText(cstrTemp);
		COleDateTime tT;
		tT.ParseDateTime(cstrTemp);
		SYSTEMTIME beginTime;
		tT.GetAsSystemTime(beginTime);
		//查询间隔时间
		m_editQueryAdhocDuration.GetWindowText(cstrTemp);
		std::string duration = cstrTemp.GetBuffer();
		TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> response = queryAdhocConfFreeBusyEx( confAccessCodes, beginTime, duration );
		if ( 0 == response.resultCode )
		{
			CString cstrMsg = "查询ADHOC会议忙闲成功。";
			for ( list<AdhocConfFreeBusyStateEx>::iterator ite = response.result.begin(); ite != response.result.end(); ite++ )
			{
				cstrTemp.Format("会议接入号: %s,", ite->confAccessCode.c_str());
				for ( list<FreeBusyStateEx>::iterator itera = ite->freebusys.begin(); itera != ite->freebusys.end(); ite++ )
				{
					CString cstrFreeBusy;
					cstrFreeBusy.Format("起始时间：%04d-%02d-%02dT%02d:%02d:%02d%s，时间跨度：%s，忙闲状态：%d，会议ID：%s，会议名称：%s 。",
						                itera->startTime.wYear, itera->startTime.wMonth, itera->startTime.wDay, itera->startTime.wHour, itera->startTime.wSecond,
										itera->startTime.wSecond, TP_Tool::GetLocalTimeZone().c_str(), itera->span.c_str(), itera->state, itera->confId.c_str(),
										itera->confName.c_str());
					cstrTemp = cstrTemp + cstrFreeBusy;
				}
				cstrMsg = cstrMsg + cstrTemp;
			}
			m_editResultPanel.SetWindowText(cstrMsg);
		} 
		else
		{
			CString cstrMsg;
			cstrMsg.Format( "查询ADHOC会议忙闲失败，返回码：%d", response.resultCode );
			m_editResultPanel.SetWindowText(cstrMsg);
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择Adhoc会议"));
	}
}


void CTP_Native_AdhocConfTempManage::OnNMClickList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMItemActivate->iItem != -1) 
	{ 
		if(m_listAllAdhocConference.GetCheck(pNMItemActivate->iItem)) 
		{ 
			m_listAllAdhocConference.SetItemState(pNMItemActivate->iItem, 0, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listAllAdhocConference.SetCheck(pNMItemActivate->iItem,FALSE); 
		} 
		else
		{
			m_listAllAdhocConference.SetItemState(pNMItemActivate->iItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
			m_listAllAdhocConference.SetCheck(pNMItemActivate->iItem,TRUE);
		} 
	}
	*pResult = 0;
}

void CTP_Native_AdhocConfTempManage::GetChoosedAdhocConferenceList()
{
	m_listChoosedAdhocConferences.clear();
	list<AdhocConferenceEx>::iterator iter = m_listAllAdhocConferences.begin();
	for (int i = 0;i<m_listAllAdhocConference.GetItemCount();i++)
	{
		iter++;
		if(m_listAllAdhocConference.GetCheck(i)) 
		{ 
			m_listChoosedAdhocConferences.push_back(*iter);
		} 
	}
}

void CTP_Native_AdhocConfTempManage::OnBnClickedButtonSynchAdhocConfFreeBusy()
{
	// TODO: Add your control notification handler code here
	GetChoosedAdhocConferenceList();
	if ( m_listChoosedAdhocConferences.size() > 0 )
	{	
		list<std::string> confAccessCodes;
		for ( list<AdhocConferenceEx>::iterator iter = m_listChoosedAdhocConferences.begin(); iter != m_listChoosedAdhocConferences.end(); iter++ )
		{
			confAccessCodes.push_back(iter->confAccessCode);
		}
		//查询开始时间
		CString cstrTemp;
		m_editQueryBeginTime.GetWindowText(cstrTemp);
		COleDateTime tT;
		tT.ParseDateTime(cstrTemp);
		SYSTEMTIME beginTime;
		tT.GetAsSystemTime(beginTime);
		//查询间隔时间
		m_editQueryAdhocDuration.GetWindowText(cstrTemp);
		std::string duration = cstrTemp.GetBuffer();
		TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> response = synchAdhocConfFreeBusyEx(confAccessCodes, beginTime, duration);
		if ( 0 == response.resultCode )
		{
			CString cstrMsg = "查询ADHOC会议忙闲状态变化的数据成功。";
			for ( list<AdhocConfFreeBusyStateEx>::iterator ite = response.result.begin(); ite != response.result.end(); ite++ )
			{
				cstrTemp.Format("会议接入号: %s,", ite->confAccessCode.c_str());
				for ( list<FreeBusyStateEx>::iterator itera = ite->freebusys.begin(); itera != ite->freebusys.end(); ite++ )
				{
					CString cstrFreeBusy;
					cstrFreeBusy.Format("起始时间：%04d-%02d-%02dT%02d:%02d:%02d%s，时间跨度：%s，忙闲状态：%d，会议ID：%s，会议名称：%s 。",
						                 itera->startTime.wYear, itera->startTime.wMonth, itera->startTime.wDay, itera->startTime.wHour, itera->startTime.wSecond,
						                 itera->startTime.wSecond, TP_Tool::GetLocalTimeZone().c_str(), itera->span.c_str(), itera->state, itera->confId.c_str(),
						                 itera->confName.c_str());
					cstrTemp = cstrTemp + cstrFreeBusy;
				}
				cstrMsg = cstrMsg + cstrTemp;
			}
			m_editResultPanel.SetWindowText(cstrMsg);
		} 
		else
		{
			CString cstrMsg;
			cstrMsg.Format( "查询ADHOC会议忙闲状态变化的数据失败，返回码：%d", response.resultCode );
			m_editResultPanel.SetWindowText(cstrMsg);
		}
	}
	else
	{
		m_editResultPanel.SetWindowText(_T("请先选择Adhoc会议"));
	}
}


void CTP_Native_AdhocConfTempManage::OnBnClickedButtonQueryPointToPointCdr()
{
	// TODO: Add your control notification handler code here
	//TPSDKResponseEx<QueryPointToPointCDRExResponse> response = queryPointToPointCDREx(const PointToPointCDRQueryConfigEx &queryConfig);
}

void CTP_Native_AdhocConfTempManage::getChoosedAdhocConfTemplateList()
{
	clearChoosedConfTemplate();
	m_choosedConfTemplateId = "";
	for (int i = 0;i<m_listAllAdhocConfTemplate.GetItemCount();i++)
	{
		if(m_listAllAdhocConfTemplate.GetCheck(i)) 
		{ 
			m_choosedConfTemplateId = m_listAllAdhocConfTemplate.GetItemText(i,0).GetBuffer();
			break;
		} 
	}
}

void CTP_Native_AdhocConfTempManage::clearChoosedConfTemplate()
{
	m_choosedConfTemplate.adhocConfTemplateId = "";
	m_choosedConfTemplate.accessCode = "";
	m_choosedConfTemplate.sites.clear();
	m_choosedConfTemplate.name = "";
	m_choosedConfTemplate.rate = "";
	m_choosedConfTemplate.state = 0;
}
