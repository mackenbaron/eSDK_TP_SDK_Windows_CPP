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

#include "stdafx.h"
#include "TP_XMLProcess.h"
#include "Log.h"
#include "TP_Error.h"
#include "TP_Tool.h"
#include "TP_Native_Xml.h"
#include "TP_Native_SOAP_Define.h"
#include "TP_Native_Types.h"
#include <typeinfo>

//OngoingConfNotificationEx *m_pOngoingConfNotificationEx = NULL;
//ScheduledConfNotificationEx *m_pScheduledConfNotificationEx = NULL;
//OverflowNotificationEx *m_pOverFlowNotificationEx = NULL;
//ConferenceStatusEx *m_pConferenceStatusEx = NULL;
//SiteStatusEx *m_pSiteStatusEx = NULL;

int CheckDigital(char *value);

XMLProcess::XMLProcess(void)
{
}


XMLProcess::~XMLProcess(void)
{
}

//elem_flag: 0 means optional elem; 1 means must elem;
int XMLProcess::GetXMLElemValue(CXml *xmlParse, const char *elem, int elem_flag,std::string &strValue)
{
	const char *srcValue = NULL;

	if (!xmlParse->FindElem(elem))													
	{	
		
		if (elem_flag)
		{
			TP_LOG_ERROR("FindElem %s failed.", elem);								
			return TP_SDK_ERR_XML_FIND_ELEM;										
		}
		else
		{
			return TP_SDK_ERR_SUCCESS;
		}
			
	}																			
	
	srcValue = xmlParse->GetElemValue();												
	if (NULL == srcValue)														
	{																			
		TP_LOG_ERROR("GetElemValue %s failed.", elem);							
		return TP_SDK_ERR_XML_GET_ELEM_VALUE;										
	}																			
	strValue = srcValue;
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::Package_BasicSOAP(const char *SMC_ELEM, CXml *xml)
{
	(void)xml->AddElem(TP_D_SOAP_ENVELOPE_ELEM);
	(void)xml->AddAttribute(TP_D_SOAP_ENVELOPE_ATTR_SOAPENV,TP_D_SOAP_ENVELOPE_ATTR_SOAPENV_VALUE);
	(void)xml->AddAttribute(TP_D_SOAP_ENVELOPE_ATTR_SMC,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE);
	(void)xml->AddChildElem(TP_D_SOAP_HEADER_ELEM);
	(void)xml->IntoElem();
	(void)xml->AddElem(TP_D_SOAP_BODY_ELEM);
	(void)xml->AddChildElem(SMC_ELEM);
	(void)xml->IntoElem();
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_LoginRequest(const std::string &userName, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");

	CXml xml;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_LOGINREQ_ELEM, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SMC_USRNAME);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(TP_Tool::UTF8ToANSI(userName.c_str()).c_str());
	(void)xml.AddElem(TP_D_SOAP_SMC_CLIENTTYPE);
	(void)xml.SetElemValue(TP_Tool::UTF8ToANSI(TP_D_SOAP_SMC_CLIENTTYPE_VALUE).c_str());
	(void)xml.AddElem(TP_D_SOAP_SMC_VERSION);
	(void)xml.SetElemValue(TP_Tool::Int2String(TP_D_SOAP_SMC_VERSION_VALUE).c_str());
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}
	
	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Package_SiteInfoEx(const SiteInfoEx *site, CXml *xml)
{
	int ret = TP_SDK_ERR_SUCCESS;

	(void)xml->AddChildElem(TP_D_SOAP_NAME);
	(void)xml->IntoElem();
	(void)xml->SetElemValue(TP_Tool::ANSIToUTF8(site->name.c_str()).c_str());
	(void)xml->AddElem(TP_D_SOAP_URI);
	(void)xml->SetElemValue(site->uri.c_str());
	(void)xml->AddElem(TP_D_SOAP_TYPE);
	(void)xml->SetElemValue(TP_Tool::Int2String(site->type).c_str());
	(void)xml->AddElem(TP_D_SOAP_FROM);
	(void)xml->SetElemValue(TP_Tool::Int2String(site->from).c_str());
	(void)xml->AddElem(TP_D_SOAP_DIALINGMODE);
	(void)xml->SetElemValue(TP_Tool::Int2String(site->dialingMode).c_str());
	(void)xml->AddElem(TP_D_SOAP_RATE);
	(void)xml->SetElemValue(site->rate.c_str());
	(void)xml->AddElem(TP_D_SOAP_VIDEO_FORMAT);
	(void)xml->SetElemValue(TP_Tool::Int2String(site->videoFormat).c_str());
	(void)xml->AddElem(TP_D_SOAP_VIDEO_PROTOCOL);
	(void)xml->SetElemValue(TP_Tool::Int2String(site->videoProtocol).c_str());
	(void)xml->AddElem(TP_D_SOAP_IS_LOCK_VIDEO_SOURCE);
	(void)xml->SetElemValue(TP_Tool::Int2String(site->isLockVideoSource).c_str());
	(void)xml->AddElem(TP_D_SOAP_PARTICIPANT_TYPE);
	(void)xml->SetElemValue(TP_Tool::Int2String(site->participantType).c_str());
	(void)xml->AddElem(TP_D_SOAP_STATUS);
	(void)xml->SetElemValue(TP_Tool::Int2String(site->status).c_str());
	//(void)xml->AddElem(TP_D_SOAP_DTMF);
	//(void)xml->SetElemValue(site->dtmf.c_str());
	(void)xml->OutOfElem();
	return ret;
}

int XMLProcess::Package_ConferenceNoticeEx(const ConferenceNoticeEx *conferenceNotice, CXml *xml)
{
	int ret = TP_SDK_ERR_SUCCESS;
	if(conferenceNotice->email.length())
	{
		(void)xml->AddChildElem(TP_D_SOAP_EMAIL);
		(void)xml->IntoElem();
		(void)xml->SetElemValue(conferenceNotice->email.c_str());
		if (conferenceNotice->content.length())
		{
			(void)xml->AddElem(TP_D_SOAP_CONTENT);
			(void)xml->SetElemValue(conferenceNotice->content.c_str());
		}
		(void)xml->OutOfElem();
	}
	else
	{
		if (conferenceNotice->content.length())
		{
			(void)xml->AddChildElem(TP_D_SOAP_CONTENT);
			(void)xml->IntoElem();
			(void)xml->SetElemValue(conferenceNotice->content.c_str());
			(void)xml->OutOfElem();
		}
	}
	
	return ret;
}

int XMLProcess::Package_ConferenceInfo(const ConferenceInfoEx *conferenceInfo,CXml *xml)
{
	unsigned int i = 0;
	int ret = TP_SDK_ERR_SUCCESS;
	char strTime[256]={0};
	if (conferenceInfo->name.length())
	{
		(void)xml->AddChildElem(TP_D_SOAP_NAME);
		(void)xml->IntoElem();
		(void)xml->SetElemValue(TP_Tool::ANSIToUTF8(conferenceInfo->name).c_str());

		if(conferenceInfo->beginTime.wDay || conferenceInfo->beginTime.wMonth || conferenceInfo->beginTime.wYear)
		{
			(void)xml->AddElem(TP_D_SOAP_BEGINTIME);
			(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d%s"
				,conferenceInfo->beginTime.wYear,conferenceInfo->beginTime.wMonth,conferenceInfo->beginTime.wDay
				,conferenceInfo->beginTime.wHour,conferenceInfo->beginTime.wMinute,conferenceInfo->beginTime.wSecond,TP_Tool::GetLocalTimeZone().c_str());
			(void)xml->SetElemValue(strTime);
		}
	}
	else
	{
		if(conferenceInfo->beginTime.wDay || conferenceInfo->beginTime.wMonth || conferenceInfo->beginTime.wYear)
		{
			(void)xml->AddChildElem(TP_D_SOAP_BEGINTIME);
			(void)xml->IntoElem();
			(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d%s"
				,conferenceInfo->beginTime.wYear,conferenceInfo->beginTime.wMonth,conferenceInfo->beginTime.wDay
				,conferenceInfo->beginTime.wHour,conferenceInfo->beginTime.wMinute,conferenceInfo->beginTime.wSecond,TP_Tool::GetLocalTimeZone().c_str());
			(void)xml->SetElemValue(strTime);
		}
	}

	
	/*sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d%s"
	,conferenceInfo->beginTime.wYear,conferenceInfo->beginTime.wMonth,conferenceInfo->beginTime.wDay
	,conferenceInfo->beginTime.wHour,conferenceInfo->beginTime.wMinute,conferenceInfo->beginTime.wSecond,"+08:00");*/
	

	if (conferenceInfo->confId.length())
	{
		(void)xml->AddElem(TP_D_SOAP_CONFID);
		(void)xml->SetElemValue(conferenceInfo->confId.c_str());
	}

	if (conferenceInfo->duration.length())
	{
		(void)xml->AddElem(TP_D_SOAP_DURATION);
		(void)xml->SetElemValue(conferenceInfo->duration.c_str());
	}
	
	if (conferenceInfo->accessCode.length())
	{
		(void)xml->AddElem(TP_D_SOAP_ACCESS_CODE);
		(void)xml->SetElemValue(conferenceInfo->accessCode.c_str());
	}
	
	if (conferenceInfo->password.length())
	{
		(void)xml->AddElem(TP_D_SOAP_PASSWORD);
		(void)xml->SetElemValue(conferenceInfo->password.c_str());
	}
	
	(void)xml->AddElem(TP_D_SOAP_MEDIA_ENCRYPT_TYPE);
	(void)xml->SetElemValue(TP_Tool::Int2String(conferenceInfo->mediaEncryptType).c_str());
	(void)xml->AddElem(TP_D_SOAP_AUX_VIDEO_FORMAT);
	(void)xml->SetElemValue(TP_Tool::Int2String(conferenceInfo->auxVideoFormat).c_str());
	(void)xml->AddElem(TP_D_SOAP_AUX_VIDEO_PROTOCOL);
	(void)xml->SetElemValue(TP_Tool::Int2String(conferenceInfo->auxVideoProtocol).c_str());
	(void)xml->AddElem(TP_D_SOAP_CP_RESOURCE);
	(void)xml->SetElemValue(TP_Tool::Int2String(conferenceInfo->cpResouce).c_str());
	
	if (conferenceInfo->rate.length())
	{
		(void)xml->AddElem(TP_D_SOAP_RATE);
		(void)xml->SetElemValue(conferenceInfo->rate.c_str());
	}
	
	(void)xml->AddElem(TP_D_SOAP_ISRECORDING);
	(void)xml->SetElemValue(TP_Tool::Int2String(conferenceInfo->isRecording).c_str());
	if (conferenceInfo->recorderAddr.length())
	{
		(void)xml->AddElem(TP_D_SOAP_RECORDER_ADDR);
		(void)xml->SetElemValue(conferenceInfo->recorderAddr.c_str());
	}
	
	(void)xml->AddElem(TP_D_SOAP_IS_LIVE_BROADCAST);
	(void)xml->SetElemValue(TP_Tool::Int2String(conferenceInfo->isLiveBroadcast).c_str());
	(void)xml->AddElem(TP_D_SOAP_PRESENTATION);
	(void)xml->SetElemValue(TP_Tool::Int2String(conferenceInfo->presentation).c_str());
	if (conferenceInfo->chairmanPassword.length())
	{
		(void)xml->AddElem(TP_D_SOAP_CHAIRMAN_PASSWORD);
		(void)xml->SetElemValue(conferenceInfo->chairmanPassword.c_str());
	}
	
	(void)xml->AddElem(TP_D_SOAP_STATUS);
	(void)xml->SetElemValue(TP_Tool::Int2String(conferenceInfo->status).c_str());
	
	if (conferenceInfo->billCode.length())
	{
		(void)xml->AddElem(TP_D_SOAP_BILL_CODE);
		(void)xml->SetElemValue(conferenceInfo->billCode.c_str());
	}
	
	if (conferenceInfo->mainSiteUri.length())
	{
		(void)xml->AddElem(TP_D_SOAP_MAIN_SITE_URI);
		(void)xml->SetElemValue(conferenceInfo->mainSiteUri.c_str());
	}
	
	if(conferenceInfo->conferenceNotice.content.length() || conferenceInfo->conferenceNotice.email.length())
	{
		(void)xml->AddElem(TP_D_SOAP_CONFERENCE_NOTICE);
		(void)Package_ConferenceNoticeEx(&conferenceInfo->conferenceNotice, xml);
	}

	//if (conferenceInfo->maxSitesCount > 0  )
	//{
	//	(void)xml->AddElem(TP_D_SOAP_MAX_SITES_COUNT);
	//	(void)xml->SetElemValue(TP_Tool::Int2String(conferenceInfo->maxSitesCount).c_str());
	//}

	for(i=0; i<conferenceInfo->sites.size(); i++)
	{
		(void)xml->AddElem(TP_D_SOAP_SITES);
		(void)Package_SiteInfoEx(&conferenceInfo->sites[i], xml);
	}
	xml->OutOfElem();
	return ret;
}


int XMLProcess::Package_RecurrenceConfInfoEx(const RecurrenceConfInfoEx *recuConfInfo,CXml *xml)
{
	int ret = TP_SDK_ERR_SUCCESS;
	list<int>::const_iterator i;
	
	(void)XMLProcess::Package_ConferenceInfo( &recuConfInfo->base_info, xml);
	(void)xml->IntoElem();
	(void)xml->AddElem(TP_D_SOAP_FREQUENCY);
	(void)xml->SetElemValue(TP_Tool::Int2String(recuConfInfo->frequency).c_str());
	(void)xml->AddElem(TP_D_SOAP_INTERVAL);
	(void)xml->SetElemValue(TP_Tool::Int2String(recuConfInfo->interval).c_str());

	for (i=recuConfInfo->weekDays.begin(); i!=recuConfInfo->weekDays.end(); i++)
	{
		(void)xml->AddElem(TP_D_SOAP_WEEKDAYS);
		(void)xml->SetElemValue(TP_Tool::Int2String(*i).c_str());
	}
	
	(void)xml->AddElem(TP_D_SOAP_WEEKDAY);
	(void)xml->SetElemValue(TP_Tool::Int2String(recuConfInfo->weekDay).c_str());
	(void)xml->AddElem(TP_D_SOAP_MONTHDAY);
	(void)xml->SetElemValue(TP_Tool::Int2String(recuConfInfo->monthDay).c_str());
	(void)xml->AddElem(TP_D_SOAP_COUNT);
	(void)xml->SetElemValue(TP_Tool::Int2String(recuConfInfo->count).c_str());

	if (recuConfInfo->endDate.wYear || recuConfInfo->endDate.wMonth || recuConfInfo->endDate.wDay)
	{
		(void)xml->AddElem(TP_D_SOAP_ENDDATE);
		char strTime[256]={0};
		(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d%s"
			,recuConfInfo->endDate.wYear,recuConfInfo->endDate.wMonth,recuConfInfo->endDate.wDay
			,recuConfInfo->endDate.wHour,recuConfInfo->endDate.wMinute,recuConfInfo->endDate.wSecond,TP_Tool::GetLocalTimeZone().c_str());
		(void)xml->SetElemValue(strTime);
	}
	
	//(void)xml->SetElemValue(recuConfInfo->endDate.c_str());
	
	if (recuConfInfo->timeZone.length())
	{
		(void)xml->AddElem(TP_D_SOAP_TIMEZONE);
		(void)xml->SetElemValue(recuConfInfo->timeZone.c_str());
	}
	return ret;
}

int XMLProcess::SetXml_scheduleRecurrenceConferenceEx(const RecurrenceConfInfoEx *recuConfInfo, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	int ret = TP_SDK_ERR_SUCCESS;
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SCHEDULE_RECURRENCE_CONFEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SCHEDULECONF);
	(void)xml.IntoElem();
	(void)Package_RecurrenceConfInfoEx(recuConfInfo,&xml);
	(void)xml.OutOfElem();
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return ret;
}

