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
#include "tpProfessionalMCUMgr.h"
#include "SDKInterface.h"
#include "TP_XMLProcess.h"
#include "TP_Tool.h"
#include "TP_Native_SOAP_Define.h"
#include "base64.h"
#include "TP_Error.h"

CTPMCUMgr::CTPMCUMgr()
{
	m_Interface = NULL;
	memset(m_strURL, 0, (TP_D_URI_LEN+1));
}

CTPMCUMgr::~CTPMCUMgr()
{
	m_Interface = NULL;
}


void CTPMCUMgr::SetURL(char *baseURL, char *baseMethod)
{
	sprintf_s(m_strURL,TP_D_URI_LEN,"%s/%s",baseURL,baseMethod);
}

TPSDKResponseEx<QueryMCUInfoExResponse> CTPMCUMgr::queryMCUInfoEx(const QueryConfigEx &queryConfig)
{
	TP_DEBUG_TRACE("");
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<QueryMCUInfoExResponse> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_MCU_INFOEX);
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

	XMLProcess::SetXml_queryMCUInfoEx(queryConfig, request.strReqData);

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

	retVal.resultCode = XMLProcess::GetXml_queryMCUInfoEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<list<MCUResourceEx>>  CTPMCUMgr::queryMCUFutureResourceEx(const list<int> &mcus, const SYSTEMTIME &beginTime, const std::string &duration)
{
	TP_DEBUG_TRACE("mcus num:%d,beginTime:%04d-%02d-%02dT%02d:%02d:%02d.%03d,duration:%s"
		,mcus.size()
		,beginTime.wYear,beginTime.wMonth,beginTime.wDay,beginTime.wHour,beginTime.wMinute,beginTime.wSecond,beginTime.wMilliseconds
		,duration.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<MCUResourceEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_MCU_FUTURE_RESOURCEEX);
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

	XMLProcess::SetXml_queryMCUFutureResourceEx(mcus,beginTime, duration, request.strReqData);

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

	retVal.resultCode = XMLProcess::GetXml_queryMCUFutureResourceEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}