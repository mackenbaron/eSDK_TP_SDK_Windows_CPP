
// HoldMultiConfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HoldMultiConf.h"
#include "HoldMultiConfDlg.h"
#include "afxdialogex.h"
#include <iterator>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHoldMultiConfDlg dialog




CHoldMultiConfDlg::CHoldMultiConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHoldMultiConfDlg::IDD, pParent)
	, m_strUsername(_T(""))
	, m_strPassword(_T(""))
	, m_value(_T(""))
	, m_searchID(_T(""))
	, m_searchSum(_T(""))
	, m_searchPage(_T(""))
	, m_confName(_T(""))
	, m_beginTime(_T(""))
	, m_confTime(_T(""))
	, m_chairmanPwd(_T(""))
	, m_confPwd(_T(""))
	, m_accessCode(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iLastChoosedItem  = -1;
	m_listConfItemSel = -1;
	m_listConfBeHit = -1;
	m_listConfBeHit = FALSE;
}

void CHoldMultiConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strUsername);
	DDX_Text(pDX, IDC_EDIT2, m_strPassword);
	DDX_Control(pDX, IDC_COMBO_SORT_ITEM_INDEX, m_cmbSortItemIndex);
	DDX_Control(pDX, IDC_SEARCH_LIST, m_searchList);
	DDX_Control(pDX, IDC_COMBO_FILTER_BASE_COLUMN, m_cmbFilterBaseColumnIndex);
	DDX_Control(pDX, IDC_COMBO_SORT_TYPE, m_cmbSortType);
	DDX_Control(pDX, IDC_EDIT6, m_showPan);
	DDX_Text(pDX, IDC_EDIT7, m_value);
	DDX_Text(pDX, IDC_EDIT3, m_searchID);
	DDX_Text(pDX, IDC_EDIT4, m_searchSum);
	DDX_Text(pDX, IDC_EDIT5, m_searchPage);

	DDX_Control(pDX, IDC_LIST_CONF, m_listConference);
	DDX_Control(pDX, IDC_LIST_CONF_SITES, m_listSitesInConf);
	DDX_Text(pDX, IDC_EDIT_CONFNAME, m_confName);
	DDX_Text(pDX, IDC_EDIT_BEGINTIME, m_beginTime);
	DDX_Text(pDX, IDC_EDIT_HOWLONG, m_confTime);
	DDX_Control(pDX, IDC_COMBO_FREQUENCY, m_cmbRecurrenceConfFrequency);
	DDX_Control(pDX, IDC_EDIT_RECURRENCE_COUNT, m_editRecurrenceConfCount);
	DDX_Control(pDX, IDC_EDIT_RECURRENCE_CONF_INTERVAL, m_editRecurrenceConfInterval);
	DDX_Control(pDX, IDC_LIST8, m_sitesInfoList);
	DDX_Text(pDX, IDC_EDIT_CHAIRMANPWD, m_chairmanPwd);
	DDX_Control(pDX, IDC_COMBO_RATE, m_cb_rate);
	DDX_Control(pDX, IDC_COMBO_PWDTYPE, m_cb_pwdtype);
	DDX_Control(pDX, IDC_COMBO_MULTI, m_cb_multi);
	DDX_Control(pDX, IDC_COMBO_VEDIOFM, m_cb_vediofm);
	DDX_Control(pDX, IDC_COMBO_VEDIOPR, m_cb_vediopr);
	DDX_Text(pDX, IDC_EDIT_PWD, m_confPwd);
	DDX_Text(pDX, IDC_EDIT_ACCESSCODE, m_accessCode);
}