int XMLProcess::SetXml_editScheduleRecurrenceConferenceEx(const RecurrenceConfInfoEx *recuConfInfo, const SYSTEMTIME &beginDateTime, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_EDIT_RECURRENCE_CONFEX, &xml)!=TP_SDK_ERR_SUCCESS)
	{
		TP_LOG_ERROR("Package_BasicSOAP is error.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	(void)xml.AddChildElem(TP_D_SOAP_EDITCONF);
	(void)xml.IntoElem();
	(void)Package_RecurrenceConfInfoEx(recuConfInfo,&xml);


	//(void)xml.IntoElem();
	//(void)xml.AddElem(TP_D_SOAP_CONFID);
	//(void)xml.SetElemValue(recuConfInfo->base_info.confId.c_str());

	(void)xml.OutOfElem();
	if (beginDateTime.wYear||beginDateTime.wMonth||beginDateTime.wDay)
	{
		(void)xml.AddElem(TP_D_SOAP_BEGINTIME);
		(void)xml.IntoElem();
		char strTime[256]={0};
		(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d%s"
			,beginDateTime.wYear,beginDateTime.wMonth,beginDateTime.wDay
			,beginDateTime.wHour,beginDateTime.wMinute,beginDateTime.wSecond,TP_Tool::GetLocalTimeZone().c_str());
		(void)xml.SetElemValue(strTime);
	}
	

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_querySitesEx(std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_SITESEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_editScheduledConfEx(const ConferenceInfoEx *conferenceInfo, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_EDIT_SCHEDULECONFEX, &xml)!=TP_SDK_ERR_SUCCESS)
	{
		TP_LOG_ERROR("Package_BasicSOAP is error.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}
	
	(void)xml.AddChildElem(TP_D_SOAP_EDITCONF);
	(void)xml.IntoElem();
	(void)Package_ConferenceInfo(conferenceInfo, &xml);
	(void)xml.IntoElem();
	(void)xml.AddElem(TP_D_SOAP_CONFID);
	(void)xml.SetElemValue(conferenceInfo->confId.c_str());
	(void)xml.OutOfElem();
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_querySitesEx(const char *xmlStr,list<SiteInfoEx> *listSites)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYSITESEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed,not found TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed,not found TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYSITESEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYSITESEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	listSites->clear();
	if (!xmlParse.FindElem(TP_D_SOAP_SITEINFOS))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SITEINFOS.");
		return resCode;
	}
	do
	{
		SiteInfoEx siteInfo;
		(void)xmlParse.IntoElem();
		std::string strtype;
		//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_URI, srcValue, elemValue, uiMaxLen);
		//strncpy_s(recuConfInfo->siteAccessInfos[i].uri,elemValue,TP_D_CONFID_MAX_LEN);
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.name))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
			listSites->clear();
			return resCode;
		}
		siteInfo.name = TP_Tool::UTF8ToANSI(siteInfo.name);
		//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_CONFACCESSCODE, srcValue, elemValue, uiMaxLen);
		//strncpy_s(recuConfInfo->siteAccessInfos[i].uri,elemValue,TP_D_CONFID_MAX_LEN);
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_URI, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.uri))
		{
			TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_URI.");
			listSites->clear();
			return resCode;
		}

		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_TYPE, TP_D_ELEM_OPTIONAL_FLAG, strtype))
		{
			TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_TYPE.");
			listSites->clear();
			return resCode;
		}

		siteInfo.type = atoi(strtype.c_str());

		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_RATE, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.rate))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RATE.");
			listSites->clear();
			return resCode;
		}


		listSites->push_back(siteInfo);
		xmlParse.OutOfElem();
		
	}while(xmlParse.NextElem());

	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_scheduleConfEx(const ConferenceInfoEx *conferenceInfo, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_SCHEDULECONFEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SCHEDULECONF);
	(void)xml.IntoElem();
	(void)Package_ConferenceInfo(conferenceInfo, &xml);
	(void)xml.OutOfElem();
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_Authenticate(const std::string &encryptPassword, std::string& xmlStr)
{
	/************************************************************************
	--- XML 格式 ---
	<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:smc="http://smc.huawei.com/">
	<soapenv:Header/>
	<soapenv:Body>
	<smc:Authenticate>
	<encryptPassword>l/qjnOSOaby2KWBXEXILX7qp</encryptPassword>
	</smc:Authenticate>
	</soapenv:Body>
	</soapenv:Envelope>

	************************************************************************/

	TP_DEBUG_TRACE("");

	
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_AUTHENTICATE, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_ENCRYPTPASSWORD);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(encryptPassword.c_str());
	xml.OutOfElem();
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}
	
	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_Logout(std::string& xmlStr)
{
	/************************************************************************
	--- XML 格式 ---
	<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:smc="http://smc.huawei.com/">
	<soapenv:Header/>
	<soapenv:Body>
	<smc:Logout/>
	</soapenv:Body>
	</soapenv:Envelope>
	************************************************************************/

	TP_DEBUG_TRACE("");

	
	CXml xml;
	
	if(Package_BasicSOAP(TP_D_SOAP_SMC_LOGOUT, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}
	
	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_KeepAlive(std::string& xmlStr)
{
	/************************************************************************
	--- XML 格式 ---
	<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:smc="http://smc.huawei.com/">
	<soapenv:Header/>
	<soapenv:Body>
	<smc:KeepAlive/>
	</soapenv:Body>
	</soapenv:Envelope>
	************************************************************************/

	TP_DEBUG_TRACE("");

	
	CXml xml;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_KEEPALIVE, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}
	
	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_prolongScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginDateTime, const std::string &prolongTime, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strTime[256]={0};
	CXml xml;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_PROLONG_SCHEDULED_CONFEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	if(beginDateTime.wYear || beginDateTime.wMonth || beginDateTime.wDay)
	{
		(void)xml.AddElem(TP_D_SOAP_BEGINDATE);
		(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
			,beginDateTime.wYear,beginDateTime.wMonth,beginDateTime.wDay
			,beginDateTime.wHour,beginDateTime.wMinute,beginDateTime.wSecond,beginDateTime.wMilliseconds
			,TP_Tool::GetLocalTimeZone().c_str());
		(void)xml.SetElemValue(strTime);
	}

	if(prolongTime.length())
	{
		(void)xml.AddElem(TP_D_SOAP_PROLONGTIME);
		(void)xml.SetElemValue(prolongTime.c_str());
	}
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;

}

int XMLProcess::SetXml_querySiteStatusEx(const list<string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strTime[256]={0};
	CXml xml;
	list<string>::const_iterator i;
	int first_flag = 1;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_SITE_STATUSEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	for(i=siteUris.begin();i!=siteUris.end();i++)
	{
		if(first_flag)
		{
			(void)xml.AddChildElem(TP_D_SOAP_SITEURIS);
			(void)xml.IntoElem();
			first_flag = 0;
		}
		else
		{
		(void)xml.AddElem(TP_D_SOAP_SITEURIS);
		}
		(void)xml.SetElemValue(i->c_str());
	}
	
	//xml.OutOfElem();
	(void)xml.AddElem(TP_D_SOAP_BEGINTIME);
	(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
		,beginTime.wYear,beginTime.wMonth,beginTime.wDay
		,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
		,TP_Tool::GetLocalTimeZone().c_str());
	(void)xml.SetElemValue(strTime);

	(void)xml.AddElem(TP_D_SOAP_DURATION);
	(void)xml.SetElemValue(duration.c_str());


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_queryConferencesStatusEx(const list<string>& confIds, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strTime[256]={0};
	CXml xml;
	list<string>::const_iterator i;
	int first_flag = 1;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_CONFERENCES_STATUSEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	for(i=confIds.begin();i!=confIds.end();i++)
	{
		if(first_flag)
		{
			(void)xml.AddChildElem(TP_D_SOAP_CONFIDS);
			(void)xml.IntoElem();
			first_flag = 0;
		}
		else
		{
			(void)xml.AddElem(TP_D_SOAP_CONFIDS);
		}
		(void)xml.SetElemValue(i->c_str());
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_queryConferencesStatusEx(const char *xmlStr, list<ConferenceStatusEx> *list_ConferenceStatus)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYCONFERENCESTATUSEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYCONFERENCESTATUSEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYCONFERENCESTATUSEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	list_ConferenceStatus->clear();
	if (!xmlParse.FindElem(TP_D_SOAP_CONFSTATUS))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CONFSTATUS.");
		return resCode;
	}
	do
	{
		std::string strVal;
		ConferenceStatusEx confStatus;
		(void)xmlParse.IntoElem();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_ID, TP_D_ELEM_OPTIONAL_FLAG, confStatus.id))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
			return resCode;
		}

		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_OPTIONAL_FLAG, confStatus.name))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
			return resCode;
		}
		confStatus.name = TP_Tool::UTF8ToANSI(confStatus.name);
		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_STATUS, TP_D_ELEM_MUST_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_STATUS.");
			return resCode;
		}
		if(strVal.length()!=0)
		{
			confStatus.status = TP_Tool::String2Int(strVal);
		}
		


		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_CHAIR, TP_D_ELEM_OPTIONAL_FLAG, confStatus.chair))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CHAIR.");
			return resCode;
		}

		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_BROADCAST, TP_D_ELEM_OPTIONAL_FLAG, confStatus.broadcast))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
			return resCode;
		}


		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_SPEAKING, TP_D_ELEM_OPTIONAL_FLAG, confStatus.speaking))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SPEAKING.");
			return resCode;
		}

		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_PRESENTATION, TP_D_ELEM_OPTIONAL_FLAG, confStatus.presentation))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_PRESENTATION.");
			return resCode;
		}
		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_ISLOCK, TP_D_ELEM_OPTIONAL_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ISLOCK.");
			return resCode;
		}
		
		if(strVal.length() != 0)
		{
			confStatus.isLock = TP_Tool::String2Int(strVal);
		}

		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_ISAUDIOSWITCH, TP_D_ELEM_OPTIONAL_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ISAUDIOSWITCH.");
			return resCode;
		}

		if(strVal.length() != 0)
		{
			confStatus.isAudioSwitch = TP_Tool::String2Int(strVal);
		}

		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_SWITCHGATE, TP_D_ELEM_OPTIONAL_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SWITCHGATE.");
			return resCode;
		}

		if(strVal.length() != 0)
		{
			confStatus.switchGate = TP_Tool::String2Int(strVal);
		}

		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_BEGINTIME, TP_D_ELEM_OPTIONAL_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BEGINTIME.");
			return resCode;
		}

		if(strVal.length()!=0)
		{
			(void)StringTimeFormatTOSystemtime(strVal,confStatus.beginTime);
		}

		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_ENDTIME, TP_D_ELEM_OPTIONAL_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ENDTIME.");
			return resCode;
		}

		if(strVal.length()!=0)
		{
			(void)StringTimeFormatTOSystemtime(strVal,confStatus.endTime);
		}

		list_ConferenceStatus->push_back(confStatus);
		xmlParse.OutOfElem();
	} while (xmlParse.NextElem());

	

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_queryScheduleConferencesEx(const QueryConfigEx &queryConfig, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strTime[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_SCHEDULE_CONFERENCESEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}

	(void)xml.AddChildElem(TP_D_SOAP_QUERY_CONFIG);
	(void)xml.IntoElem();

	int first_flag = 1;
	list<SortItemEx>::const_iterator i;
	for( i = queryConfig.sortItems.begin(); i != queryConfig.sortItems.end(); i++ )
	{
		if(first_flag)
		{
			(void)xml.AddChildElem(TP_D_SOAP_SORT_ITEMS);
			(void)xml.IntoElem();
			(void)xml.AddChildElem(TP_D_SOAP_SORT);
			(void)xml.IntoElem();
			(void)xml.SetElemValue( TP_Tool::Int2String( i->sort ).c_str() );
			(void)xml.AddElem(TP_D_SOAP_ITEM_INDEX);
			(void)xml.SetElemValue( TP_Tool::Int2String( i->itemIndex ).c_str() );
			(void)xml.OutOfElem();
			first_flag = 0;
		}
		else
		{
			(void)xml.AddElem(TP_D_SOAP_SORT_ITEMS);
			(void)xml.IntoElem();
			(void)xml.AddChildElem(TP_D_SOAP_SORT);
			(void)xml.IntoElem();
			(void)xml.SetElemValue( TP_Tool::Int2String( i->sort ).c_str() );
			(void)xml.AddElem(TP_D_SOAP_ITEM_INDEX);
			(void)xml.SetElemValue( TP_Tool::Int2String( i->itemIndex ).c_str() );
			(void)xml.OutOfElem();
		}
		//(void)xml.OutOfElem();
	}
	//(void)xml.OutOfElem();
	first_flag = 1;
	for ( list<StringFilterEx>::const_iterator ite = queryConfig.filters.begin(); ite != queryConfig.filters.end(); ite++ )
	{
		if(first_flag)
		{
			(void)xml.AddElem(TP_D_SOAP_FILTERS);
			(void)xml.AddAttribute(TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI,TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI_VALUE);
			(void)xml.AddAttribute(TP_D_SOAP_FILTERS_ATTR_XSI_TYPE,TP_D_SOAP_FILTERS_ATTR_XSI_TYPE_VALUE);
			(void)xml.IntoElem();
			(void)xml.AddChildElem(TP_D_SOAP_COLUMN_INDEX);
			(void)xml.IntoElem();
			(void)xml.SetElemValue( TP_Tool::Int2String( ite->columnIndex ).c_str() );
			(void)xml.AddElem(TP_D_SOAP_VALUE);
			(void)xml.SetElemValue(TP_Tool::ANSIToUTF8(ite->value).c_str() );
			(void)xml.OutOfElem();
			first_flag = 0;
		}
		else
		{
			(void)xml.AddElem(TP_D_SOAP_FILTERS);
			(void)xml.AddAttribute(TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI,TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI_VALUE);
			(void)xml.AddAttribute(TP_D_SOAP_FILTERS_ATTR_XSI_TYPE,TP_D_SOAP_FILTERS_ATTR_XSI_TYPE_VALUE);
			(void)xml.IntoElem();
			(void)xml.AddChildElem(TP_D_SOAP_COLUMN_INDEX);
			(void)xml.IntoElem();
			(void)xml.SetElemValue( TP_Tool::Int2String( ite->columnIndex ).c_str() );
			(void)xml.AddElem(TP_D_SOAP_VALUE);
			(void)xml.SetElemValue(TP_Tool::ANSIToUTF8(ite->value).c_str() );
			(void)xml.OutOfElem();
		}
	}
	//(void)xml.OutOfElem();

	(void)xml.AddElem(TP_D_SOAP_FOCUSITEM);
	(void)xml.IntoElem();
	(void)xml.SetElemValue( TP_Tool::Int2String(queryConfig.focusItem).c_str() );
	//(void)xml.OutOfElem();

	(void)xml.AddElem(TP_D_SOAP_PAGEPARAM);
	(void)xml.IntoElem();
	(void)xml.AddChildElem(TP_D_SOAP_NUMBERPERPAGE);
	(void)xml.IntoElem();
	(void)xml.SetElemValue( TP_Tool::Int2String( queryConfig.pageParam.numberPerPage ).c_str() );	
	(void)xml.AddElem(TP_D_SOAP_CURRENTPAGE);
	(void)xml.IntoElem();
	(void)xml.SetElemValue( TP_Tool::Int2String( queryConfig.pageParam.currentPage ).c_str() );

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_queryScheduleConferencesEx(const char *xmlStr, list<ConferenceStatusEx> *list_ConferenceStatus, PagesInfoEx  &pagesInfo)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYSCHEDULECONFERENCESEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYSCHEDULECONFERENCESEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYCONFERENCESTATUSEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_RESULTCODE_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_RESULTCODE_ELEM.");
		return resCode;
	}

	std::string strResultCode;
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_RSP_RESULTCODE_ELEM, TP_D_ELEM_OPTIONAL_FLAG, strResultCode))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}
	if ( "0" != strResultCode )
	{
		resCode = TP_Tool::String2Int( strResultCode );
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	list_ConferenceStatus->clear();
	if(xmlParse.FindElem(TP_D_SOAP_CONFS))
	{
		do
		{
			std::string strVal;
			ConferenceStatusEx confStatus;
			if(xmlParse.GetElem() == NULL)
			{
				continue;
			}
			if (strncmp(xmlParse.GetElem(),TP_D_SOAP_CONFS,strlen(TP_D_SOAP_CONFS)) == 0 )
			{
				if(xmlParse.IntoElem())
				{
					Parse_ConferenceStatusEx(&xmlParse,confStatus);
					list_ConferenceStatus->push_back(confStatus);
					xmlParse.OutOfElem();
				}
			}
			else
			{
				break;
			}
		} while (xmlParse.NextElem());
	}
	

	if(xmlParse.FindElem(TP_D_SOAP_PAGE_INFO))
	{
		(void)xmlParse.IntoElem();
		(void)Parse_PagesInfoEx(&xmlParse, pagesInfo);
		xmlParse.OutOfElem();
	}

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Package_AdhocConfTemplateParamEx(const AdhocConfTemplateParamEx &adhocConfTemplate, CXml *xml)
{
	if(!adhocConfTemplate.adhocConfTemplateId.length())
	{
		return TP_SDK_ERR_INVALID_PARAM;
	}
	xml->AddChildElem(TP_D_SOAP_ADHOC_CONF_TEMPLATE_ID);
	xml->IntoElem();
	xml->SetElemValue(adhocConfTemplate.adhocConfTemplateId.c_str());
	
	if(adhocConfTemplate.name.length())
	{
		xml->AddElem(TP_D_SOAP_NAME);
		xml->SetElemValue(TP_Tool::ANSIToUTF8(adhocConfTemplate.name).c_str());
	}

	if(adhocConfTemplate.accessCode.length())
	{
		xml->AddElem(TP_D_SOAP_ACCESS_CODE);
		xml->SetElemValue(adhocConfTemplate.accessCode.c_str());
	}

	if(adhocConfTemplate.duration.length())
	{
		xml->AddElem(TP_D_SOAP_DURATION);
		xml->SetElemValue(adhocConfTemplate.duration.c_str());
	}

	if(adhocConfTemplate.billCode.length())
	{
		xml->AddElem(TP_D_SOAP_BILL_CODE);
		xml->SetElemValue(adhocConfTemplate.billCode.c_str());
	}

	if(adhocConfTemplate.password.length())
	{
		xml->AddElem(TP_D_SOAP_PASSWORD);
		xml->SetElemValue(adhocConfTemplate.password.c_str());
	}

	xml->AddElem(TP_D_SOAP_CPRESOURCE);
	xml->SetElemValue(TP_Tool::Int2String(adhocConfTemplate.cpResouce).c_str());

	if(adhocConfTemplate.rate.length())
	{
		xml->AddElem(TP_D_SOAP_RATE);
		xml->SetElemValue(adhocConfTemplate.rate.c_str());
	}

	xml->AddElem(TP_D_SOAP_MEDIA_ENCRYPT_TYPE);
	xml->SetElemValue(TP_Tool::Int2String(adhocConfTemplate.mediaEncryptType).c_str());

	xml->AddElem(TP_D_SOAP_IS_LIVE_BROADCAST);
	xml->SetElemValue(TP_Tool::Int2String(adhocConfTemplate.isLiveBroadcast).c_str());

	xml->AddElem(TP_D_SOAP_ISRECORDING);
	xml->SetElemValue(TP_Tool::Int2String(adhocConfTemplate.isRecording).c_str());

	xml->AddElem(TP_D_SOAP_PRESENTATION);
	xml->SetElemValue(TP_Tool::Int2String(adhocConfTemplate.presentation).c_str());

	if(adhocConfTemplate.chairmanPassword.length())
	{
		xml->AddElem(TP_D_SOAP_CHAIRMAN_PASSWORD);
		xml->SetElemValue(adhocConfTemplate.chairmanPassword.c_str());
	}

	xml->AddElem(TP_D_SOAP_PRESENTATION_VIDEO);
	xml->IntoElem();
	xml->AddChildElem(TP_D_SOAP_PROTOCOL);
	xml->IntoElem();
	xml->SetElemValue(TP_Tool::Int2String(adhocConfTemplate.presentationVideo.videoProtocol).c_str());

	xml->AddElem(TP_D_SOAP_FORMAT);
	xml->SetElemValue(TP_Tool::Int2String(adhocConfTemplate.presentationVideo.videoFormat).c_str());
	xml->OutOfElem();

	if(adhocConfTemplate.mainSiteUri.length())
	{
		xml->AddElem(TP_D_SOAP_MAIN_SITE_URI);
		xml->SetElemValue(adhocConfTemplate.mainSiteUri.c_str());
	}

	if(adhocConfTemplate.notice.content.length() || adhocConfTemplate.notice.email.length()||adhocConfTemplate.notice.telephone.length())
	{
		xml->AddElem(TP_D_SOAP_NOTICE);
		xml->IntoElem();
		
		if(adhocConfTemplate.notice.email.length())
		{
			xml->AddChildElem(TP_D_SOAP_SEMAIL);
			xml->IntoElem();
			xml->SetElemValue(adhocConfTemplate.notice.email.c_str());
		}

		if(adhocConfTemplate.notice.content.length())
		{
			xml->AddElem(TP_D_SOAP_SCONTENT);
			xml->SetElemValue(adhocConfTemplate.notice.content.c_str());
		}

		if(adhocConfTemplate.notice.telephone.length())
		{
			xml->AddElem(TP_D_SOAP_TELEPHONE);
			xml->SetElemValue(adhocConfTemplate.notice.telephone.c_str());
		}
		xml->OutOfElem();
	}

	xml->AddElem(TP_D_SOAP_MAX_SITES_COUNT);
	xml->SetElemValue(TP_Tool::Int2String(adhocConfTemplate.maxSitesCount).c_str());

	xml->AddElem(TP_D_SOAP_RESERVED_CSD_PORTS);
	xml->SetElemValue(TP_Tool::Int2String(adhocConfTemplate.reservedCsdPorts).c_str());

	xml->AddElem(TP_D_SOAP_STATE);
	xml->SetElemValue(TP_Tool::Int2String(adhocConfTemplate.state).c_str());

	
	list<SiteInfoEx>::const_iterator i;
	if(adhocConfTemplate.sites.size())
	{
		
		for(i=adhocConfTemplate.sites.begin();i!=adhocConfTemplate.sites.end();i++)
		{
			xml->AddElem(TP_D_SOAP_SITES);
			xml->IntoElem();
			Package_SiteInfoEx(&(*i),xml);

			//xml->OutOfElem();
		}
	}

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_addAdhocConfTemplateEx(const std::string &orgId, const AdhocConfTemplateParamEx &adhocConfTemplate, std::string &xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;
	list<string>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_ADD_ADHOC_CONF_TEMPLATEEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.IntoElem();
	
	if(orgId.length())
	{
		(void)xml.AddChildElem(TP_D_SOAP_ORGID);
		(void)xml.IntoElem();
		(void)xml.SetElemValue(orgId.c_str());
	}
	
	(void)xml.AddElem(TP_D_SOAP_ADHOC_CONF_TEMPLATE);
	(void)xml.IntoElem();
	(void)Package_AdhocConfTemplateParamEx(adhocConfTemplate, &xml);

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_addAdhocConfTemplateEx(const char *xmlStr, std::string &adhocConfTemplateId)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_ADDADHOCCONFTEMPLATEEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		resCode = TP_SDK_ERR_XML_PARSE;
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		resCode = TP_SDK_ERR_XML_FIND_ELEM;
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		resCode = TP_SDK_ERR_XML_FIND_ELEM;
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ADDADHOCCONFTEMPLATEEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYCONFERENCESTATUSEX.");
		resCode = TP_SDK_ERR_XML_FIND_ELEM;
		return resCode;
	}
	(void)xmlParse.IntoElem();


	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_ADHOC_CONF_TEMPLATE_ID, TP_D_ELEM_MUST_FLAG, adhocConfTemplateId))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ADHOC_CONF_TEMPLATE_ID.");
		resCode = TP_SDK_ERR_XML_GET_ELEM_VALUE;
	}


	return resCode;
}


int XMLProcess::SetXml_editAdhocConfTemplateEx(const AdhocConfTemplateParamEx &adhocConfTemplate, std::string &xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;
	list<string>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_EDIT_ADHOC_CONF_TEMPLATEEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.IntoElem();


	(void)xml.AddChildElem(TP_D_SOAP_ADHOC_CONF_TEMPLATE);
	(void)xml.IntoElem();
	(void)Package_AdhocConfTemplateParamEx(adhocConfTemplate, &xml);

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_editAdhocConfTemplateEx(const char *xmlStr)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_EDITADHOCCONFTEMPLATEEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
	}

	return resCode;
}

int XMLProcess::SetXml_delAdhocConfTemplateEx(const std::string &adhocConfTemplateId, std::string &xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;
	list<string>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_DEL_ADHOC_CONF_TEMPLATEEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.IntoElem();

	(void)xml.AddChildElem(TP_D_SOAP_ADHOC_CONF_TEMPLATE_ID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(adhocConfTemplateId.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_delAdhocConfTemplateEx(const char *xmlStr)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_DELADHOCCONFTEMPLATEEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
	}

	return resCode;
}


int XMLProcess::SetXml_queryAdhocConfTemplateListEx(const QueryConfigEx &queryConfig, std::string &xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_ADHOC_CONF_TEMPLATE_LISTEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_QUERY_CONFIG);
	(void)xml.IntoElem();
	(void)Package_QueryConfigEx(&queryConfig, &xml);
	xml.OutOfElem();

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_queryAdhocConfTemplateListEx(const char *xmlStr, list<AdhocConfTemplateParamEx> *list_AdhocConfTemplateParam, PagesInfoEx &pagesInfo)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYADHOCCONFTEMPLATELISTEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYADHOCCONFTEMPLATELISTEX))
	{
		TP_LOG_ERROR("parse xml failed, not found %s. ",TP_D_SOAP_RSP_QUERYADHOCCONFTEMPLATELISTEX);
		return resCode;
	}
	(void)xmlParse.IntoElem();

	if (xmlParse.FindElem(TP_D_SOAP_ADHOCCONFERENCES))
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}

			if(strncmp(xmlParse.GetElem(),TP_D_SOAP_ADHOCCONFERENCES,sizeof(TP_D_SOAP_ADHOCCONFERENCES)) !=0)
			{
				xmlParse.OutOfElem();
				break;
			}
			AdhocConfTemplateParamEx adhocConfTemplateParam;
			(void)xmlParse.IntoElem();
			(void)Parse_AdhocConfTemplateParamEx(&xmlParse, adhocConfTemplateParam);
			xmlParse.OutOfElem();
			list_AdhocConfTemplateParam->push_back(adhocConfTemplateParam);

		} while (xmlParse.NextElem());
	}

	(void)xmlParse.IntoElem();
	if(xmlParse.FindElem(TP_D_SOAP_PAGE_INFO))
	{
		(void)xmlParse.IntoElem();
		(void)Parse_PagesInfoEx(&xmlParse, pagesInfo);
		xmlParse.OutOfElem();
	}

	return TP_SDK_ERR_SUCCESS;	
}


