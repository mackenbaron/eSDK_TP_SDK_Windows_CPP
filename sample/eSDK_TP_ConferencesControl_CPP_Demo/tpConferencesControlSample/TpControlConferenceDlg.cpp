// TpControlConferenceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tpConferencesControlSample.h"
#include "TpControlConferenceDlg.h"
#include "afxdialogex.h"

unsigned int __stdcall ThreadFunc(void* para)
{
	if (NULL == para)
	{
		return TP_E_RET_CODE_FAIL;
	}

	CTpControlConferenceDlg* instance = (CTpControlConferenceDlg*)para;
	instance->KeepAlive();
	return TP_E_RET_CODE_SUCCESS;
}

// CTpControlConferenceDlg dialog

IMPLEMENT_DYNAMIC(CTpControlConferenceDlg, CDialogEx)

CTpControlConferenceDlg::CTpControlConferenceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTpControlConferenceDlg::IDD, pParent)
{
	m_run = true;
	m_thread = NULL;
	m_threadID = NULL;
}

CTpControlConferenceDlg::~CTpControlConferenceDlg()
{
}

void CTpControlConferenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, m_editConfId);
	DDX_Control(pDX, IDC_EDIT1, m_editSiteUri);
	DDX_Control(pDX, IDC_EDIT2, m_editVideoSourceUri);
	DDX_Control(pDX, IDC_EDIT3, m_editTarget);
	DDX_Control(pDX, IDC_COMBO2, m_cbbPresenceMode);
	DDX_Control(pDX, IDC_COMBO1, m_cbbIsBroadcast);
	DDX_Control(pDX, IDC_LIST1, m_listSitesStatus);
}


BEGIN_MESSAGE_MAP(CTpControlConferenceDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CTpControlConferenceDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CTpControlConferenceDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTpControlConferenceDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CTpControlConferenceDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON4, &CTpControlConferenceDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTpControlConferenceDlg message handlers


void CTpControlConferenceDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	StopMsgRetrieval();
	KillTimer(1);
	int iRet = logout();
	if ( 0 == iRet )
	{
		CDialogEx::OnCancel();
	} 
	else
	{
		AfxMessageBox(_T("登出失败"));
	}

}