BEGIN_MESSAGE_MAP(CHoldMultiConfDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIN, &CHoldMultiConfDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_LOGOUT, &CHoldMultiConfDlg::OnBnClickedLogout)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ADD_SEARCH_CONDITION, &CHoldMultiConfDlg::OnBnClickedAddSearchCondition)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_SEARCH_CONDITION, &CHoldMultiConfDlg::OnBnClickedButtonClearSearchCondition)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_SITES_INFO, &CHoldMultiConfDlg::OnBnClickedButtonQuerySitesInfo)
	ON_BN_CLICKED(IDC_BUTTON_QUERY_CONF_STATUS, &CHoldMultiConfDlg::OnBnClickedButtonQueryConfStatus)
	ON_BN_CLICKED(IDC_BUTTON_GET_CONF_SITES, &CHoldMultiConfDlg::OnBnClickedButtonGetConfSites)
	ON_BN_CLICKED(IDC_BTN_QUERY_SITES, &CHoldMultiConfDlg::OnBnClickedBtnQuerySites)
	ON_BN_CLICKED(IDC_BTN_CREATECONF, &CHoldMultiConfDlg::OnBnClickedBtnCreateconf)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CONF, &CHoldMultiConfDlg::OnNMClickListConf)
	ON_BN_CLICKED(IDC_CHECK_RECURRENCE_CONF, &CHoldMultiConfDlg::OnBnClickedCheckRecurrenceConf)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CONF, &CHoldMultiConfDlg::OnNMRClickListConf)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CONF, &CHoldMultiConfDlg::OnLvnItemchangedListConf)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONF, &CHoldMultiConfDlg::OnNMDblclkListConf)
	ON_NOTIFY(NM_RDBLCLK, IDC_LIST_CONF, &CHoldMultiConfDlg::OnNMRDblclkListConf)
END_MESSAGE_MAP()


// CHoldMultiConfDlg message handlers

BOOL CHoldMultiConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

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

	m_cmbSortType.AddString("升序排列");
	m_cmbSortType.AddString("降序排列");
	m_cmbSortType.SetCurSel(0);

	m_cmbSortItemIndex.AddString("会场名称");
	m_cmbSortItemIndex.AddString("会场URI");
	m_cmbSortItemIndex.AddString("会场状态(暂不支持)");
	m_cmbSortItemIndex.AddString("会场类型(暂不支持)");
	m_cmbSortItemIndex.AddString("会议模板名");
	m_cmbSortItemIndex.AddString("会议模板接入号");
	m_cmbSortItemIndex.AddString("MCU名称");
	m_cmbSortItemIndex.SetCurSel(0);

	m_cmbFilterBaseColumnIndex.AddString("会场名称");
	m_cmbFilterBaseColumnIndex.AddString("会场URI");
	m_cmbFilterBaseColumnIndex.AddString("会场状态(暂不支持)");
	m_cmbFilterBaseColumnIndex.AddString("会场类型(暂不支持)");
	m_cmbFilterBaseColumnIndex.AddString("会议模板名");
	m_cmbFilterBaseColumnIndex.AddString("会议模板接入号");
	m_cmbFilterBaseColumnIndex.AddString("MCU名称");
	m_cmbFilterBaseColumnIndex.SetCurSel(0);


	m_sitesInfoList.ModifyStyle(0,LVS_REPORT);

	dwStyle = m_sitesInfoList.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_sitesInfoList.SetExtendedStyle(dwStyle); // 设置扩展风格 

	m_sitesInfoList.InsertColumn(0,"URI",LVCFMT_CENTER,80,NULL);
	m_sitesInfoList.InsertColumn(1,"名称",LVCFMT_CENTER,80,NULL);
	m_sitesInfoList.InsertColumn(2,"类型",LVCFMT_CENTER,80,NULL);
	m_sitesInfoList.InsertColumn(3,"速率",LVCFMT_CENTER,100,NULL);

	SetDlgItemText(IDC_EDIT_CONFNAME, _T("New Conf"));
	SetDlgItemText(IDC_EDIT1,_T("esdk_user"));
	SetDlgItemText(IDC_EDIT2,_T("Huawei@123"));
	SetDlgItemText(IDC_EDIT3,_T("0"));
	SetDlgItemText(IDC_EDIT4,_T("10"));
	SetDlgItemText(IDC_EDIT5,_T("1"));
	
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
	GetDlgItem(IDC_EDIT_ACCESSCODE)->EnableWindow(TRUE);

	m_editRecurrenceConfInterval.SetWindowText("1");
	m_editRecurrenceConfCount.SetWindowText("2");


	m_listConference.ModifyStyle(0,LVS_SINGLESEL|LVS_REPORT,SWP_FRAMECHANGED|SWP_DRAWFRAME);
	dwStyle = m_listConference.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_listConference.SetExtendedStyle(dwStyle); // 设置扩展风格 
	m_listConference.InsertColumn(0,"会议ID",LVCFMT_CENTER,80,NULL);
	m_listConference.InsertColumn(1,"会议名称",LVCFMT_CENTER,80,NULL);
	m_listConference.InsertColumn(2,"会议状态",LVCFMT_CENTER,80,NULL);
	m_listConference.InsertColumn(3,"开始时间",LVCFMT_CENTER,160,NULL);

	m_listSitesInConf.ModifyStyle(0,LVS_REPORT);
	dwStyle = m_listSitesInConf.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;
	m_listSitesInConf.SetExtendedStyle(dwStyle);
	m_listSitesInConf.InsertColumn(0,"URI",LVCFMT_CENTER,80,NULL);
	m_listSitesInConf.InsertColumn(1,"会场名称",LVCFMT_CENTER,80,NULL);
	m_listSitesInConf.InsertColumn(2,"会场类型",LVCFMT_CENTER,80,NULL);
	m_listSitesInConf.InsertColumn(3,"会场状态",LVCFMT_CENTER,80,NULL);


	//m_editProlongConfTime.SetWindowText("P0Y0M0DT1H0M0.000S");
	//m_editNewConfName.SetWindowText("Edit Conference");
	m_num = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHoldMultiConfDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHoldMultiConfDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHoldMultiConfDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHoldMultiConfDlg::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	int ret = TP_E_RET_CODE_SUCCESS;
	UpdateData(TRUE);
	ret = login(m_strUsername.GetBuffer(),m_strPassword.GetBuffer());
	if (TP_E_RET_CODE_SUCCESS == ret)
	{
		AfxMessageBox("登录成功");
		SetTimer( 1, 19000, NULL );
	}
	else
	{
		char result[1024]={0};
		sprintf_s(result, 1023, "登录失败； 返回码 ：%d",ret);
		AfxMessageBox(result);
		KillTimer(1);
	}
	UpdateData(FALSE);

}