int XMLProcess::Package_OngoingConfSubscribeEx(const OngoingConfSubscribeEx &subscribeInfos, CXml *xml)
{
	int resCode = TP_SDK_ERR_INVALID_PARAM;

	//(void)xml->AddChildElem(TP_D_SOAP_SUBSCRIBE_INFOS);
	//(void)xml->AddElem(TP_D_SOAP_SUBSCRIBE_INFOS);
	//(void)xml->IntoElem();
	(void)xml->AddAttribute(TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI,TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI_VALUE);
	(void)xml->AddAttribute(TP_D_SOAP_FILTERS_ATTR_XSI_TYPE,TP_D_SOAP_SMC_ONGOING_CONF_SUBSCRIBE);
	(void)xml->IntoElem();

	(void)xml->AddChildElem(TP_D_SOAP_IS_SUBSCRIBE);
	(void)xml->IntoElem();
	(void)xml->SetElemValue(TP_Tool::Int2String(subscribeInfos.isSubscribe).c_str());
	
	if ( subscribeInfos.confIds.empty() == false )
	{

		(void)xml->AddElem(TP_D_SOAP_CONFIDS);
		(void)xml->IntoElem();
		(void)xml->SetElemValue(subscribeInfos.confIds.c_str());
		(void)xml->IntoElem();

	}
	resCode = TP_SDK_ERR_SUCCESS;
	return resCode;
}


int XMLProcess::Package_ScheduledConfSubscribeEx(const ScheduledConfSubscribeEx &subscribeInfos, CXml *xml)
{
	int resCode = TP_SDK_ERR_INVALID_PARAM;

	//(void)xml->AddChildElem(TP_D_SOAP_SUBSCRIBE_INFOS);
	//(void)xml->IntoElem();
	(void)xml->AddAttribute(TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI,TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI_VALUE);
	(void)xml->AddAttribute(TP_D_SOAP_FILTERS_ATTR_XSI_TYPE,TP_D_SOAP_SMC_SCHEDULED_CONF_SUBSCIRBE);
	(void)xml->IntoElem();

	(void)xml->AddChildElem(TP_D_SOAP_IS_SUBSCRIBE);
	(void)xml->IntoElem();
	(void)xml->SetElemValue(TP_Tool::Int2String(subscribeInfos.isSubscribe).c_str());

	if ( subscribeInfos.confIds.empty() == false )
	{
		(void)xml->AddElem(TP_D_SOAP_CONFIDS);
		(void)xml->IntoElem();
		(void)xml->SetElemValue(subscribeInfos.confIds.c_str());
		(void)xml->IntoElem();
	}


	resCode = TP_SDK_ERR_SUCCESS;
	return resCode;
}

int XMLProcess::SetXml_subscribeEx(const list<SubscribeInfoEx *>  &subscribeInfos, std::string &xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;
	list<SubscribeInfoEx *>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_SUBSCRIBE, &xml)!=TP_SDK_ERR_SUCCESS){}else{}

	
	bool bFirstChildElem = true;
	for(i=subscribeInfos.begin(); i!=subscribeInfos.end(); i++)
	{
		if(TP_D_SCHEDULED_CONF_SUBSCRIBE_TYPE == (*i)->type)
		{
			ScheduledConfSubscribeEx *pSubscribe = (ScheduledConfSubscribeEx *)&(**i);
			if ( true == bFirstChildElem )
			{
				(void)xml.AddChildElem(TP_D_SOAP_SUBSCRIBE_INFOS);
				(void)xml.IntoElem();
				Package_ScheduledConfSubscribeEx((*pSubscribe), &xml);
				(void)xml.OutOfElem();
				bFirstChildElem = false;
			} 
			else
			{
				(void)xml.AddElem(TP_D_SOAP_SUBSCRIBE_INFOS);
				Package_ScheduledConfSubscribeEx((*pSubscribe), &xml);
				(void)xml.OutOfElem();
			}

		}
		else if(TP_D_ONGOING_CONF_SUBSCRIBE_TYPE == (*i)->type)
		{
			OngoingConfSubscribeEx *pSubscribe = (OngoingConfSubscribeEx *)&(**i);
			if ( true == bFirstChildElem )
			{
				(void)xml.AddChildElem(TP_D_SOAP_SUBSCRIBE_INFOS);
				(void)xml.IntoElem();
				Package_OngoingConfSubscribeEx((*pSubscribe), &xml);
				(void)xml.OutOfElem();
				bFirstChildElem = false;
			} 
			else
			{
				(void)xml.AddElem(TP_D_SOAP_SUBSCRIBE_INFOS);
				Package_OngoingConfSubscribeEx((*pSubscribe), &xml);
				(void)xml.OutOfElem();
			}
		}
		else
		{
			TP_LOG_ERROR("subscribeInfos type:%d is error",(*i)->type);
			return TP_SDK_ERR_INVALID_PARAM;
		}

		
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetRSPXml_subscribeEx(const char *xmlStr)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_SUBSCRIBEEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
	}

	return resCode;
}


int XMLProcess::SetXml_enablePushEx(int pushMode,const std::string &extendParameter, std::string &xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;
	list<string>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_ENABLE_PUSH, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_PUSH_MODE);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(TP_Tool::Int2String(pushMode).c_str());
	
	if(extendParameter.length())
	{
		(void)xml.AddElem(TP_D_SOAP_EXTEND_PARAMETER);
		(void)xml.SetElemValue(extendParameter.c_str());
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_enablePushEx(const char *xmlStr)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode( xmlStr, TP_D_SOAP_RSP_ENABLEDPUSHEX );
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
	}

	return resCode;
}

int XMLProcess::SetXml_queryNotificationEx(std::string &xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;
	list<string>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_NOTIFICATION, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int  XMLProcess::Parse_OngoingConfNotificationEx(CXml *xmlParse, OngoingConfNotificationEx *notification)
{
	std::string strVal;
	int resCode = TP_SDK_ERR_XML_PARSE;
	
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_EVENT, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}

	if(strVal.length())
	{
		notification->event = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CONFID, TP_D_ELEM_OPTIONAL_FLAG, notification->confId))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_BEGINTIME, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}
	if(strVal.length()!=0)
	{
		(void)StringTimeFormatTOSystemtime(strVal,notification->beginTime);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SITEURI, TP_D_ELEM_OPTIONAL_FLAG, notification->siteUri))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}

	if (xmlParse->FindElem(TP_D_SOAP_CHANGES))
	{
		do
		{
			if(xmlParse->GetElem() == NULL)
			{
				continue;
			}
			if(strncmp(xmlParse->GetElem(),TP_D_SOAP_CHANGES,sizeof(TP_D_SOAP_CHANGES))!=0)
			{
				break;
			}
			const char *type_name = xmlParse->GetAttributeValue(TP_D_SOAP_FILTERS_ATTR_XSI_TYPE);
			if(!type_name)
			{
				continue;
			}
			if(strncmp(type_name,TP_D_SOAP_RSP_CONFERENCE_STATUS,sizeof(TP_D_SOAP_RSP_CONFERENCE_STATUS)) == 0)
			{
				ConferenceStatusEx *status = new ConferenceStatusEx;
				if(!status)
				{
					break;
				}
				//status->structtype = TP_D_CONFERENCE_STATUS_TYPE;
				(void)xmlParse->IntoElem();
				(void)Parse_ConferenceStatusEx(xmlParse, *status);
				notification->changes.push_back(status);
				status = NULL;
				xmlParse->OutOfElem();
			}
			else if(strncmp(type_name, TP_D_SOAP_RSP_STIE_STATUS, sizeof(TP_D_SOAP_RSP_STIE_STATUS)) == 0)
			{
				SiteStatusEx *status = new SiteStatusEx;
				if(!status)
				{
					break;
				}
				//status->structtype = TP_D_SITE_STATUS_TYPE;
				(void)xmlParse->IntoElem();
				(void)Parse_siteFreeBusyStates(xmlParse, *status);
				notification->changes.push_back(status);
				status = NULL;
				xmlParse->OutOfElem();
			}
			
		}while(xmlParse->NextElem());
	}
	

	return TP_SDK_ERR_SUCCESS;
}

int  XMLProcess::Parse_ScheduledConfNotificationEx(CXml *xmlParse, ScheduledConfNotificationEx *notification)
{
	std::string strVal;
	int resCode = TP_SDK_ERR_XML_PARSE;

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_EVENT, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}

	if(strVal.length())
	{
		notification->event = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_EVENT, TP_D_ELEM_OPTIONAL_FLAG, notification->confId))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_BEGINTIME, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}
	if(strVal.length()!=0)
	{
		(void)StringTimeFormatTOSystemtime(strVal,notification->beginTime);
	}
	return TP_SDK_ERR_SUCCESS;
}

int  XMLProcess::Parse_OverflowNotificationEx(CXml *xmlParse, OverflowNotificationEx *notification)
{
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::GetRSPXml_queryNotificationEx(const char *xmlStr, list<NotificationEx *> &list_Notification)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERY_NOTIFICATIONEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERY_NOTIFICATIONEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_SYNCSITESTATUSEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	//map_SiteStatus->clear();
	if (xmlParse.FindElem(TP_D_SOAP_NOTIFICATIONS))
	{
		do
		{
			std::string uri;
			if(xmlParse.GetElem() == NULL)
			{
				continue;
			}
			if(strncmp(xmlParse.GetElem(),TP_D_SOAP_NOTIFICATIONS,sizeof(TP_D_SOAP_NOTIFICATIONS))!=0)
			{
				break;
			}
			const char *type_name = xmlParse.GetAttributeValue(TP_D_SOAP_FILTERS_ATTR_XSI_TYPE);
			if(!type_name)
			{
				continue;
			}
			if(strncmp(type_name, TP_D_SOAP_RSP_ONGOING_CONF_NOTIFICATION, sizeof(TP_D_SOAP_RSP_ONGOING_CONF_NOTIFICATION))==0)
			{
				OngoingConfNotificationEx *notification = new OngoingConfNotificationEx;
				if(!notification)
				{
					break;
				}
				if(xmlParse.IntoElem()==true)
				{
					//notification->type = TP_D_ONGOING_CONF_NOTIFICATION_TYPE;
					(void)Parse_OngoingConfNotificationEx(&xmlParse, notification);

					(void)list_Notification.push_back(notification);

					notification = NULL;
					xmlParse.OutOfElem();
				}
				
			}
			else if(strncmp(type_name, TP_D_SOAP_RSP_SCHEDULED_CONF_NOTIFICATION, sizeof(TP_D_SOAP_RSP_SCHEDULED_CONF_NOTIFICATION))==0)
			{
				ScheduledConfNotificationEx *notification = new ScheduledConfNotificationEx;
				if(!notification)
				{
					break;
				}
				if(xmlParse.IntoElem() == true)
				{
					//notification->type = TP_D_SCHEDULED_CONF_NOTIFICATION_TYPE;
					(void)Parse_ScheduledConfNotificationEx(&xmlParse, notification);

					(void)list_Notification.push_back(notification);
					notification = NULL;
					xmlParse.OutOfElem();
				}
			}
			else if(strncmp(type_name, TP_D_SOAP_RSP_OVERFLOW_NOTIFICATION, sizeof(TP_D_SOAP_RSP_OVERFLOW_NOTIFICATION))==0)
			{
				OverflowNotificationEx *notification = new OverflowNotificationEx;
				if(!notification)
				{
					break;
				}
				if(xmlParse.IntoElem() == true)
				{
					//m_pOverFlowNotificationEx->type = TP_D_OVERFLOW_NOTIFICATION_TYPE;
					(void)Parse_OverflowNotificationEx(&xmlParse, notification);

					(void)list_Notification.push_back(notification);
					notification = NULL;
					xmlParse.OutOfElem();
				}
			}


		}while(xmlParse.NextElem());	
	}
	

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_queryConfSitesStatusEx(const std::string &confId, const list<std::string> &siteUris, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	CXml xml;
	list<string>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_CONF_SITE_STATUS, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	for(i=siteUris.begin();i!=siteUris.end();i++)
	{
		
		(void)xml.AddElem(TP_D_SOAP_SITEURIS);
		(void)xml.SetElemValue(i->c_str());
	}


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_synchSiteStatusEx(const list<string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strTime[256]={0};
	int first_flag=1;
	CXml xml;
	list<string>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_SYNC_SITE_STATUS, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	for(i=siteUris.begin(); i!=siteUris.end(); i++)
	{
		if(first_flag)
		{
			(void)xml.AddChildElem(TP_D_SOAP_SITEURIS);
			(void)xml.IntoElem();
			first_flag = 0;
		}
		else
		{
			(void)xml.AddElem(TP_D_SOAP_SITEURIS);
		}
		
		(void)xml.SetElemValue(i->c_str());
	}
	if(first_flag)
	{
		if (beginTime.wYear || beginTime.wMonth || beginTime.wDay)
		{
			(void)xml.AddChildElem(TP_D_SOAP_BEGINTIME);
			(void)xml.IntoElem();
			(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
				,beginTime.wYear,beginTime.wMonth,beginTime.wDay
				,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
				,TP_Tool::GetLocalTimeZone().c_str());
			(void)xml.SetElemValue(strTime);
		}
		
		//first_flag = 0;
	}
	else
	{
		if (beginTime.wYear || beginTime.wMonth || beginTime.wDay)
		{
			(void)xml.AddElem(TP_D_SOAP_BEGINTIME);
			(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
				,beginTime.wYear,beginTime.wMonth,beginTime.wDay
				,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
				,TP_Tool::GetLocalTimeZone().c_str());
			(void)xml.SetElemValue(strTime);
		}
		
	}

	(void)xml.AddElem(TP_D_SOAP_DURATION);
	(void)xml.SetElemValue(duration.c_str());



	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_synchSiteStatusEx(const char *xmlStr, map<string, list<FreeBusyStateEx>> *map_SiteStatus)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_SYNCSITESTATUSEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_SYNCSITESTATUSEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_SYNCSITESTATUSEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	map_SiteStatus->clear();
	if (!xmlParse.FindElem(TP_D_SOAP_SITE_FREE_BUSY_STATES))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SITE_FREE_BUSY_STATES.");
		return resCode;
	}
	do
	{
		std::string uri;
		list<FreeBusyStateEx> list_SiteStatus;
		(void)xmlParse.IntoElem();
		(void)Parse_siteFreeBusyStates(&xmlParse, uri,list_SiteStatus);

		(void)map_SiteStatus->insert(pair<string, list<FreeBusyStateEx>>(uri,list_SiteStatus));

		xmlParse.OutOfElem();
	}while(xmlParse.NextElem());

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_addSiteToConfEx(const std::string &confId, const SiteInfoEx &siteInfo, const SYSTEMTIME &beginTime, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strTime[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_ADD_SITE_TO_CONF, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	(void)xml.AddElem(TP_D_SOAP_SITEINFO);
	(void)Package_SiteInfoEx(&siteInfo,&xml);
	if(beginTime.wYear || beginTime.wMonth || beginTime.wDay)
	{
		(void)xml.AddElem(TP_D_SOAP_BEGINTIME);
		(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
			,beginTime.wYear,beginTime.wMonth,beginTime.wDay
			,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
			,TP_Tool::GetLocalTimeZone().c_str());
		(void)xml.SetElemValue(strTime);
	}
	(void)xml.OutOfElem();
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_addSiteToConfEx(const char *xmlStr, list<SiteAccessInfoEx> *siteAccessInfo)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}

	if(NULL == siteAccessInfo)
	{
		TP_LOG_ERROR("siteAccessInfo is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_ADDSITETOCONFEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ADDSITETOCONFEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ADDSITETOCONFEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	do
	{
		if (xmlParse.GetElem()==NULL)
		{
			break;
		}
		if(strcmp(xmlParse.GetElem(),TP_D_SOAP_SITEACCESSINFOS) !=0)
		{
			continue;
		}
		SiteAccessInfoEx tmp_siteAccessInfo;
		(void)xmlParse.IntoElem();
		(void)Parse_SiteAccessInfoEx(&xmlParse, tmp_siteAccessInfo);
		xmlParse.OutOfElem();
		siteAccessInfo->push_back(tmp_siteAccessInfo);

	} while (xmlParse.NextElem());
	return TP_SDK_ERR_SUCCESS;	
}


int  XMLProcess::SetXml_delSiteFromConfEx(const std::string &confId, const std::string &siteUri, const SYSTEMTIME &beginTime, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strTime[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_DEL_SITE_FROM_CONF, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	(void)xml.AddElem(TP_D_SOAP_SITEURI);
	(void)xml.SetElemValue(siteUri.c_str());
	if(beginTime.wYear || beginTime.wMonth || beginTime.wDay)
	{
		(void)xml.AddElem(TP_D_SOAP_BEGINTIME);
		(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
			,beginTime.wYear,beginTime.wMonth,beginTime.wDay
			,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
			,TP_Tool::GetLocalTimeZone().c_str());
		(void)xml.SetElemValue(strTime);
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_connectSitesEx(const std::string &confId, const list<std::string> &siteUris, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strTime[256]={0};
	CXml xml;
	list<string>::const_iterator i;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_CONNECT_SITE, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	for(i=siteUris.begin(); i!=siteUris.end(); i++)
	{
		(void)xml.AddElem(TP_D_SOAP_SITEURIS);
		(void)xml.SetElemValue(i->c_str());
	}

	
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_disconnectSitesEx(const std::string &confId, const list<std::string> &siteUris, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strTime[256]={0};
	CXml xml;
	list<string>::const_iterator i;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_DISCONNECT_SITE, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	for(i=siteUris.begin(); i!=siteUris.end(); i++)
	{
		(void)xml.AddElem(TP_D_SOAP_SITEURIS);
		(void)xml.SetElemValue(i->c_str());
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_delScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginTime, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strTime[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_DEL_SCHEDULED_CONF, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	if(beginTime.wYear != 0 || beginTime.wMonth !=0 || beginTime.wDay != 0)
	{
		(void)xml.AddElem(TP_D_SOAP_BEGINTIME);
		(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
			,beginTime.wYear,beginTime.wMonth,beginTime.wDay
			,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
			,TP_Tool::GetLocalTimeZone().c_str());
		(void)xml.SetElemValue(strTime);
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Package_MultiPointCDRQueryConfigEx(const MultiPointCDRQueryConfigEx *queryConfig,CXml *xml)
{
	char strTime[256]={0};
	char strTmp[256]={0};
	(void)xml->AddChildElem(TP_D_SOAP_BEGINTIME);
	(void)xml->IntoElem();
	(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
		,queryConfig->beginTime.wYear,queryConfig->beginTime.wMonth,queryConfig->beginTime.wDay
		,queryConfig->beginTime.wHour,queryConfig->beginTime.wMinute,queryConfig->beginTime.wSecond,queryConfig->beginTime.wMilliseconds
		,TP_Tool::GetLocalTimeZone().c_str());

	(void)xml->SetElemValue(strTime);
	(void)xml->AddElem(TP_D_SOAP_DURATION);
	(void)xml->SetElemValue(queryConfig->duration.c_str());
	if(queryConfig->siteUri.length())
	{
		(void)xml->AddElem(TP_D_SOAP_SITEURI);
		(void)xml->SetElemValue(queryConfig->siteUri.c_str());
	}
	(void)xml->AddElem(TP_D_SOAP_PAGEPARAM);
	(void)xml->AddChildElem(TP_D_SOAP_NUMBERPERPAGE);
	(void)xml->IntoElem();
	(void)sprintf_s(strTmp,255,"%d",queryConfig->pageParam.numberPerPage);
	(void)xml->SetElemValue(strTmp);
	(void)xml->AddElem(TP_D_SOAP_CURRENT_PAGE);
	(void)sprintf_s(strTmp,255,"%d",queryConfig->pageParam.currentPage);
	(void)xml->SetElemValue(strTmp);
	(void)xml->OutOfElem();
	(void)xml->OutOfElem();
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Package_PointToPointCDRQueryConfigEx(const PointToPointCDRQueryConfigEx *queryConfig,CXml *xml)
{
	char strTime[256]={0};
	char strTmp[256]={0};
	(void)xml->AddChildElem(TP_D_SOAP_BEGINTIME);
	(void)xml->IntoElem();
	(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
		,queryConfig->beginTime.wYear,queryConfig->beginTime.wMonth,queryConfig->beginTime.wDay
		,queryConfig->beginTime.wHour,queryConfig->beginTime.wMinute,queryConfig->beginTime.wSecond,queryConfig->beginTime.wMilliseconds
		,TP_Tool::GetLocalTimeZone().c_str());
	(void)xml->SetElemValue(strTime);
	(void)xml->AddElem(TP_D_SOAP_DURATION);
	(void)xml->SetElemValue(queryConfig->duration.c_str());
	
	if (queryConfig->endPoint.siteUri.length())
	{
		(void)xml->AddElem(TP_D_SOAP_ENDPOINT);
		(void)xml->AddChildElem(TP_D_SOAP_TYPE);
		(void)xml->IntoElem();
		(void)sprintf_s(strTmp,255,"%d",queryConfig->endPoint.type);
		(void)xml->SetElemValue(strTmp);
		(void)xml->AddElem(TP_D_SOAP_SITEURI);
		(void)xml->SetElemValue(queryConfig->endPoint.siteUri.c_str());
		(void)xml->OutOfElem();
	}
	

	(void)xml->AddElem(TP_D_SOAP_PAGEPARAM);
	(void)xml->AddChildElem(TP_D_SOAP_NUMBERPERPAGE);
	(void)xml->IntoElem();
	(void)sprintf_s(strTmp,255,"%d",queryConfig->pageParam.numberPerPage);
	(void)xml->SetElemValue(strTmp);
	(void)xml->AddElem(TP_D_SOAP_CURRENT_PAGE);
	(void)sprintf_s(strTmp,255,"%d",queryConfig->pageParam.currentPage);
	(void)xml->SetElemValue(strTmp);
	(void)xml->OutOfElem();
	(void)xml->OutOfElem();
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_queryMultiPointCDREx(const MultiPointCDRQueryConfigEx &queryConfig, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strTime[256]={0};
	CXml xml;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_MULTI_POINT_CDR, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_QUERY_CONFIG);
	(void)xml.IntoElem();
	(void)Package_MultiPointCDRQueryConfigEx(&queryConfig, &xml);
	
	xml.OutOfElem();


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Parse_PagesInfoEx(CXml *xmlParse, PagesInfoEx &pageInfo)
{
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_TOTAL_PAGES, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_TOTAL_PAGES.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length())
	{
		pageInfo.totalPages = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CURRENT_PAGE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CURRENT_PAGE.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length())
	{
		pageInfo.currentPage = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_TOTAL_RECORDS, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_TOTAL_RECORDS.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length())
	{
		pageInfo.totalRecords = TP_Tool::String2Int(strVal);
	}

	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::Parse_MultiPointCDREx(CXml *xmlParse, MultiPointCDREx &multiPointCDR)
{
	std::string strVal;
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SITENAME, TP_D_ELEM_MUST_FLAG, multiPointCDR.siteName))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SITENAME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	multiPointCDR.siteName = TP_Tool::UTF8ToANSI(multiPointCDR.siteName);

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SITEURI, TP_D_ELEM_MUST_FLAG, multiPointCDR.siteUri))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SITEURI.");
		return TP_SDK_ERR_XML_PARSE;
	}
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SITETYPE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SITETYPE.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length())
	{
		multiPointCDR.siteType = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_PARTICIPANT_TYPE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_PARTICIPANT_TYPE.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length())
	{
		multiPointCDR.participantType = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_RATE, TP_D_ELEM_MUST_FLAG, multiPointCDR.rate))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RATE.");
		return TP_SDK_ERR_XML_PARSE;
	}


	
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_STARTTIME, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_STARTTIME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{

		(void)StringTimeFormatTOSystemtime(strVal, multiPointCDR.startTime);
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ENDTIME, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ENDTIME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		(void)StringTimeFormatTOSystemtime(strVal, multiPointCDR.endTime);

	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CONFERENCE_NAME, TP_D_ELEM_MUST_FLAG, multiPointCDR.conferenceName))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CONFERENCE_NAME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	multiPointCDR.conferenceName = TP_Tool::UTF8ToANSI(multiPointCDR.conferenceName);

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CONFERENCE_ID, TP_D_ELEM_MUST_FLAG, multiPointCDR.conferenceId))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CONFERENCE_ID.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CONFERENCE_CREATER, TP_D_ELEM_MUST_FLAG, multiPointCDR.conferenceCreater))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CONFERENCE_CREATER.");
		return TP_SDK_ERR_XML_PARSE;
	}
	multiPointCDR.conferenceCreater = TP_Tool::UTF8ToANSI(multiPointCDR.conferenceCreater);

	//not follow spec,please check.
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_BILL_CODE, TP_D_ELEM_MUST_FLAG, multiPointCDR.billCode))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BILL_CODE.");
		return TP_SDK_ERR_XML_PARSE;
	}


	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Parse_PointToPointCDREx(CXml *xmlParse, PointToPointCDREx &PointToPointCDR)
{

	std::string strVal;
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CALLING_URI, TP_D_ELEM_MUST_FLAG, PointToPointCDR.callingUri))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CALLING_URI.");
		return TP_SDK_ERR_XML_PARSE;
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CALLING_PROTOCOL, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CALLING_PROTOCOL.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length())
	{
		PointToPointCDR.callingProtocol = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CALLED_URI, TP_D_ELEM_MUST_FLAG, PointToPointCDR.calledUri))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CALLED_URI.");
		return TP_SDK_ERR_XML_PARSE;
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CALLED_PROTOCOL, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CALLED_PROTOCOL.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		PointToPointCDR.calledProtocol = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_RATE, TP_D_ELEM_MUST_FLAG, PointToPointCDR.rate))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RATE.");
		return TP_SDK_ERR_XML_PARSE;
	}



	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_STARTTIME, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_STARTTIME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		
		(void)StringTimeFormatTOSystemtime(strVal, PointToPointCDR.startTime);


	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ENDTIME, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ENDTIME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		(void)StringTimeFormatTOSystemtime(strVal, PointToPointCDR.endTime);

	}

	return TP_SDK_ERR_SUCCESS;

}



