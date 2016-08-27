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

/****************************************************   
 * @file   tpProfessionalTerminalConfCtr.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   ÷’∂Àπ‹¿Ì¿‡
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init tpProfessionalTerminalConfCtr.h
****************************************************/

#ifndef _TP_PROFESSIONAL_TERMINAL_CONFCTRL_H_
#define _TP_PROFESSIONAL_TERMINAL_CONFCTRL_H_

#include "Common.h"
#include "string.h"
#include "TP_Native_Types.h"
#include <list>


const char TP_D_REQUEST_CHAIRX[]="requestChairEx";
const char TP_D_RELEASE_CHAIRX[]="releaseChairEx";
const char TP_D_QUERY_CONF_CTRL_PWDEX[]="queryConfCtrlPwdEx";
const char TP_D_QUERY_BROAD_INFOEX[]="queryBroadInfoEx";
const char TP_D_SET_RECORD_BROADEX[]="setRecordBroadEx";
const char TP_D_SET_DIRECT_BROADEX[]="setDirectBroadEx";


class CSDKInterface;
class CTPTermConfMgr
{
public:
	CTPTermConfMgr();
	~CTPTermConfMgr();

	int requestChairEx(const std::string &siteUri);
	int releaseChairEx(const std::string &siteUri);
	TPSDKResponseEx<int> queryConfCtrlPwdEx(const std::string &siteUri);
	TPSDKResponseEx<BroadInfoEx> queryBroadInfoEx(const std::string &siteUri);
	int setRecordBroadEx(const std::string &siteUri, int action);
	int setDirectBroadEx(const std::string &siteUri, int action);

	void SetInterfaceObj(CSDKInterface* interface) {m_Interface = interface;}//lint !e10 !e49 !e26 !e64
	void SetURL(char *baseURL, char *baseMethod);



private:
	CSDKInterface* m_Interface;
	char m_strURL[TP_D_URI_LEN+1];
};

#endif //_TP_PROFESSIONAL_MCUMGR_H_