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

#include "StdAfx.h"
#include "SDKInterface.h"
#include "TP_Error.h"
#include <stdio.h>
#include <string>
#include <map>
#include "TP_XMLProcess.h"

#define DLL_NAME		"TP_Native_SDK.dll"
#define INI_FILE		"eSDKClientLogCfg.ini"
#define LOG_NAME		"log"

CSDKInterface::CSDKInterface(void)
{
	std::string dllPath = GetDllPath(DLL_NAME);
	std::string iniFile = dllPath + INI_FILE;
	std::string logPath = dllPath + LOG_NAME;
	unsigned int logLevel[LOG_CATEGORY] = {INVALID_LOG_LEVEL, INVALID_LOG_LEVEL, INVALID_LOG_LEVEL};
	int ret = 0;
	if (GetConfigInfo(dllPath)!=TP_SDK_ERR_SUCCESS){}else{}
	
	ret = LogInit(PRODUCT_NAME, iniFile.c_str(), logLevel, logPath.c_str());
	if(TP_SDK_ERR_SUCCESS == ret)
	{
		TP_LOG_INFO("SDK Compile Time:%s %s",__DATE__,__TIME__);
	}

	m_TPCommon.SetURL(m_configInfo.cURL, m_configInfo.cCommonInterface);
	m_TPCommon.SetInterfaceObj(this);
	m_TPConfMgr.SetURL(m_configInfo.cURL, m_configInfo.cConfMgrInterface);
	m_TPConfMgr.SetInterfaceObj(this);
	m_TPConfCtrl.SetURL(m_configInfo.cURL, m_configInfo.cConfCtrlInterface);
	m_TPConfCtrl.SetInterfaceObj(this);

	m_TPSiteMgr.SetURL(m_configInfo.cURL, m_configInfo.cSiteMgrInterface);
	m_TPSiteMgr.SetInterfaceObj(this);

	m_TPMCUMgr.SetURL(m_configInfo.cURL, m_configInfo.cMCUMgrInterface);
	m_TPMCUMgr.SetInterfaceObj(this);


	m_TPOrgaMgr.SetURL(m_configInfo.cURL, m_configInfo.cORGAMgrInterface);
	m_TPOrgaMgr.SetInterfaceObj(this);

	m_TPTermConfMgr.SetURL(m_configInfo.cURL, m_configInfo.cTermConfCtrInterface);
	m_TPTermConfMgr.SetInterfaceObj(this);

	m_TPScribMgr.SetURL(m_configInfo.cURL, m_configInfo.cSubscribeServiceMgrInterface);
	m_TPScribMgr.SetInterfaceObj(this);
	memset(&m_configInfo,0,sizeof(TP_S_CONFIG_INFO));

#if 0
	m_SubscriptionMgr.SetInterfaceObj(this);
	m_AddrBookMgr.SetInterfaceObj(this);
	m_CallMgr.SetInterfaceObj(this);
	m_ConfMgr.SetInterfaceObj(this);
	m_MediaCtrlMgr.SetInterfaceObj(this);
#endif
}


CSDKInterface::~CSDKInterface(void)
{
	LogFini(PRODUCT_NAME);
}


std::string CSDKInterface::GetDllPath(const std::string &dllName)
{
	HMODULE hModule = GetModuleHandleA(dllName.c_str());
	if(NULL == hModule)
	{
		return "";
	}
	char dllpath[MAX_PATH];
	memset(dllpath, 0, sizeof(dllpath));
	::GetModuleFileNameA(hModule, dllpath, MAX_PATH);
	std::string strPath(dllpath);
	strPath = strPath.substr(0, strPath.rfind("\\")+1);
	return strPath;
}