int XMLProcess::GetRSPXml_queryMultiPointCDREx(const char *xmlStr, QueryMultiPointCDRExResponse *queryMultiPointCDR)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYMULTIPOINTCDREX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYMULTIPOINTCDREX))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_QUERYMULTIPOINTCDREX. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	queryMultiPointCDR->cdr.clear();
	
	if (xmlParse.FindElem(TP_D_SOAP_CDR))		//error,lich
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse.GetElem(),TP_D_SOAP_CDR) !=0)
			{
				break;
			}

			MultiPointCDREx MultiPointCDR;
			(void)xmlParse.IntoElem();
			(void)Parse_MultiPointCDREx(&xmlParse, MultiPointCDR);

			queryMultiPointCDR->cdr.push_back(MultiPointCDR);
			xmlParse.OutOfElem();
		} while (xmlParse.NextElem());
	}

	if(xmlParse.FindElem(TP_D_SOAP_PAGE_INFO))
	{
		(void)xmlParse.IntoElem();
		(void)Parse_PagesInfoEx(&xmlParse, queryMultiPointCDR->PageInfo);
		xmlParse.OutOfElem();
	}
	else
	{
		TP_LOG_ERROR("parse xml failed,not found TP_D_SOAP_PAGE_INFO.");
		return resCode;
	}
	
	return TP_SDK_ERR_SUCCESS;	
}

int XMLProcess::SetXml_queryPointToPointCDREx(const PointToPointCDRQueryConfigEx &queryConfig, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strTime[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_POINT_TO_POINT_CDR, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_QUERY_CONFIG);
	(void)xml.IntoElem();
	(void)Package_PointToPointCDRQueryConfigEx(&queryConfig, &xml);

	xml.OutOfElem();

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_queryPointToPointCDREx(const char *xmlStr, QueryPointToPointCDRExResponse *queryPointToPointCDR)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYPOINTTOPOINTCDREX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYPOINTTOPOINTCDREX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYPOINTTOPOINTCDREX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	queryPointToPointCDR->cdr.clear();
	
	if (xmlParse.FindElem(TP_D_SOAP_CDR))		//error,lich
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse.GetElem(),TP_D_SOAP_CDR) !=0)
			{
				break;
			}

			PointToPointCDREx PointToPointCDR;
			(void)xmlParse.IntoElem();
			(void)Parse_PointToPointCDREx(&xmlParse, PointToPointCDR);

			queryPointToPointCDR->cdr.push_back(PointToPointCDR);
			xmlParse.OutOfElem();
		} while (xmlParse.NextElem());
	}

	if(xmlParse.FindElem(TP_D_SOAP_PAGE_INFO))
	{
		(void)xmlParse.IntoElem();
		(void)Parse_PagesInfoEx(&xmlParse, queryPointToPointCDR->PageInfo);
		xmlParse.OutOfElem();
	}
	else
	{
		TP_LOG_ERROR("parse xml failed,not found TP_D_SOAP_PAGE_INFO.");
		return resCode;
	}

	return TP_SDK_ERR_SUCCESS;	
}


int XMLProcess::SetXml_synchAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strTime[256]={0};
	CXml xml;
	list<string>::const_iterator i;
	int first_flag = 1;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_SYNC_ADHOC_CONF_FREE_BUSY, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	for(i=confAccessCodes.begin(); i!=confAccessCodes.end(); i++)
	{
		if(first_flag)
		{
			(void)xml.AddChildElem(TP_D_SOAP_CONF_ACCESS_CODES);
			(void)xml.IntoElem();
			first_flag = 0;
		}
		else
		{
			(void)xml.AddElem(TP_D_SOAP_CONF_ACCESS_CODES);
		}
		
		(void)xml.SetElemValue(i->c_str());
	}

	if(first_flag)
	{
		if (beginTime.wYear || beginTime.wMonth || beginTime.wDay)
		{
			(void)xml.AddChildElem(TP_D_SOAP_BEGINTIME);
			(void)xml.IntoElem();
			(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
				,beginTime.wYear,beginTime.wMonth,beginTime.wDay
				,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
				,TP_Tool::GetLocalTimeZone().c_str());
			(void)xml.SetElemValue(strTime);
		}
		
		//first_flag = 0;
	}
	else
	{
		if (beginTime.wYear || beginTime.wMonth || beginTime.wDay)
		{
			(void)xml.AddElem(TP_D_SOAP_BEGINTIME);
			(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
				,beginTime.wYear,beginTime.wMonth,beginTime.wDay
				,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
				,TP_Tool::GetLocalTimeZone().c_str());
			(void)xml.SetElemValue(strTime);
		}
		
	}
	
	(void)xml.AddElem(TP_D_SOAP_DURATION);
	(void)xml.SetElemValue(duration.c_str());


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Parse_AdhocConfFreeBusyStateEx(CXml *xmlParse, AdhocConfFreeBusyStateEx &adhocConfState)
{
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CONFACCESSCODE, TP_D_ELEM_MUST_FLAG, adhocConfState.confAccessCode))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CONFACCESSCODE.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if (!xmlParse->FindElem(TP_D_SOAP_FREEBUSYS))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_FREEBUSYS. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	do
	{
		if (xmlParse->GetElem()==NULL)
		{
			break;
		}
		if(strcmp(xmlParse->GetElem(),TP_D_SOAP_FREEBUSYS) !=0)
		{
			break;
		}
		FreeBusyStateEx siteState;
		(void)xmlParse->IntoElem();
		(void)Parse_FreeBusyStateEx(xmlParse, siteState);
		xmlParse->OutOfElem();
		adhocConfState.freebusys.push_back(siteState);

	}while(xmlParse->NextElem());
	return TP_SDK_ERR_SUCCESS;

}

int XMLProcess::GetRSPXml_synchAdhocConfFreeBusyEx(const char *xmlStr, list<AdhocConfFreeBusyStateEx> *adhocConfFreeBusyState)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_SYNCADHOCCONFFREEBUSYEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_BODY_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_SYNCADHOCCONFFREEBUSYEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_SYNCADHOCCONFFREEBUSYEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	adhocConfFreeBusyState->clear();

	if (xmlParse.FindElem(TP_D_SOAP_FREEBUSY))
	{
		(void)xmlParse.IntoElem();
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			//if(strcmp(xmlParse.GetElem(),TP_D_SOAP_FREEBUSY) !=0)
			//{
			//	break;
			//}
			AdhocConfFreeBusyStateEx adhocConfState;
			(void)xmlParse.IntoElem();
			(void)Parse_AdhocConfFreeBusyStateEx(&xmlParse, adhocConfState);
			xmlParse.OutOfElem();
			adhocConfFreeBusyState->push_back(adhocConfState);

		} while (xmlParse.NextElem());
	}

	return TP_SDK_ERR_SUCCESS;	
}

int XMLProcess::SetXml_queryAdhocConfFreeBusyEx(const list<std::string>& confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strTime[256]={0};
	CXml xml;
	list<string>::const_iterator i;
	int first_flag = 1;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_ADHOC_CONF_FREE_BUSY, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	for(i=confAccessCodes.begin(); i!=confAccessCodes.end(); i++)
	{
		if(first_flag)
		{
			(void)xml.AddChildElem(TP_D_SOAP_CONF_ACCESS_CODES);
			(void)xml.IntoElem();
			first_flag = 0;
		}
		else
		{
			(void)xml.AddElem(TP_D_SOAP_CONF_ACCESS_CODES);
		}
		
		(void)xml.SetElemValue(i->c_str());
	}

	if(first_flag)
	{
		if (beginTime.wYear || beginTime.wMonth || beginTime.wDay)
		{
			(void)xml.AddChildElem(TP_D_SOAP_BEGINTIME);
			(void)xml.IntoElem();
			(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
				,beginTime.wYear,beginTime.wMonth,beginTime.wDay
				,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds,TP_Tool::GetLocalTimeZone().c_str());
			(void)xml.SetElemValue(strTime);
		}
		
	}
	else
	{
		if (beginTime.wYear || beginTime.wMonth || beginTime.wDay)
		{
			(void)xml.AddElem(TP_D_SOAP_BEGINTIME);
			(void)sprintf_s(strTime,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
				,beginTime.wYear,beginTime.wMonth,beginTime.wDay
				,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds,TP_Tool::GetLocalTimeZone().c_str());
			(void)xml.SetElemValue(strTime);
		}

		
	}

	(void)xml.AddElem(TP_D_SOAP_DURATION);
	(void)xml.SetElemValue(duration.c_str());


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_queryAdhocConfFreeBusyEx(const char *xmlStr, list<AdhocConfFreeBusyStateEx> *adhocConfFreeBusyState)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYADHOCCONFFREEBUSYEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYADHOCCONFFREEBUSYEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYADHOCCONFFREEBUSYEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	adhocConfFreeBusyState->clear();
	if (!xmlParse.FindElem(TP_D_SOAP_FREEBUSY))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_FREEBUSY.");
		return resCode;
	}
	do
	{
		if (xmlParse.GetElem()==NULL)
		{
			break;
		}
		if(strcmp(xmlParse.GetElem(),TP_D_SOAP_FREEBUSY) !=0)
		{
			break;
		}
		AdhocConfFreeBusyStateEx adhocConfState;
		(void)xmlParse.IntoElem();
		(void)Parse_AdhocConfFreeBusyStateEx(&xmlParse, adhocConfState);
		xmlParse.OutOfElem();
		adhocConfFreeBusyState->push_back(adhocConfState);

	} while (xmlParse.NextElem());



	return TP_SDK_ERR_SUCCESS;	
}


int XMLProcess::SetXml_queryAdhocConferencesEx(const QueryConfigEx &queryConfig, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;
	list<SortItemEx>::const_iterator i;
	list<StringFilterEx>::const_iterator j;
	int first_flag = 1;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_ADHOC_CONFERENCESEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_QUERY_CONFIG);
	(void)xml.IntoElem();
	for(i=queryConfig.sortItems.begin(); i!=queryConfig.sortItems.end(); i++)
	{
		if(first_flag)
		{
			(void)xml.AddChildElem(TP_D_SOAP_SORT_ITEMS);
			(void)xml.IntoElem();
			first_flag = 0;
		}
		else
		{
			(void)xml.AddElem(TP_D_SOAP_SORT_ITEMS);
		}

		
		(void)xml.AddChildElem(TP_D_SOAP_SORT);
		(void)xml.IntoElem();
		(void)sprintf_s(strVal,255,"%d",i->sort);
		(void)xml.SetElemValue(strVal);
		(void)xml.AddElem(TP_D_SOAP_ITEM_INDEX);
		(void)sprintf_s(strVal,255,"%d",i->itemIndex);
		(void)xml.SetElemValue(strVal);
		(void)xml.OutOfElem();
	}

	for(j=queryConfig.filters.begin(); j!=queryConfig.filters.end(); j++)
	{
		if(first_flag)
		{
			(void)xml.AddChildElem(TP_D_SOAP_FILTERS);
			(void)xml.IntoElem();
			first_flag = 0;
		}
		else
		{
			(void)xml.AddElem(TP_D_SOAP_FILTERS);
		}
		
		(void)xml.AddAttribute(TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI,TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI_VALUE);
		(void)xml.AddAttribute(TP_D_SOAP_FILTERS_ATTR_XSI_TYPE,TP_D_SOAP_FILTERS_ATTR_XSI_TYPE_VALUE);
		(void)xml.AddChildElem(TP_D_SOAP_COLUMN_INDEX);
		(void)xml.IntoElem();
		(void)sprintf_s(strVal,255,"%d",j->columnIndex);
		(void)xml.SetElemValue(strVal);
		(void)xml.AddElem(TP_D_SOAP_VALUE);
		(void)xml.SetElemValue(TP_Tool::ANSIToUTF8(j->value).c_str());
		(void)xml.OutOfElem();
	}
	if(first_flag)
	{
		(void)xml.AddChildElem(TP_D_SOAP_PAGEPARAM);
		(void)xml.IntoElem();
	}
	else
	{
		(void)xml.AddElem(TP_D_SOAP_PAGEPARAM);
	}
	
	(void)xml.AddChildElem(TP_D_SOAP_NUMBERPERPAGE);
	(void)xml.IntoElem();
	(void)sprintf_s(strVal,255,"%d",queryConfig.pageParam.numberPerPage);
	(void)xml.SetElemValue(strVal);
	(void)xml.AddElem(TP_D_SOAP_CURRENT_PAGE);
	(void)sprintf_s(strVal,255,"%d",queryConfig.pageParam.currentPage);
	(void)xml.SetElemValue(strVal);


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;

}
int XMLProcess::GetRSPXml_queryAdhocConferencesEx(const char *xmlStr, QueryAdhocConferenceExResponse *queryAdhocConfExResponse)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYADHOCCONFERENCESEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYADHOCCONFERENCESEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYADHOCCONFERENCESEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	queryAdhocConfExResponse->adhocConferences.clear();
	if (xmlParse.FindElem(TP_D_SOAP_ADHOCCONFERENCES))
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse.GetElem(), TP_D_SOAP_ADHOCCONFERENCES) !=0)
			{
				break;
			}
			AdhocConferenceEx AdhocConf;
			(void)xmlParse.IntoElem();
			(void)Parse_AdhocConferenceEx(&xmlParse, AdhocConf);

			queryAdhocConfExResponse->adhocConferences.push_back(AdhocConf);
			xmlParse.OutOfElem();
		} while (xmlParse.NextElem());	
	}

	if(xmlParse.FindElem(TP_D_SOAP_PAGE_INFO))
	{
		(void)xmlParse.IntoElem();
		(void)Parse_PagesInfoEx(&xmlParse, queryAdhocConfExResponse->PageInfo);
		xmlParse.OutOfElem();
	}
	else
	{
		TP_LOG_ERROR("parse xml failed,not found TP_D_SOAP_PAGE_INFO.");
		return resCode;
	}

	

	return TP_SDK_ERR_SUCCESS;	
}