BOOL CTpControlConferenceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	m_cbbPresenceMode.AddString("CP_None");
	m_cbbPresenceMode.AddString("CP_1_1");
	m_cbbPresenceMode.AddString("CP_2_1");
	m_cbbPresenceMode.AddString("CP_2_2");
	m_cbbPresenceMode.AddString("CP_2_3");
	m_cbbPresenceMode.AddString("CP_3_1");
	m_cbbPresenceMode.AddString("CP_3_2");
	m_cbbPresenceMode.AddString("CP_3_3");
	m_cbbPresenceMode.AddString("CP_3_4");
	m_cbbPresenceMode.AddString("CP_3_5");
	m_cbbPresenceMode.AddString("CP_3_6");
	m_cbbPresenceMode.AddString("CP_4_1");
	m_cbbPresenceMode.AddString("CP_4_2");
	m_cbbPresenceMode.AddString("CP_4_3");
	m_cbbPresenceMode.AddString("CP_4_4");
	m_cbbPresenceMode.AddString("CP_4_5");
	m_cbbPresenceMode.AddString("CP_4_6");
	m_cbbPresenceMode.AddString("CP_5_1");
	m_cbbPresenceMode.AddString("CP_5_2");
	m_cbbPresenceMode.AddString("CP_5_3");
	m_cbbPresenceMode.AddString("CP_5_4");
	m_cbbPresenceMode.AddString("CP_6_1");
	m_cbbPresenceMode.AddString("CP_6_2");
	m_cbbPresenceMode.AddString("CP_6_3");
	m_cbbPresenceMode.AddString("CP_6_4");
	m_cbbPresenceMode.AddString("CP_6_5");
	m_cbbPresenceMode.AddString("CP_7_1");
	m_cbbPresenceMode.AddString("CP_7_2");
	m_cbbPresenceMode.AddString("CP_7_3");
	m_cbbPresenceMode.AddString("CP_7_4");
	m_cbbPresenceMode.AddString("CP_7_5");
	m_cbbPresenceMode.AddString("CP_8_1");
	m_cbbPresenceMode.AddString("CP_8_2");
	m_cbbPresenceMode.AddString("CP_8_3");
	m_cbbPresenceMode.AddString("CP_8_4");
	m_cbbPresenceMode.AddString("CP_9_1");
	m_cbbPresenceMode.AddString("CP_10_1");
	m_cbbPresenceMode.AddString("CP_10_2");
	m_cbbPresenceMode.AddString("CP_10_3");
	m_cbbPresenceMode.AddString("CP_10_4");
	m_cbbPresenceMode.AddString("CP_10_5");
	m_cbbPresenceMode.AddString("CP_10_6");
	m_cbbPresenceMode.AddString("CP_13_1");
	m_cbbPresenceMode.AddString("CP_13_2");
	m_cbbPresenceMode.AddString("CP_13_3");
	m_cbbPresenceMode.AddString("CP_13_4");
	m_cbbPresenceMode.AddString("CP_13_5");
	m_cbbPresenceMode.AddString("CP_16_1");
	m_cbbPresenceMode.AddString("CP_20_1");
	m_cbbPresenceMode.AddString("CP_24_1");
	m_cbbPresenceMode.SetCurSel(0);

	m_cbbIsBroadcast.AddString("开始广播会场");
	m_cbbIsBroadcast.AddString("停止广播会场");
	m_cbbIsBroadcast.SetCurSel(0);

	m_listSitesStatus.InsertColumn(0, "URI", LVCFMT_LEFT, 60);
	m_listSitesStatus.InsertColumn(1,"会场名",LVCFMT_LEFT,80);
	m_listSitesStatus.InsertColumn(2,"会场状态",LVCFMT_LEFT,65);
	DWORD NewStyle = LVS_EX_GRIDLINES;
	m_listSitesStatus.SetExtendedStyle(NewStyle);
	SetTimer( 1, 19000, NULL );

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTpControlConferenceDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString cstrTemp;
	m_editConfId.GetWindowText(cstrTemp);
	std::string confID = cstrTemp.GetBuffer();
	m_editSiteUri.GetWindowText(cstrTemp);
	std::string sitUri = cstrTemp.GetBuffer();
	m_editVideoSourceUri.GetWindowText(cstrTemp);
	std::string videoSourceUri = cstrTemp.GetBuffer();
	int resultCode= setVideoSourceEx(confID, sitUri, videoSourceUri, 0);
	if (resultCode==0)
	{
		AfxMessageBox("设置指定会场的视频源成功");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"设置指定会场的视频源失败；返回码 : %d",resultCode);
		AfxMessageBox(result);
	}
}


void CTpControlConferenceDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CString cstrTemp;
	m_editConfId.GetWindowText(cstrTemp);
	std::string confId = cstrTemp.GetBuffer();
	m_editTarget.GetWindowText(cstrTemp);
	std::string target = cstrTemp.GetBuffer();
	int presenceMode = m_cbbPresenceMode.GetCurSel();
	//获得会场列表
	list<SiteStatusEx> sitesList = getConfAllSitesStatusEx( confId );
	list<std::string> subPics;
	for ( list<SiteStatusEx>::iterator iter = sitesList.begin(); iter != sitesList.end(); ++iter )
	{
		subPics.push_back(iter->uri);
	}
	int iRet = setContinuousPresenceEx(confId, target, presenceMode, subPics);
	if ( 0 == iRet )
	{
		AfxMessageBox(_T("设置多画面参数成功"));
	} 
	else
	{
		CString cstrShowMsg;
		cstrShowMsg.Format("查询会议的会场失败，失败码=%d", iRet);
		AfxMessageBox(cstrShowMsg);
	}
}


void CTpControlConferenceDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString cstrTemp;
	m_editConfId.GetWindowText(cstrTemp);
	std::string confID = cstrTemp.GetBuffer();
	int isBroadCast = m_cbbIsBroadcast.GetCurSel();

	int resultCode= setBroadcastContinuousPresenceEx(confID, isBroadCast);
	if (resultCode==0)
	{
		if ( 0 == isBroadCast )
		{
			AfxMessageBox("设置广播多画面成功");
		}
		else if ( 1 == isBroadCast )
		{
			AfxMessageBox("停止广播多画面成功");
		}
	} 
	else
	{
		char result[1024] = {0};
		if ( 0 == isBroadCast )
		{
			sprintf_s(result,1023,"设置广播多画面失败；返回码：%d",resultCode);
		}
		else if ( 1 == isBroadCast )
		{
			sprintf_s(result,1023,"停止广播多画面失败；返回码：%d",resultCode);
		}
		AfxMessageBox(result);
	}
}

list<SiteStatusEx> CTpControlConferenceDlg::getConfAllSitesStatusEx(std::string strConfId)
{
	list<std::string> siteUris;
	TPSDKResponseEx<list<SiteStatusEx>> response;
	response = queryConfSitesStatusEx( strConfId, siteUris );
	if ( 0 == response.resultCode )
	{
		return response.result;
	} 
	else
	{
		CString cstrShowMsg;
		cstrShowMsg.Format("查询会议的会场失败，失败码=%d", response.resultCode);
		return response.result;
	}
}

void CTpControlConferenceDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	StartMsgRetrieval();
	CDialogEx::OnTimer(nIDEvent);
}

void CTpControlConferenceDlg::StartMsgRetrieval()
{
	m_run = true;
	m_thread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (void*)this, 0, &m_threadID);
}

void CTpControlConferenceDlg::StopMsgRetrieval()
{
	if (NULL == m_thread)
	{
		return;
	}

	m_run = false;
	DWORD i = WaitForSingleObject(m_thread, INFINITE);
	m_thread = NULL;
}

void CTpControlConferenceDlg::KeepAlive()
{
	int ret = keepAlive();
}

void CTpControlConferenceDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CString cstrTemp;
	m_editConfId.GetWindowText(cstrTemp);
	std::string confId = cstrTemp.GetBuffer();
	list<SiteStatusEx> sitesList = getConfAllSitesStatusEx( confId );
	showSitesStatus(sitesList);
}

void CTpControlConferenceDlg::showSitesStatus(list<SiteStatusEx> &siteStatusList)
{
	m_listSitesStatus.DeleteAllItems();
	for ( list<SiteStatusEx>::iterator iter = siteStatusList.begin(); iter != siteStatusList.end(); ++iter )
	{
		int i = m_listSitesStatus.GetItemCount();
		m_listSitesStatus.InsertItem(i,iter->uri.c_str());
		m_listSitesStatus.SetItemText(i, 1, iter->name.c_str());
		switch (iter->status)
		{
		case 1:
			{
				m_listSitesStatus.SetItemText(i, 2, "会场不存在");
				break;
			}
		case 2:
			{
				m_listSitesStatus.SetItemText(i, 2, "在会议中");
				break;
			}
		case 3:
			{
				m_listSitesStatus.SetItemText(i, 2, "未入会");
				break;
			}
		case 4:
			{
				m_listSitesStatus.SetItemText(i, 2, "正在呼叫");
				break;
			}
		case 5:
			{
				m_listSitesStatus.SetItemText(i, 2, "正在振铃");
				break;
			}
		default:
			{
				m_listSitesStatus.SetItemText(i, 2, "未知状态");
				break;
			}
		}
	}
}