int CSDKInterface::GetConfigInfo(const std::string &strPath)
{
	FILE *fp = NULL;
	char *pBuf = NULL;
	int len = 0;

	std::map<std::string, std::string> MapKeyValue;
	std::map<std::string, std::string>::iterator iter;
	std::string configPath = strPath + "/esdk_tp_native_professional_cs.dll.config";
	errno_t err = fopen_s(&fp,configPath.c_str(),"r");
	
	if (err)
	{
		if (fp!=NULL)
		{
			(void)fclose(fp);
			fp = NULL;
			DealPointUnusedWarn(fp)
		}
		TP_LOG_ERROR("can not open file: %s",configPath.c_str());
		return TP_SDK_ERR_NULL_POINTER;
	}
	(void)fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	if (len<0)
	{
		len=0;
	}
	(void)fseek(fp, 0, SEEK_SET);
	pBuf = (char *)malloc(len+1);
	if (pBuf==NULL)
	{
		(void)fclose(fp);
		fp = NULL;
		DealPointUnusedWarn(fp)
		return TP_SDK_ERR_NULL_POINTER;
	}
	memset(pBuf, 0, (len+1));
	(void)fread(pBuf,1,len,fp);
	(void)fclose(fp);
	fp = NULL;
	DealPointUnusedWarn(fp)

	int ret = XMLProcess::GetXml_Config(pBuf, &MapKeyValue);
	free(pBuf);
	pBuf = NULL;
	DealPointUnusedWarn(pBuf)
	if (ret!=TP_SDK_ERR_SUCCESS)
	{
		return ret;
	}
	//iter = MapKeyValue.find(TP_CONFIG_URL);
	iter = MapKeyValue.find(TP_CONFIG_URL);
	
	if(MapKeyValue.end() == iter)
	{
		TP_LOG_ERROR("can not find %s in config file",TP_CONFIG_URL);
	}
	else
	{
		if(strncpy_s(m_configInfo.cURL, iter->second.c_str(), TP_D_URI_LEN)!=0){}else{}

		MapKeyValue.erase(iter);
	}
	
	iter = MapKeyValue.find(TP_CONFIG_COMMON);
	if(MapKeyValue.end() == iter)
	{
		TP_LOG_ERROR("can not find %s in config file",TP_CONFIG_COMMON);
	}
	else
	{
		if(strncpy_s(m_configInfo.cCommonInterface, iter->second.c_str(), TP_D_INTERFACE_LEN)!=0){}else{}

		MapKeyValue.erase(iter);
	}

	iter = MapKeyValue.find(TP_CONFIG_CONFCTRL);
	if(MapKeyValue.end() == iter)
	{
		TP_LOG_ERROR("can not find %s in config file",TP_CONFIG_CONFCTRL);
	}
	else
	{
		if(strncpy_s(m_configInfo.cConfCtrlInterface, iter->second.c_str(), TP_D_INTERFACE_LEN)!=0){}else{}

		MapKeyValue.erase(iter);
	}

	iter = MapKeyValue.find(TP_CONFIG_CONFMGR);
	if(MapKeyValue.end() == iter)
	{
		TP_LOG_ERROR("can not find %s in config file",TP_CONFIG_CONFMGR);
	}
	else
	{
		if(strncpy_s(m_configInfo.cConfMgrInterface, iter->second.c_str(), TP_D_INTERFACE_LEN)!=0){}else{}

		MapKeyValue.erase(iter);
	}

	iter = MapKeyValue.find(TP_CONFIG_SITEMGR);
	if(MapKeyValue.end() == iter)
	{
		TP_LOG_ERROR("can not find %s in config file",TP_CONFIG_SITEMGR);
	}
	else
	{
		if(strncpy_s(m_configInfo.cSiteMgrInterface, iter->second.c_str(), TP_D_INTERFACE_LEN)!=0){}else{}

		MapKeyValue.erase(iter);
	}

	iter = MapKeyValue.find(TP_CONFIG_MCUMGR);
	if(MapKeyValue.end() == iter)
	{
		TP_LOG_ERROR("can not find %s in config file",TP_CONFIG_MCUMGR);
	}
	else
	{
		if(strncpy_s(m_configInfo.cMCUMgrInterface, iter->second.c_str(), TP_D_INTERFACE_LEN)!=0){}else{}

		MapKeyValue.erase(iter);
	}

	iter = MapKeyValue.find(TP_CONFIG_ORGAMGR);
	if(MapKeyValue.end() == iter)
	{
		TP_LOG_ERROR("can not find %s in config file",TP_CONFIG_ORGAMGR);
	}
	else
	{
		if(strncpy_s(m_configInfo.cORGAMgrInterface, iter->second.c_str(), TP_D_INTERFACE_LEN)!=0){}else{}

		MapKeyValue.erase(iter);
	}

	iter = MapKeyValue.find(TP_CONFIG_TERM_CONFCTR);
	if(MapKeyValue.end() == iter)
	{
		TP_LOG_ERROR("can not find %s in config file",TP_CONFIG_TERM_CONFCTR);
	}
	else
	{
		if(strncpy_s(m_configInfo.cTermConfCtrInterface, iter->second.c_str(), TP_D_INTERFACE_LEN)!=0){}else{}

		MapKeyValue.erase(iter);
	}

	iter = MapKeyValue.find(TP_CONFIG_PLATFORMKEYMGR);
	if(MapKeyValue.end() == iter)
	{
		TP_LOG_ERROR("can not find %s in config file",TP_CONFIG_PLATFORMKEYMGR);
	}
	else
	{
		if(strncpy_s(m_configInfo.cPlatformKeyMgrInterface, iter->second.c_str(), TP_D_INTERFACE_LEN)!=0){}else{}

		MapKeyValue.erase(iter);
	}

	iter = MapKeyValue.find(TP_CONFIG_SUBSCRIBE_SERVICEMGR);
	if(MapKeyValue.end() == iter)
	{
		TP_LOG_ERROR("can not find %s in config file",TP_CONFIG_SUBSCRIBE_SERVICEMGR);
	}
	else
	{
		if(strncpy_s(m_configInfo.cSubscribeServiceMgrInterface, iter->second.c_str(), TP_D_INTERFACE_LEN)!=0){}else{}

		MapKeyValue.erase(iter);
	}

	return TP_SDK_ERR_SUCCESS;
}