void CHoldMultiConfDlg::OnBnClickedLogout()
{
	// TODO: Add your control notification handler code here
	int ret = TP_E_RET_CODE_SUCCESS;
	UpdateData(TRUE);
	ret = logout();
	if (TP_E_RET_CODE_SUCCESS == ret)
	{
		AfxMessageBox("登出成功");
		KillTimer(1);
	}
	else
	{
		char result[1024]={0};
		sprintf_s(result, 1023, "登出失败； 返回码 ：%d",ret);
		AfxMessageBox(result);
	}
	UpdateData(FALSE);
}


void CHoldMultiConfDlg::MainLoop()
{
	int ret = keepAlive();
}

unsigned int __stdcall ThreadFunc(void* para)
{
	if (NULL == para)
	{
		return TP_E_RET_CODE_FAIL;
	}

	CHoldMultiConfDlg* instance = (CHoldMultiConfDlg*)para;
	instance->MainLoop();
	return TP_E_RET_CODE_SUCCESS;
}

void CHoldMultiConfDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	StartMsgRetrieval();
	CDialogEx::OnTimer(nIDEvent);
}


void CHoldMultiConfDlg::StartMsgRetrieval()
{
	_beginthreadex(NULL, 0, ThreadFunc, (void*)this, 0, &m_threadID);
}

void CHoldMultiConfDlg::OnBnClickedAddSearchCondition()
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


void CHoldMultiConfDlg::OnBnClickedButtonClearSearchCondition()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	for(int i = 0;i<m_searchList.GetItemCount();++i)
	{
		if(m_searchList.GetCheck(i))
		{
			m_searchList.DeleteItem(i);
			m_num--;
		}
	}

}


void CHoldMultiConfDlg::OnBnClickedButtonQuerySitesInfo()
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
	for(int i = 0;i<m_searchList.GetItemCount();++i)
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
		for(it = returnInfo.result.sites.begin();it!=returnInfo.result.sites.end();++it)
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


