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
#include "tpProfessionalConfMgr.h"
#include "SDKInterface.h"
#include "TP_XMLProcess.h"
#include "TP_Tool.h"
#include "TP_Native_SOAP_Define.h"
#include "base64.h"
#include "TP_Error.h"

CTPConfMgr::CTPConfMgr()
{
	m_Interface = NULL;
	memset(m_strURL, 0, (TP_D_URI_LEN+1));
}

CTPConfMgr::~CTPConfMgr()
{
	m_Interface = NULL;
}


void CTPConfMgr::SetURL(char *baseURL, char *baseMethod)
{
	sprintf_s(m_strURL,TP_D_URI_LEN,"%s/%s",baseURL,baseMethod);
}

TPSDKResponseEx<ConferenceInfoEx> CTPConfMgr::editScheduledConfEx(const ConferenceInfoEx *conferenceInfo)
{
	TP_DEBUG_TRACE("confId:%s,name:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,rate:%s,duration:%s,sites num:%d"
		,conferenceInfo->confId.c_str(),conferenceInfo->name.c_str(),conferenceInfo->beginTime.wYear,conferenceInfo->beginTime.wMonth,conferenceInfo->beginTime.wDay
		,conferenceInfo->beginTime.wHour,conferenceInfo->beginTime.wMinute,conferenceInfo->beginTime.wSecond,conferenceInfo->beginTime.wMilliseconds
		,conferenceInfo->rate.c_str(),conferenceInfo->duration.c_str(),conferenceInfo->sites.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<ConferenceInfoEx> retVal;
	/*vector<SiteInfoEx>::const_iterator it = conferenceInfo->sites.begin();

	if ((conferenceInfo->confId.length() == 0) || (conferenceInfo->name.length()==0) || (conferenceInfo->rate.length()==0)
	|| (conferenceInfo->duration.length() == 0) || (conferenceInfo->sites.size() == 0)
	||(conferenceInfo->beginTime.wDay == 0&&conferenceInfo->beginTime.wMonth==0&&conferenceInfo->beginTime.wYear==0))
	{
	TP_LOG_ERROR("some parameter is NULL!");
	retVal.resultCode = TP_E_RET_CODE_LOST_PARA;
	return retVal;
	}

	for(;it!=conferenceInfo->sites.end();it++)
	{
	if(it->uri.length() == 0)
	{
	TP_LOG_ERROR("some parameter is NULL!");
	retVal.resultCode = TP_E_RET_CODE_LOST_PARA;
	return retVal;
	}
	}*/

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_EDIT_SCHE_CONFEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());
	
	//memset(&retVal.result, 0, sizeof(ConferenceInfoEx));

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_editScheduledConfEx(conferenceInfo, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] , error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, ret);
		retVal.resultCode = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}
	
	retVal.resultCode = XMLProcess::GetRSPXml_editScheduleConfEx(rspBody.c_str(),&retVal.result);;
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s resultCode:%d fail.",__FUNCTION__,retVal.resultCode);
	}
	return retVal;


}

