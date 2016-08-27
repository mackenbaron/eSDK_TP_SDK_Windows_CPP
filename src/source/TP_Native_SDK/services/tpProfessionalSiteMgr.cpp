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
#include "tpProfessionalSiteMgr.h"
#include "SDKInterface.h"
#include "TP_XMLProcess.h"
#include "TP_Tool.h"
#include "TP_Native_SOAP_Define.h"
#include "base64.h"
#include "TP_Error.h"

CTPSiteMgr::CTPSiteMgr()
{
	m_Interface = NULL;
	memset(m_strURL, 0, (TP_D_URI_LEN+1));
}

CTPSiteMgr::~CTPSiteMgr()
{
	m_Interface = NULL;
}


void CTPSiteMgr::SetURL(char *baseURL, char *baseMethod)
{
	sprintf_s(m_strURL,TP_D_URI_LEN,"%s/%s",baseURL,baseMethod);
}


int CTPSiteMgr::addSiteInfoEx(const std::string &orgId, const TerminalInfoEx &siteInfo)
{
	TP_DEBUG_TRACE("orgId:%s,siteInfo name:%s,siteInfo uri:%s,siteInfo type:%d",orgId.c_str(),siteInfo.name.c_str(),siteInfo.uri.c_str(),siteInfo.type);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_ADD_SITE_INFOEX);
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

	XMLProcess::SetXml_addSiteInfoEx(orgId, siteInfo, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_ADDSITEINFOEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}
int CTPSiteMgr::editSiteInfoEx(const TerminalInfoEx &siteInfo)
{
	TP_DEBUG_TRACE("siteInfo name:%s,siteInfo uri:%s,siteInfo type:%d",siteInfo.name.c_str(),siteInfo.uri.c_str(),siteInfo.type);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_EDIT_SITE_INFOEX);
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

	XMLProcess::SetXml_editSiteInfoEx(siteInfo, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_EDITSITEINFOEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}
int CTPSiteMgr::deleteSiteInfoEx(const list<std::string> &siteUris)
{
	TP_DEBUG_TRACE("siteUris num:%d",siteUris.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_DELETE_SITE_INFOEX);
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

	XMLProcess::SetXml_deleteSiteInfoEx(siteUris, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_DELETESITEINFOEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}
TPSDKResponseEx<QuerySitesInfoExResponse> CTPSiteMgr::querySitesInfoEx(const QueryConfigEx &queryConfig)
{
	TP_DEBUG_TRACE("");
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<QuerySitesInfoExResponse> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_SITE_INFOEX);
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

	XMLProcess::SetXml_querySitesInfoEx(queryConfig, request.strReqData);

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

	retVal.resultCode = XMLProcess::GetXml_querySitesInfoEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}