void CHoldMultiConfDlg::OnBnClickedButtonQueryConfStatus()
{
	// TODO: Add your control notification handler code here
	m_iLastChoosedItem  = -1;
	m_listConference.DeleteAllItems();

	list<std::string> confIds;
	m_ChoosedConferences.clear();
	m_conferenceList.clear();
	TPSDKResponseEx<list<ConferenceStatusEx>> returnInfo = queryConferencesStatusEx(confIds);

	if (returnInfo.resultCode==0)
	{
		std::copy(returnInfo.result.begin(), returnInfo.result.end(), std::back_inserter(m_conferenceList));	
		int i = 0;
		for ( list<ConferenceStatusEx>::reverse_iterator iter = returnInfo.result.rbegin(); iter != returnInfo.result.rend(); ++iter)
		{
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
		m_showPan.SetWindowText(_T("查询已调度会议的状态成功"));
	} 
	else
	{
		CString s; 
		s.Format("查询已调度会议的状态失败；返回码：%d",returnInfo.resultCode);
		m_showPan.SetWindowText(s);
	}
}


ConferenceStatusEx CHoldMultiConfDlg::GetChoosedConferencesItem()
{
	ConferenceStatusEx choosedConference;
	choosedConference.id = "";
	m_ChoosedConferences.clear();
	if ( m_listConference.GetItemCount() > 0 )
	{

		for ( int i = 0; i < m_listConference.GetItemCount(); i++ )
		{
			//int iMaxCount = m_conferenceList.size() - 1;
			if ( m_listConference.GetCheck(i) )
			{
				std::string cstrConfId = m_listConference.GetItemText(i, 0).GetBuffer();
				if ( cstrConfId == m_conferenceList[m_iLastChoosedItem].id )
				{
					choosedConference.id = m_conferenceList[m_iLastChoosedItem].id;
					choosedConference.name = m_conferenceList[m_iLastChoosedItem].name;
					choosedConference.status = m_conferenceList[m_iLastChoosedItem].status;
					choosedConference.chair = m_conferenceList[m_iLastChoosedItem].chair;
					choosedConference.broadcast = m_conferenceList[m_iLastChoosedItem].broadcast;
					choosedConference.speaking = m_conferenceList[m_iLastChoosedItem].speaking;
					choosedConference.presentation = m_conferenceList[m_iLastChoosedItem].presentation;
					choosedConference.isLock = m_conferenceList[m_iLastChoosedItem].isLock;
					choosedConference.isAudioSwitch = m_conferenceList[m_iLastChoosedItem].isAudioSwitch;
					choosedConference.switchGate = m_conferenceList[m_iLastChoosedItem].switchGate;
					choosedConference.beginTime = m_conferenceList[m_iLastChoosedItem].beginTime;
					choosedConference.endTime = m_conferenceList[m_iLastChoosedItem].endTime;
					choosedConference.isLockPresentation = m_conferenceList[m_iLastChoosedItem].isLockPresentation;
					choosedConference.recording = m_conferenceList[m_iLastChoosedItem].recording;
					choosedConference.conferenceMode = m_conferenceList[m_iLastChoosedItem].conferenceMode;
					return choosedConference;
				}
			}
		}
	}
	return choosedConference;
}

void CHoldMultiConfDlg::OnBnClickedButtonGetConfSites()
{
	// TODO: Add your control notification handler code here
	m_listSitesInConf.DeleteAllItems();
	ConferenceStatusEx beChoosedConf = GetChoosedConferencesItem();
	if ( beChoosedConf.id  != "" )
	{
		list<std::string> siteUris;
		TPSDKResponseEx<list<SiteStatusEx>> response = queryConfSitesStatusEx( beChoosedConf.id, siteUris );
		if ( 0 == response.resultCode )
		{

			for ( list<SiteStatusEx>::iterator iter = response.result.begin(); iter != response.result.end(); ++iter )
			{
				int i = m_listSitesInConf.GetItemCount();
				m_listSitesInConf.InsertItem(i,iter->uri.c_str());
				m_listSitesInConf.SetItemText( i, 1, iter->name.c_str());
				CString cstrTemp;
				cstrTemp.Format( "%d", iter->type );
				m_listSitesInConf.SetItemText( i, 2, cstrTemp );	//类型
				if ( iter->status == 2 )
				{
					cstrTemp.Format( "会议中" );
				} 
				else
				{
					cstrTemp.Format( "未入会" );
				}

				m_listSitesInConf.SetItemText( i, 3, cstrTemp );	//会场状态
			}
			m_showPan.SetWindowText(_T("查询会议的会场成功"));
		} 
		else
		{
			CString cstrShowMsg;
			cstrShowMsg.Format("查询会议的会场失败，失败码=%d", response.resultCode);
			m_showPan.SetWindowText(cstrShowMsg);
		}
	}
	else
	{
		m_showPan.SetWindowText(_T("请选择要查询的会议"));
	}
}


void CHoldMultiConfDlg::OnBnClickedBtnQuerySites()
{
	// TODO: Add your control notification handler code here
	UpdateSiteList();
}


void CHoldMultiConfDlg::UpdateSiteList()
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
			str.Format("%s",i->rate.c_str());
			m_sitesInfoList.SetItemText(j,3,str);
			j++;
		}
	}
}

