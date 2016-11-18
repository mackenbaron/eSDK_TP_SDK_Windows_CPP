// TP_Native_ConfControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TP_Native_Demo.h"
#include "TP_Native_ConfScheduleDlg.h"
#include "afxdialogex.h"


// CTP_Native_ConfControlDlg dialog

IMPLEMENT_DYNAMIC(CTP_Native_ConfScheduleDlg, CPropertyPage)

CTP_Native_ConfScheduleDlg::CTP_Native_ConfScheduleDlg()
	: CPropertyPage(CTP_Native_ConfScheduleDlg::IDD)
{

}

CTP_Native_ConfScheduleDlg::~CTP_Native_ConfScheduleDlg()
{
}

void CTP_Native_ConfScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CONFERENCE, m_listConference);
}


BEGIN_MESSAGE_MAP(CTP_Native_ConfScheduleDlg, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CTP_Native_ConfScheduleDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTP_Native_ConfControlDlg message handlers


void CTP_Native_ConfScheduleDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
	m_listConference.DeleteAllItems();

	TPSDKResponseEx<list<ConferenceStatusEx>> returnInfo;
	list<std::string> confIds;

	returnInfo=queryConferencesStatusEx(confIds);

	if (returnInfo.resultCode==0)
	{
		m_conferenceList = returnInfo.result;
		int i = 0;
		for ( list<ConferenceStatusEx>::iterator iter = m_conferenceList.begin(); iter != m_conferenceList.end(); iter++)
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
			cstrTemp.Format( "%d-%d-%d %d:%d", iter->beginTime.wYear, iter->beginTime.wMonth, iter->beginTime.wDay, iter->beginTime.wHour, iter->beginTime.wMinute);
			m_listConference.SetItemText(i, 3, cstrTemp);
		}
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,_T("查询已调度会议的状态成功"));
	} 
	else
	{
		CString s; 
		s.Format("查询已调度会议的状态失败；返回码：%d",returnInfo.resultCode);
		SetDlgItemText(IDC_STATIC_INTERFACE_RETURN,s.GetBuffer());
	}
}


BOOL CTP_Native_ConfScheduleDlg::OnInitDialog()
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
	m_listConference.InsertColumn(2,"会议名称",LVCFMT_CENTER,80,NULL);
	m_listConference.InsertColumn(1,"会议状态",LVCFMT_CENTER,80,NULL);
	m_listConference.InsertColumn(1,"开始时间",LVCFMT_CENTER,80,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