TPSDKResponseEx<ConferenceInfoEx> CTPConfMgr::scheduleConfEx(const ConferenceInfoEx *conferenceInfo)
{
	TP_DEBUG_TRACE("name:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,rate:%s,duration:%s,sites num:%d"
		,conferenceInfo->name.c_str(),conferenceInfo->beginTime.wYear,conferenceInfo->beginTime.wMonth,conferenceInfo->beginTime.wDay
		,conferenceInfo->beginTime.wHour,conferenceInfo->beginTime.wMinute,conferenceInfo->beginTime.wSecond,conferenceInfo->beginTime.wMilliseconds
		,conferenceInfo->rate.c_str(),conferenceInfo->duration.c_str(),conferenceInfo->sites.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<ConferenceInfoEx> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SCHE_CONFEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	//memset(&retVal.result, 0, sizeof(ConferenceInfoEx));
	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_scheduleConfEx(conferenceInfo, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, ret);
		retVal.resultCode = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_scheduleConfEx(rspBody.c_str(),&retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;


}


TPSDKResponseEx<RecurrenceConfInfoEx> CTPConfMgr::scheduleRecurrenceConferenceEx(const RecurrenceConfInfoEx *recuConfInfo)
{

	TP_DEBUG_TRACE("name:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,rate:%s,duration:%s,sites num:%d,frequency:%d,interval:%d,count:%d"
		,recuConfInfo->base_info.name.c_str(),recuConfInfo->base_info.beginTime.wYear,recuConfInfo->base_info.beginTime.wMonth,recuConfInfo->base_info.beginTime.wDay
		,recuConfInfo->base_info.beginTime.wHour,recuConfInfo->base_info.beginTime.wMinute,recuConfInfo->base_info.beginTime.wSecond,recuConfInfo->base_info.beginTime.wMilliseconds
		,recuConfInfo->base_info.rate.c_str(),recuConfInfo->base_info.duration.c_str(),recuConfInfo->base_info.sites.size(),recuConfInfo->frequency,recuConfInfo->interval,recuConfInfo->count);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<RecurrenceConfInfoEx> retVal;
	/*vector<SiteInfoEx>::const_iterator it = recuConfInfo->base_info.sites.begin();

	if ((recuConfInfo->base_info.name.length()==0) || (recuConfInfo->base_info.rate.length()==0)
	|| (recuConfInfo->base_info.duration.length() == 0) || (recuConfInfo->base_info.sites.size() == 0)
	||(recuConfInfo->base_info.beginTime.wDay == 0&&recuConfInfo->base_info.beginTime.wMonth==0&&recuConfInfo->base_info.beginTime.wYear==0)
	)
	{
	TP_LOG_ERROR("some parameter is NULL!");
	retVal.resultCode = TP_E_RET_CODE_LOST_PARA;
	return retVal;
	}

	for(;it!=recuConfInfo->base_info.sites.end();it++)
	{
	if ((it->name.length() == 0) || (it->uri.length()==0))
	{
	TP_LOG_ERROR("some parameter is NULL!");
	retVal.resultCode = TP_E_RET_CODE_LOST_PARA;
	return retVal;
	}
	}*/

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SCHE_RECURRENCE_CONFEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

//	memset(&retVal.result, 0, sizeof(RecurrenceConfInfoEx));

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_scheduleRecurrenceConferenceEx(recuConfInfo, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, ret);
		retVal.resultCode = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode =  XMLProcess::GetRSPXml_scheduleRecurrenceConferenceEx(rspBody.c_str(),&retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s resultCode:%d fail",__FUNCTION__,retVal.resultCode);
	}
	return retVal;
}

TPSDKResponseEx<RecurrenceConfInfoEx> CTPConfMgr::editRecurrenceConferenceEx(const RecurrenceConfInfoEx *recuConfInfo,const SYSTEMTIME &beginDateTime)
{

	TP_DEBUG_TRACE("confId:%s,name:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,rate:%s,duration:%s,sites num:%d,frequency:%d,interval:%d,count:%d"
		,recuConfInfo->base_info.confId.c_str(),recuConfInfo->base_info.name.c_str(),recuConfInfo->base_info.beginTime.wYear,recuConfInfo->base_info.beginTime.wMonth,recuConfInfo->base_info.beginTime.wDay
		,recuConfInfo->base_info.beginTime.wHour,recuConfInfo->base_info.beginTime.wMinute,recuConfInfo->base_info.beginTime.wSecond,recuConfInfo->base_info.beginTime.wMilliseconds
		,recuConfInfo->base_info.rate.c_str(),recuConfInfo->base_info.duration.c_str(),recuConfInfo->base_info.sites.size(),recuConfInfo->frequency,recuConfInfo->interval,recuConfInfo->count);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<RecurrenceConfInfoEx> retVal;

	/*vector<SiteInfoEx>::const_iterator it = recuConfInfo->base_info.sites.begin();

	if ((recuConfInfo->base_info.name.length()==0) || (recuConfInfo->base_info.rate.length()==0)
		|| (recuConfInfo->base_info.duration.length() == 0) || (recuConfInfo->base_info.sites.size() == 0)
		||(recuConfInfo->base_info.beginTime.wDay == 0&&recuConfInfo->base_info.beginTime.wMonth==0&&recuConfInfo->base_info.beginTime.wYear==0)
		)
	{
		TP_LOG_ERROR("some parameter is NULL!");
		retVal.resultCode = TP_E_RET_CODE_LOST_PARA;
		return retVal;
	}

	for(;it!=recuConfInfo->base_info.sites.end();it++)
	{
		if ((it->name.length() == 0) || (it->uri.length() == 0))
		{
			TP_LOG_ERROR("some parameter is NULL!");
			retVal.resultCode = TP_E_RET_CODE_LOST_PARA;
			return retVal;
		}
	}*/

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_EDIT_RECURRENCE_CONFEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());
	//memset(&retVal.result, 0, sizeof(RecurrenceConfInfoEx));

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_editScheduleRecurrenceConferenceEx(recuConfInfo, beginDateTime, request.strReqData);
	
	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] , error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, ret);
		retVal.resultCode = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_editScheduleRecurrenceConferenceEx(rspBody.c_str(),&retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s resultCode:%d fail.",__FUNCTION__,retVal.resultCode);
	}
	return retVal;
}