void CHoldMultiConfDlg::OnBnClickedBtnCreateconf()
{
	// TODO: Add your control notification handler code here
	vector<int> indexTemp;
	for (int i=0;i<m_sitesInfoList.GetItemCount();++i)
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
		if ( m_accessCode.Trim().IsEmpty() == false )
		{
			scheduleConf.accessCode = m_accessCode.GetBuffer();
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

		for (int j=0;j<indexTemp.size();++j)
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
				m_showPan.SetWindowText(s.GetBuffer());
			} 
			else
			{
				CString s; 
				s.Format("创建会议失败；返回码：%d",confInfoReturn.resultCode);
				m_showPan.SetWindowText(s.GetBuffer());
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
				m_showPan.SetWindowText(s.GetBuffer());
			} 
			else
			{
				CString s; 
				s.Format("创建会议失败；返回码：%d",response.resultCode);
				m_showPan.SetWindowText(s.GetBuffer());
			}
		}
	}
	else
	{
		m_showPan.SetWindowText( _T("请先勾选要参与会议的会场"));
	}
}


void CHoldMultiConfDlg::OnNMClickListConf(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//获取单击所在的行号   
	//找出鼠标位置   
	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_listConference.ScreenToClient(&point);  
	//定义结构体   
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//获取行号信息   
	int nItem = m_listConference.HitTest(&lvinfo);  
	if(nItem != -1)  
	{
		//判断是否点击在CheckBox上   
		if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
		{
			m_listConfBeHit = TRUE;  
			m_listConfItemSel = lvinfo.iItem;   //当前行号   
		}
	}

	*pResult = 0;
}


void CHoldMultiConfDlg::OnBnClickedCheckRecurrenceConf()
{
	// TODO: Add your control notification handler code here
	if(BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK_RECURRENCE_CONF))->GetCheck())
	{
		m_cmbRecurrenceConfFrequency.EnableWindow(FALSE);
		m_editRecurrenceConfCount.EnableWindow(FALSE);
		m_editRecurrenceConfInterval.EnableWindow(FALSE);
	}
	else
	{
		m_cmbRecurrenceConfFrequency.EnableWindow(TRUE);
		//GetDlgItem(IDC_EDIT_ACCESSCODE)->EnableWindow(FALSE);
		m_editRecurrenceConfCount.EnableWindow(TRUE);
		m_editRecurrenceConfInterval.EnableWindow(TRUE);
	}
}


void CHoldMultiConfDlg::OnNMRClickListConf(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_listConference.ScreenToClient(&point);  
	//定义结构体   
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//获取行号信息   
	int nItem = m_listConference.HitTest(&lvinfo);  
	if(nItem != -1)  
	{
		//判断是否点击在CheckBox上   
		if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
		{
			m_listConfBeHit = TRUE;  
			m_listConfItemSel = lvinfo.iItem;   //当前行号   
		}
	}
	*pResult = 0;
}


void CHoldMultiConfDlg::OnLvnItemchangedListConf(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	int ibak = -1;
	if(TRUE == m_listConfBeHit)  
	{  
		m_listConfBeHit = FALSE;     //复位   

		if(TRUE == m_listConference.GetCheck(m_listConfItemSel))  
		{       //CheckBox被选中   
			//do your own processing  
			ibak = m_iLastChoosedItem;
			m_iLastChoosedItem = m_listConfItemSel;
			m_listConference.SetItemState(m_listConfItemSel, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
		}  
		else  
		{      //CheckBox取消选择   
			//do your own processing 
			int iBAK = m_iLastChoosedItem;
			m_iLastChoosedItem = -1;
		}  
	}  
	if ( -1 != ibak)
	{
		m_listConference.SetCheck( ibak, FALSE );
	}
	*pResult = 0;
}


void CHoldMultiConfDlg::OnNMDblclkListConf(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_listConference.ScreenToClient(&point);  
	//定义结构体   
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//获取行号信息   
	int nItem = m_listConference.HitTest(&lvinfo);  
	if(nItem != -1)  
	{
		//判断是否点击在CheckBox上   
		if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
		{
			m_listConfBeHit = TRUE;  
			m_listConfItemSel = lvinfo.iItem;   //当前行号   
		}
	}
	*pResult = 0;
}


void CHoldMultiConfDlg::OnNMRDblclkListConf(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_listConference.ScreenToClient(&point);  
	//定义结构体   
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//获取行号信息   
	int nItem = m_listConference.HitTest(&lvinfo);  
	if(nItem != -1)  
	{
		//判断是否点击在CheckBox上   
		if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
		{
			m_listConfBeHit = TRUE;  
			m_listConfItemSel = lvinfo.iItem;   //当前行号   
		}
	}
	*pResult = 0;
}