TPSDKResponseEx<int> CTPSiteMgr::isConnectAuxSourceEx(const std::string &siteUri)
{
	TP_DEBUG_TRACE("siteUri:%s",siteUri.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<int> retVal;
	retVal.result = 0;
	retVal.resultCode = TP_E_RET_CODE_SUCCESS;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_IS_CONNECT_AUX_SOURCEEX);
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

	XMLProcess::SetXml_isConnectAuxSourceEx(siteUri, request.strReqData);

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

	retVal.resultCode = XMLProcess::GetXml_isConnectAuxSourceEx(rspBody.c_str(), retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<int> CTPSiteMgr::isSendAuxStreamEx(const std::string &siteUri)
{
	TP_DEBUG_TRACE("siteUri:%s",siteUri.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<int> retVal;
	retVal.result = 0;
	retVal.resultCode = TP_E_RET_CODE_SUCCESS;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_IS_SEND_AUX_STREAMEX);
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

	XMLProcess::SetXml_isSendAuxStreamEx(siteUri, request.strReqData);

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

	retVal.resultCode = XMLProcess::GetXml_isSendAuxStreamEx(rspBody.c_str(), retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<int> CTPSiteMgr::isReceiveRemAuxStrmEx(const std::string &siteUri)
{
	TP_DEBUG_TRACE("siteUri:%s",siteUri.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<int> retVal;
	retVal.result = 0;
	retVal.resultCode = TP_E_RET_CODE_SUCCESS;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_IS_RECEIVE_REM_AUX_STRMEX);
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

	XMLProcess::SetXml_isReceiveRemAuxStrmEx(siteUri, request.strReqData);

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

	retVal.resultCode = XMLProcess::GetXml_isReceiveRemAuxStrmEx(rspBody.c_str(), retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

int CTPSiteMgr::setAuxStreamEx(const std::string &siteUri, int controlCode)
{
	TP_DEBUG_TRACE("siteUri:%s,controlCode:%d",siteUri.c_str(),controlCode);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_AUX_STREAMEX);
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

	XMLProcess::SetXml_setAuxStreamEx(siteUri, controlCode,request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETAUXSTREAMEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<list<AuxStreamInfoEx>> CTPSiteMgr::queryAuxStreamSourcesEx(const std::string &siteUri)
{
	TP_DEBUG_TRACE("siteUri:%s",siteUri.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<AuxStreamInfoEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_AUX_STREAM_SOURCESEX);
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

	XMLProcess::SetXml_queryAuxStreamSourcesEx(siteUri, request.strReqData);

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

	retVal.resultCode = XMLProcess::GetXml_queryAuxStreamSourcesEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<list<VideoSourcesInfoEx>> CTPSiteMgr::queryVideoOutSrcStateEx(const std::string &siteUri)
{
	TP_DEBUG_TRACE("siteUri:%s",siteUri.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<VideoSourcesInfoEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_VIDEO_OUT_SRC_STATEEX);
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

	XMLProcess::SetXml_queryVideoOutSrcStateEx(siteUri, request.strReqData);

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

	retVal.resultCode = XMLProcess::GetXml_queryVideoOutSrcStateEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

int CTPSiteMgr::ctrlCameraEx(const std::string &siteUri, const CameraControlEx &cameraControl)
{
	TP_DEBUG_TRACE("siteUri:%s,camState:%d,camAction:%d,camPos:%d,camSrc:%d"
		,siteUri.c_str(),cameraControl.camState,cameraControl.camAction,cameraControl.camPos,cameraControl.camSrc);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_CTRL_CAMERAEX);
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

	XMLProcess::SetXml_ctrlCameraEx(siteUri, cameraControl,request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_CTRLCAMERAEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

int CTPSiteMgr::setMainAuxStreamSourcesEx(const std::string &siteUri, const list<int> &localMainSrcs, int localAuxSrc)
{
	TP_DEBUG_TRACE("siteUri:%s,localMainSrcs number:%d,localAuxSrc:%d"
		,siteUri.c_str(),localMainSrcs.size(),localAuxSrc);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_MAIN_AUX_STREAM_SOURCESEX);
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

	XMLProcess::SetXml_setMainAuxStreamSourcesEx(siteUri, localMainSrcs,localAuxSrc,request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETMAINAUXSTREAMSOURCESEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<list<AuxStreamInfoEx>> CTPSiteMgr::queryMainStreamSourcesEx(const std::string &siteUri)
{
	TP_DEBUG_TRACE("siteUri:%s",siteUri.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<list<AuxStreamInfoEx>> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_MAIN_STREAM_SOURCESEX);
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

	XMLProcess::SetXml_queryMainStreamSourcesEx(siteUri, request.strReqData);

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

	retVal.resultCode = XMLProcess::GetXml_queryMainStreamSourcesEx(rspBody.c_str(), &retVal.result);
	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

int CTPSiteMgr::setVideoOutSrcEx(const std::string &siteUri, int hdOut, int videoSrc)
{
	TP_DEBUG_TRACE("siteUri:%s,hdOut:%d,videoSrc:%d",siteUri.c_str(),hdOut,videoSrc);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_VIDEO_OUT_SRCEX);
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

	XMLProcess::SetXml_setVideoOutSrcEx(siteUri, hdOut,videoSrc,request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETVIDEOOUTSRCEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}

TPSDKResponseEx<SiteDeviceVersionInfoEx> CTPSiteMgr::querySiteVersionInfoEx(const std::string &siteUri)
{
	TP_DEBUG_TRACE("siteUri:%s",siteUri.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	TPSDKResponseEx<SiteDeviceVersionInfoEx> retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_QUERY_SITE_VERSION_INFOEX);
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

	XMLProcess::SetXml_querySiteVersionInfoEx(siteUri, request.strReqData);

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

	retVal.resultCode = XMLProcess::GetXml_querySiteVersionInfoEx(rspBody.c_str(), &retVal.result);

	if (TP_SDK_ERR_SUCCESS != retVal.resultCode)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
	}
	return retVal;
}