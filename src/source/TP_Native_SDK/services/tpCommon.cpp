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
#include "tpCommon.h"
#include "SDKInterface.h"
#include "TP_XMLProcess.h"
#include "TP_Tool.h"
#include "TP_Native_SOAP_Define.h"
#include "base64.h"

CTPCommon::CTPCommon()
{
	m_Interface = NULL;
	memset(m_strURL, 0, (TP_D_URI_LEN+1));
}

CTPCommon::~CTPCommon()
{
	m_Interface = NULL;
}

void CTPCommon::SetURL(char *baseURL, char *baseMethod)
{
	(void)sprintf_s(m_strURL,TP_D_URI_LEN,"%s/%s",baseURL,baseMethod);
}

int CTPCommon::LoginRequest(std::string username, std::string &randomSequence)
{
	TP_DEBUG_TRACE("username:%s",username.c_str());

	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	
	(void)sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_LOGINREQUEST);
	(void)sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		return TP_E_RET_CODE_URL_EMPTY;
	}

	//设置请求参数
	REQUEST_OPTIONS request;
	//request.strUrl = "https://login.vancl.com/Login/Login.aspx";
	//request.strUrl = "https://example.com/";
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	//request.uiReqMode = MODE_GET;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(strcontent_type);

	XMLProcess::SetXml_LoginRequest(username, request.strReqData);


	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, ret);
		return TP_E_RET_CODE_SEND_REQUEST_FAILED;
	}

	int iPosStart = rspHeader.find(TP_D_COOKIEKEY);

	if (-1 == iPosStart)
	{
		TP_LOG_ERROR("Can not find %s in HTTP Header:%s",TP_D_COOKIEKEY,rspHeader.c_str());
		return TP_E_RET_CODE_SEND_REQUEST_FAILED;
	}

	int len = strlen(TP_D_COOKIEKEY);
	int iPosEnd = rspHeader.find(';',iPosStart);

	m_sessionId = rspHeader.substr(iPosStart+len, iPosEnd-iPosStart-len).c_str(); 

	XMLProcess::GetRSPXml_LoginRequest(rspBody.c_str(),randomSequence);
	return TP_E_RET_CODE_SUCCESS;

}

int CTPCommon::Authenticate(const std::string sessionID, const std::string randomSequence, const std::string password)
{
	TP_DEBUG_TRACE("");

	//获取请求地址
	std::string url = m_strURL;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};
	//sprintf_s(strCookie,TP_D_COOKIE_LEN,"Cookie: JSESSIONID=%s; JSESSIONID=%s",sessionID.c_str(),sessionID.c_str());
	//sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());
	(void)sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,sessionID.c_str(),TP_D_HTTP_HEADER_JSESSIONID,sessionID.c_str());
	std::string Cookie = strCookie;
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	(void)sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	std::string soapaction ;
	(void)sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_AUTHENTICATE);
	soapaction = strsoapaction;

	std::string content_type;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		return TP_E_RET_CODE_URL_EMPTY;
	}

	REQUEST_OPTIONS request;
	request.strUrl = url;
	request.uiTimeOut = TIMEOUT_30S;
	request.uiVersion = VERSION_1_1;
	request.uiReqMode = MODE_POST;
	request.ReqHeader.push_back(soapaction);
	request.ReqHeader.push_back(Cookie);
	request.ReqHeader.push_back(content_type);
	
	char output[512]={0};
	unsigned int outputlen;
	unsigned char encryptValue[512]={0};
	
	int randomSequenceLen=0;
	if(randomSequence.length()>0 && (randomSequenceLen = randomSequence.length()))
	{
	}

	TP_Tool::EncryptPassword((unsigned char *)randomSequence.c_str(), randomSequenceLen, password,encryptValue,512);
	if(base64_encode((unsigned char *)output,&outputlen,encryptValue,32)==outputlen){}else{}
	std::string enpas = output;
	(void)XMLProcess::SetXml_Authenticate(output, request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, ret);
		return TP_E_RET_CODE_SEND_REQUEST_FAILED;
	}


	int iPosStart = rspHeader.find(TP_D_COOKIEKEY);
	int len = strlen(TP_D_COOKIEKEY);
	int iPosEnd = rspHeader.find(';',iPosStart);

	m_sessionId = rspHeader.substr(iPosStart+len, iPosEnd-iPosStart-len).c_str(); 

	//解析响应
	std::string data, paras;

	ret = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_AUTH_ELEM);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Invalid response");
		return ret;
	}

	return RET_OK ;
}