int XMLProcess::SetXml_queryConfSiteMCUEx(const std::string &confId, const list<std::string> &siteUris, const SYSTEMTIME &beginTime, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;
	list<std::string>::const_iterator i;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_CONF_SITE_MCUEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	for(i=siteUris.begin(); i!=siteUris.end(); i++)
	{
		(void)xml.AddElem(TP_D_SOAP_SITEURIS);
	
		(void)xml.SetElemValue(i->c_str());
	}

	if(beginTime.wYear || beginTime.wMonth || beginTime.wDay)
	{
		(void)xml.AddElem(TP_D_SOAP_BEGINTIME);
		(void)sprintf_s(strVal,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
			,beginTime.wYear,beginTime.wMonth,beginTime.wDay
			,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
			,TP_Tool::GetLocalTimeZone().c_str());
		(void)xml.SetElemValue(strVal);

	}
	
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_getContinuousPresenceInfoEx(const std::string &confId, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_GET_CONTINUOUS_PRESENCE_INFOEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_getContinuousPresenceInfoEx(const char *xmlStr, GetContinuousPresenceInfoResponseEx *getContinPresenceInfoResponse)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_GETCONTINPRESENCEINFO);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_GETCONTINPRESENCEINFO))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_GETCONTINPRESENCEINFO.");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	getContinPresenceInfoResponse->targets.clear();
	if (xmlParse.FindElem(TP_D_SOAP_TARGETS))
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse.GetElem(), TP_D_SOAP_TARGETS) !=0)
			{
				break;
			}
			
			std::string target;
			target = xmlParse.GetElemValue();

			getContinPresenceInfoResponse->targets.push_back(target);
			//xmlParse.OutOfElem();
		} while (xmlParse.NextElem());	
	}

	std::string strVal;
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_CPRESOURCE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CPRESOURCE.");
		return resCode;
	}
	if(strVal.length())
	{
		getContinPresenceInfoResponse->cpResource = TP_Tool::String2Int(strVal);
	}

	if (xmlParse.FindElem(TP_D_SOAP_SUPPORTCPMODES))
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse.GetElem(), TP_D_SOAP_SUPPORTCPMODES) !=0)
			{
				break;
			}
			std::string supportCPModes;
			supportCPModes = xmlParse.GetElemValue();

			getContinPresenceInfoResponse->supportCPModes.push_back(TP_Tool::String2Int(supportCPModes));
			
		} while (xmlParse.NextElem());	
	}

	return TP_SDK_ERR_SUCCESS;	
}


int XMLProcess::SetXml_getContinuousPresenceParamEx(const std::string &confId, const std::string &target, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;
	
	if(Package_BasicSOAP(TP_D_SOAP_SMC_GET_CONTINUOUS_PRESENCE_PARAMEXP, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	if(target.length())
	{
		(void)xml.AddElem(TP_D_SOAP_TARGET);
		(void)xml.SetElemValue(target.c_str());
	}
	
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_getContinuousPresenceParamEx(const char *xmlStr, GetContinuousPresenceParamResponseEx *getContinPresenceParamResponse)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_GETCONTINPRESENCEPARAM);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_GETCONTINPRESENCEPARAM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_GETCONTINPRESENCEPARAM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	std::string strVal;
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_PRESENCE_MODE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_PRESENCE_MODE.");
		return resCode;
	}
	if(strVal.length())
	{
		getContinPresenceParamResponse->presenceMode = TP_Tool::String2Int(strVal);
	}
	getContinPresenceParamResponse->subPics.clear();
	if (xmlParse.FindElem(TP_D_SOAP_SUBPICS))
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse.GetElem(), TP_D_SOAP_SUBPICS) !=0)
			{
				break;
			}
			std::string subPic;
			subPic = xmlParse.GetElemValue();

			getContinPresenceParamResponse->subPics.push_back(subPic);
		} while (xmlParse.NextElem());	
	}

	

	return TP_SDK_ERR_SUCCESS;	
}


int XMLProcess::Parse_SiteMCUEx(CXml *xmlParse, SiteMCUEx &siteMcu)
{
	std::string strVal;
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SITEURI, TP_D_ELEM_MUST_FLAG, siteMcu.siteUri))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_SITEURI. ");
		return TP_SDK_ERR_XML_PARSE;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_MCUID, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_MCUID.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length())
	{
		siteMcu.mcuId = TP_Tool::String2Int(strVal);
	}
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetRSPXml_queryConfSiteMCUEx(const char *xmlStr, list<SiteMCUEx> *list_siteMcu)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYCONFSITEMCUEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYCONFSITEMCUEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYCONFSITEMCUEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	list_siteMcu->clear();
	if (xmlParse.FindElem(TP_D_SOAP_MCUS))
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse.GetElem(), TP_D_SOAP_MCUS) !=0)
			{
				break;
			}
			SiteMCUEx sitMcu;
			(void)xmlParse.IntoElem();
			(void)Parse_SiteMCUEx(&xmlParse, sitMcu);

			list_siteMcu->push_back(sitMcu);
			xmlParse.OutOfElem();
		} while (xmlParse.NextElem());	
	}

	return TP_SDK_ERR_SUCCESS;	
}


int XMLProcess::GetRSPXml_queryConfSitesStatusEx(const char *xmlStr, list<SiteStatusEx> *list_SiteStatus)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYCONFSITESSTATUSEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYCONFSITESSTATUSEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYCONFSITESSTATUSEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	list_SiteStatus->clear();
	if (!xmlParse.FindElem(TP_D_SOAP_SITE_STATUS))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SITE_STATUS.");
		return resCode;
	}
	do
	{
		SiteStatusEx SiteStatus;
		std::string strVal;
		(void)xmlParse.IntoElem();
		(void)Parse_siteFreeBusyStates(&xmlParse, SiteStatus);

		list_SiteStatus->push_back(SiteStatus);
		xmlParse.OutOfElem();
	} while (xmlParse.NextElem());

	return TP_SDK_ERR_SUCCESS;	
}

int XMLProcess::Parse_AdhocConferenceEx(CXml *xmlParse, AdhocConferenceEx &AdhocConf)
{
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_MUST_FLAG, AdhocConf.name))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	AdhocConf.name = TP_Tool::UTF8ToANSI(AdhocConf.name);
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CONFACCESSCODE, TP_D_ELEM_MUST_FLAG, AdhocConf.confAccessCode))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_CONFACCESSCODE. ");
		return TP_SDK_ERR_XML_PARSE;
	}

	return TP_SDK_ERR_SUCCESS;
}


 int XMLProcess::Parse_FreeBusyStateEx(CXml *xmlParse, FreeBusyStateEx &siteState)
 {
	 std::string strVal;
	 strVal.clear();
	 if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_STARTTIME, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	 {
		 TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_STARTTIME. ");
		 return TP_SDK_ERR_XML_PARSE;
	 }
	 if(strVal.length())
	 {
		 
		 (void)StringTimeFormatTOSystemtime(strVal, siteState.startTime);

	 }
	 


	 if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SPAN, TP_D_ELEM_OPTIONAL_FLAG, siteState.span))
	 {
		 TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_SPAN. ");
		 return TP_SDK_ERR_XML_PARSE;
	 }

	 if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_STATE, TP_D_ELEM_MUST_FLAG, strVal))
	 {
		 TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_STATE.");
		 return TP_SDK_ERR_XML_PARSE;
	 }
	 if (!CheckDigital((char *)strVal.c_str()))
	 {
		 TP_LOG_ERROR("%s value is error:%s",TP_D_SOAP_STATE,strVal.c_str());
		 return TP_SDK_ERR_XML_PARSE;
	 }
	 siteState.state = TP_Tool::String2Int(strVal);

	 if(siteState.state<MINFreeBusyState || siteState.state>MAXFreeBusyState)
	 {
		 TP_LOG_ERROR("%s value is error:%s",TP_D_SOAP_SPAN,strVal.c_str());
		 return TP_SDK_ERR_XML_PARSE;
	 }
	 if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CONFID, TP_D_ELEM_OPTIONAL_FLAG, siteState.confId))
	 {
		 TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CONFID.");
		 return TP_SDK_ERR_XML_PARSE;
	 }
	 if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CONFNAME, TP_D_ELEM_OPTIONAL_FLAG, siteState.confName))
	 {
		 TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CONFNAME.");
		 return TP_SDK_ERR_XML_PARSE;
	 }
	 siteState.confName = TP_Tool::UTF8ToANSI(siteState.confName);
	 return TP_SDK_ERR_SUCCESS;
 }

 int  XMLProcess::Parse_siteFreeBusyStates(CXml *xmlParse, std::string &uri,list<FreeBusyStateEx> &list_freeBusyState)
 {

	 if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_URI, TP_D_ELEM_MUST_FLAG, uri))
	 {
		 TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_URI.");
		 return TP_SDK_ERR_XML_PARSE;
	 }

	 if (!xmlParse->FindElem(TP_D_SOAP_STATES))
	 {
		 TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_STATES.");
		 return TP_SDK_ERR_XML_PARSE;
	 }
	 do 
	 {
		 FreeBusyStateEx siteState; 
		 memset(&siteState,0,sizeof(FreeBusyStateEx));
		 std::string strVal;
		 (void)xmlParse->IntoElem();
		 (void)Parse_FreeBusyStateEx(xmlParse, siteState);
		 list_freeBusyState.push_back(siteState);
		 xmlParse->OutOfElem();
	 } while (xmlParse->NextElem());

	 return TP_SDK_ERR_SUCCESS;
 }


int XMLProcess::GetRSPXml_querySiteStatusEx(const char *xmlStr, map<std::string, list<FreeBusyStateEx>> *map_SiteStatus)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYSITESSTATUSEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYSITESSTATUSEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYSITESSTATUSEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	
	map_SiteStatus->clear();
	if (!xmlParse.FindElem(TP_D_SOAP_SITE_FREE_BUSY_STATES))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SITE_FREE_BUSY_STATES.");
		return resCode;
	}
	do
	{
		std::string uri;
		list<FreeBusyStateEx> list_SiteStatus;
		(void)xmlParse.IntoElem();
		(void)Parse_siteFreeBusyStates(&xmlParse, uri,list_SiteStatus);

		(void)map_SiteStatus->insert(pair<string, list<FreeBusyStateEx>>(uri,list_SiteStatus));

		xmlParse.OutOfElem();
	}while(xmlParse.NextElem());

	return TP_SDK_ERR_SUCCESS;


}


int XMLProcess::GetRSPXml_editScheduleConfEx(const char *xmlStr, ConferenceInfoEx *conferenceInfo)
{
	/************************************************************************
	--- XML 格式 ---
	<soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
	<soap:Body>
	<ns2:scheduleConfExResponse xmlns:ns2="http://smc.huawei.com/">
	<resultCode>0</resultCode>
	<conferenceInfo>
	<confId>2443</confId>
	<accessCode>01011475</accessCode>
	<sites>
	<name>VCT206</name>
	<uri>01010010</uri>
	</sites>
	<sites>
	<name>VCT205</name>
	<uri>01010086</uri>
	</sites>
	</conferenceInfo>
	</ns2:scheduleConfExResponse>
	</soap:Body>
	</soap:Envelope> 
	************************************************************************/
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_EDITSCHEDULECONF);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_BODY_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_EDITSCHEDULECONF))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_EDITSCHEDULECONF.");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	if (!xmlParse.FindElem(TP_D_SOAP_CONFINFO))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_CONFINFO. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	//const unsigned int XML_VAR_LENGTH = 50;
	//char elemValue[XML_VAR_LENGTH] = {0};
	//const char* srcValue;
	//unsigned int uiMaxLen = XML_VAR_LENGTH;
	//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_CONFID, srcValue, elemValue, uiMaxLen);
	//strncpy_s(conferenceInfo->confId, elemValue,TP_D_CONFID_MAX_LEN);
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_CONFID, TP_D_ELEM_MUST_FLAG, conferenceInfo->confId))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CONFID.");
		return resCode;
	}
	
	//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_ACCESS_CODE, srcValue, elemValue, uiMaxLen);
	//strncpy_s(conferenceInfo->accessCode, elemValue, TP_D_CONFID_MAX_LEN);
	
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_ACCESS_CODE, TP_D_ELEM_MUST_FLAG, conferenceInfo->accessCode))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ACCESS_CODE.");
		return resCode;
	}
	
	conferenceInfo->sites.clear();
	if (!xmlParse.FindElem(TP_D_SOAP_SITES))
	{
		return resCode;
	}
	do
	{
		SiteInfoEx siteInfo;
		(void)xmlParse.IntoElem();
		//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_URI, srcValue, elemValue, uiMaxLen);
		//strncpy_s(recuConfInfo->siteAccessInfos[i].uri,elemValue,TP_D_CONFID_MAX_LEN);
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.name))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
			return resCode;
		}
		siteInfo.name = TP_Tool::UTF8ToANSI(siteInfo.name);
		//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_CONFACCESSCODE, srcValue, elemValue, uiMaxLen);
		//strncpy_s(recuConfInfo->siteAccessInfos[i].uri,elemValue,TP_D_CONFID_MAX_LEN);
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_URI, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.uri))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_URI.");
			return resCode;
		}


		conferenceInfo->sites.push_back(siteInfo);
		xmlParse.OutOfElem();
	}while(xmlParse.NextElem());

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_prolongScheduledConfEx(const char *xmlStr, int &resCode)
{
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_PROLONGSCHEDULECONF);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_scheduleConfEx(const char *xmlStr, ConferenceInfoEx *conferenceInfo)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_SCHEDULECONF);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_SCHEDULECONF))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_SCHEDULECONF. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	if (!xmlParse.FindElem(TP_D_SOAP_CONFINFO))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_CONFINFO. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	//const unsigned int XML_VAR_LENGTH = 50;
	//char elemValue[XML_VAR_LENGTH] = {0};
	//const char* srcValue;
	//unsigned int uiMaxLen = XML_VAR_LENGTH;
	//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_CONFID, srcValue, elemValue, uiMaxLen);
	//strncpy_s(conferenceInfo->confId, elemValue,TP_D_CONFID_MAX_LEN);
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_CONFID, TP_D_ELEM_MUST_FLAG,conferenceInfo->confId))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_CONFID. ");
		return resCode;
	}
	
	//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_ACCESS_CODE, srcValue, elemValue, uiMaxLen);
	//strncpy_s(conferenceInfo->accessCode, elemValue, TP_D_CONFID_MAX_LEN);
	
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_ACCESS_CODE, TP_D_ELEM_MUST_FLAG,conferenceInfo->accessCode))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ACCESS_CODE.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_SITES))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SITES.");
		return resCode;
	}
	do
	{
		SiteInfoEx siteInfo;
		(void)xmlParse.IntoElem();
		//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_URI, srcValue, elemValue, uiMaxLen);
		//strncpy_s(recuConfInfo->siteAccessInfos[i].uri,elemValue,TP_D_CONFID_MAX_LEN);
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.name))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
			return resCode;
		}
		siteInfo.name = TP_Tool::UTF8ToANSI(siteInfo.name);
		//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_CONFACCESSCODE, srcValue, elemValue, uiMaxLen);
		//strncpy_s(recuConfInfo->siteAccessInfos[i].uri,elemValue,TP_D_CONFID_MAX_LEN);
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_URI, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.uri))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_URI.");
			return resCode;
		}


		conferenceInfo->sites.push_back(siteInfo);
		xmlParse.OutOfElem();
	}while(xmlParse.NextElem());
	
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::Parse_SiteAccessInfoEx(CXml *xmlParse, SiteAccessInfoEx &siteAccessInfo)
{
	std::string strVal;
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_URI, TP_D_ELEM_OPTIONAL_FLAG, siteAccessInfo.uri))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_URI. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CONFACCESSCODE, TP_D_ELEM_OPTIONAL_FLAG, siteAccessInfo.confAccessCode))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_CONFACCESSCODE. ");
		return TP_SDK_ERR_XML_PARSE;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_OPTIONAL_FLAG, siteAccessInfo.name))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	siteAccessInfo.name = TP_Tool::UTF8ToANSI(siteAccessInfo.name);

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_BEGINTIME, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_BEGINTIME. ");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length())
	{
		 (void)StringTimeFormatTOSystemtime(strVal, siteAccessInfo.beginTime);
		
	}

	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetRSPXml_scheduleRecurrenceConferenceEx(const char *xmlStr, RecurrenceConfInfoEx *recuConfInfo)
{
	int resCode = 0;
	//int i = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_SCHEDULERECURRENCECONF);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_SCHEDULERECURRENCECONF))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_SCHEDULERECURRENCECONF.");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	if (!xmlParse.FindElem(TP_D_SOAP_RECURRENCE_CONF_INFO))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RECURRENCE_CONF_INFO.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	//const unsigned int XML_VAR_LENGTH = 50;
	//char elemValue[XML_VAR_LENGTH] = {0};
	//const char* srcValue;
	//unsigned int uiMaxLen = XML_VAR_LENGTH;
	//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_CONFID, srcValue, elemValue, uiMaxLen);
	//strncpy_s(recuConfInfo->base_info.confId, elemValue,TP_D_CONFID_MAX_LEN);
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_CONFID, TP_D_ELEM_MUST_FLAG,recuConfInfo->base_info.confId))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CONFID.");
		return resCode;
	}
	recuConfInfo->siteAccessInfos.clear();

	if (!xmlParse.FindElem(TP_D_SOAP_SITEACCESSINFOS))
	{
		return resCode;
	}

	do
	{
		(void)xmlParse.IntoElem();
		SiteAccessInfoEx siteAccessInfo;
		(void)Parse_SiteAccessInfoEx(&xmlParse, siteAccessInfo);
		recuConfInfo->siteAccessInfos.push_back(siteAccessInfo);
		xmlParse.OutOfElem();
	}while(xmlParse.NextElem());

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_editScheduleRecurrenceConferenceEx(const char *xmlStr, RecurrenceConfInfoEx *recuConfInfo)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_EDITSCHEDULERECURRENCECONF);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_BODY_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_EDITSCHEDULERECURRENCECONF))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_EDITSCHEDULERECURRENCECONF.");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	if (!xmlParse.FindElem(TP_D_SOAP_RECURRENCECONFINFO))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RECURRENCECONFINFO.");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	//const unsigned int XML_VAR_LENGTH = 50;
	//char elemValue[XML_VAR_LENGTH] = {0};
	//const char* srcValue;
	//unsigned int uiMaxLen = XML_VAR_LENGTH;
	//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_CONFID, srcValue, elemValue, uiMaxLen);
	//strncpy_s(recuConfInfo->base_info.confId, elemValue,TP_D_CONFID_MAX_LEN);
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_CONFID, TP_D_ELEM_MUST_FLAG,recuConfInfo->base_info.confId))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CONFID.");
		return resCode;
	}
	recuConfInfo->siteAccessInfos.clear();
	if (!xmlParse.FindElem(TP_D_SOAP_SITEACCESSINFOS))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SITEACCESSINFOS.");
		return resCode;
	}

	do
	{
		(void)xmlParse.IntoElem();
		SiteAccessInfoEx siteAccessInfo;
		//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_URI, srcValue, elemValue, uiMaxLen);
		//strncpy_s(recuConfInfo->siteAccessInfos[i].uri,elemValue,TP_D_CONFID_MAX_LEN);
		(void)Parse_SiteAccessInfoEx(&xmlParse, siteAccessInfo);

		recuConfInfo->siteAccessInfos.push_back(siteAccessInfo);
		xmlParse.OutOfElem();
	}while(xmlParse.NextElem());
	return TP_SDK_ERR_SUCCESS;
}



int XMLProcess::GetXml_Config(const char* xmlStr, std::map<std::string, std::string> *MapKeyValue)
{
	/************************************************************************
	--- XML 格式 ---
	<?xml version="1.0" encoding="utf-8"?>
	<configuration>
	<configSections>
	</configSections>
	<appSettings>
	<add key="url" value="https://10.95.24.173:18543/esdk/services/" />
	<add key="tpCommon" value="tpCommon" />
	<add key="tpProfessionalConfCtrl" value="tpProfessionalConfCtrl" />
	<add key="tpProfessionalConfMgr" value="tpProfessionalConfMgr" />
	<add key="tpProfessionalSiteMgr" value="tpProfessionalSiteMgr" />
	<add key="tpProfessionalMCUMgr" value="tpProfessionalMCUMgr" />
	<add key="tpProfessionalOrgaMgr" value="tpProfessionalOrgaMgr" />
	<add key="tpProfessionalTerminalConfCtr" value="tpProfessionalTerminalConfCtr" />
	<add key="platformKeyMgr" value="platformKeyMgr" />
	</appSettings>
	</configuration>
	************************************************************************/
	const char *pValue = NULL;
	const char *pKey = NULL;
	std::string strValue;
	std::string strKey;
	bool ret = true;
	//int len =0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr || NULL == MapKeyValue)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return TP_SDK_ERR_XML_PARSE;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_CONFIG_APPSETTINGS_ELEM))
	{
		TP_LOG_ERROR("FindElem Content failed,not found TP_CONFIG_APPSETTINGS_ELEM.");
		return TP_SDK_ERR_XML_FIND_ELEM;
	}
	(void)xmlParse.IntoElem();
	while(pKey = xmlParse.GetAttributeValue(TP_CONFIG_ATTR_KEY))
	{
		pValue = xmlParse.GetAttributeValue(TP_CONFIG_ATTR_VALUE);
		if(!pValue)
		{
			break;
		}
		//len = strlen(pValue);
		//strValue =   new std::string;
		//if(!strValue)
		//{
		//	break;
		//}
		//memset(strValue, 0, len+1);
		//strncpy_s(strValue,len+1, pValue,len);
		strValue = pValue;

		//len = strlen(pKey);
		//strKey = new std::string;
		//if(!strKey)
		//{
		//	break;
		//}
		//memset(strKey, 0, len+1);
		//strncpy_s(strKey,len+1, pKey,len);
		strKey = pKey;

		(void)MapKeyValue->insert(std::pair <std::string, std::string> (strKey, strValue));
		ret = xmlParse.NextElem();
		if (ret == false)
		{
			break;
		}
	}
	return TP_SDK_ERR_SUCCESS;
}

