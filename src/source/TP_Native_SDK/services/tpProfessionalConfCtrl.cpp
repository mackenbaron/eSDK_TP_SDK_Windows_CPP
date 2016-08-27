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
#include "tpProfessionalConfCtrl.h"
#include "SDKInterface.h"
#include "TP_XMLProcess.h"
#include "TP_Tool.h"
#include "TP_Native_SOAP_Define.h"
#include "base64.h"
#include "TP_Error.h"

CTPConfCtrl::CTPConfCtrl()
{
	m_Interface = NULL;
	memset(m_strURL, 0, (TP_D_URI_LEN+1));
}

CTPConfCtrl::~CTPConfCtrl()
{
	m_Interface = NULL;
}


void CTPConfCtrl::SetURL(char *baseURL, char *baseMethod)
{
	sprintf_s(m_strURL,TP_D_URI_LEN,"%s/%s",baseURL,baseMethod);
}

int CTPConfCtrl::setVideoSourceEx(const std::string &confId, const std::string &siteUri, const std::string &videoSourceUri, int isLock)
{
	TP_DEBUG_TRACE("confId:%s siteUri:%s videoSourceUri:%s isLock:%d",confId.c_str(),siteUri.c_str(),videoSourceUri.c_str(),isLock);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_VIDEO_SOURCEEX);
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

	retVal = XMLProcess::SetXml_setVideoSourceEx(confId, siteUri, videoSourceUri, isLock, request.strReqData);
	
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s",__FUNCTION__,request.strReqData.c_str());
		return retVal;
	}


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


	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETVIDEOSOURCEEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::setAudioSwitchEx(const std::string &confId, int switchGate, int isSwitch)
{
	TP_DEBUG_TRACE("confId:%s,switchGate:%d,isSwitch:%d",confId.c_str(),switchGate,isSwitch);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_AUDIO_SWITCHEX);
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

	XMLProcess::SetXml_setAudioSwitchEx(confId, switchGate,isSwitch,request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETAUDIOSWITCHEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}
int CTPConfCtrl::setBroadcastSiteEx(const std::string &confId, const std::string &siteUri, int isBroadcast)
{
	TP_DEBUG_TRACE("confId:%s,siteUri:%s,isBroadcast:%d",confId.c_str(),siteUri.c_str(),isBroadcast);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_BROADCAST_SITEEX);
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

	XMLProcess::SetXml_setBroadcastSiteEx(confId, siteUri, isBroadcast,request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETBROADCASTSITEEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::setBroadcastContinuousPresenceEx(const std::string &confId, int isBroadcast)
{
	TP_DEBUG_TRACE("confId:%s,isBroadcast:%d",confId.c_str(),isBroadcast);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_BROADCAST_CONTINUOUS_PRESENCEEX);
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

	XMLProcess::SetXml_setBroadcastContinuousPresenceEx(confId, isBroadcast, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETBROADCASTCONTINUOUSPRESENCEEX);
	
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	
	return retVal;
}

