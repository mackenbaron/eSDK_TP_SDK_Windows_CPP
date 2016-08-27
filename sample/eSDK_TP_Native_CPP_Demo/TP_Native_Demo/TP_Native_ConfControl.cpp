// TP_Native_ConfControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_ConfControl.h"
#include "afxdialogex.h"


// CTP_Native_ConfControlDlg dialog

IMPLEMENT_DYNAMIC(CTP_Native_ConfControlDlg, CPropertyPage)

	CTP_Native_ConfControlDlg::CTP_Native_ConfControlDlg()
	: CPropertyPage(CTP_Native_ConfControlDlg::IDD)
	, m_confID(_T(""))
	, m_siteUri(_T(""))
	, m_videoSourceUri(_T(""))
	, m_swtichGate(_T(""))
	, m_broadcastSiteUri(_T(""))
	, m_chairmanUri(_T(""))
	, m_setSiteUri(_T(""))
	, m_target(_T(""))
	, m_volume(_T(""))
	, m_sitemarkUri(_T(""))
{
	m_num = 0;
	m_numVolume = 0;
}

CTP_Native_ConfControlDlg::~CTP_Native_ConfControlDlg()
{
}

void CTP_Native_ConfControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_confID);
	DDX_Text(pDX, IDC_EDIT3, m_siteUri);
	DDX_Text(pDX, IDC_EDIT2, m_videoSourceUri);
	DDX_Text(pDX, IDC_EDIT4, m_swtichGate);
	DDX_Text(pDX, IDC_EDIT5, m_broadcastSiteUri);
	DDX_Text(pDX, IDC_EDIT6, m_chairmanUri);
	DDX_Text(pDX, IDC_EDIT7, m_setSiteUri);
	DDX_Control(pDX, IDC_LIST2, m_siteList);
	DDX_Text(pDX, IDC_EDIT9, m_target);
	DDX_Control(pDX, IDC_COMBO1, m_isSwitch);
	DDX_Control(pDX, IDC_COMBO2, m_isBroadcast);
	DDX_Control(pDX, IDC_COMBO3, m_moreIsBroadcast);
	DDX_Control(pDX, IDC_COMBO4, m_isMute);
	DDX_Control(pDX, IDC_COMBO5, m_isQuiet);
	DDX_Text(pDX, IDC_EDIT11, m_volume);
	DDX_Text(pDX, IDC_EDIT8, m_sitemarkUri);
	DDX_Control(pDX, IDC_COMBO_CONTINUOUS_PRESENCE_MODE, m_cmbContinuousPresenceMode);
}


BEGIN_MESSAGE_MAP(CTP_Native_ConfControlDlg, CPropertyPage)
	
	ON_BN_CLICKED(IDC_BUTTON1, &CTP_Native_ConfControlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTP_Native_ConfControlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTP_Native_ConfControlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTP_Native_ConfControlDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CTP_Native_ConfControlDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTP_Native_ConfControlDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CTP_Native_ConfControlDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON11, &CTP_Native_ConfControlDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON13, &CTP_Native_ConfControlDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON12, &CTP_Native_ConfControlDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON14, &CTP_Native_ConfControlDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON5, &CTP_Native_ConfControlDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON15, &CTP_Native_ConfControlDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON8, &CTP_Native_ConfControlDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON16, &CTP_Native_ConfControlDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON18, &CTP_Native_ConfControlDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON10, &CTP_Native_ConfControlDlg::OnBnClickedButton10)
END_MESSAGE_MAP()