int CheckDigital(char *value)
{
	int i = 0,ret = 0;
	if(!value)
	{
		return ret;
	}
	int nlen = strlen(value);
	
	if(0 == nlen)
	{
		return ret;
	}

	for (i=0; i<nlen; i++)
	{
		ret = isdigit(value[i]);
		if(!ret)
		{
			break;
		}
	}
	return ret;
}

int XMLProcess::GetRSPXML_ResultCode(const char *xmlStr, char *RSP_Method_ELEM)
{
	TP_DEBUG_TRACE("");
	int ret = 0;
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_GENERAL;
	}
	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return TP_SDK_ERR_GENERAL;
	}
	//(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("FindElem Content failed,not found TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return TP_SDK_ERR_GENERAL;
	}


	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("FindElem Content failed,not found TP_D_SOAP_RSP_BODY_ELEM.");
		return TP_SDK_ERR_GENERAL;
	}

	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(RSP_Method_ELEM))
	{
		TP_LOG_ERROR("FindElem Content failed.");
		return TP_SDK_ERR_GENERAL;
	} 
	(void)xmlParse.IntoElem();

	const unsigned int XML_VAR_LENGTH = 20;
	char elemValue[XML_VAR_LENGTH] = {0};
	const char* srcValue;
	unsigned int uiMaxLen = XML_VAR_LENGTH;
	GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_RSP_RESULTCODE_ELEM, srcValue, elemValue, uiMaxLen);
	ret = CheckDigital(elemValue);
	if(!ret)
	{
		TP_LOG_ERROR("parse xml failed.");
		return TP_SDK_ERR_GENERAL;
	}
	return atoi(elemValue);
	
}

int XMLProcess::Parse_siteFreeBusyStates(CXml *xmlParse, SiteStatusEx &SiteStatus)
{
	std::string strVal;
	
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_URI, TP_D_ELEM_OPTIONAL_FLAG, SiteStatus.uri))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_URI.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_OPTIONAL_FLAG, SiteStatus.name))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_NAME. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	SiteStatus.name = TP_Tool::UTF8ToANSI(SiteStatus.name);

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_STATUS, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_STATUS. ");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length() != 0)
	{
		SiteStatus.status = TP_Tool::String2Int(strVal);
	}

	strVal.clear();

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_VOLUME, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_VOLUME. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length() != 0)
	{
		SiteStatus.volume = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_VIDEO_SOURCE, TP_D_ELEM_OPTIONAL_FLAG, SiteStatus.videoSource))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_VIDEO_SOURCE. ");
		return TP_SDK_ERR_XML_PARSE;
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ISMUTE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_ISMUTE. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length() != 0)
	{
		SiteStatus.isMute = TP_Tool::String2Int(strVal);
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ISQUIET, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_ISQUIET. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length() != 0)
	{
		SiteStatus.isQuiet = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_TYPE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_TYPE. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length() != 0)
	{
		SiteStatus.type = TP_Tool::String2Int(strVal);
	}

	if (xmlParse->FindElem(TP_D_SOAP_CALL_FAILED_REASON))
	{
		(void)xmlParse->IntoElem();
		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ERRCODE, TP_D_ELEM_MUST_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ERRCODE.");
			return TP_SDK_ERR_XML_PARSE;
		}
		if(strVal.length() != 0)
		{
			SiteStatus.callFailedReason.errCode = TP_Tool::String2Int(strVal);
		}
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_DESCRIPTION, TP_D_ELEM_MUST_FLAG, SiteStatus.callFailedReason.description))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_DESCRIPTION.");
			return TP_SDK_ERR_XML_PARSE;
		}

		xmlParse->OutOfElem();
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ISLOCALVIDEOOPEN, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ISLOCALVIDEOOPEN.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length() != 0)
	{
		SiteStatus.isLocalVideoOpen = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_PARTICIPANTTYPE, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_PARTICIPANTTYPE. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length() != 0)
	{
		SiteStatus.participantType = TP_Tool::String2Int(strVal);
	}
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetRSPXml_LoginRequest(const char *xmlStr, std::string &randomSequence)
{
	/************************************************************************
	<soapenv:Envelope xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/" xmlns:smc="http://smc.huawei.com/">
	<soapenv:Header/>
	<soapenv:Body>
	<smc:LoginRequestResponse>
	<resultCode>0</resultCode>
	<randomSequence>AK+KLbyo7qJAENalCIwakQ==</randomSequence>
	<hashType>SHA256</hashType>
	</smc:LoginRequestResponse>
	</soapenv:Body>
	</soapenv:Envelope>
	************************************************************************/
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_LOGINREQ_ELEM);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_LOGINREQ_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_LOGINREQ_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	//const unsigned int XML_VAR_LENGTH = 50;
	//char elemValue[XML_VAR_LENGTH] = {0};
	//const char* srcValue;
	//unsigned int uiMaxLen = XML_VAR_LENGTH;
	//GET_XML_ELEM_VALUE_CHAR(xmlParse, TP_D_SOAP_RSP_LOGINREQUEST_RANDOMSEQ_ELEM, srcValue, elemValue, uiMaxLen);
	//randomSequence = elemValue;
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_RSP_LOGINREQUEST_RANDOMSEQ_ELEM, TP_D_ELEM_MUST_FLAG,randomSequence))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_LOGINREQUEST_RANDOMSEQ_ELEM.");
		return resCode;
	}
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_setVideoSourceEx(const std::string &confId, const std::string &siteUri, const std::string &videoSourceUri, int isLock, std::string& xmlStr)
{
	TP_DEBUG_TRACE("confId:%s siteUri:%s videoSourceUri:%s isLock:%d",confId.c_str(),siteUri.c_str(),videoSourceUri.c_str(),isLock);
	char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_VIDEO_SOURCE, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	(void)xml.AddElem(TP_D_SOAP_SITEURI);
	(void)xml.SetElemValue(siteUri.c_str());
	if ( videoSourceUri != "" )
	{
		(void)xml.AddElem(TP_D_SOAP_VIDEO_SOURCE_URI);
		(void)xml.SetElemValue(videoSourceUri.c_str());
	}

	if(isLock==1|| isLock == 0)
	{
		(void)sprintf_s(strVal,255,"%d",isLock);
		(void)xml.AddElem(TP_D_SOAP_ISLOCK);
		(void)xml.SetElemValue(strVal);
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_setAudioSwitchEx(const std::string &confId, int switchGate, int isSwitch, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_AUDIO_SWITCH, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());


	(void)sprintf_s(strVal,255,"%d",switchGate);
	(void)xml.AddElem(TP_D_SOAP_SWITCHGATE);
	(void)xml.SetElemValue(strVal);
	

	(void)sprintf_s(strVal,255,"%d",isSwitch);
	(void)xml.AddElem(TP_D_SOAP_ISSWITCH);
	(void)xml.SetElemValue(strVal);


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_setBroadcastSiteEx(const std::string &confId, const std::string &siteUri, int isBroadcast, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_BROADCAST_SITE, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());

	(void)xml.AddElem(TP_D_SOAP_SITEURI);
	(void)xml.SetElemValue(siteUri.c_str());

	(void)sprintf_s(strVal,255,"%d",isBroadcast);
	(void)xml.AddElem(TP_D_SOAP_ISBROADCAST);
	(void)xml.SetElemValue(strVal);

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_setBroadcastContinuousPresenceEx(const std::string &confId, int isBroadcast, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_BROADCAST_CONTINUOURS_PRESENCE, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());

	(void)sprintf_s(strVal,255,"%d",isBroadcast);
	(void)xml.AddElem(TP_D_SOAP_ISBROADCAST);
	(void)xml.SetElemValue(strVal);
	
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_setSitesMuteEx(const std::string &confId, const list<std::string>& siteUris, int isMute, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;
	list<string>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_SITES_MUTE, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	
	for(i=siteUris.begin(); i!=siteUris.end(); i++)
	{
		(void)xml.AddElem(TP_D_SOAP_SITEURIS);
		(void)xml.SetElemValue(i->c_str());
	}

	(void)sprintf_s(strVal,255,"%d",isMute);
	(void)xml.AddElem(TP_D_SOAP_ISMUTE);
	(void)xml.SetElemValue(strVal);	

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_setSitesQuietEx(const std::string &confId, const list<std::string> &siteUris, int isQuiet, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;
	list<string>::const_iterator i;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_SITES_QUIET, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());

	for(i=siteUris.begin(); i!=siteUris.end(); i++)
	{
		(void)xml.AddElem(TP_D_SOAP_SITEURIS);
		(void)xml.SetElemValue(i->c_str());
	}

	(void)sprintf_s(strVal,255,"%d",isQuiet);
	(void)xml.AddElem(TP_D_SOAP_ISQUIET);
	(void)xml.SetElemValue(strVal);

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}



int XMLProcess::SetXml_setContinuousPresenceEx(const std::string &confId, const std::string &target, int presenceMode, const list<std::string>& subPics, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;
	list<string>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_CONTINUOURS_PRESENCE, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());

	(void)xml.AddElem(TP_D_SOAP_TARGET);
	if(target.length())
	{
		(void)xml.SetElemValue(target.c_str());
	}

	(void)sprintf_s(strVal,255,"%d",presenceMode);
	(void)xml.AddElem(TP_D_SOAP_PRESENCE_MODE);
	(void)xml.SetElemValue(strVal);
	
	for(i=subPics.begin(); i!=subPics.end(); i++)
	{
		(void)xml.AddElem(TP_D_SOAP_SUBPICS);
		(void)xml.SetElemValue(i->c_str());
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_requestConfChairEx(const std::string &confId, const std::string &chairmanUri, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_REQUEST_CONF_CHAIR, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());

	(void)xml.AddElem(TP_D_SOAP_CHAIRMAN_URI);
	(void)xml.SetElemValue(chairmanUri.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_releaseConfChairEx(const std::string &confId, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_RELEASE_CONF_CHAIR, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_setFloorEx(const std::string &confId, const std::string &siteUri, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_FLOOR, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	(void)xml.AddElem(TP_D_SOAP_SITEURI);
	(void)xml.SetElemValue(siteUri.c_str());


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_setConfSiteVolumeEx(const std::string &confId, const list<SiteVolumeEx>& siteVolumes, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;
	list<SiteVolumeEx>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_CONF_SITE_VOLUME, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	
	for(i=siteVolumes.begin();i!=siteVolumes.end();i++)
	{
		(void)xml.AddElem(TP_D_SOAP_SITE_VOLUMES);
		(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
		(void)xml.IntoElem();
		(void)xml.SetElemValue(i->siteUri.c_str());
		(void)xml.AddElem(TP_D_SOAP_VOLUME);
		(void)sprintf_s(strVal,255,"%d",i->volume);
		(void)xml.SetElemValue(strVal);
		xml.OutOfElem();
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_displayConfSiteLocalVideoEx(const std::string &confId,  const list<std::string> &siteUris, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;
	list<std::string>::const_iterator i;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_DISPLAY_CONF_SITE_LOCAL_VIDEO, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());

	for(i=siteUris.begin();i!=siteUris.end();i++)
	{
		(void)xml.AddElem(TP_D_SOAP_SITEURIS);
		(void)xml.SetElemValue(i->c_str());
	}


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_hideConfSiteLocalVideoEx(const std::string &confId, const list<std::string> &siteUris, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;
	list<std::string>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_HIDE_CONF_SITE_LOCAL_VIDEO, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());

	for(i=siteUris.begin();i!=siteUris.end();i++)
	{
		(void)xml.AddElem(TP_D_SOAP_SITEURIS);
		(void)xml.SetElemValue(i->c_str());
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_lockPresentationEx(const std::string &confId, const std::string &siteUri, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;
	
	if(Package_BasicSOAP(TP_D_SOAP_SMC_LOCK_PRESENTATION, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());
	(void)xml.AddElem(TP_D_SOAP_SITEURI);
	(void)xml.SetElemValue(siteUri.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_unlockPresentationEx(const std::string &confId, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_UNLOCK_PRESENTATION, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_CONFID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(confId.c_str());


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int  XMLProcess::Package_TerminalInfoEx(const TerminalInfoEx *siteInfo, CXml *xml)
{
	char strVal[256]={0};
	list<VideoCapbilityItemEx>::const_iterator i;
	list<int>::const_iterator j;
	(void)xml->AddChildElem(TP_D_SOAP_NAME);
	(void)xml->IntoElem();

	std::string tempStr=TP_Tool::ANSIToUTF8(siteInfo->name);

	(void)xml->SetElemValue(tempStr.c_str());
	(void)xml->AddElem(TP_D_SOAP_URI);
	(void)xml->SetElemValue(siteInfo->uri.c_str());
	(void)xml->AddElem(TP_D_SOAP_TYPE);
	(void)sprintf_s(strVal,255,"%d",siteInfo->type);
	(void)xml->SetElemValue(strVal);
	if(siteInfo->rate.length())
	{
		(void)xml->AddElem(TP_D_SOAP_RATE);
		(void)xml->SetElemValue(TP_Tool::ANSIToUTF8(siteInfo->rate).c_str());
	}
	if(siteInfo->videoCapbility.size())
	{
		for(i=siteInfo->videoCapbility.begin();i!=siteInfo->videoCapbility.end(); i++)
		{
			(void)xml->AddElem(TP_D_SOAP_VIDEO_CAPBILITY);
			(void)xml->AddChildElem(TP_D_SOAP_VIDEO_PROTOCOL);
			(void)xml->IntoElem();
			(void)sprintf_s(strVal, 255, "%d", i->videoProtocol);
			(void)xml->SetElemValue(strVal);
			for(j=i->videoFormat.begin(); j!=i->videoFormat.end(); j++)
			{
				(void)xml->AddElem(TP_D_SOAP_VIDEO_FORMAT);
				(void)sprintf_s(strVal, 255, "%d",*j);
				(void)xml->SetElemValue(strVal);
			}
			xml->OutOfElem();
		}
	}

	if(siteInfo->regUser.length())
	{
		(void)xml->AddElem(TP_D_SOAP_REGUSER);
		(void)xml->SetElemValue(siteInfo->regUser.c_str());
	}

	if(siteInfo->regPassword.length())
	{
		(void)xml->AddElem(TP_D_SOAP_REGPASSWORD);
		(void)xml->SetElemValue(siteInfo->regPassword.c_str());
	}
	
	xml->OutOfElem();	
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_addSiteInfoEx(const std::string &orgId, const TerminalInfoEx &siteInfo, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_ADD_SITE_INFOEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_ORGID);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(orgId.c_str());
	(void)xml.AddElem(TP_D_SOAP_SITEINFO);
	(void)Package_TerminalInfoEx(&siteInfo, &xml);
	xml.OutOfElem();

	
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_editSiteInfoEx(const TerminalInfoEx &siteInfo, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;
	
	if(Package_BasicSOAP(TP_D_SOAP_SMC_EDIT_SITE_INFOEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEINFO);
	(void)xml.IntoElem();
	(void)Package_TerminalInfoEx(&siteInfo, &xml);

	xml.OutOfElem();

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_deleteSiteInfoEx(const list<std::string> &siteUris, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;
	list<std::string>::const_iterator i;
	int first_flag = 1;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_DELETE_SITE_INFOEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	for(i=siteUris.begin();i!=siteUris.end();i++)
	{
		if(first_flag)
		{
			(void)xml.AddChildElem(TP_D_SOAP_SITEURIS);
			(void)xml.IntoElem();
			first_flag = 0;
		}
		else
		{
			(void)xml.AddElem(TP_D_SOAP_SITEURIS);
		}
		
		(void)xml.SetElemValue(i->c_str());
	}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Package_QueryConfigEx(const QueryConfigEx *queryConfig, CXml *xml)
{
	char strVal[256]={0};
	list<SortItemEx>::const_iterator i;
	list<StringFilterEx>::const_iterator j;
	int first_flag = 1;

	(void)xml->AddChildElem(TP_D_SOAP_FOCUSITEM);
	(void)xml->IntoElem();
	(void)xml->SetElemValue( TP_Tool::Int2String(queryConfig->focusItem).c_str() );

	(void)xml->AddElem(TP_D_SOAP_PAGEPARAM);
	(void)xml->IntoElem();
	(void)xml->AddChildElem(TP_D_SOAP_NUMBERPERPAGE);
	(void)xml->IntoElem();
	(void)sprintf_s(strVal,255,"%d",queryConfig->pageParam.numberPerPage);
	(void)xml->SetElemValue(strVal);
	(void)xml->AddElem(TP_D_SOAP_CURRENT_PAGE);
	(void)sprintf_s(strVal,255,"%d",queryConfig->pageParam.currentPage);
	(void)xml->SetElemValue(strVal);
	(void)xml->OutOfElem();
	//(void)xml->OutOfElem();

	if(queryConfig->sortItems.size())
	{
		for(i=queryConfig->sortItems.begin(); i!=queryConfig->sortItems.end(); i++)
		{

			(void)xml->AddElem(TP_D_SOAP_SORT_ITEMS);
			(void)xml->IntoElem();

			(void)xml->AddChildElem(TP_D_SOAP_SORT);
			(void)xml->IntoElem();
			(void)sprintf_s(strVal,255,"%d",i->sort);
			(void)xml->SetElemValue(strVal);

			(void)xml->AddElem(TP_D_SOAP_ITEM_INDEX);
			(void)sprintf_s(strVal,255,"%d",i->itemIndex);
			(void)xml->SetElemValue(strVal);
			(void)xml->OutOfElem();
		}
	}

	if(queryConfig->filters.size())
	{
		for(j=queryConfig->filters.begin(); j!=queryConfig->filters.end(); j++)
		{

			(void)xml->AddElem(TP_D_SOAP_FILTERS);
			(void)xml->IntoElem();
			(void)xml->AddAttribute(TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI,TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI_VALUE);
			(void)xml->AddAttribute(TP_D_SOAP_FILTERS_ATTR_XSI_TYPE,TP_D_SOAP_FILTERS_ATTR_XSI_TYPE_VALUE);

			(void)xml->AddChildElem(TP_D_SOAP_COLUMN_INDEX);
			(void)xml->IntoElem();
			(void)sprintf_s(strVal,255,"%d",j->columnIndex);
			(void)xml->SetElemValue(strVal);

			(void)xml->AddElem(TP_D_SOAP_VALUE);
			(void)xml->IntoElem();
			(void)xml->SetElemValue(TP_Tool::ANSIToUTF8(j->value).c_str());
			(void)xml->OutOfElem();
		}
	}

	//(void)xml->AddElem(TP_D_SOAP_FOCUSITEM);
	//(void)xml->IntoElem();
	//(void)xml->SetElemValue( TP_Tool::Int2String(queryConfig->focusItem).c_str() );

	//if(first_flag)
	//{
	//	(void)xml->AddChildElem(TP_D_SOAP_PAGEPARAM);
	//	(void)xml->IntoElem();
	//	//first_flag = 0;
	//}
	//else
	//{
	//	(void)xml->AddElem(TP_D_SOAP_PAGEPARAM);
	//}
	//
	//(void)xml->AddChildElem(TP_D_SOAP_NUMBERPERPAGE);
	//(void)xml->IntoElem();
	//(void)sprintf_s(strVal,255,"%d",queryConfig->pageParam.numberPerPage);
	//(void)xml->SetElemValue(strVal);
	//(void)xml->AddElem(TP_D_SOAP_CURRENT_PAGE);
	//(void)sprintf_s(strVal,255,"%d",queryConfig->pageParam.currentPage);
	//(void)xml->SetElemValue(strVal);
	//(void)xml->OutOfElem();
	//(void)xml->OutOfElem();
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_querySitesInfoEx(const QueryConfigEx &queryConfig, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;
	
	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_SITES_INFO, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_QUERY_CONFIG);
	(void)xml.IntoElem();
	(void)Package_QueryConfigEx(&queryConfig, &xml);
	xml.OutOfElem();

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::Parse_TerminalInfoEx(CXml *xmlParse, TerminalInfoEx &site)
{
	std::string strVal;

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_MUST_FLAG, site.name))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_NAME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	site.name = TP_Tool::UTF8ToANSI(site.name);
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_URI, TP_D_ELEM_MUST_FLAG, site.uri))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_URI. ");
		return TP_SDK_ERR_XML_PARSE;
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_TYPE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_TYPE. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		site.type = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_RATE, TP_D_ELEM_OPTIONAL_FLAG, site.rate))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RATE. ");
		return TP_SDK_ERR_XML_PARSE;
	}

	if (xmlParse->FindElem(TP_D_SOAP_VIDEO_CAPBILITY))
	{
		do 
		{
			if (xmlParse->GetElem()==NULL)
			{
				break;
			}
			VideoCapbilityItemEx videoCapbilityItem;
			if(strcmp(xmlParse->GetElem(),TP_D_SOAP_VIDEO_CAPBILITY)!=0)
			{
				break;
			}
			(void)xmlParse->IntoElem();
			strVal.clear();
			if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_VIDEO_CAPBILITY, TP_D_ELEM_MUST_FLAG, strVal))
			{
				TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_VIDEO_CAPBILITY. ");
				return TP_SDK_ERR_XML_PARSE;
			}
			if(strVal.length())
			{
				videoCapbilityItem.videoProtocol = TP_Tool::String2Int(strVal);
			}
			
			if(xmlParse->FindElem(TP_D_SOAP_VIDEO_FORMAT))
			{
				do 
				{
					if (xmlParse->GetElem()==NULL)
					{
						break;
					}
					int format;
					if(strcmp(xmlParse->GetElem(),TP_D_SOAP_VIDEO_FORMAT)!=0)
					{
						break;
					}
					strVal.clear();
					if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_VIDEO_FORMAT, TP_D_ELEM_MUST_FLAG, strVal))
					{
						TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_VIDEO_FORMAT. ");
						return TP_SDK_ERR_XML_PARSE;
					}
					format = TP_Tool::String2Int(strVal);
					videoCapbilityItem.videoFormat.push_back(format);
				} while (xmlParse->NextElem());
			}

			xmlParse->OutOfElem();
			site.videoCapbility.push_back(videoCapbilityItem);
		} while (xmlParse->NextElem());

	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_REGUSER, TP_D_ELEM_OPTIONAL_FLAG, site.regUser))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_REGUSER.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_REGPASSWORD, TP_D_ELEM_OPTIONAL_FLAG, site.regPassword))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_REGPASSWORD. ");
		return TP_SDK_ERR_XML_PARSE;
	}

	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetXml_querySitesInfoEx(const char *xmlStr, QuerySitesInfoExResponse *querySitesInfoExResponse)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYSITESINFOEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYSITESINFOEX))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_QUERYSITESINFOEX. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	querySitesInfoExResponse->sites.clear();
	if (xmlParse.FindElem(TP_D_SOAP_SITES))
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
		
			if(strcmp(xmlParse.GetElem(),TP_D_SOAP_SITES) !=0)
			{
				break;
			}
			TerminalInfoEx site;
			(void)xmlParse.IntoElem();
			(void)Parse_TerminalInfoEx(&xmlParse, site);
			xmlParse.OutOfElem();
			querySitesInfoExResponse->sites.push_back(site);

		} while (xmlParse.NextElem());
	}

	if(xmlParse.FindElem(TP_D_SOAP_PAGE_INFO))
	{
		(void)xmlParse.IntoElem();
		(void)Parse_PagesInfoEx(&xmlParse, querySitesInfoExResponse->pageInfo);
		xmlParse.OutOfElem();
	}

	return TP_SDK_ERR_SUCCESS;	
}