int CTPCommon::Login(const std::string &userName, const std::string &password)
{
	TP_DEBUG_TRACE("username:%s",userName.c_str());

	//保存请求地址
	//获取请求地址
	std::string url = m_strURL;
	std::string xmlStr;
	//request.strReqData = XMLProcess::SetXml_LoginRequest(userName, xmlStr);
	//请求Session
	std::string sessionId;
	std::string randomSequence;
	int ret =  LoginRequest(userName,randomSequence);
	if (TP_E_RET_CODE_SUCCESS != ret)
	{
		TP_LOG_ERROR("Request session id failed, error code[%d]", ret);
		return ret;
	}

	//请求认证
	ret = Authenticate(m_sessionId, randomSequence, password);
	if (TP_E_RET_CODE_SUCCESS != ret)
	{
		TP_LOG_ERROR("Request certification failed, error code[%d]", ret);
		return ret;
	}

	m_Interface->SetCookie(m_sessionId);
	//启动保活
	//ret = m_Interface->StartKeepAlive(); 2015/1/8 SDK调用者通过keepAlive接口自行控制保活

	return ret;
}


int CTPCommon::Logout()
{
	TP_DEBUG_TRACE("");

	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};


	if(!m_Interface || (strlen(m_Interface->GetCookie().c_str()) == 0))
	{
		if(!m_Interface)
		{
			TP_LOG_ERROR("m_Interface is NULL!");
		}
		else
		{
			TP_LOG_ERROR("Cookie:%s, Please login first!",m_Interface->GetCookie().c_str());
		}
		
		return TP_E_RET_CODE_FAIL;
	}

	(void)sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());
	std::string Cookie = strCookie;

	(void)sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_LOGOUT);
	(void)sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		return TP_E_RET_CODE_URL_EMPTY;
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

	XMLProcess::SetXml_Logout(request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		return TP_E_RET_CODE_SEND_REQUEST_FAILED;
	}

	ret = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_LOGOUT);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Invalid response,request.strReqData:%s rspBody:%s",request.strReqData.c_str(),rspBody.c_str());
		return ret;
	}
	return RET_OK;
}




int CTPCommon::KeepAlive()
{
	TP_DEBUG_TRACE("");

	//获取请求地址
	std::string url = m_strURL;
	std::string soapaction ;
	std::string content_type;
	char strsoapaction[TP_D_SOAPACTION_LEN+1]={0};
	char strcontent_type[TP_D_CONTENTTYPE_LEN+1]={0};
	char strCookie[TP_D_COOKIE_LEN+1]={0};


	if(!m_Interface || (strlen(m_Interface->GetCookie().c_str()) == 0))
	{
		if(!m_Interface)
		{
			TP_LOG_ERROR("m_Interface is NULL!");
		}
		else
		{
			TP_LOG_ERROR("Cookie:%s, Please login first!",m_Interface->GetCookie().c_str());
		}

		return TP_E_RET_CODE_FAIL;
	}

	(void)sprintf_s(strCookie,TP_D_COOKIE_LEN,"%s=%s; %s=%s",TP_D_HTTP_HEADER_COOKIE,m_Interface->GetCookie().c_str(),TP_D_HTTP_HEADER_JSESSIONID,m_Interface->GetCookie().c_str());
	std::string Cookie = strCookie;

	(void)sprintf_s(strsoapaction,TP_D_SOAPACTION_LEN,"%s:\"%s%s\"",TP_D_HTTP_HEADER_SOAPACTION,TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE,TP_D_KEEPALIVE);
	(void)sprintf_s(strcontent_type, TP_D_CONTENTTYPE_LEN, "%s",TP_D_HTTP_HEADER_CONTENT_TYPE);
	soapaction = strsoapaction;
	content_type = strcontent_type;
	if (url.empty())
	{
		TP_LOG_ERROR("Get server url failed, please login first");
		return TP_E_RET_CODE_URL_EMPTY;
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

	XMLProcess::SetXml_KeepAlive(request.strReqData);

	//发送请求
	std::string rspBody;
	std::string rspHeader;
	int ret = eSDK_HTTP_SendRequest(request, rspBody, rspHeader);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Send http request failed, url[%s] time out[%d] http version[%d] mode[%d] data[%s], error code[%d]", 
			request.strUrl.c_str(), request.uiTimeOut, request.uiVersion, request.uiReqMode, request.strReqData.c_str(), ret);
		return TP_E_RET_CODE_SEND_REQUEST_FAILED;
	}

	ret = XMLProcess::GetRSPXML_ResultCode(rspBody.c_str(), TP_D_SOAP_RSP_KEEPALIVE);
	if (RET_OK != ret)
	{
		TP_LOG_ERROR("Invalid response,ReqData:%s rspBody:%s", request.strReqData.c_str(),rspBody.c_str());
		return ret;
	}
	return RET_OK;
}