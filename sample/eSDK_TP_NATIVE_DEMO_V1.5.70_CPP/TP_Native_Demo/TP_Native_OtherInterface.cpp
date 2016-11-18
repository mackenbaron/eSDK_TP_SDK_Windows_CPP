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

// TP_Native_OtherInterface.cpp : implementation file
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_OtherInterface.h"
#include "afxdialogex.h"


// CTP_Native_OtherInterface dialog

IMPLEMENT_DYNAMIC(CTP_Native_OtherInterface, CPropertyPage)

CTP_Native_OtherInterface::CTP_Native_OtherInterface()
	: CPropertyPage(CTP_Native_OtherInterface::IDD)
	, m_confId(_T(""))
{

}

CTP_Native_OtherInterface::~CTP_Native_OtherInterface()
{
}

void CTP_Native_OtherInterface::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_confId);
}


BEGIN_MESSAGE_MAP(CTP_Native_OtherInterface, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CTP_Native_OtherInterface::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTP_Native_OtherInterface::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTP_Native_OtherInterface::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTP_Native_OtherInterface::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTP_Native_OtherInterface::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTP_Native_OtherInterface::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTP_Native_OtherInterface::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTP_Native_OtherInterface::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CTP_Native_OtherInterface::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CTP_Native_OtherInterface::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CTP_Native_OtherInterface::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CTP_Native_OtherInterface::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CTP_Native_OtherInterface::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CTP_Native_OtherInterface::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CTP_Native_OtherInterface::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CTP_Native_OtherInterface::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CTP_Native_OtherInterface::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CTP_Native_OtherInterface::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CTP_Native_OtherInterface::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CTP_Native_OtherInterface::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CTP_Native_OtherInterface::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CTP_Native_OtherInterface::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, &CTP_Native_OtherInterface::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CTP_Native_OtherInterface::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON25, &CTP_Native_OtherInterface::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, &CTP_Native_OtherInterface::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON27, &CTP_Native_OtherInterface::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &CTP_Native_OtherInterface::OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON29, &CTP_Native_OtherInterface::OnBnClickedButton29)
	ON_BN_CLICKED(IDC_BUTTON30, &CTP_Native_OtherInterface::OnBnClickedButton30)
	ON_BN_CLICKED(IDC_BUTTON31, &CTP_Native_OtherInterface::OnBnClickedButton31)
	ON_BN_CLICKED(IDC_BUTTON32, &CTP_Native_OtherInterface::OnBnClickedButton32)
	ON_BN_CLICKED(IDC_BUTTON33, &CTP_Native_OtherInterface::OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON34, &CTP_Native_OtherInterface::OnBnClickedButton34)
	ON_BN_CLICKED(IDC_BUTTON35, &CTP_Native_OtherInterface::OnBnClickedButton35)
	ON_BN_CLICKED(IDC_BUTTON36, &CTP_Native_OtherInterface::OnBnClickedButton36)
	ON_BN_CLICKED(IDC_BUTTON37, &CTP_Native_OtherInterface::OnBnClickedButton37)
	ON_BN_CLICKED(IDC_BUTTON38, &CTP_Native_OtherInterface::OnBnClickedButton38)
	ON_BN_CLICKED(IDC_BUTTON39, &CTP_Native_OtherInterface::OnBnClickedButton39)
	ON_BN_CLICKED(IDC_BUTTON40, &CTP_Native_OtherInterface::OnBnClickedButton40)
	ON_BN_CLICKED(IDC_BUTTON41, &CTP_Native_OtherInterface::OnBnClickedButton41)
	ON_BN_CLICKED(IDC_BUTTON42, &CTP_Native_OtherInterface::OnBnClickedButton42)
	ON_BN_CLICKED(IDC_BUTTON43, &CTP_Native_OtherInterface::OnBnClickedButton43)
	ON_BN_CLICKED(IDC_BUTTON44, &CTP_Native_OtherInterface::OnBnClickedButton44)
	ON_BN_CLICKED(IDC_BUTTON45, &CTP_Native_OtherInterface::OnBnClickedButton45)
	ON_BN_CLICKED(IDC_BUTTON46, &CTP_Native_OtherInterface::OnBnClickedButton46)
	ON_BN_CLICKED(IDC_BUTTON47, &CTP_Native_OtherInterface::OnBnClickedButton47)
	ON_BN_CLICKED(IDC_BUTTON48, &CTP_Native_OtherInterface::OnBnClickedButton48)
	ON_BN_CLICKED(IDC_BUTTON49, &CTP_Native_OtherInterface::OnBnClickedButton49)
	ON_BN_CLICKED(IDC_BUTTON50, &CTP_Native_OtherInterface::OnBnClickedButton50)
	ON_BN_CLICKED(IDC_BUTTON51, &CTP_Native_OtherInterface::OnBnClickedButton51)
	ON_BN_CLICKED(IDC_BUTTON52, &CTP_Native_OtherInterface::OnBnClickedButton52)
	ON_BN_CLICKED(IDC_BUTTON53, &CTP_Native_OtherInterface::OnBnClickedButton53)
	ON_BN_CLICKED(IDC_BUTTON54, &CTP_Native_OtherInterface::OnBnClickedButton54)
	ON_BN_CLICKED(IDC_BUTTON55, &CTP_Native_OtherInterface::OnBnClickedButton55)
	ON_BN_CLICKED(IDC_BUTTON56, &CTP_Native_OtherInterface::OnBnClickedButton56)
	ON_BN_CLICKED(IDC_BUTTON57, &CTP_Native_OtherInterface::OnBnClickedButton57)
	ON_BN_CLICKED(IDC_BUTTON58, &CTP_Native_OtherInterface::OnBnClickedButton58)
	ON_BN_CLICKED(IDC_BUTTON59, &CTP_Native_OtherInterface::OnBnClickedButton59)
	ON_BN_CLICKED(IDC_BUTTON60, &CTP_Native_OtherInterface::OnBnClickedButton60)
	ON_BN_CLICKED(IDC_BUTTON61, &CTP_Native_OtherInterface::OnBnClickedButton61)
	ON_BN_CLICKED(IDC_BUTTON62, &CTP_Native_OtherInterface::OnBnClickedButton62)
	ON_BN_CLICKED(IDC_BUTTON63, &CTP_Native_OtherInterface::OnBnClickedButton63)
	ON_BN_CLICKED(IDC_BUTTON64, &CTP_Native_OtherInterface::OnBnClickedButton64)
END_MESSAGE_MAP()


// CTP_Native_OtherInterface message handlers