int XMLProcess::SetXml_queryMCUInfoEx(const QueryConfigEx &queryConfig, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_MCU_INFOEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_QUERY_CONFIG);
	(void)xml.IntoElem();

	(void)Package_QueryConfigEx(&queryConfig, &xml);
	xml.OutOfElem();

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Parse_MCUInfoEx(CXml *xmlParse, MCUInfoEx &mcuInfo)
{
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ID, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		mcuInfo.id = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_MUST_FLAG, mcuInfo.name))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	mcuInfo.name = TP_Tool::UTF8ToANSI(mcuInfo.name);
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_TYPE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_TYPE.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		mcuInfo.type = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_IP1, TP_D_ELEM_OPTIONAL_FLAG, mcuInfo.ip1))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_IP1.");
		return TP_SDK_ERR_XML_PARSE;
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_PORT1, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_PORT1.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		mcuInfo.port1 = TP_Tool::String2Int(strVal);
	}


	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_IP2, TP_D_ELEM_OPTIONAL_FLAG, mcuInfo.ip2))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_IP2.");
		return TP_SDK_ERR_XML_PARSE;
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_PORT2, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_PORT2.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		mcuInfo.port2 = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_DOMAIN_NAME, TP_D_ELEM_MUST_FLAG, mcuInfo.domainName))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_DOMAIN_NAME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_STUTAS, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_STUTAS.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length())
	{
		mcuInfo.stutas = TP_Tool::String2Int(strVal);
	}

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetXml_queryMCUInfoEx(const char *xmlStr, QueryMCUInfoExResponse *queryMCUInfoExResponse)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYMCUINFOEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_BODY_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYMCUINFOEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYMCUINFOEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	queryMCUInfoExResponse->mcus.clear();
	if (xmlParse.FindElem(TP_D_SOAP_MCUS))
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}

			if(strcmp(xmlParse.GetElem(),TP_D_SOAP_MCUS) !=0)
			{
				break;
			}
			MCUInfoEx mcuInfo;
			(void)xmlParse.IntoElem();
			(void)Parse_MCUInfoEx(&xmlParse, mcuInfo);
			xmlParse.OutOfElem();
			queryMCUInfoExResponse->mcus.push_back(mcuInfo);

		} while (xmlParse.NextElem());
	}

	if(xmlParse.FindElem(TP_D_SOAP_PAGE_INFO))
	{
		(void)xmlParse.IntoElem();
		(void)Parse_PagesInfoEx(&xmlParse, queryMCUInfoExResponse->pageInfo);
		xmlParse.OutOfElem();
	}

	return TP_SDK_ERR_SUCCESS;	
}

int XMLProcess::SetXml_queryMCUFutureResourceEx(const list<int> &mcus, const SYSTEMTIME &beginTime, const std::string &duration, std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;
	list<int>::const_iterator i;
	int first_flag = 1;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_MCU_FUTURE_RESOURCEEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	for(i=mcus.begin(); i!=mcus.end(); i++)
	{
		if(first_flag)
		{
			(void)xml.AddChildElem(TP_D_SOAP_MCUS);
			(void)xml.IntoElem();
			first_flag = 0;
		}
		else
		{
			(void)xml.AddElem(TP_D_SOAP_MCUS);
		}
		
		(void)sprintf_s(strVal,255,"%d",*i);
		(void)xml.SetElemValue(strVal);
	}
	
	if(first_flag)
	{
		if (beginTime.wYear || beginTime.wMonth || beginTime.wDay)
		{
			(void)xml.AddChildElem(TP_D_SOAP_BEGINTIME);
			(void)xml.IntoElem();
			(void)sprintf_s(strVal,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
				,beginTime.wYear,beginTime.wMonth,beginTime.wDay
				,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
				,TP_Tool::GetLocalTimeZone().c_str());
			(void)xml.SetElemValue(strVal);
		}
		
	}
	else
	{
		if (beginTime.wYear || beginTime.wMonth || beginTime.wDay)
		{
			(void)xml.AddElem(TP_D_SOAP_BEGINTIME);
			(void)sprintf_s(strVal,255,"%04d-%02d-%02dT%02d:%02d:%02d.%03d%s"
				,beginTime.wYear,beginTime.wMonth,beginTime.wDay
				,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
				,TP_Tool::GetLocalTimeZone().c_str());
			(void)xml.SetElemValue(strVal);
		}
		
	}
	if (duration.length())
	{
		(void)xml.AddElem(TP_D_SOAP_DURATION);
		(void)xml.SetElemValue(duration.c_str());
	}
	

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::Parse_MCUResourceEx(CXml *xmlParse, MCUResourceEx &mcuResource)
{
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_MCUID, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_MCUID. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		mcuResource.mcuId = TP_Tool::String2Int(strVal);
	}

	if(!xmlParse->FindElem(TP_D_SOAP_RESOURCE_LIST))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RESOURCE_LIST.");
		return TP_SDK_ERR_XML_PARSE;
	}
	do 
	{
		if (xmlParse->GetElem()==NULL)
		{
			break;
		}
		if(strcmp(xmlParse->GetElem(),TP_D_SOAP_RESOURCE_LIST))
		{
			break;
		}
		MCUResourceItemEx mcuResourceItem;
		(void)xmlParse->IntoElem();
		(void)Parse_MCUResourceItemEx(xmlParse, mcuResourceItem);
		xmlParse->OutOfElem();
		mcuResource.resourceList.push_back(mcuResourceItem);
	} while (xmlParse->NextElem());

	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetXml_queryMCUFutureResourceEx(const char *xmlStr, list<MCUResourceEx> *MCUResouce)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYMCUFUTURERESOURCEEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYMCUFUTURERESOURCEEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYMCUFUTURERESOURCEEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();

	MCUResouce->clear();
	if (xmlParse.FindElem(TP_D_SOAP_MCURES_LIST))
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}

			if(strcmp(xmlParse.GetElem(),TP_D_SOAP_MCURES_LIST) !=0)
			{
				break;
			}
			MCUResourceEx mcuResource;
			(void)xmlParse.IntoElem();
			(void)Parse_MCUResourceEx(&xmlParse, mcuResource);
			xmlParse.OutOfElem();
			MCUResouce->push_back(mcuResource);

		} while (xmlParse.NextElem());
	}

	return TP_SDK_ERR_SUCCESS;	
}

int XMLProcess::Parse_MCUResourceItemEx(CXml *xmlParse, MCUResourceItemEx &mcuResourceItem)
{
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_RESOURCE_TYPE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RESOURCE_TYPE.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		mcuResourceItem.resourceType = TP_Tool::String2Int(strVal);
	}

	if(!xmlParse->FindElem(TP_D_SOAP_RESOURCE_STATUS))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RESOURCE_STATUS.");
		return TP_SDK_ERR_XML_PARSE;
	}
	do 
	{
		if (xmlParse->GetElem()==NULL)
		{
			break;
		}
		if(strcmp(xmlParse->GetElem(),TP_D_SOAP_RESOURCE_STATUS))
		{
			break;
		}
		ResourceOccupiedStatusEx resourceOccupiedStatus;
		(void)xmlParse->IntoElem();
		(void)Parse_ResourceOccupiedStatusEx(xmlParse, resourceOccupiedStatus);
		xmlParse->OutOfElem();
		mcuResourceItem.resourceStatus.push_back(resourceOccupiedStatus);
	} while (xmlParse->NextElem());

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Parse_ResourceOccupiedStatusEx(CXml *xmlParse, ResourceOccupiedStatusEx &ResourceOccupiedStatus)
{
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_FREE_COUNT, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_FREE_COUNT.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		ResourceOccupiedStatus.freeCount = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_TOTAL_COUNT, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_TOTAL_COUNT.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		ResourceOccupiedStatus.totalcount = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_BEGINTIME, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BEGINTIME.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if(strVal.length()!=0)
	{
		(void)StringTimeFormatTOSystemtime(strVal,ResourceOccupiedStatus.beginTime);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_DURATION, TP_D_ELEM_MUST_FLAG, ResourceOccupiedStatus.duration))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_DURATION.");
		return TP_SDK_ERR_XML_PARSE;
	}
	

	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_queryOrganizationEx(std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_ORGANIZATIONEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Parse_OrganizationItemEx(CXml *xmlParse, OrganizationItemEx &orgaItem)
{
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ID, TP_D_ELEM_MUST_FLAG, orgaItem.id))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_MUST_FLAG, orgaItem.name))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	orgaItem.name = TP_Tool::UTF8ToANSI(orgaItem.name);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetXml_queryOrganizationEx(const char *xmlStr, list<OrganizationItemEx> *list_orgItem)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYORGANIZATIONEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYORGANIZATIONEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYORGANIZATIONEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();


	list_orgItem->clear();
	if (xmlParse.FindElem(TP_D_SOAP_ORGS))
	{
		do
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}

			if(strcmp(xmlParse.GetElem(),TP_D_SOAP_ORGS) !=0)
			{
				break;
			}
			OrganizationItemEx orgaItem;
			(void)xmlParse.IntoElem();
			(void)Parse_OrganizationItemEx(&xmlParse, orgaItem);
			xmlParse.OutOfElem();
			list_orgItem->push_back(orgaItem);

		} while (xmlParse.NextElem());
	}

	return TP_SDK_ERR_SUCCESS;	
}

int XMLProcess::SetXml_requestChairEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_REQUEST_CHAIREX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_releaseChairEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_RELEASE_CHAIREX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_queryConfCtrlPwdEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_CONF_CTRL_PWDEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetXml_queryConfCtrlPwdEx(const char *xmlStr, int &result)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYCONFCTRLPWDEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYCONFCTRLPWDEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYCONFCTRLPWDEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_RESULT, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RESULT.");
		return resCode;
	}
	
	if(strVal.length())
	{
		result = TP_Tool::String2Int(strVal);
	}

	return TP_SDK_ERR_SUCCESS;	
}
int XMLProcess::SetXml_queryBroadInfoEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_BROAD_INFOEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetXml_queryBroadInfoEx(const char *xmlStr, BroadInfoEx *broadInfo)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYBROADINFOEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYBROADINFOEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYBROADINFOEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (xmlParse.FindElem(TP_D_SOAP_BROAD_INFO))
	{
		(void)xmlParse.IntoElem();
		std::string strVal;
		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_DIRECT_BROAD, TP_D_ELEM_MUST_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_DIRECT_BROAD. ");
			return resCode;
		}
		if(strVal.length())
		{
			broadInfo->directBroad = TP_Tool::String2Int(strVal);
		}

		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_RECORD_BROAD, TP_D_ELEM_MUST_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RECORD_BROAD.");
			return resCode;
		}
		if(strVal.length())
		{
			broadInfo->recordBroad = TP_Tool::String2Int(strVal);
		}

		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_DIRECT_BROAD_STATUS, TP_D_ELEM_OPTIONAL_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_DIRECT_BROAD_STATUS.");
			return resCode;
		}
		if(strVal.length())
		{
			broadInfo->directBroadStatus = TP_Tool::String2Int(strVal);
		}

		strVal.clear();
		if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_RECORD_BROAD_STATUS, TP_D_ELEM_OPTIONAL_FLAG, strVal))
		{
			TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RECORD_BROAD_STATUS.");
			return resCode;
		}
		if(strVal.length())
		{
			broadInfo->recordBroadStatus = TP_Tool::String2Int(strVal);
		}

	}
	

	return TP_SDK_ERR_SUCCESS;	
}
int XMLProcess::SetXml_setRecordBroadEx(const std::string &siteUri, int action,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_RECORD_BROADEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	(void)xml.AddElem(TP_D_SOAP_ACTION);
	(void)sprintf_s(strVal,255,"%d",action);
	(void)xml.SetElemValue(strVal);


	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_setDirectBroadEx(const std::string &siteUri, int action,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_DIRECT_BROADEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	(void)xml.AddElem(TP_D_SOAP_ACTION);
	(void)sprintf_s(strVal,255,"%d",action);
	(void)xml.SetElemValue(strVal);

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}


int XMLProcess::SetXml_isConnectAuxSourceEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_IS_CONNECT_AUX_SOURCEEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetXml_isConnectAuxSourceEx(const char *xmlStr, int &result)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_ISCONNECTAUXSOURCEEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ISCONNECTAUXSOURCEEX))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ISCONNECTAUXSOURCEEX. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_RESULT, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RESULT.");
		return resCode;
	}

	if(strVal.length())
	{
		result = TP_Tool::String2Int(strVal);
	}

	return TP_SDK_ERR_SUCCESS;	
}
int XMLProcess::SetXml_isSendAuxStreamEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_IS_SEND_AUX_STREAMEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetXml_isSendAuxStreamEx(const char *xmlStr, int &result)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_ISSENDAUXSTREAMEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ISSENDAUXSTREAMEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ISSENDAUXSTREAMEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_RESULT, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RESULT.");
		return resCode;
	}

	if(strVal.length())
	{
		result = TP_Tool::String2Int(strVal);
	}

	return TP_SDK_ERR_SUCCESS;	
}
int XMLProcess::SetXml_isReceiveRemAuxStrmEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;


	if(Package_BasicSOAP(TP_D_SOAP_SMC_IS_RECEIVE_REM_AUX_STRMEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetXml_isReceiveRemAuxStrmEx(const char *xmlStr, int &result)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_ISRECEIVEREMAUXSTRMEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_BODY_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ISRECEIVEREMAUXSTRMEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ISRECEIVEREMAUXSTRMEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(&xmlParse, TP_D_SOAP_RESULT, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RESULT. ");
		return resCode;
	}

	if(strVal.length())
	{
		result = TP_Tool::String2Int(strVal);
	}

	return TP_SDK_ERR_SUCCESS;	
}

int XMLProcess::SetXml_setAuxStreamEx(const std::string &siteUri, int controlCode,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_AUX_STREAMEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	(void)xml.AddElem(TP_D_SOAP_CONTROL_CODE);
	(void)sprintf_s(strVal,255,"%d",controlCode);
	(void)xml.SetElemValue(strVal);

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_queryAuxStreamSourcesEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_AUX_STREAM_SOURCEEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	
	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Parse_AuxStreamInfoEx(CXml *xmlParse, AuxStreamInfoEx &auxStreamInfo)
{
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ID, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		auxStreamInfo.id = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_MUST_FLAG, auxStreamInfo.name))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_NAME. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	auxStreamInfo.name = TP_Tool::UTF8ToANSI(auxStreamInfo.name);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetXml_queryAuxStreamSourcesEx(const char *xmlStr, list<AuxStreamInfoEx> *list_auxStreamInfo)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYAUXSTREAMSOURCESEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_ENVELOP_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYAUXSTREAMSOURCESEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYAUXSTREAMSOURCESEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (xmlParse.FindElem(TP_D_SOAP_AUXSTREAMS))
	{
		do 
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse.GetElem(),TP_D_SOAP_AUXSTREAMS))
			{
				break;
			}
			AuxStreamInfoEx auxStreamInfo;
			(void)xmlParse.IntoElem();
			(void)Parse_AuxStreamInfoEx(&xmlParse, auxStreamInfo);
			list_auxStreamInfo->push_back(auxStreamInfo);
			xmlParse.OutOfElem();
		} while (xmlParse.NextElem());
	}

	return TP_SDK_ERR_SUCCESS;	
}



int XMLProcess::SetXml_queryVideoOutSrcStateEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_VIDEO_OUT_SRC_STATEEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Parse_VideoSourcesInfoEx(CXml *xmlParse, VideoSourcesInfoEx &videoSourcesInfo)
{
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SOURCE_ID, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SOURCE_ID.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		videoSourcesInfo.sourcesId = TP_Tool::String2Int(strVal);
	}


	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SOURCES_STATE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_SOURCES_STATE. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	if(strVal.length())
	{
		videoSourcesInfo.sourcesState = TP_Tool::String2Int(strVal);
	}


	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SOURCES_NAME, TP_D_ELEM_OPTIONAL_FLAG, videoSourcesInfo.sourcesName))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SOURCES_NAME.");
		return TP_SDK_ERR_XML_PARSE;
	}
	videoSourcesInfo.sourcesName = TP_Tool::UTF8ToANSI(videoSourcesInfo.sourcesName);
	return TP_SDK_ERR_SUCCESS;

}

