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
	m_isSwitch.InsertString(0,_T("���������л�"));
	m_isSwitch.InsertString(1,_T("�ر������л�"));
	m_isSwitch.SetCurSel(0);

	m_isBroadcast.InsertString(0,_T("��ʼ�㲥�᳡"));
	m_isBroadcast.InsertString(1,_T("ֹͣ�㲥�᳡"));
	m_isBroadcast.SetCurSel(0);

	m_moreIsBroadcast.InsertString(0,_T("��ʼ�㲥�໭��"));
	m_moreIsBroadcast.InsertString(1,_T("ֹͣ�㲥�໭��"));
	m_moreIsBroadcast.SetCurSel(0);

	m_isMute.InsertString(0,_T("����"));
	m_isMute.InsertString(1,_T("������"));
	m_isMute.SetCurSel(0);

	m_isQuiet.InsertString(0,_T("����"));
	m_isQuiet.InsertString(1,_T("������"));
	m_isQuiet.SetCurSel(0);

	// TODO:  Add extra initialization here
	LONG lStyle;
	lStyle = GetWindowLong(m_siteList.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_siteList.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_siteList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_siteList.SetExtendedStyle(dwStyle); //������չ���
	m_siteList.InsertColumn( 0, "URI/��ʶ", LVCFMT_LEFT, 500 );    //������

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
		AfxMessageBox("����ָ���᳡����ƵԴ�ɹ�");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"����ָ���᳡����ƵԴʧ�ܣ������� : %d",resultCode);
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
	if(!str.Compare(_T("���������л�")))
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
			AfxMessageBox("���û���������л��ɹ�");
		}
		else
		{
			AfxMessageBox("�رջ���������л��ɹ�");
		}
	} 
	else
	{
		char result[1024] = {0};
		if ( 1 == isSwitch )
		{
			sprintf_s(result,1023,"���û���������л�ʧ�ܣ������룺%d",resultCode);
		}
		else if ( 0 == isSwitch )
		{
			sprintf_s(result,1023,"�رջ���������л�ʧ�ܣ������룺%d",resultCode);
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
		SetDlgItemText(IDC_STATIC_BROADCAST_REST, _T("������дҪ�㲥�Ļ᳡URI�����ID"));
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
				AfxMessageBox("�㲥�ɹ�");
			}
			else if ( 1 == m_isBroadcast.GetCurSel() )
			{
				AfxMessageBox("�رչ㲥�ɹ�");
			}
		}
		else
		{
			char result[1024] = {0};
			if ( 0 == m_isBroadcast.GetCurSel() )
			{
				sprintf_s(result,1023,"�㲥ʧ�ܣ������룺%d",resultCode);
			}
			else if ( 1 == m_isBroadcast.GetCurSel() )
			{
				sprintf_s(result,1023,"�رչ㲥ʧ�ܣ������룺%d",resultCode);
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
	if(!str.Compare(_T("��ʼ�㲥�໭��")))
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
			AfxMessageBox("���ù㲥�໭��ɹ�");
		}
		else if ( 1 == isBroadCast )
		{
			AfxMessageBox("ֹͣ�㲥�໭��ɹ�");
		}
		
	} 
	else
	{
		char result[1024] = {0};
		if ( 0 == isBroadCast )
		{
			sprintf_s(result,1023,"���ù㲥�໭��ʧ�ܣ������룺%d",resultCode);
		}
		else if ( 1 == isBroadCast )
		{
			sprintf_s(result,1023,"ֹͣ�㲥�໭��ʧ�ܣ������룺%d",resultCode);
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
		AfxMessageBox("������ϯ�ɹ�");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"������ϯʧ�ܣ������룺%d",resultCode);
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
		AfxMessageBox("ָ���᳡���Գɹ�");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"ָ���᳡����ʧ�ܣ������룺%d",resultCode);
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
		AfxMessageBox("�򿪻����л᳡����Ƶ�ɹ�");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"�򿪻����л᳡����Ƶʧ�ܣ������룺%d",resultCode);
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
		AfxMessageBox("��������ʾ�����Ƴɹ�");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"��������ʾ������ʧ�ܣ������룺%d",resultCode);
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
		AfxMessageBox("��������ʾ�����Ƴɹ�");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"��������ʾ������ʧ�ܣ������룺%d",resultCode);
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
		AfxMessageBox("�ͷ���ϯ�ɹ�");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"�ͷ���ϯʧ�ܣ������룺%d",resultCode);
		AfxMessageBox(result);
	}
}


void CTP_Native_ConfControlDlg::OnBnClickedButton14()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(!m_sitemarkUri.Compare("")||!m_temp.Compare(m_sitemarkUri))
	{
		AfxMessageBox("Ϊ�ջ����ظ�");
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
	if(!str.Compare(_T("����")))
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
			AfxMessageBox("ָ���᳡�����ɹ�");
		}
		else
		{
			AfxMessageBox("ָ���᳡�������ɹ�");
		}
	} 
	else
	{
		char result[1024] = {0};
		if ( 0 == isMute )
		{
			sprintf_s(result,1023,"ָ���᳡����ʧ�ܣ������룺%d",resultCode);
		}
		else
		{
			sprintf_s(result,1023,"ָ���᳡������ʧ�ܣ������룺%d",resultCode);
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
	if(!str.Compare(_T("����")))
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
			AfxMessageBox("ָ���᳡�����ɹ�");
		}
		else
		{
			AfxMessageBox("ָ���᳡�������ɹ�");
		}
		
	} 
	else
	{
		char result[1024] = {0};
		if ( 0 == isQuiet )
		{
			sprintf_s(result,1023,"ָ���᳡����ʧ�ܣ������룺%d",resultCode);
		}
		else
		{
			sprintf_s(result,1023,"ָ���᳡������ʧ�ܣ������룺%d",resultCode);
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
		AfxMessageBox(_T("���������ID"));
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
		AfxMessageBox(_T("��ѡ��᳡"));
		return;
	}
	int resultCode= setConfSiteVolumeEx(confID, siteVolumes);
	if (resultCode==0)
	{
		AfxMessageBox("���û᳡����ֵ�ɹ�");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"���û᳡����ֵʧ�ܣ������룺%d",resultCode);
		AfxMessageBox(result);
	}
}


//void CTP_Native_ConfControlDlg::OnBnClickedButton17()
//{
//	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
//	if(!m_siteList.GetItemCount())
//	{
//		AfxMessageBox("û�����URI");
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
		AfxMessageBox("���ö໭������ɹ�");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"���ö໭�����ʧ�ܣ������룺%d",resultCode);
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
		AfxMessageBox("�رջ����л᳡����Ƶ�ɹ�");
	} 
	else
	{
		char result[1024] = {0};
		sprintf_s(result,1023,"�رջ����л᳡����Ƶʧ�ܣ������룺%d",resultCode);
		AfxMessageBox(result);
	}
}