void CTP_Native_OtherInterface::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<RecurrenceConfInfoEx> returnInfo;
	RecurrenceConfInfoEx scheduleConf;


	//��������
	scheduleConf.base_info.name ="RecurrenceConf";

	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,30, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);

	scheduleConf.base_info.beginTime = st;

	//����ʱ��
	/*int minutes = 30;
	int hours = minutes / 60;
	minutes = minutes - hours * 60;
	CString s; 
	s.Format("P0Y0M0DT%dH%dM0.000S", hours,minutes);
	scheduleConf.base_info.duration = s.GetBuffer();*/
	scheduleConf.base_info.duration="P0Y0M0DT1H0M0.000S";

	//����
	scheduleConf.base_info.rate = "1920k";

	scheduleConf.frequency=0;
	scheduleConf.interval=1;
	scheduleConf.count=5;

	scheduleConf.weekDay=1;
	//COleDateTime tT;
	tT.ParseDateTime("2015-11-28T12:00:00+08:00");
	//SYSTEMTIME st;
	tT.GetAsSystemTime(st);
	scheduleConf.endDate = st;

	SiteInfoEx siteInfo;
	siteInfo.rate="1920K";
	siteInfo.type = 4;
	siteInfo.videoProtocol = 1;
	siteInfo.from=0;
	siteInfo.dialingMode=0;
	siteInfo.videoFormat=0;
	siteInfo.videoProtocol=1;
	siteInfo.isLockVideoSource=1;
	siteInfo.participantType=1;
	siteInfo.status=0;

	siteInfo.uri="01010086";
	siteInfo.name="site1";
	scheduleConf.base_info.sites.push_back(siteInfo);

	siteInfo.uri="01010010";
	siteInfo.name="site2";
	scheduleConf.base_info.sites.push_back(siteInfo);

	////������
	scheduleConf.base_info.accessCode = "1404292";

	////����
	//if (m_confPwd.GetLength()>0)
	//{
	//	scheduleConf.password = m_confPwd.GetBuffer();
	//	scheduleConf.chairmanPassword = m_chairmanPwd.GetBuffer();
	//}
	////���ܷ�ʽ
	scheduleConf.base_info.mediaEncryptType = 0;
	////�໭��ģʽ
	scheduleConf.base_info.cpResouce = 0;
	////������Ƶ��ʽ
	scheduleConf.base_info.auxVideoFormat = 0;
	////��ƵЭ��
	scheduleConf.base_info.auxVideoProtocol =0;
	////����
	//CString strRate;
	//m_cb_rate.GetLBText(m_cb_rate.GetCurSel(),strRate);
	//scheduleConf.rate = strRate.GetBuffer();
	////��ʾ��ʽ
	scheduleConf.base_info.presentation = 0;
	scheduleConf.base_info.password = "123456";
	scheduleConf.base_info.chairmanPassword = "123456";
	scheduleConf.base_info.isLiveBroadcast=0;
	scheduleConf.base_info.isRecording=0;
	scheduleConf.base_info.status=0;
	scheduleConf.monthDay=1;
	scheduleConf.timeZone = "Asia/Shanghai";
	scheduleConf.weekDays.push_back(1);
	scheduleConf.weekDays.push_back(2);
	scheduleConf.weekDays.push_back(3);
	scheduleConf.weekDays.push_back(4);
	returnInfo=scheduleRecurrenceConferenceEx(scheduleConf);
	if (returnInfo.resultCode==0)
	{
		CString s; 
		s.Format("ԤԼ���ڻ���ɹ�������ID��%s",returnInfo.result.base_info.confId.c_str());
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	} 
	else
	{
		CString s; 
		s.Format("ԤԼ���ڻ���ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<ConferenceInfoEx> returnInfo;
	ConferenceInfoEx scheduleConf;
	UpdateData(TRUE);
	scheduleConf.confId=m_confId.GetBuffer();
	//��������
	scheduleConf.name ="editConf";

	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,30, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);

	scheduleConf.beginTime = st;

	//����ʱ��
	/*int minutes = 30;
	int hours = minutes / 60;
	minutes = minutes - hours * 60;
	CString s; 
	s.Format("P0Y0M0DT%dH%dM0.000S", hours,minutes);
	scheduleConf.base_info.duration = s.GetBuffer();*/
	scheduleConf.duration="P0Y0M0DT1H0M0.000S";

	//����
	scheduleConf.rate = "1920k";

	SiteInfoEx siteInfo;
	siteInfo.rate="1920K";
	siteInfo.type = 4;
	siteInfo.videoProtocol = 1;
	siteInfo.from=0;
	siteInfo.dialingMode=0;
	siteInfo.videoFormat=0;
	siteInfo.videoProtocol=1;
	siteInfo.isLockVideoSource=1;
	siteInfo.participantType=1;
	siteInfo.status=0;

	siteInfo.uri="01051801";
	siteInfo.name="site1";
	scheduleConf.sites.push_back(siteInfo);

	siteInfo.uri="01051802";
	siteInfo.name="site2";
	scheduleConf.sites.push_back(siteInfo);

	////������
	//scheduleConf.accessCode = "01051806";

	////����
	//if (m_confPwd.GetLength()>0)
	//{
	//	scheduleConf.password = m_confPwd.GetBuffer();
	//	scheduleConf.chairmanPassword = m_chairmanPwd.GetBuffer();
	//}
	////���ܷ�ʽ
	scheduleConf.mediaEncryptType = 0;
	////�໭��ģʽ
	scheduleConf.cpResouce = 0;
	////������Ƶ��ʽ
	scheduleConf.auxVideoFormat = 0;
	////��ƵЭ��
	scheduleConf.auxVideoProtocol =0;
	////����
	//CString strRate;
	//m_cb_rate.GetLBText(m_cb_rate.GetCurSel(),strRate);
	//scheduleConf.rate = strRate.GetBuffer();
	////��ʾ��ʽ
	scheduleConf.presentation = 0;
	scheduleConf.isLiveBroadcast=0;
	scheduleConf.isRecording=0;
	scheduleConf.status=0;

	returnInfo=editScheduledConfEx(scheduleConf);
	if (returnInfo.resultCode==0)
	{
		CString s; 
		s.Format("�༭��Լ��ͨ����ɹ�������ID��%s",returnInfo.result.confId.c_str());
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	} 
	else
	{
		CString s; 
		s.Format("�༭��Լ��ͨ����ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,30, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	memset(&st,0,sizeof(SYSTEMTIME));

	int retCode=prolongScheduledConfEx(m_confId.GetBuffer(), st, "P0Y0M0DT1H0M0.000S");
	if (retCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�ӳ�����ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("�ӳ�����ʧ�ܣ������룺%d",retCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<map<std::string, list<FreeBusyStateEx>>> returnInfo;
	list<std::string> siteUris;
	siteUris.push_back("01051801");
	siteUris.push_back("01051802");
	siteUris.push_back("01051803");

	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,-60, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);

	returnInfo=querySiteStatusEx(siteUris, st, "P0Y0M0DT1H0M0.000S");
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯָ���᳡ָ��ʱ����ڵ�æ��״̬�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯָ���᳡ָ��ʱ����ڵ�æ��״̬ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<ConferenceStatusEx>> returnInfo;
	list<std::string> confIds;
	UpdateData(TRUE);

	string confids=m_confId.GetBuffer();

	for(int i=0; i<confids.size(); i++)
	{
		int pos=confids.find(",",i);
		if(pos<confids.size())
		{
			std::string s=confids.substr(i,pos-i);
			confIds.push_back(s);
			i=pos;
		}
	}

	returnInfo=queryConferencesStatusEx(confIds);

	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯ�ѵ��Ȼ����״̬�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯ�ѵ��Ȼ����״̬ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<map<string, list<FreeBusyStateEx>>> returnInfo;
	list<string> siteUris;
	siteUris.push_back("01051801");
	siteUris.push_back("01051802");
	siteUris.push_back("01051803");

	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,-30, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);

	std::string duration="P0Y0M0DT1H0M0.000S";

	returnInfo=synchSiteStatusEx(siteUris,st,duration);
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("ָ���᳡æ��״̬ͬ���ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("ָ���᳡æ��״̬ͬ��ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	SYSTEMTIME beginTime;
	memset(&beginTime,0,sizeof(SYSTEMTIME));

	int returnCode=delSiteFromConfEx(m_confId.GetBuffer(), "01051801", beginTime);
	if (returnCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("ɾ�������еĻ᳡�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("ɾ�������еĻ᳡ʧ�ܣ������룺%d",returnCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	list<std::string> siteUris;
	siteUris.push_back("01051802");
	siteUris.push_back("01051803");
	int returnCode= disconnectSitesEx(m_confId.GetBuffer(),siteUris);
	if (returnCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�Ͽ�ָ������Ļ᳡�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("�Ͽ�ָ������Ļ᳡ʧ�ܣ������룺%d",returnCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SYSTEMTIME beginTime;
	memset(&beginTime,0,sizeof(SYSTEMTIME));
	int returnCode= delScheduledConfEx(m_confId.GetBuffer(), beginTime);
	if (returnCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("ɾ��ԤԼ�����������ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("ɾ��ԤԼ����&��������ʧ�ܣ������룺%d",returnCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton10()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<QueryMultiPointCDRExResponse> returnInfo;
	MultiPointCDRQueryConfigEx queryConfig;

	//��ѯ��ʼʱ��
	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,-120, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);
	queryConfig.beginTime = st;

	//��ѯʱ���ȡ�����ʱ�����磺P0Y0M0DT1H0M0.000S����PT1H����ʾ1Сʱ
	queryConfig.duration = "P0Y0M0DT1H0M0.000S";

	
	queryConfig.pageParam.currentPage=1;
	queryConfig.pageParam.numberPerPage=10;


	returnInfo=queryMultiPointCDREx(queryConfig);
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯ���CDR�����ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯ���CDR����ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton11()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<QueryPointToPointCDRExResponse> returnInfo;
	PointToPointCDRQueryConfigEx queryConfig;

	//��ѯ��ʼʱ��
	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,-120, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);
	queryConfig.beginTime = st;
	//queryConfig.beginTime = st;

	//��ѯʱ���ȡ�����ʱ�����磺P0Y0M0DT2H0M0.000S����PT2H����ʾ2Сʱ
	queryConfig.duration = "P0Y0M0DT2H0M0.000S";

	queryConfig.pageParam.currentPage=1;
	queryConfig.pageParam.numberPerPage=10;


	returnInfo=queryPointToPointCDREx( queryConfig);
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯ��Ե�CDR�����ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯ��Ե�CDR����ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton12()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> returnInfo;
	list<std::string> confAccessCodes;
	confAccessCodes.push_back("01051804");

	//��ѯ��ʼʱ��
	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,-120, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);

	returnInfo=queryAdhocConfFreeBusyEx(confAccessCodes,st,"P2D");
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯAdhoc����æ��״̬�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯAdhoc����æ��״̬ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton13()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> returnInfo;

	list<std::string> confAccessCodes;
	confAccessCodes.push_back("01012931");
	confAccessCodes.push_back("01022943");
	//��ѯ��ʼʱ��
	CTime m_time;
	CString strTime;
	CTimeSpan delta(-2, -4,-120, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);

	returnInfo=synchAdhocConfFreeBusyEx(confAccessCodes, st, "PT4H");
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯAdhoc����æ��״̬�仯�����ݳɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯAdhoc����æ��״̬�仯������ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton14()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<QueryAdhocConferenceExResponse> returnInfo;

	QueryConfigEx queryConfig;
	//����������ϣ�Ŀǰֻ֧�ֵ�������
	
	SortItemEx s;
	s.sort = 0;
	s.itemIndex = 5;
	queryConfig.sortItems.push_back(s);
	
	//����������ϣ�֧�ֶ������������ΪAND��ϵ
	StringFilterEx sf;
	sf.columnIndex = 5;
	sf.value = "12345";
	queryConfig.filters.push_back(sf);

	//ҳ�붨λ����
	queryConfig.pageParam.numberPerPage = 10;
	queryConfig.pageParam.currentPage = 1;

	//��������ID��ָ����ǰ��ѯ���ȷ��ذ���ָ��ID������ҳ��
	queryConfig.focusItem = 0;

	returnInfo=queryAdhocConferencesEx(queryConfig);
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯAd hoc���͵Ļ����б�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯAd hoc���͵Ļ����б�ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton15()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<SiteMCUEx>> returnInfo;
	UpdateData(TRUE);
	list<std::string> siteUris;
	 SYSTEMTIME beginTime;
	 memset(&beginTime,0,sizeof(SYSTEMTIME));
	returnInfo=queryConfSiteMCUEx(m_confId.GetBuffer(), siteUris, beginTime);
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯָ�������еĻ᳡����MCU�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯָ�������еĻ᳡����MCUʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton16()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<GetContinuousPresenceInfoResponseEx> returnInfo;
	UpdateData(TRUE);
	returnInfo=getContinuousPresenceInfoEx(m_confId.GetBuffer());
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯ�໭��ģʽ��Դ���ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯ�໭��ģʽ��Դ��ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton17()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<GetContinuousPresenceParamResponseEx> returnInfo;
	UpdateData(TRUE);
	returnInfo=getContinuousPresenceParamEx(m_confId.GetBuffer(),"0");
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ȡָ������Ķ໭������ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ȡָ������Ķ໭�����ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton18()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int resultCode= setVideoSourceEx(m_confId.GetBuffer(), "01051801", "01022001", 0);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("����ָ���᳡����ƵԴ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("����ָ���᳡����ƵԴʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton19()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int resultCode= setAudioSwitchEx(m_confId.GetBuffer(), 50,1);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("���û���������л��ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("���û���������л�ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton20()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int resultCode= setBroadcastContinuousPresenceEx(m_confId.GetBuffer(), 0);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("���ù㲥�໭��ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("���ù㲥�໭��ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton21()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	list<std::string> siteUris;
	siteUris.push_back("01051801");
	siteUris.push_back("01051802");
	siteUris.push_back("01051803");
	int resultCode= setSitesMuteEx(m_confId.GetBuffer(), siteUris, 0);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("ָ���᳡�����ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("ָ���᳡����ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton22()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	list<std::string> siteUris;
	siteUris.push_back("01051801");
	siteUris.push_back("01051802");
	siteUris.push_back("01051803");
	int resultCode= setSitesQuietEx(m_confId.GetBuffer(), siteUris,0);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("ָ���᳡�����ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("ָ���᳡����ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton23()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	list<std::string> subPics;
	subPics.push_back("01051801");
	subPics.push_back("01051802");
	subPics.push_back("01051803");
	int resultCode= setContinuousPresenceEx(m_confId.GetBuffer(),"0", 12,subPics);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("���ö໭������ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("���ö໭�����ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton24()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int resultCode= requestConfChairEx(m_confId.GetBuffer(), "01050001");
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("������ϯ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("������ϯʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton25()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int resultCode= releaseConfChairEx(m_confId.GetBuffer());
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�ͷ���ϯ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("�ͷ���ϯʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton26()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int resultCode= setFloorEx(m_confId.GetBuffer(),"01051801");
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("ָ���᳡���Գɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("ָ���᳡����ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton27()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	 list<SiteVolumeEx> siteVolumes;
	 SiteVolumeEx sv;
	 sv.siteUri="01022001";
	 sv.volume=70;
	 siteVolumes.push_back(sv);

	 /* sv.siteUri="01051802";
	 sv.volume=70;
	 siteVolumes.push_back(sv);


	 sv.siteUri="01051803";
	 sv.volume=70;
	 siteVolumes.push_back(sv);*/


	int resultCode= setConfSiteVolumeEx(m_confId.GetBuffer(), siteVolumes);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("���û᳡����ֵ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("���û᳡����ֵʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton28()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	list<std::string> siteUris;
	siteUris.push_back("01051801");
	siteUris.push_back("01051802");
	siteUris.push_back("01051803");

	int resultCode= displayConfSiteLocalVideoEx(m_confId.GetBuffer(), siteUris);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�򿪻����л᳡����Ƶ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("�򿪻����л᳡����Ƶʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton29()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	list<std::string> siteUris;
	siteUris.push_back("01051801");
	siteUris.push_back("01051802");
	siteUris.push_back("01051803");

	int resultCode= hideConfSiteLocalVideoEx(m_confId.GetBuffer(), siteUris);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�رջ����л᳡����Ƶ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("�رջ����л᳡����Ƶʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton30()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int resultCode= lockPresentationEx(m_confId.GetBuffer(), "01051801");
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��������ʾ�����Ƴɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��������ʾ������ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton31()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int resultCode=  unlockPresentationEx(m_confId.GetBuffer());
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��������ʾ�����Ƴɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��������ʾ������ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton32()
{
	// TODO: Add your control notification handler code here
	TerminalInfoEx siteInfo;

	list<VideoCapbilityItemEx> videoCapbility;


	//�᳡����
	siteInfo.name = "��Ϣ";
	//�᳡��ʶ
	siteInfo.uri = "01051812";
	//�᳡����
	siteInfo.type = 1;
	//���ʡ���ʽΪ������ֵk/M�����硰1920k����Ĭ����ϵͳ�Զ�ѡ��
	siteInfo.rate = "1920K";
	//����ѡ��H.323��SIPЭ��᳡ע��SC���û���
	siteInfo.regUser = "eSDK_test";
	//����ѡ��H.323��SIPЭ��᳡ע��SC������
	siteInfo.regPassword = "Huawei@123";
	//����ѡ���ն�֧�ֵ���Ƶ���������б�����������Ϊ֧��������Ƶ

	list<int> videoFormat;
	videoFormat.push_back(0);
	videoFormat.push_back(1);
	videoFormat.push_back(2);
	videoFormat.push_back(3);

	VideoCapbilityItemEx vc;
	vc.videoProtocol=0;
	vc.videoFormat=videoFormat;

	videoCapbility.push_back(vc);

	siteInfo.videoCapbility = videoCapbility;



	int resultCode=   addSiteInfoEx("1", siteInfo);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ӻ᳡��Ϣ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ӻ᳡��Ϣʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton33()
{
	// TODO: Add your control notification handler code here
	TerminalInfoEx siteInfo;

	list<VideoCapbilityItemEx> videoCapbility;


	//�᳡����
	siteInfo.name = "test80";
	//�᳡��ʶ
	siteInfo.uri = "01051811";
	//�᳡����
	siteInfo.type = 1;
	//���ʡ���ʽΪ������ֵk/M�����硰1920k����Ĭ����ϵͳ�Զ�ѡ��
	siteInfo.rate = "1920K";
	//����ѡ��H.323��SIPЭ��᳡ע��SC���û���
	siteInfo.regUser = "eSDK_test";
	//����ѡ��H.323��SIPЭ��᳡ע��SC������
	siteInfo.regPassword = "Huawei@123";
	//����ѡ���ն�֧�ֵ���Ƶ���������б�����������Ϊ֧��������Ƶ

	list<int> videoFormat;
	videoFormat.push_back(0);
	videoFormat.push_back(1);
	videoFormat.push_back(2);
	videoFormat.push_back(3);

	VideoCapbilityItemEx vc;
	vc.videoProtocol=0;
	vc.videoFormat=videoFormat;

	videoCapbility.push_back(vc);

	siteInfo.videoCapbility = videoCapbility;



	int resultCode=   editSiteInfoEx(siteInfo);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�༭�᳡��Ϣ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("�༭�᳡��Ϣʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton34()
{
	// TODO: Add your control notification handler code here
	list<std::string> siteUris;
	siteUris.push_back("01051811");
	int resultCode=  deleteSiteInfoEx(siteUris);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("ɾ���᳡��Ϣ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("ɾ���᳡��Ϣʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton35()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<QuerySitesInfoExResponse> returnInfo;

	QueryConfigEx queryConfig;

	//����������ϣ�Ŀǰֻ֧�ֵ�������
	SortItemEx sortItem;
	sortItem.sort = 0;
	sortItem.itemIndex = 4;
	queryConfig.sortItems.push_back(sortItem);

	//����������ϣ�֧�ֶ������������ΪAND��ϵ
	StringFilterEx sf;
	sf.columnIndex = 4;
	sf.value = "Conference";
	queryConfig.filters.push_back(sf);

	//ҳ�붨λ����
	PageParamEx pageParam;
	pageParam.numberPerPage = 10;
	pageParam.currentPage = 1;
	queryConfig.pageParam = pageParam;
	//��������ID��ָ����ǰ��ѯ���ȷ��ذ���ָ��ID������ҳ��
	queryConfig.focusItem = 0;
	//���û᳡�����е�querySitesInfoEx��������ѯ�᳡��Ϣ



	returnInfo= querySitesInfoEx(queryConfig);
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯ�᳡��Ϣ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯ�᳡��Ϣʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}

}


void CTP_Native_OtherInterface::OnBnClickedButton36()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<QueryMCUInfoExResponse> returnInfo;

	QueryConfigEx queryConfig;

	SortItemEx sortItem;
	sortItem.sort = 0;
	sortItem.itemIndex = 6;
	queryConfig.sortItems.push_back(sortItem);

	//����������ϣ�֧�ֶ������������ΪAND��ϵ
	StringFilterEx sf;
	sf.columnIndex = 6;
	sf.value = "testMUC";
	queryConfig.filters.push_back(sf);

	//ҳ�붨λ����
	PageParamEx pageParam;
	pageParam.numberPerPage = 15;
	pageParam.currentPage = 1;
	queryConfig.pageParam = pageParam;

	//��������ID��ָ����ǰ��ѯ���ȷ��ذ���ָ��ID������ҳ��
	queryConfig.focusItem = 0;
	//����MCU�����е�queryMCUInfoEx��������ѯSMC 2.0 �ϵ�MCU��Ϣ�б�


	returnInfo=queryMCUInfoEx(queryConfig);
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯMCU��Ϣ�б�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯMCU��Ϣ�б�ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton37()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<MCUResourceEx>> returnInfo;

	//����ѯ��Դ��MCU ID�б�
	list<int> mcus;
	mcus.push_back(0);
	mcus.push_back(1);
	mcus.push_back(27);
	mcus.push_back(3);
	mcus.push_back(4);

	//��ѯ��ʼʱ��
	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,-30, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);


	string duration = "P0Y0M0DT10H0M0.000S";
	//����MCU�����е�queryMCUFutureResourceEx��������ѯδ��ʱ��MCU����Դռ�����


	returnInfo= queryMCUFutureResourceEx(mcus,st,  duration);
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯδ��ʱ��MCU����Դռ������ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯδ��ʱ��MCU����Դռ�����ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}

}


void CTP_Native_OtherInterface::OnBnClickedButton38()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<OrganizationItemEx>>  returnInfo;
	returnInfo=queryOrganizationEx();
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯϵͳ����֯�ڵ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯϵͳ����֯�ڵ�ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton39()
{
	// TODO: Add your control notification handler code here
	int resultCode=  requestChairEx("01051810");
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("������ϯ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("������ϯʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton40()
{
	// TODO: Add your control notification handler code here
	int resultCode=  releaseChairEx("01051810");
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�ͷ���ϯ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("�ͷ���ϯʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton41()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<int> returnCode;
	returnCode= queryConfCtrlPwdEx("01022001");
	if (returnCode.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯ�᳡���ڻ����Ƿ��������ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯ�᳡���ڻ����Ƿ��������ʧ�ܣ������룺%d",returnCode.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton42()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<BroadInfoEx> returnCode;
	returnCode= queryBroadInfoEx("01022001");
	if (returnCode.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯָ���᳡���ڻ�����¼����ֱ������Ϣ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯָ���᳡���ڻ�����¼����ֱ������Ϣʧ�ܣ������룺%d",returnCode.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton43()
{
	// TODO: Add your control notification handler code here
	int resultCode= setRecordBroadEx("01022001", 0);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("����������ֹͣ¼���ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("����������ֹͣ¼��ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton44()
{
	// TODO: Add your control notification handler code here
	int resultCode= setDirectBroadEx("01022001", 0);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("����������ֱֹͣ���ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("����������ֱֹͣ��ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton45()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<int> returnInfo;
	returnInfo=isConnectAuxSourceEx("01022001");
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯ�Ƿ���븨������Դ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯ�Ƿ���븨������Դʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton46()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<int> returnInfo;
	returnInfo=isSendAuxStreamEx("01022001");
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯ��ǰ�Ƿ����ڷ��͸����ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯ��ǰ�Ƿ����ڷ��͸���ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton47()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<int> returnInfo;
	returnInfo=isReceiveRemAuxStrmEx("01022001");
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯָ���᳡�Ƿ����ڽ���Զ�˸����ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯָ���᳡�Ƿ����ڽ���Զ�˸���ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton48()
{
	// TODO: Add your control notification handler code here
	int resultCode= setAuxStreamEx("01022001",0);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("���ÿ�ʼ��ֹͣ���͸����ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("���ÿ�ʼ��ֹͣ���͸���ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton49()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<AuxStreamInfoEx>> returnInfo;
	returnInfo=queryAuxStreamSourcesEx("01022001");

	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ȡ������ƵԴ�б�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ȡ������ƵԴ�б�ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton50()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<VideoSourcesInfoEx>> returnInfo;
	returnInfo=queryVideoOutSrcStateEx("01022001");
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯ��Ƶ����ڽ�����ƵԴ״̬�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯ��Ƶ����ڽ�����ƵԴ״̬ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton51()
{
	// TODO: Add your control notification handler code here
	CameraControlEx cameraControl;
	//��ʼ����ƽ�� 
	cameraControl.camAction = 1;
	//Ԥ��λΪ255�����������Ԥ��λ�йصĲ�������camPos��ֵ�ɶ�����Ϊ255 
	cameraControl.camPos = 255; 
	//�����idΪ1 
	cameraControl.camSrc = 1; 
	//��������ͷ 
	cameraControl.camState = 0; 

	int resultCode= ctrlCameraEx("01022001", cameraControl);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��������Ʋ����ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��������Ʋ���ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton52()
{
	// TODO: Add your control notification handler code here
	list<int> localMainSrcs;
	localMainSrcs.push_back(0);
	localMainSrcs.push_back(1);
	int resultCode= setMainAuxStreamSourcesEx("01022001", localMainSrcs, 1);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("����������ƵԴ��������ƵԴ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("����������ƵԴ��������ƵԴʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton53()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<AuxStreamInfoEx>> returnInfo;
	
	returnInfo= queryMainStreamSourcesEx("01022001");
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ȡ������ƵԴ�������б�����ݳɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ȡ������ƵԴ�������б������ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton54()
{
	// TODO: Add your control notification handler code here
	int resultCode= setVideoOutSrcEx("01022001",0,0);
	if (resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�����������ʾ���ݳɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("�����������ʾ����ʧ�ܣ������룺%d",resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton55()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<SiteDeviceVersionInfoEx> returnInfo;

	returnInfo=  querySiteVersionInfoEx("01022001");
	if (returnInfo.resultCode==0)
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ѯ��ȡ�ն��ͺ�/�汾��Ϣ�ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("��ѯ��ȡ�ն��ͺ�/�汾��Ϣʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton56()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<RecurrenceConfInfoEx> returnInfo;
	RecurrenceConfInfoEx scheduleConf;
	UpdateData(TRUE);

	scheduleConf.base_info.confId=m_confId.GetBuffer();
	//��������
	scheduleConf.base_info.name ="editConf";

	//���鿪ʼʱ��Ϊ30����֮��
	CTime m_time;
	CString strTime;
	CTimeSpan delta(0, 0,30, 0);
	m_time=CTime::GetCurrentTime();//��ȡ��ǰʱ������  
	m_time+=delta;
	strTime=m_time.Format(_T("%Y/%m/%d %H:%M:%S"));   //��ʽ������ʱ�� 

	COleDateTime tT;
	tT.ParseDateTime(strTime);
	SYSTEMTIME st;
	tT.GetAsSystemTime(st);
	scheduleConf.base_info.beginTime = st;

	//�½�һ��SiteInfoEx���� 
	SiteInfoEx siteInfo1;
	//�᳡URIΪ01010086 
	siteInfo1.uri = "01051808";
	//�᳡����Ϊ1920K
	siteInfo1.rate = "1920K";
	//�᳡����Ϊsite1
	siteInfo1.name = "site1";
	//���з�ʽΪMCU�������л᳡
	siteInfo1.dialingMode = 0;
	//�᳡��ԴΪ�ڲ��᳡
	siteInfo1.from = 0;
	//�᳡����ΪH.323�᳡����
	siteInfo1.type = 4;
	//�᳡��Ƶ��ʽΪ4CIF
	siteInfo1.videoFormat = 0;
	//�᳡��ƵЭ��ΪH.263
	siteInfo1.videoProtocol = 1;
	//ԤԼ������Ҫ�������ϻ᳡���������½�һ���᳡
	SiteInfoEx siteInfo2;
	siteInfo2.uri = "01051809";
	siteInfo2.rate = "1920K";
	siteInfo2.name = "site2";
	siteInfo2.dialingMode = 0;
	siteInfo2.from = 0;
	siteInfo2.type = 4;
	siteInfo2.videoFormat = 0;
	siteInfo2.videoProtocol = 1;

	//��������Ϊ1920k
	scheduleConf.base_info.rate = "1920k";
	//����ʱ��Ϊ60����
	scheduleConf.base_info.duration = "P0Y0M0DT1H0M0.000S";
	//��������� ������Ϊ���ָ�ʽ���ַ���
	scheduleConf.base_info.accessCode = "1404290";
	//���������ӻ᳡
	scheduleConf.base_info.sites.push_back(siteInfo1);
	scheduleConf.base_info.sites.push_back(siteInfo2);

	//�����Ƿ�֧��¼�ƹ���
	scheduleConf.base_info.isRecording = 0;
	//����������롣ֻ֧��0��9�����֣�����Ϊ6λ����
	scheduleConf.base_info.password = "123456";
	//��ϯ���������������롣ֻ֧��0��9�����֣�����Ϊ6λ����
	scheduleConf.base_info.chairmanPassword = "654321";
	//���ڻ����������ͣ�ȡֵ˵�����£�0��Daily ÿ�죻1��Weekly ÿ�ܣ�2��Monthly ÿ��
	scheduleConf.frequency = 0;
	//�������ڼ�������ڻ��� interval �������0
	scheduleConf.interval = 1;
	//�ظ�����
	scheduleConf.count = 6;
	//���ڻ��鱾��ʱ����ʱ���ִ���ʾ����ο�A ʱ���б�
	scheduleConf.timeZone = "Asia/Shanghai";
	//���û�������scheduleConfEx����ԤԼ���飬����TPSDKResponseEx<ConferenceInfoEx>����
	returnInfo = editRecurrenceConferenceEx(scheduleConf,st);
	
	if (returnInfo.resultCode==0)
	{
		CString s; 
		s.Format("�༭��Լ���ڻ���ɹ�������ID��%s",returnInfo.result.base_info.confId.c_str());
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	} 
	else
	{
		CString s; 
		s.Format("�༭��Լ���ڻ���ʧ�ܣ������룺%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton57()
{
	// TODO: Add your control notification handler code here
	QueryConfigEx queryCfg;
	
	SortItemEx s;
	s.sort = 0;
	s.itemIndex = 0;
	queryCfg.sortItems.push_back(s);
	queryCfg.focusItem = 0;

	//StringFilterEx f;
	//f.value = "VCT2";
	//f.columnIndex = 1;
	//queryCfg.filters.push_back(f);

	queryCfg.pageParam.currentPage = 1;
	queryCfg.pageParam.numberPerPage = 5;

	TPSDKResponseWithPageEx<list<ConferenceStatusEx>> result = queryScheduleConferencesEx(queryCfg);
	if ( 0 == result.resultCode )
	{
		CString s; 
		s.Format("��ѯ���Ȼ����״̬�ɹ����ܹ�%dҳ����ǰ��%dҳ���ܹ�%d����¼",result.pagesInfo.totalPages, result.pagesInfo.currentPage, result.pagesInfo.totalRecords);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	} 
	else
	{
		CString s; 
		s.Format("��ѯ���еĵ��Ȼ���״̬ʧ�ܣ������룺%d",result.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton58()
{
	// TODO: Add your control notification handler code here
	int iPushMode = 1;
	std::string strExtendParameter = "";
	int result = enablePushEx(iPushMode, strExtendParameter);
	if ( 0 == result )
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�������͹��ܳɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("�������͹���ʧ�ܣ������룺%d",result);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton59()
{
	// TODO: Add your control notification handler code here
	//SubscribeInfoEx subscribeInfoEx;			//SubscribeInfoEx�������ͺͽӿڲο��ĵ��ж���Ĳ�һ�����п��ܻ�������
	//subscribeInfoEx.isSubscribe = 1;
	//subscribeInfoEx.type = 0;
	//SubscribeInfoEx *pSubScribeInfoEx = new SubscribeInfoEx;
	//pSubScribeInfoEx->isSubscribe = 1;
	//pSubScribeInfoEx->type = 0;

	ScheduledConfSubscribeEx *pScheduledConfSubscribeEx = new ScheduledConfSubscribeEx;
	if ( NULL == pScheduledConfSubscribeEx )
	{
		return;
	}
	pScheduledConfSubscribeEx->isSubscribe = 1;
	CString cstrConfId;
	GetDlgItemText(IDC_EDIT1,cstrConfId);
	pScheduledConfSubscribeEx->confIds =  "750" /* "750" */;

	SubscribeInfoEx *pSubscribeInfoEx = pScheduledConfSubscribeEx;

	list<SubscribeInfoEx *> listsubscribeInfos;
	//listsubscribeInfos.push_back(pSubscribeInfoEx);

	OngoingConfSubscribeEx *pOngoingConfSubscribeEx = new OngoingConfSubscribeEx;
	if ( NULL == pOngoingConfSubscribeEx )
	{
		return ;
	}
	pOngoingConfSubscribeEx->isSubscribe = 1;
	pOngoingConfSubscribeEx->confIds = cstrConfId;
	SubscribeInfoEx *pSubscribeInfoEx1 = pOngoingConfSubscribeEx;
	listsubscribeInfos.push_back(pSubscribeInfoEx1);
	listsubscribeInfos.push_back(pSubscribeInfoEx1);
	listsubscribeInfos.push_back(pSubscribeInfoEx);
	listsubscribeInfos.push_back(pSubscribeInfoEx);
	listsubscribeInfos.push_back(pSubscribeInfoEx1);
	listsubscribeInfos.push_back(pSubscribeInfoEx);

	int result = subscribeEx(listsubscribeInfos);
	if ( 0 == result )
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�޸�������Ϣ�Ĺ��������ɹ�"));
	} 
	else
	{
		CString s; 
		s.Format("�޸�������Ϣ�Ĺ�������ʧ�ܣ������룺%d",result);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
	pSubscribeInfoEx = NULL;
	listsubscribeInfos.clear();
	delete pScheduledConfSubscribeEx;
	pScheduledConfSubscribeEx = NULL;
}


void CTP_Native_OtherInterface::OnBnClickedButton60()
{
	// TODO: Add your control notification handler code here
	TPSDKResponseEx<list<NotificationEx *>> result = queryNotificationEx();
	if ( 0 == result.resultCode )
	{
		//for ( list<NotificationEx *>::iterator ite = result.result.begin(); ite != result.result.end(); ite++ )
		//{
		//	if ( TP_D_OVERFLOW_NOTIFICATION_TYPE == (*ite)->type  )
		//	{
		//		OverflowNotificationEx *pOverflowNtf = (OverflowNotificationEx *)*ite;
		//		delete pOverflowNtf;
		//		pOverflowNtf = NULL;
		//		*ite = NULL;
		//	} 
		//	else if (  TP_D_SCHEDULED_CONF_NOTIFICATION_TYPE == (*ite)->type )
		//	{
		//		ScheduledConfNotificationEx *pScheduledConfNtf = (ScheduledConfNotificationEx *)*ite;
		//		delete pScheduledConfNtf;
		//		pScheduledConfNtf = NULL;
		//		*ite = NULL;
		//	} 
		//	else if ( TP_D_ONGOING_CONF_NOTIFICATION_TYPE == (*ite)->type )
		//	{
		//		OngoingConfNotificationEx *pOngoingConfNtf = (OngoingConfNotificationEx *)*ite;
		//		for ( list<NotificationStatusEx *>::iterator iter = pOngoingConfNtf->changes.begin(); iter != pOngoingConfNtf->changes.end(); iter++ )
		//		{
		//			if ( TP_D_CONFERENCE_STATUS_TYPE == (*iter)->structtype )
		//			{
		//				ConferenceStatusEx *pConferenceStatusEx = (ConferenceStatusEx *)*iter;
		//				delete pConferenceStatusEx;
		//				pConferenceStatusEx = NULL;
		//				*iter = NULL;
		//			} 
		//			else if ( TP_D_SITE_STATUS_TYPE == (*iter)->structtype )
		//			{
		//				SiteStatusEx *pSiteStatusEx = (SiteStatusEx *)*iter;
		//				//delete pSiteStatusEx;
		//				pSiteStatusEx = NULL;
		//				//*iter = NULL;
		//				delete *iter;
		//				*iter = NULL;
		//			}

		//		}
		//		pOngoingConfNtf->changes.clear();	//���changes list
		//		delete pOngoingConfNtf;
		//		pOngoingConfNtf = NULL;
		//		*ite = NULL;
		//	}
		//}
		//result.result.clear();	//���result list
		releasequeryNotificationMemery(result.result);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("��ȡ֪ͨ��Ϣ�ɹ�"));
	}
	else
	{
		CString s; 
		s.Format("��ȡ֪ͨ��Ϣʧ�ܣ������룺%d",result.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton61()
{
	// TODO: Add your control notification handler code here
	std::string OrgId = "1";
	AdhocConfTemplateParamEx AdhocConfTemplate;
	AdhocConfTemplate.adhocConfTemplateId = "0";
	AdhocConfTemplate.name = "testAdhocConf12b";
	AdhocConfTemplate.accessCode = "1";
	AdhocConfTemplate.duration = "P0Y0M0DT1H0M0.000S";
	AdhocConfTemplate.billCode = "0";
	AdhocConfTemplate.password = "0";
	AdhocConfTemplate.cpResouce = 0;
	AdhocConfTemplate.rate = "1920K";
	AdhocConfTemplate.mediaEncryptType = 2;		//�����ܡ����ۻ᳡�Ƿ��м���������ý�����������ü���
	AdhocConfTemplate.isLiveBroadcast = 0;
	AdhocConfTemplate.isRecording = 0;
	AdhocConfTemplate.presentation = 0;
	AdhocConfTemplate.chairmanPassword = "0";
	AdhocConfTemplate.presentationVideo.videoProtocol = 1;
	AdhocConfTemplate.presentationVideo.videoFormat = 0;
	AdhocConfTemplate.mainSiteUri = "01010086";
	AdhocConfTemplate.notice.email = "abc@huawei.com";
	AdhocConfTemplate.notice.content = "0";
	AdhocConfTemplate.notice.telephone = "0";
	AdhocConfTemplate.maxSitesCount = 0;
	AdhocConfTemplate.reservedCsdPorts = 0;
	AdhocConfTemplate.state = 0;

	SiteInfoEx sites1;
	sites1.name = "site1";
	sites1.uri = "01010086";
	sites1.type = 4;
	sites1.from = 0;
	sites1.dialingMode = 0;
	sites1.rate = "1920K";
	sites1.videoFormat = 0;
	sites1.videoProtocol = 1;
	sites1.isLockVideoSource = 0;
	sites1.participantType = 0;
	sites1.status = 0;
	sites1.dtmf = "0";

	SiteInfoEx sites2;
	sites2.name = "site2";
	sites2.uri = "01010010";
	sites2.type = 4;
	sites2.from = 0;
	sites2.dialingMode = 0;
	sites2.rate = "1920K";
	sites2.videoFormat = 0;
	sites2.videoProtocol = 1;
	sites2.isLockVideoSource = 0;
	sites2.participantType = 0;
	sites2.status = 0;
	sites2.dtmf = "0";

	AdhocConfTemplate.sites.push_back(sites1);
	AdhocConfTemplate.sites.push_back(sites2);
	TPSDKResponseEx<std::string> result = addAdhocConfTemplateEx( OrgId, AdhocConfTemplate );
	if ( 0 == result.resultCode )
	{
		CString s; 
		s.Format("���Ad hoc����ģ��ɹ���ģ��ID�ǣ�%s",result.result.c_str());
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	} 
	else
	{
		CString s; 
		s.Format("���Ad hoc����ģ��ʧ�ܣ������룺%d",result.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}

//�༭����ģ��
void CTP_Native_OtherInterface::OnBnClickedButton62()
{
	// TODO: Add your control notification handler code here
	CString cstrConfId;
	GetDlgItemText(IDC_EDIT1,cstrConfId);
	AdhocConfTemplateParamEx AdhocConfTemplate;
	AdhocConfTemplate.adhocConfTemplateId = cstrConfId;
	AdhocConfTemplate.name = "editTestAdhocConf";
	AdhocConfTemplate.accessCode = "1";
	AdhocConfTemplate.duration = "P0Y0M0DT1H0M0.000S";
	AdhocConfTemplate.billCode = "0";
	AdhocConfTemplate.password = "0";
	AdhocConfTemplate.cpResouce = 3;
	AdhocConfTemplate.rate = "1920K";
	AdhocConfTemplate.mediaEncryptType = 2;
	AdhocConfTemplate.isLiveBroadcast = 0;
	AdhocConfTemplate.isRecording = 0;
	AdhocConfTemplate.presentation = 0;
	AdhocConfTemplate.chairmanPassword = "0";
	AdhocConfTemplate.presentationVideo.videoProtocol = 1;
	AdhocConfTemplate.presentationVideo.videoFormat = 0;
	AdhocConfTemplate.mainSiteUri = "01010086";
	AdhocConfTemplate.notice.email = "abc@huawei.com";
	AdhocConfTemplate.notice.content = "0";
	AdhocConfTemplate.notice.telephone = "0";
	AdhocConfTemplate.maxSitesCount = 0;
	AdhocConfTemplate.reservedCsdPorts = 0;
	AdhocConfTemplate.state = 0;

	SiteInfoEx sites1;
	sites1.name = "site1";
	sites1.uri = "01010086";
	sites1.type = 4;
	sites1.from = 0;
	sites1.dialingMode = 0;
	sites1.rate = "1920K";
	sites1.videoFormat = 0;
	sites1.videoProtocol = 1;
	sites1.isLockVideoSource = 0;
	sites1.participantType = 0;
	sites1.status = 0;
	sites1.dtmf = "0";
	AdhocConfTemplate.sites.push_back(sites1);

	//SiteInfoEx sites2;
	//sites2.name = "site2";
	//sites2.uri = "01010010";
	//sites2.type = 4;
	//sites2.from = 0;
	//sites2.dialingMode = 0;
	//sites2.rate = "1920K";
	//sites2.videoFormat = 0;
	//sites2.videoProtocol = 1;
	//sites2.isLockVideoSource = 0;
	//sites2.participantType = 0;
	//sites2.status = 0;
	//sites2.dtmf = "0";
	//AdhocConfTemplate.sites.push_back(sites2);

	int result = editAdhocConfTemplateEx(AdhocConfTemplate);
	if ( 0 == result )
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("�༭Ad hoc����ģ��ɹ�"));
	}
	else
	{
		CString s; 
		s.Format("�༭Ad hoc����ģ��ʧ�ܣ������룺%d",result);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton63()
{
	// TODO: Add your control notification handler code here
	CString cstrConfId;
	GetDlgItemText(IDC_EDIT1,cstrConfId);
	std::string AdhocConfTemplateId = cstrConfId;
	int result = delAdhocConfTemplateEx(AdhocConfTemplateId);
	if ( 0 == result )
	{
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("ɾ��Ad hoc����ģ��ɹ�"));
	}
	else
	{
		CString s; 
		s.Format("ɾ��Ad hoc����ģ��ʧ�ܣ������룺%d",result);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


void CTP_Native_OtherInterface::OnBnClickedButton64()
{
	// TODO: Add your control notification handler code here
	QueryConfigEx queryCfg;

	SortItemEx s;
	s.sort = 0;
	s.itemIndex = 4;
	queryCfg.sortItems.push_back(s);

	StringFilterEx f;
	f.value = "A";
	f.columnIndex = 4;
	queryCfg.filters.push_back(f);
	queryCfg.focusItem = 1;

	queryCfg.pageParam.currentPage = 1;
	queryCfg.pageParam.numberPerPage = 5;

	TPSDKResponseWithPageEx<list<AdhocConfTemplateParamEx>> result = queryAdhocConfTemplateListEx( queryCfg );
	if ( 0 == result.resultCode )
	{
		CString s; 
		s.Format("��ѯAd hoc����ģ��ɹ������ģ��������%d",result.result.size());
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	} 
	else
	{
		CString s; 
		s.Format("��ѯAd hoc����ģ��ʧ�ܣ������룺%d",result.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}