int XMLProcess::GetXml_queryVideoOutSrcStateEx(const char *xmlStr, list<VideoSourcesInfoEx> *list_VideoSourcesInfo)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYVIDEOOUTSRCSTATEEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_BODY_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYVIDEOOUTSRCSTATEEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYVIDEOOUTSRCSTATEEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (xmlParse.FindElem(TP_D_SOAP_VIDEO_SOURCES_INFOS))
	{
		do 
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse.GetElem(),TP_D_SOAP_VIDEO_SOURCES_INFOS))
			{
				break;
			}
			VideoSourcesInfoEx videoSourcesInfo;
			(void)xmlParse.IntoElem();
			(void)Parse_VideoSourcesInfoEx(&xmlParse, videoSourcesInfo);
			list_VideoSourcesInfo->push_back(videoSourcesInfo);
			xmlParse.OutOfElem();
		} while (xmlParse.NextElem());
	}

	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_ctrlCameraEx(const std::string &siteUri, const CameraControlEx &cameraControl,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_CTRL_CAMERAEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	(void)xml.AddElem(TP_D_SOAP_CAMERA_CONTROL);
	(void)xml.AddChildElem(TP_D_SOAP_CAM_STATE);
	(void)xml.IntoElem();
	(void)sprintf_s(strVal,"%d",cameraControl.camState);
	(void)xml.SetElemValue(strVal);
	(void)xml.AddElem(TP_D_SOAP_CAM_ACTION);
	(void)sprintf_s(strVal,"%d",cameraControl.camAction);
	(void)xml.SetElemValue(strVal);
	(void)xml.AddElem(TP_D_SOAP_CAM_POS);
	(void)sprintf_s(strVal,"%d",cameraControl.camPos);
	(void)xml.SetElemValue(strVal);
	(void)xml.AddElem(TP_D_SOAP_CAM_SRC);
	(void)sprintf_s(strVal,"%d",cameraControl.camSrc);
	(void)xml.SetElemValue(strVal);

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_setMainAuxStreamSourcesEx(const std::string &siteUri, const list<int> &localMainSrcs, int localAuxSrc,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;
	list<int>::const_iterator i;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_MAIN_AUX_STREAM_SOURCESEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	for(i=localMainSrcs.begin();i!=localMainSrcs.end();i++)
	{
		(void)xml.AddElem(TP_D_SOAP_LOCAL_MAIN_SRCS);
		(void)sprintf_s(strVal,"%d",*i);
		(void)xml.SetElemValue(strVal);
	}
	(void)xml.AddElem(TP_D_SOAP_LOCAL_AUX_SRC);
	(void)sprintf_s(strVal,"%d",localAuxSrc);
	(void)xml.SetElemValue(strVal);

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::SetXml_queryMainStreamSourcesEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_MAIN_STREAM_SOURCESEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}
int XMLProcess::GetXml_queryMainStreamSourcesEx(const char *xmlStr, list<AuxStreamInfoEx> *list_auxStreamInfo)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYMAINSTREAMSOURCESEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_BODY_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYMAINSTREAMSOURCESEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYMAINSTREAMSOURCESEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (xmlParse.FindElem(TP_D_SOAP_AUXSTREAMS))
	{
		do 
		{
			if (xmlParse.GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse.GetElem(),TP_D_SOAP_AUXSTREAMS))
			{
				break;
			}
			AuxStreamInfoEx auxStreamInfo;
			(void)xmlParse.IntoElem();
			(void)Parse_AuxStreamInfoEx(&xmlParse, auxStreamInfo);
			list_auxStreamInfo->push_back(auxStreamInfo);
			xmlParse.OutOfElem();
		} while (xmlParse.NextElem());
	}

	return TP_SDK_ERR_SUCCESS;	
}
int XMLProcess::SetXml_setVideoOutSrcEx(const std::string &siteUri, int hdOut, int videoSrc,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	char strVal[256]={0};
	CXml xml;
	if(Package_BasicSOAP(TP_D_SOAP_SMC_SET_VIDEO_OUT_SRCEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());
	(void)xml.AddElem(TP_D_SOAP_HDOUT);
	(void)sprintf_s(strVal,"%d",hdOut);
	(void)xml.SetElemValue(strVal);
	(void)xml.AddElem(TP_D_SOAP_VIDEO_SRC);
	(void)sprintf_s(strVal,"%d",videoSrc);
	(void)xml.SetElemValue(strVal);

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::SetXml_querySiteVersionInfoEx(const std::string &siteUri,std::string& xmlStr)
{
	TP_DEBUG_TRACE("");
	//char strVal[256]={0};
	CXml xml;

	if(Package_BasicSOAP(TP_D_SOAP_SMC_QUERY_SITE_VERSION_INFOEX, &xml)!=TP_SDK_ERR_SUCCESS){}else{}
	(void)xml.AddChildElem(TP_D_SOAP_SITEURI);
	(void)xml.IntoElem();
	(void)xml.SetElemValue(siteUri.c_str());

	unsigned int uiLen = 0;
	const char* pXmlStr = xml.GetXMLStream(uiLen);
	if (NULL == pXmlStr)
	{
		TP_LOG_ERROR("pXmlStr is null.");
		return TP_SDK_ERR_XML_CONSTRUCT;
	}

	xmlStr = pXmlStr;
	//TP_LOG_INFO(xmlStr);
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Parse_SiteMicVersionMapEx(CXml *xmlParse,SiteMicVersionMapEx &micVersionMap)
{
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_MICIP, TP_D_ELEM_MUST_FLAG, micVersionMap.micIP))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_MICIP. ");
		return TP_SDK_ERR_XML_PARSE;
	}
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_VERSION, TP_D_ELEM_MUST_FLAG, micVersionMap.version))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_VERSION.");
		return TP_SDK_ERR_XML_PARSE;
	}
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::Parse_SiteDeviceVersionInfoEx(CXml *xmlParse, SiteDeviceVersionInfoEx *siteDeviceVersionInfo)
{
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_MODEL, TP_D_ELEM_OPTIONAL_FLAG, siteDeviceVersionInfo->model))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_MODEL.");
		return TP_SDK_ERR_XML_PARSE;
	}


	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_LICENSE, TP_D_ELEM_OPTIONAL_FLAG, siteDeviceVersionInfo->license))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_LICENSE.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SOFT_VERSION, TP_D_ELEM_OPTIONAL_FLAG, siteDeviceVersionInfo->softVersion))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SOFT_VERSION.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_HARD_VERSION, TP_D_ELEM_OPTIONAL_FLAG, siteDeviceVersionInfo->hardVersion))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_HARD_VERSION.");
		return TP_SDK_ERR_XML_PARSE;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_LOGIC_VERSION, TP_D_ELEM_OPTIONAL_FLAG, siteDeviceVersionInfo->logicVersion))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_LOGIC_VERSION.");
		return TP_SDK_ERR_XML_PARSE;
	}
	if (xmlParse->FindElem(TP_D_SOAP_MIC_VERSIONS))
	{
		do 
		{
			if (xmlParse->GetElem()==NULL)
			{
				break;
			}
			if(strcmp(xmlParse->GetElem(),TP_D_SOAP_MIC_VERSIONS))
			{
				break;
			}
			SiteMicVersionMapEx siteMicVersionMap;
			(void)xmlParse->IntoElem();
			(void)Parse_SiteMicVersionMapEx(xmlParse, siteMicVersionMap);
			siteDeviceVersionInfo->micVersions.push_back(siteMicVersionMap);
			xmlParse->OutOfElem();
		} while (xmlParse->NextElem());
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_MANUFACTURER, TP_D_ELEM_OPTIONAL_FLAG, siteDeviceVersionInfo->manufacturer))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_MANUFACTURER.");
		return TP_SDK_ERR_XML_PARSE;
	}
	return TP_SDK_ERR_SUCCESS;
}

int XMLProcess::GetXml_querySiteVersionInfoEx(const char *xmlStr, SiteDeviceVersionInfoEx *siteDeviceVersionInfo)
{
	int resCode = 0;
	TP_DEBUG_TRACE("");
	if (NULL == xmlStr)
	{
		TP_LOG_ERROR("xmlStr is null.");
		return TP_SDK_ERR_INVALID_PARAM;
	}
	resCode = GetRSPXML_ResultCode(xmlStr, TP_D_SOAP_RSP_QUERYSITEVERSIONINFOEX);
	if (TP_E_RET_CODE_SUCCESS != resCode)
	{
		TP_LOG_ERROR("Response error! result Code:%d .",resCode);
		return resCode;
	}

	CXml xmlParse;
	if (!xmlParse.Parse(xmlStr))
	{
		TP_LOG_ERROR("parse xml failed.");
		return resCode;
	}

	if (!xmlParse.FindElem(TP_D_SOAP_RSP_ENVELOP_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found TP_D_SOAP_RSP_ENVELOP_ELEM. ");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_BODY_ELEM))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_BODY_ELEM.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (!xmlParse.FindElem(TP_D_SOAP_RSP_QUERYSITEVERSIONINFOEX))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_RSP_QUERYSITEVERSIONINFOEX.");
		return resCode;
	}
	(void)xmlParse.IntoElem();
	if (xmlParse.FindElem(TP_D_SOAP_SITE_DEVICE_VERSION_INFO))
	{
		(void)xmlParse.IntoElem();
		(void)Parse_SiteDeviceVersionInfoEx(&xmlParse, siteDeviceVersionInfo);
	}

	return TP_SDK_ERR_SUCCESS;	
}
int XMLProcess::Parse_ConferenceStatusEx(CXml *xmlParse, ConferenceStatusEx &confStatus)
{
	std::string strVal;
	int resCode = TP_SDK_ERR_XML_PARSE;
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ID, TP_D_ELEM_OPTIONAL_FLAG, confStatus.id))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_OPTIONAL_FLAG, confStatus.name))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
		return resCode;
	}
	confStatus.name = TP_Tool::UTF8ToANSI(confStatus.name);
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_STATUS, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_STATUS.");
		return resCode;
	}
	if(strVal.length()!=0)
	{
		confStatus.status = TP_Tool::String2Int(strVal);
	}



	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CHAIR, TP_D_ELEM_OPTIONAL_FLAG, confStatus.chair))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CHAIR.");
		return resCode;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_BROADCAST, TP_D_ELEM_OPTIONAL_FLAG, confStatus.broadcast))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}


	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SPEAKING, TP_D_ELEM_OPTIONAL_FLAG, confStatus.speaking))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SPEAKING.");
		return resCode;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_PRESENTATION, TP_D_ELEM_OPTIONAL_FLAG, confStatus.presentation))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_PRESENTATION.");
		return resCode;
	}
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ISLOCK, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ISLOCK.");
		return resCode;
	}

	if(strVal.length() != 0)
	{
		confStatus.isLock = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ISAUDIOSWITCH, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ISAUDIOSWITCH.");
		return resCode;
	}

	if(strVal.length() != 0)
	{
		confStatus.isAudioSwitch = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SWITCHGATE, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_SWITCHGATE.");
		return resCode;
	}

	if(strVal.length() != 0)
	{
		confStatus.switchGate = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_BEGINTIME, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BEGINTIME.");
		return resCode;
	}

	if(strVal.length()!=0)
	{
		(void)StringTimeFormatTOSystemtime(strVal,confStatus.beginTime);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ENDTIME, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ENDTIME.");
		return resCode;
	}

	if(strVal.length()!=0)
	{
		(void)StringTimeFormatTOSystemtime(strVal,confStatus.endTime);
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ISLOCKPRESENTATION, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ENDTIME.");
		return resCode;
	}

	if(strVal.length()!=0)
	{
		confStatus.isLockPresentation = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_LOCKPRESENTATION, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ENDTIME.");
		return resCode;
	}

	if(strVal.length()!=0)
	{
		confStatus.lockPresentation = strVal;
	}

	if (xmlParse->FindElem(TP_D_SOAP_RECORDING))
	{
		xmlParse->IntoElem();
		(void)Parse_RecordStatusEx(xmlParse, confStatus.recording);
		xmlParse->OutOfElem();
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CONFERENCEMODE, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ENDTIME.");
		return resCode;
	}

	if(strVal.length()!=0)
	{
		confStatus.conferenceMode = TP_Tool::String2Int(strVal);
	}

	resCode = TP_SDK_ERR_SUCCESS;
	return resCode;
}

int XMLProcess::Parse_RecordStatusEx(CXml *xmlParse, RecordStatusEx &recordStatus)
{
	std::string strVal;
	int resCode = TP_SDK_ERR_XML_PARSE;
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ISSUPPORTLIVING, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}

	if(strVal.length()!=0)
	{
		recordStatus.isSupportLiving = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ISSUPPORTRECORDING, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
		return resCode;
	}

	if(strVal.length()!=0)
	{
		recordStatus.isSupportRecording = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_STATUS, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_STATUS.");
		return resCode;
	}
	if(strVal.length()!=0)
	{
		recordStatus.status = TP_Tool::String2Int(strVal);
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ISAUTORECORDINGVIDEOSOURCE, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CHAIR.");
		return resCode;
	}
	if(strVal.length()!=0)
	{
		recordStatus.isAutoRecordingVideoSource = TP_Tool::String2Int(strVal);
	}


	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_BROADCAST, TP_D_ELEM_OPTIONAL_FLAG, recordStatus.videoSource))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	resCode = TP_SDK_ERR_SUCCESS;
	return resCode;
}

int XMLProcess::Parse_AdhocConfTemplateParamEx(CXml *xmlParse, AdhocConfTemplateParamEx &adhocConfTemplateParam)
{
	std::string strVal;
	int resCode = TP_SDK_ERR_XML_PARSE;

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ADHOC_CONF_TEMPLATE_ID, TP_D_ELEM_MUST_FLAG, adhocConfTemplateParam.adhocConfTemplateId))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_ID.");
		return resCode;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_OPTIONAL_FLAG, adhocConfTemplateParam.name))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_NAME.");
		return resCode;
	}
	adhocConfTemplateParam.name = TP_Tool::UTF8ToANSI(adhocConfTemplateParam.name);

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ACCESS_CODE, TP_D_ELEM_MUST_FLAG, adhocConfTemplateParam.accessCode))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_STATUS.");
		return resCode;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_DURATION, TP_D_ELEM_OPTIONAL_FLAG, adhocConfTemplateParam.duration))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_CHAIR.");
		return resCode;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_BILL_CODE, TP_D_ELEM_OPTIONAL_FLAG, adhocConfTemplateParam.billCode))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_PASSWORD, TP_D_ELEM_OPTIONAL_FLAG, adhocConfTemplateParam.password))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CPRESOURCE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	if(strVal.length())
	{
		adhocConfTemplateParam.cpResouce = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_RATE, TP_D_ELEM_OPTIONAL_FLAG, adhocConfTemplateParam.rate))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_MEDIA_ENCRYPT_TYPE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	if(strVal.length())
	{
		adhocConfTemplateParam.mediaEncryptType = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_IS_LIVE_BROADCAST, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	if(strVal.length())
	{
		adhocConfTemplateParam.isLiveBroadcast = TP_Tool::String2Int(strVal);
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_ISRECORDING, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	if(strVal.length())
	{
		adhocConfTemplateParam.isRecording = TP_Tool::String2Int(strVal);
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_PRESENTATION, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	if(strVal.length())
	{
		adhocConfTemplateParam.presentation = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_CHAIRMAN_PASSWORD, TP_D_ELEM_OPTIONAL_FLAG, adhocConfTemplateParam.chairmanPassword))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	if (xmlParse->FindElem(TP_D_SOAP_PRESENTATION_VIDEO))
	{
		Parse_VideoParamEx(xmlParse, adhocConfTemplateParam.presentationVideo);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_MAIN_SITE_URI, TP_D_ELEM_OPTIONAL_FLAG, adhocConfTemplateParam.mainSiteUri))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}

	if (xmlParse->FindElem(TP_D_SOAP_NOTICE))
	{
		xmlParse->IntoElem();
		Parse_ConferenceNoticeEx(xmlParse,adhocConfTemplateParam.notice);
		if ( adhocConfTemplateParam.notice.content == "" && adhocConfTemplateParam.notice.email == "" && adhocConfTemplateParam.notice.telephone == "" )
		{

		}
		else
		{
			xmlParse->OutOfElem();
		}
	}
	

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_MAX_SITES_COUNT, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}
	if(strVal.length())
	{
		adhocConfTemplateParam.maxSitesCount = TP_Tool::String2Int(strVal);
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_STATE, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}
	if(strVal.length())
	{
		adhocConfTemplateParam.state = TP_Tool::String2Int(strVal);
	}

	if(xmlParse->FindElem(TP_D_SOAP_SITES))
	{
		do 
		{
			if(xmlParse->GetElem() == NULL)
			{
				continue;
			}
			if(strncmp(xmlParse->GetElem(),TP_D_SOAP_SITES,sizeof(TP_D_SOAP_SITES)))
			{
				break;
			}
			SiteInfoEx siteInfo;
			xmlParse->IntoElem();
			Parse_SiteInfoEx(xmlParse, siteInfo);
			adhocConfTemplateParam.sites.push_back(siteInfo);
			xmlParse->OutOfElem();


		} while (xmlParse->NextElem());
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_RESERVED_CSD_PORTS, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_RESERVED_CSD_PORTS);
		return resCode;
	}
	if(strVal.length())
	{
		adhocConfTemplateParam.reservedCsdPorts = TP_Tool::String2Int(strVal);
	}

	resCode = TP_SDK_ERR_SUCCESS;
	return resCode;

}

int XMLProcess::Parse_SiteInfoEx(CXml *xmlParse, SiteInfoEx &siteInfo)
{
	std::string strVal;
	int resCode = TP_SDK_ERR_XML_PARSE;

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_NAME, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.name))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_NAME);
		return resCode;
	}
	siteInfo.name = TP_Tool::UTF8ToANSI(siteInfo.name);
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_URI, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.uri))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_URI);
		return resCode;
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_TYPE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_TYPE);
		return resCode;
	}

	if (strVal.length())
	{
		siteInfo.type = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_FROM, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_FROM);
		return resCode;
	}

	if (strVal.length())
	{
		siteInfo.from = TP_Tool::String2Int(strVal);
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_DIALINGMODE, TP_D_ELEM_MUST_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_DIALINGMODE);
		return resCode;
	}

	if (strVal.length())
	{
		siteInfo.dialingMode = TP_Tool::String2Int(strVal);
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_RATE, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.rate))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_RATE);
		return resCode;
	}

	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_VIDEO_FORMAT, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_VIDEO_FORMAT);
		return resCode;
	}

	if (strVal.length())
	{
		siteInfo.videoFormat = TP_Tool::String2Int(strVal);
	}


	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_VIDEO_PROTOCOL, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_VIDEO_PROTOCOL);
		return resCode;
	}

	if (strVal.length())
	{
		siteInfo.videoProtocol = TP_Tool::String2Int(strVal);
	}

	//isLockVideoSource
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_IS_LOCK_VIDEO_SOURCE, TP_D_ELEM_OPTIONAL_FLAG,strVal) )
	{	
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_IS_LOCK_VIDEO_SOURCE);
		return resCode;
	} 
	else
	{
		siteInfo.isLockVideoSource = TP_Tool::String2Int(strVal);
	}

	//participantType
	strVal.clear();
	if ( TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_PARTICIPANT_TYPE, TP_D_ELEM_OPTIONAL_FLAG, strVal) )
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_PARTICIPANT_TYPE);
		return resCode;
	} 
	else
	{
		siteInfo.participantType = TP_Tool::String2Int(strVal);
	}

	//dtmf
	strVal.clear();
	if ( TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_DTMF, TP_D_ELEM_OPTIONAL_FLAG, siteInfo.dtmf) )
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_PARTICIPANT_TYPE);
		return resCode;
	} 

	resCode = TP_SDK_ERR_SUCCESS;
	return resCode;

}

int XMLProcess::Parse_ConferenceNoticeEx(CXml *xmlParse, ConferenceNoticeEx &conferenceNotice)
{
	int resCode = TP_SDK_ERR_XML_PARSE;
	
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SEMAIL, TP_D_ELEM_OPTIONAL_FLAG, conferenceNotice.email))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_SEMAIL);
		return resCode;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_SCONTENT, TP_D_ELEM_OPTIONAL_FLAG, conferenceNotice.content))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_SCONTENT);
		return resCode;
	}

	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_TELEPHONE, TP_D_ELEM_OPTIONAL_FLAG, conferenceNotice.telephone))
	{
		TP_LOG_ERROR("parse xml failed, not found  %s.",TP_D_SOAP_TELEPHONE);
		return resCode;
	}
	resCode = TP_SDK_ERR_SUCCESS;
	return resCode;
}

int XMLProcess::Parse_VideoParamEx(CXml *xmlParse, VideoParamEx &videoParam)
{
	int resCode = TP_SDK_ERR_XML_PARSE;
	xmlParse->IntoElem();
	std::string strVal;
	strVal.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_PROTOCOL, TP_D_ELEM_OPTIONAL_FLAG, strVal))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}
	if(strVal.length())
	{
		videoParam.videoProtocol = TP_Tool::String2Int(strVal);
	}

	std::string strVal1;
	strVal1.clear();
	if (TP_SDK_ERR_SUCCESS != GetXMLElemValue(xmlParse, TP_D_SOAP_FORMAT, TP_D_ELEM_OPTIONAL_FLAG, strVal1))
	{
		TP_LOG_ERROR("parse xml failed, not found  TP_D_SOAP_BROADCAST.");
		return resCode;
	}
	if(strVal1.length())
	{
		videoParam.videoFormat = TP_Tool::String2Int(strVal1);
	}

	if ( strVal == "" && strVal1 == "" )
	{}
	else
	{
		xmlParse->OutOfElem();
	}
	resCode = TP_SDK_ERR_SUCCESS;
	return resCode;

}

int XMLProcess::StringTimeFormatTOSystemtime(const std::string &strTime,SYSTEMTIME& sysTime)
{
	int wYear;
	int wMonth;
	int wDay;
	int wHour;
	int wMinute;
	int wSecond;
	int wMilliseconds;

	//SYSTEMTIME t1;  
	//SYSTEMTIME t2;
	//::GetSystemTime(&t2);
	//::GetLocalTime(&t1);	

	//int hour;
	//int min;

	//min = t1.wMinute - t2.wMinute;
	//hour = t1.wHour - t2.wHour;

	//if (min<0)
	//{
	//	min = 0 - min;
	//	if(hour>0)
	//	{
	//		hour = hour - 1;
	//	}
	//	else
	//	{
	//		hour = hour + 1;
	//	}

	//}

	sscanf_s(strTime.c_str(),"%04d-%02d-%02dT%02d:%02d:%02d.%03d%*s"
		,&wYear,&wMonth,&wDay
		,&wHour,&wMinute,&wSecond
		,&wMilliseconds);

	//wHour += hour;
	//if ( wHour >= 24 )
	//{
	//	wDay += 1;
	//	wHour -= 24;
	//}
	//else if ( wHour < 0 )
	//{
	//	wDay -= 1;
	//	wHour += 24;
	//}

	sysTime.wYear=wYear;
	sysTime.wMonth=wMonth;
	sysTime.wDay=wDay;
	sysTime.wHour=wHour;
	sysTime.wMinute=wMinute;
	sysTime.wSecond=wSecond;
	sysTime.wMilliseconds=wMilliseconds;

	return 0;
}