BOOL CTP_Native_ConfControlDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_isSwitch.InsertString(0,_T("启用声控切换"));
	m_isSwitch.InsertString(1,_T("关闭声控切换"));
	m_isSwitch.SetCurSel(0);

	m_isBroadcast.InsertString(0,_T("开始广播会场"));
	m_isBroadcast.InsertString(1,_T("停止广播会场"));
	m_isBroadcast.SetCurSel(0);

	m_moreIsBroadcast.InsertString(0,_T("开始广播多画面"));
	m_moreIsBroadcast.InsertString(1,_T("停止广播多画面"));
	m_moreIsBroadcast.SetCurSel(0);

	m_isMute.InsertString(0,_T("闭音"));
	m_isMute.InsertString(1,_T("不闭音"));
	m_isMute.SetCurSel(0);

	m_isQuiet.InsertString(0,_T("静音"));
	m_isQuiet.InsertString(1,_T("不静音"));
	m_isQuiet.SetCurSel(0);

	// TODO:  Add extra initialization here
	LONG lStyle;
	lStyle = GetWindowLong(m_siteList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_siteList.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_siteList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_siteList.SetExtendedStyle(dwStyle); //设置扩展风格
	m_siteList.InsertColumn( 0, "URI/标识", LVCFMT_LEFT, 500 );    //插入列

	m_cmbContinuousPresenceMode.AddString("CP_None");
	m_cmbContinuousPresenceMode.AddString("CP_1_1");
	m_cmbContinuousPresenceMode.AddString("CP_2_1");
	m_cmbContinuousPresenceMode.AddString("CP_2_2");
	m_cmbContinuousPresenceMode.AddString("CP_2_3");
	m_cmbContinuousPresenceMode.AddString("CP_3_1");
	m_cmbContinuousPresenceMode.AddString("CP_3_2");
	m_cmbContinuousPresenceMode.AddString("CP_3_3");
	m_cmbContinuousPresenceMode.AddString("CP_3_4");
	m_cmbContinuousPresenceMode.AddString("CP_3_5");
	m_cmbContinuousPresenceMode.AddString("CP_3_6");
	m_cmbContinuousPresenceMode.AddString("CP_4_1");
	m_cmbContinuousPresenceMode.AddString("CP_4_2");
	m_cmbContinuousPresenceMode.AddString("CP_4_3");
	m_cmbContinuousPresenceMode.AddString("CP_4_4");
	m_cmbContinuousPresenceMode.AddString("CP_4_5");
	m_cmbContinuousPresenceMode.AddString("CP_4_6");
	m_cmbContinuousPresenceMode.AddString("CP_5_1");
	m_cmbContinuousPresenceMode.AddString("CP_5_2");
	m_cmbContinuousPresenceMode.AddString("CP_5_3");
	m_cmbContinuousPresenceMode.AddString("CP_5_4");
	m_cmbContinuousPresenceMode.AddString("CP_6_1");
	m_cmbContinuousPresenceMode.AddString("CP_6_2");
	m_cmbContinuousPresenceMode.AddString("CP_6_3");
	m_cmbContinuousPresenceMode.AddString("CP_6_4");
	m_cmbContinuousPresenceMode.AddString("CP_6_5");
	m_cmbContinuousPresenceMode.AddString("CP_7_1");
	m_cmbContinuousPresenceMode.AddString("CP_7_2");
	m_cmbContinuousPresenceMode.AddString("CP_7_3");
	m_cmbContinuousPresenceMode.AddString("CP_7_4");
	m_cmbContinuousPresenceMode.AddString("CP_7_5");
	m_cmbContinuousPresenceMode.AddString("CP_8_1");
	m_cmbContinuousPresenceMode.AddString("CP_8_2");
	m_cmbContinuousPresenceMode.AddString("CP_8_3");
	m_cmbContinuousPresenceMode.AddString("CP_8_4");
	m_cmbContinuousPresenceMode.AddString("CP_9_1");
	m_cmbContinuousPresenceMode.AddString("CP_10_1");
	m_cmbContinuousPresenceMode.AddString("CP_10_2");
	m_cmbContinuousPresenceMode.AddString("CP_10_3");
	m_cmbContinuousPresenceMode.AddString("CP_10_4");
	m_cmbContinuousPresenceMode.AddString("CP_10_5");
	m_cmbContinuousPresenceMode.AddString("CP_10_6");
	m_cmbContinuousPresenceMode.AddString("CP_13_1");
	m_cmbContinuousPresenceMode.AddString("CP_13_2");
	m_cmbContinuousPresenceMode.AddString("CP_13_3");
	m_cmbContinuousPresenceMode.AddString("CP_13_4");
	m_cmbContinuousPresenceMode.AddString("CP_13_5");
	m_cmbContinuousPresenceMode.AddString("CP_16_1");
	m_cmbContinuousPresenceMode.AddString("CP_20_1");
	m_cmbContinuousPresenceMode.AddString("CP_24_1");
	m_cmbContinuousPresenceMode.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTP_Native_ConfControlDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	std::string sitUri;
	std::string videoSourceUri;
	UpdateData(TRUE);
	confID = m_confID;
	sitUri = m_siteUri;
	videoSourceUri = m_videoSourceUri;
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


void CTP_Native_ConfControlDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	int switchGate;
	int isSwitch;
	CString str;
	UpdateData(TRUE);
	confID = m_confID;
	switchGate = _ttoi(m_swtichGate);
	int nIndex = m_isSwitch.GetCurSel();
	if(nIndex !=CB_ERR)
	{
		m_isSwitch.GetLBText(nIndex , str);
	}
	if(!str.Compare(_T("启用声控切换")))
	{
		isSwitch = 1;
	}
	else
	{
		isSwitch = 0;
	}
	int resultCode= setAudioSwitchEx(confID, switchGate,isSwitch);
	if (resultCode==0)
	{
		if ( 1 == isSwitch )
		{
			AfxMessageBox("启用会议的声控切换成功");
		}
		else
		{
			AfxMessageBox("关闭会议的声控切换成功");
		}
	} 
	else
	{
		char result[1024] = {0};
		if ( 1 == isSwitch )
		{
			sprintf_s(result,1023,"启用会议的声控切换失败；返回码：%d",resultCode);
		}
		else if ( 0 == isSwitch )
		{
			sprintf_s(result,1023,"关闭会议的声控切换失败；返回码：%d",resultCode);
		}
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ( m_broadcastSiteUri =="" || m_confID == "" )
	{
		SetDlgItemText(IDC_STATIC_BROADCAST_REST, _T("请先填写要广播的会场URI或会议ID"));
	} 
	else
	{
		std::string confId = m_confID.GetBuffer();
		std::string siteUri = m_broadcastSiteUri.GetBuffer();
		int resultCode =setBroadcastSiteEx( confId, siteUri, m_isBroadcast.GetCurSel() );
		if (resultCode == 0)
		{
			if ( 0 == m_isBroadcast.GetCurSel() )
			{
				AfxMessageBox("广播成功");
			}
			else if ( 1 == m_isBroadcast.GetCurSel() )
			{
				AfxMessageBox("关闭广播成功");
			}
		}
		else
		{
			char result[1024] = {0};
			if ( 0 == m_isBroadcast.GetCurSel() )
			{
				sprintf_s(result,1023,"广播失败，返回码：%d",resultCode);
			}
			else if ( 1 == m_isBroadcast.GetCurSel() )
			{
				sprintf_s(result,1023,"关闭广播失败，返回码：%d",resultCode);
			}
			AfxMessageBox(result);
		}
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	int isBroadCast;
	CString str;
	UpdateData(TRUE);
	confID = m_confID;
	int nIndex = m_moreIsBroadcast.GetCurSel();
	if(nIndex !=CB_ERR)
	{
		m_moreIsBroadcast.GetLBText(nIndex , str);
	}
	if(!str.Compare(_T("开始广播多画面")))
	{
		isBroadCast = 0;
	}
	else
	{
		isBroadCast = 1;
	}
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


void CTP_Native_ConfControlDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	std::string chairmanUri;
	UpdateData(TRUE);
	confID = m_confID;
	chairmanUri = m_chairmanUri;
	int resultCode= requestConfChairEx(confID, chairmanUri);
	if (resultCode==0)
	{
		AfxMessageBox("申请主席成功");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"申请主席失败；返回码：%d",resultCode);
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	std::string setSiteUri;
	std::string confID;
	UpdateData(TRUE);
	confID = m_confID;
	setSiteUri = m_setSiteUri;
	int resultCode= setFloorEx(confID,setSiteUri);
	if (resultCode==0)
	{
		AfxMessageBox("指定会场发言成功");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"指定会场发言失败；返回码：%d",resultCode);
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	std::string setSiteUri;
	std::string confID;
	std::string str;
	UpdateData(TRUE);
	confID = m_confID;
	list<std::string> siteUris;
	for(int i = 0;i<m_siteList.GetItemCount();i++)
	{
		if(m_siteList.GetCheck(i))
		{
			str = m_siteList.GetItemText(i,0);
			siteUris.push_back(str);
		}
	}
	int resultCode= displayConfSiteLocalVideoEx(confID, siteUris);
	if (resultCode==0)
	{
		AfxMessageBox("打开会议中会场的视频成功");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"打开会议中会场的视频失败；返回码：%d",resultCode);
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton11()
{
	// TODO: Add your control notification handler code here
	std::string confID = m_confID;
	std::string sitURI = m_setSiteUri;
	UpdateData(TRUE);

	int resultCode= lockPresentationEx(confID, sitURI);
	if (resultCode==0)
	{
		AfxMessageBox("锁定的演示者令牌成功");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"锁定的演示者令牌失败；返回码：%d",resultCode);
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton13()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	UpdateData(TRUE);
	confID = m_confID;
	int resultCode=  unlockPresentationEx(confID);
	if (resultCode==0)
	{
		AfxMessageBox("解锁的演示者令牌成功");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"解锁的演示者令牌失败；返回码：%d",resultCode);
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton12()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	UpdateData(TRUE);
	confID = m_confID;
	int resultCode= releaseConfChairEx(confID);
	if (resultCode==0)
	{
		AfxMessageBox("释放主席成功");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"释放主席失败；返回码：%d",resultCode);
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton14()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(!m_sitemarkUri.Compare("")||!m_temp.Compare(m_sitemarkUri))
	{
		AfxMessageBox("为空或者重复");
	}
	else
	{
		m_siteList.InsertItem(m_num,m_sitemarkUri.GetBuffer());
		m_temp = m_sitemarkUri;
		m_num ++;
	}
	
}


void CTP_Native_ConfControlDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	std::string siteURI;
	CString str;
	int isMute;
	UpdateData(TRUE);
	list<std::string> siteUris;
	confID = m_confID;
	for(int i = 0;i<m_siteList.GetItemCount();i++)
	{
		if(m_siteList.GetCheck(i))
		{
			siteURI = m_siteList.GetItemText(i,0);
			siteUris.push_back(siteURI);
		}
	}
	int nIndex = m_isMute.GetCurSel();
	if(nIndex !=CB_ERR)
	{
		m_isMute.GetLBText(nIndex , str);
	}
	if(!str.Compare(_T("闭音")))
	{
		isMute = 0;
	}
	else
	{
		isMute = 1;
	}
	int resultCode= setSitesMuteEx(confID, siteUris, isMute);
	if (resultCode==0)
	{
		if ( 0 == isMute )
		{
			AfxMessageBox("指定会场闭音成功");
		}
		else
		{
			AfxMessageBox("指定会场不闭音成功");
		}
	} 
	else
	{
		char result[1024] = {0};
		if ( 0 == isMute )
		{
			sprintf_s(result,1023,"指定会场闭音失败；返回码：%d",resultCode);
		}
		else
		{
			sprintf_s(result,1023,"指定会场不闭音失败；返回码：%d",resultCode);
		}
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton15()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	std::string siteURI;
	CString str;
	int isQuiet;
	UpdateData(TRUE);
	confID = m_confID;
	list<std::string> siteUris;
	for(int i = 0;i<m_siteList.GetItemCount();i++)
	{
		if(m_siteList.GetCheck(i))
		{
			siteURI = m_siteList.GetItemText(i,0);
			siteUris.push_back(siteURI);
		}
	}
	int nIndex = m_isQuiet.GetCurSel();
	if(nIndex !=CB_ERR)
	{
		m_isQuiet.GetLBText(nIndex , str);
	}
	if(!str.Compare(_T("静音")))
	{
		isQuiet = 0;
	}
	else
	{
		isQuiet = 1;
	}

	int resultCode= setSitesQuietEx(confID, siteUris,isQuiet);
	if (resultCode==0)
	{
		if ( 0 == isQuiet )
		{
			AfxMessageBox("指定会场静音成功");
		}
		else
		{
			AfxMessageBox("指定会场不静音成功");
		}
		
	} 
	else
	{
		char result[1024] = {0};
		if ( 0 == isQuiet )
		{
			sprintf_s(result,1023,"指定会场静音失败；返回码：%d",resultCode);
		}
		else
		{
			sprintf_s(result,1023,"指定会场不静音失败；返回码：%d",resultCode);
		}
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	std::string siteURI;
	CString volume;
	UpdateData(TRUE);
	if ( m_confID == "" )
	{
		AfxMessageBox(_T("请输入会议ID"));
		return;
	}
	confID = m_confID;
	list<SiteVolumeEx> siteVolumes;
	SiteVolumeEx sv;
	for(int i = 0;i<m_siteList.GetItemCount();i++)
	{
		if(m_siteList.GetCheck(i))
		{
			siteURI = m_siteList.GetItemText(i,0);
			//volume = m_siteList.GetItemText(i,1);
			sv.siteUri = siteURI;
			sv.volume = _ttoi(m_volume);
			siteVolumes.push_back(sv);
		}
	}
	if ( siteVolumes.size() == 0 )
	{
		AfxMessageBox(_T("请选择会场"));
		return;
	}
	int resultCode= setConfSiteVolumeEx(confID, siteVolumes);
	if (resultCode==0)
	{
		AfxMessageBox("设置会场音量值成功");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"设置会场音量值失败；返回码：%d",resultCode);
		AfxMessageBox(result);
	}
}


//void CTP_Native_ConfControlDlg::OnBnClickedButton17()
//{
//	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
//	if(!m_siteList.GetItemCount())
//	{
//		AfxMessageBox("没有添加URI");
//	}
//	else
//	{
//		m_siteList.SetItemText(m_num-1,1,m_volume);
//	}
//}


void CTP_Native_ConfControlDlg::OnBnClickedButton16()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	std::string target;
	std::string str;
	UpdateData(TRUE);
	confID = m_confID;
	target = m_target;
	int mode = m_cmbContinuousPresenceMode.GetCurSel();
	list<std::string> subPics;
	for(int i = 0;i<m_siteList.GetItemCount();i++)
	{
		if(m_siteList.GetCheck(i))
		{
			str = m_siteList.GetItemText(i,0);
			subPics.push_back(str);
		}
	}
	int resultCode= setContinuousPresenceEx(confID,target, mode,subPics);
	if (resultCode==0)
	{
		AfxMessageBox("设置多画面参数成功");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"设置多画面参数失败；返回码：%d",resultCode);
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton18()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	for(int i = 0;i<m_siteList.GetItemCount();i++)
	{
		if(m_siteList.GetCheck(i))
		{
			m_siteList.DeleteItem(i);
			m_num --;
		}
	}
	m_temp.Format("");
	m_tempVolume.Format("");
}


void CTP_Native_ConfControlDlg::OnBnClickedButton10()
{
	// TODO: Add your control notification handler code here
	std::string confID;
	std::string str;
	UpdateData(TRUE);
	confID = m_confID;
	list<std::string> siteUris;
	for(int i = 0;i<m_siteList.GetItemCount();i++)
	{
		if(m_siteList.GetCheck(i))
		{
			str = m_siteList.GetItemText(i,0);
			siteUris.push_back(str);
		}
	}
	int resultCode= hideConfSiteLocalVideoEx(confID, siteUris);
	if (resultCode==0)
	{
		AfxMessageBox("关闭会议中会场的视频成功");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"关闭会议中会场的视频失败；返回码：%d",resultCode);
		AfxMessageBox(result);
	}
}