int CTPConfCtrl::setSitesMuteEx(const std::string &confId, const list<std::string> &siteUris, int isBroadcast)
{
	TP_DEBUG_TRACE("confId:%s,siteUris num:%d,isBroadcast:%d",confId.c_str(),siteUris.size(),isBroadcast);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_SITES_MUTEEX);
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

	XMLProcess::SetXml_setSitesMuteEx(confId, siteUris, isBroadcast, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETSITESMUTEEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::setSitesQuietEx(const std::string &confId, const list<std::string> &siteUris, int isQuiet)
{
	TP_DEBUG_TRACE("confId:%s,siteUris num:%d,isQuiet:%d",confId.c_str(),siteUris.size(),isQuiet);
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_SITES_QUIETEX);
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

	XMLProcess::SetXml_setSitesQuietEx(confId, siteUris, isQuiet, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETSITESQUIETEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::setContinuousPresenceEx(const std::string &confId, const std::string &target, int presenceMode, const list<std::string> &subPics)
{
	TP_DEBUG_TRACE("confId:%s,target:%s,presenceMode:%d,subPics num:%d",confId.c_str(),target.c_str(),presenceMode,subPics.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_CONTINUOUS_PRESENCEEX);
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

	XMLProcess::SetXml_setContinuousPresenceEx(confId, target, presenceMode, subPics, request.strReqData);

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
	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETCONTINUOUSPRESENCEEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::requestConfChairEx(const std::string &confId, const std::string &chairmanUri)
{
	TP_DEBUG_TRACE("confId:%s,chairmanUri:%s",confId.c_str(),chairmanUri.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_REQUEST_CONF_CHAIREX);
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

	XMLProcess::SetXml_requestConfChairEx(confId, chairmanUri, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_REQUESTCONFCHAIREX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::releaseConfChairEx(const std::string &confId)
{
	TP_DEBUG_TRACE("confId:%s",confId.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_RELEASE_CONF_CHAIREX);
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

	XMLProcess::SetXml_releaseConfChairEx(confId, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_RELEASECONFCHAIREX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::setFloorEx(const std::string &confId, const std::string &siteUri)
{
	TP_DEBUG_TRACE("confId:%s,siteUri:%s",confId.c_str(),siteUri.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_FLOOREX);
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

	XMLProcess::SetXml_setFloorEx(confId, siteUri, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETFLOOREX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::setConfSiteVolumeEx(const std::string &confId, const list<SiteVolumeEx> &siteVolumes)
{
	TP_DEBUG_TRACE("confId:%s siteVolumes num:%d",confId.c_str(),siteVolumes.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_SET_CONF_SITE_VOLUMEEX);
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

	XMLProcess::SetXml_setConfSiteVolumeEx(confId, siteVolumes, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_SETCONFSITEVOLUMEEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::displayConfSiteLocalVideoEx(const std::string &confId, const list<std::string> &siteUris)
{
	TP_DEBUG_TRACE("confId:%s,siteUris:%d",confId.c_str(),siteUris.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_DISPLAY_CONF_SITE_LOCAL_VIDEOEX);
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

	XMLProcess::SetXml_displayConfSiteLocalVideoEx(confId, siteUris, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_DISPLAYCONFSITELOCALVIDEOEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::hideConfSiteLocalVideoEx(const std::string &confId, const list<std::string> &siteUris)
{
	TP_DEBUG_TRACE("confId:%s,siteUris:%d",confId.c_str(),siteUris.size());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_HIDE_CONF_SITE_LOCAL_VIDEOEX);
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

	XMLProcess::SetXml_hideConfSiteLocalVideoEx(confId, siteUris, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_HIDECONFSITELOCALVIDEOEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

int CTPConfCtrl::lockPresentationEx(const std::string &confId, const std::string &siteUri)
{
	TP_DEBUG_TRACE("confId:%s,siteUri:%s",confId.c_str(),siteUri.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_LOCK_PRESENTATIONEX);
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

	XMLProcess::SetXml_lockPresentationEx(confId, siteUri, request.strReqData);

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

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_LOCKPRESENTATIONEX);
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}


int CTPConfCtrl::unlockPresentationEx(const std::string &confId)
{
	TP_DEBUG_TRACE("confId:%s",confId.c_str());
	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	int retVal;

	sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_UNLOCK_PRESENTATIONEX);
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

	XMLProcess::SetXml_unlockPresentationEx(confId, request.strReqData);

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

	

	retVal = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_UNLOCKPRESENTATIONEX);
	
	if (TP_SDK_ERR_SUCCESS != retVal)
	{
		TP_LOG_DEBUG("%s request packet:%s\n, response packet:%s",__FUNCTION__,request.strReqData.c_str(),rspBody.c_str());
		return retVal;
	}
	return retVal;
}