TPSDKResponseEx<list<SiteInfoEx>> CTPConfMgr::querySitesEx()
{
	TP_DEBUG_TRACE("");
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<SiteInfoEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_SITESEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_querySitesEx(request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_querySitesEx(rspBody.c_str(),&retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;

}

int CTPConfMgr::prolongScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginDateTime, const std::string &prolongTime)
{
	TP_DEBUG_TRACE("confId:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,prolongTime:%s"
		,confId.c_str(),beginDateTime.wYear,beginDateTime.wMonth,beginDateTime.wDay
		,beginDateTime.wHour,beginDateTime.wMinute,beginDateTime.wSecond,beginDateTime.wMilliseconds,prolongTime.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal=TP_E_RET_CODE_SUCCESS;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_PROLONG_SCHE_CONFEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		return TP_E_RET_CODE_FAIL;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_prolongScheduledConfEx(confId, beginDateTime, prolongTime, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	XMLProcess::GetRSPXml_prolongScheduledConfEx(rspBody.c_str(),retVal);
	//retVal  = TP_E_RET_CODE_SUCCESS;
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}


TPSDKResponseEx<map<std::string, list<FreeBusyStateEx>>> CTPConfMgr::querySiteStatusEx(const list<string>& siteUris, const SYSTEMTIME &beginTime, const std::string &duration)
{
	TP_DEBUG_TRACE("siteUris num:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s"
		,siteUris.size(),beginTime.wYear,beginTime.wMonth,beginTime.wDay
		,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds,duration.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<map<std::string, list<FreeBusyStateEx>>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_SITE_STATUSEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());
	retVal.result.clear();
	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_querySiteStatusEx(siteUris, beginTime, duration, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_querySiteStatusEx(rspBody.c_str(), &retVal.result);
	//retVal  = TP_E_RET_CODE_SUCCESS;
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}


TPSDKResponseEx<list<ConferenceStatusEx>> CTPConfMgr::queryConferencesStatusEx(const list<string> &confIds)
{
	TP_DEBUG_TRACE("confIds num:%d",confIds.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<ConferenceStatusEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_CONF_STATUSEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());
	retVal.result.clear();
	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_queryConferencesStatusEx(confIds, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_queryConferencesStatusEx(rspBody.c_str(), &retVal.result);
	//retVal  = TP_E_RET_CODE_SUCCESS;
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}

	return retVal;
}

TPSDKResponseWithPageEx<list<ConferenceStatusEx>> CTPConfMgr::queryScheduleConferencesEx(const QueryConfigEx &queryConfig)
{
	TP_DEBUG_TRACE("");
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseWithPageEx<list<ConferenceStatusEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SOAP_QUERY_SCHEDULE_CONFERENCESEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());
	retVal.result.clear();
	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_queryScheduleConferencesEx(queryConfig, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_queryScheduleConferencesEx(rspBody.c_str(), &retVal.result, retVal.pagesInfo);
	//retVal  = TP_E_RET_CODE_SUCCESS;
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}

	return retVal;
}

TPSDKResponseEx<list<SiteStatusEx>> CTPConfMgr::queryConfSitesStatusEx(const std::string &confId, const list<std::string> &siteUris)
{
	TP_DEBUG_TRACE("confId:%s,siteUris num:%d",confId.c_str(),siteUris.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<SiteStatusEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_CONF_SITES_STATUSEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());
	retVal.result.clear();
	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_queryConfSitesStatusEx(confId, siteUris, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}
	
	retVal.resultCode = XMLProcess::GetRSPXml_queryConfSitesStatusEx(rspBody.c_str(), &retVal.result);
	
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}


TPSDKResponseEx<map<string, list<FreeBusyStateEx>>>  CTPConfMgr::synchSiteStatusEx(const list<string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration)
{
	TP_DEBUG_TRACE("siteUris num:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s"
		,siteUris.size(),beginTime.wYear,beginTime.wMonth,beginTime.wDay
		,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds,duration.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<map<string, list<FreeBusyStateEx>>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SYNC_SITE_STATUSEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());
	retVal.result.clear();
	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_synchSiteStatusEx(siteUris, beginTime, duration, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode =XMLProcess::GetRSPXml_synchSiteStatusEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<list<SiteAccessInfoEx>> CTPConfMgr::addSiteToConfEx(const std::string &confId, const SiteInfoEx &siteInfo, const SYSTEMTIME &beginTime)
{

	TP_DEBUG_TRACE("confId:%s,siteInfo.name:%s,siteInfo.uri:%s,siteInfo.type:%d,siteInfo.dialingMode:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d"
		,confId.c_str(),siteInfo.name.c_str(),siteInfo.uri.c_str(),siteInfo.type,siteInfo.dialingMode
		,beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<SiteAccessInfoEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_ADD_SITE_TO_CONFEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_addSiteToConfEx(confId, siteInfo, beginTime, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_addSiteToConfEx(rspBody.c_str(), &retVal.result);
	//retVal  = TP_E_RET_CODE_SUCCESS;
	
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;

}


int  CTPConfMgr::delSiteFromConfEx(const std::string &confId, const std::string &siteUri, const SYSTEMTIME &beginTime)
{
	TP_DEBUG_TRACE("confId:%s,siteUri:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d"
		,confId.c_str(),siteUri.c_str(),beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_DEL_SITE_FROM_CONFEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		return TP_E_RET_CODE_FAIL;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_delSiteFromConfEx(confId, siteUri, beginTime, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_DELSITEFROMCONFEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}


int CTPConfMgr::connectSitesEx(const std::string &confId, const list<std::string> &siteUris)
{
	TP_DEBUG_TRACE("confId:%s,siteUris num:%d",confId.c_str(),siteUris.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_CONNECT_SITESEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		return TP_E_RET_CODE_FAIL;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_connectSitesEx(confId, siteUris, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_CONNECTSITEEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

int CTPConfMgr::disconnectSitesEx(const std::string &confId, const list<std::string> &siteUris)
{
	TP_DEBUG_TRACE("confId:%s,siteUris num:%d",confId.c_str(),siteUris.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_DISCONNECT_SITESEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		return TP_E_RET_CODE_FAIL;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_disconnectSitesEx(confId, siteUris, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_DISCONNECTSITEEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

int CTPConfMgr::delScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginTime)
{
	TP_DEBUG_TRACE("confId:%s,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d"
		,confId.c_str(),beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_DEL_SCHE_CONFEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		return TP_E_RET_CODE_FAIL;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_delScheduledConfEx(confId, beginTime, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_DELSCHEDULECONFEX);
	
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;

}

TPSDKResponseEx<QueryMultiPointCDRExResponse> CTPConfMgr::queryMultiPointCDREx(const MultiPointCDRQueryConfigEx &queryConfig)
{
	TP_DEBUG_TRACE("beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s"
		,queryConfig.beginTime.wYear,queryConfig.beginTime.wMonth,queryConfig.beginTime.wDay,queryConfig.beginTime.wHour,queryConfig.beginTime.wMinute,queryConfig.beginTime.wSecond,queryConfig.beginTime.wMilliseconds
		,queryConfig.duration.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<QueryMultiPointCDRExResponse> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_QUERY_MULTI_POINT_CDREX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_queryMultiPointCDREx(queryConfig, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_queryMultiPointCDREx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<QueryPointToPointCDRExResponse> CTPConfMgr::queryPointToPointCDREx(const PointToPointCDRQueryConfigEx &queryConfig)
{
	TP_DEBUG_TRACE("beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s"
		,queryConfig.beginTime.wYear,queryConfig.beginTime.wMonth,queryConfig.beginTime.wDay,queryConfig.beginTime.wHour,queryConfig.beginTime.wMinute,queryConfig.beginTime.wSecond,queryConfig.beginTime.wMilliseconds
		,queryConfig.duration.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<QueryPointToPointCDRExResponse> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_QUERY_POINTTOPOINT_CDREX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_queryPointToPointCDREx(queryConfig, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_queryPointToPointCDREx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}
TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> CTPConfMgr::queryAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration)
{
	TP_DEBUG_TRACE("confAccessCodes num:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s"
		,confAccessCodes.size(),beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds,duration.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_QUERY_ADHOC_CONF_FREE_BUSY);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_queryAdhocConfFreeBusyEx(confAccessCodes,beginTime,duration,request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_queryAdhocConfFreeBusyEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> CTPConfMgr::synchAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration)
{
	TP_DEBUG_TRACE("confAccessCodes num:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s"
		,confAccessCodes.size(),beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds,duration.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_SYNC_ADHOC_CONF_FREE_BUSY);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_synchAdhocConfFreeBusyEx(confAccessCodes,beginTime,duration,request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_synchAdhocConfFreeBusyEx(rspBody.c_str(), &retVal.result);
	
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<QueryAdhocConferenceExResponse> CTPConfMgr::queryAdhocConferencesEx(const QueryConfigEx &queryConfig)
{
	TP_DEBUG_TRACE("");
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<QueryAdhocConferenceExResponse> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_QUERY_ADHOC_CONFERENCESEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_queryAdhocConferencesEx(queryConfig,request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_queryAdhocConferencesEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}


TPSDKResponseEx<list<SiteMCUEx>> CTPConfMgr::queryConfSiteMCUEx(const std::string &confId, const list<std::string>& siteUris, const SYSTEMTIME &beginTime)
{
	TP_DEBUG_TRACE("confId:%s,siteUris num:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d"
		,confId.c_str(),siteUris.size()
		,beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<SiteMCUEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_QUERY_CONF_SITE_MCUEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_queryConfSiteMCUEx(confId, siteUris, beginTime,request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_queryConfSiteMCUEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}


TPSDKResponseEx<GetContinuousPresenceInfoResponseEx> CTPConfMgr::getContinuousPresenceInfoEx(const std::string &confId)
{
	TP_DEBUG_TRACE("confId:%s",confId.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<GetContinuousPresenceInfoResponseEx> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_GET_CONTI_PRESENCE_INFOEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_getContinuousPresenceInfoEx(confId, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_getContinuousPresenceInfoEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<GetContinuousPresenceParamResponseEx> CTPConfMgr::getContinuousPresenceParamEx(const std::string &confId, const std::string &target)
{
	TP_DEBUG_TRACE("confId:%s,target:%s",confId.c_str(),target.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<GetContinuousPresenceParamResponseEx> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_GET_CONTI_PRESENCE_PARAMEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_getContinuousPresenceParamEx(confId, target,request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_getContinuousPresenceParamEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<std::string> CTPConfMgr::addAdhocConfTemplateEx(const std::string &orgId, const AdhocConfTemplateParamEx &adhocConfTemplate)
{
	TP_DEBUG_TRACE("orgId:%s adhocConfTemplateId:%s",orgId.c_str(),adhocConfTemplate.adhocConfTemplateId.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<std::string> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_ADD_ADHOC_CONF_TEMPLATEEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_addAdhocConfTemplateEx(orgId, adhocConfTemplate,request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_addAdhocConfTemplateEx(rspBody.c_str(), retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}


int CTPConfMgr::editAdhocConfTemplateEx(const AdhocConfTemplateParamEx &adhocConfTemplate)
{
	TP_DEBUG_TRACE("adhocConfTemplateId:%s",adhocConfTemplate.adhocConfTemplateId.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_EDIT_ADHOC_CONF_TEMPLATEEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_editAdhocConfTemplateEx(adhocConfTemplate, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal = XMLProcess::GetRSPXml_editAdhocConfTemplateEx(rspBody.c_str());
	if (TP_SDK_ERR_SUCCESS != retVal )
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

int CTPConfMgr::delAdhocConfTemplateEx(const std::string &adhocConfTemplateId)
{
	TP_DEBUG_TRACE("adhocConfTemplateId:%s",adhocConfTemplateId.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_DEL_ADHOC_CONF_TEMPLATEEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_delAdhocConfTemplateEx(adhocConfTemplateId,request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal = XMLProcess::GetRSPXml_delAdhocConfTemplateEx(rspBody.c_str());
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseWithPageEx<list<AdhocConfTemplateParamEx>> CTPConfMgr::queryAdhocConfTemplateListEx(const QueryConfigEx &queryConfig)
{
	TP_DEBUG_TRACE("");
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseWithPageEx<list<AdhocConfTemplateParamEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE, TP_D_QUERY_ADHOC_CONF_TEMPLATE_LISTEX);
	sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	if(!m_Interface)
	{
		TP_LOG_ERROR("m_Interface is NULL!");
		retVal.resultCode = TP_E_RET_CODE_FAIL;
		return retVal;
	}
	sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());

	std::string Cookie = strCookie;
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		retVal.resultCode  = TP_E_RET_CODE_URL_EMPTY;
		return retVal;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_queryAdhocConfTemplateListEx(queryConfig,request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		retVal.resultCode  = TP_E_RET_CODE_SEND_REQUEST_FAILED;
		return retVal;
	}

	retVal.resultCode = XMLProcess::GetRSPXml_queryAdhocConfTemplateListEx(rspBody.c_str(),&retVal.result, retVal.pagesInfo);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}