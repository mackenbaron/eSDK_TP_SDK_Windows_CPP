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
 * @file   tpCommon.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   登录管理类
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init  tpCommon.h
****************************************************/

#ifndef _TP_COMMON_H_
#define _TP_COMMON_H_

#include "Common.h"
#include "string.h"
#include "TP_Native_Types.h"
const char TP_D_LOGINREQUEST[]="LoginRequest";
const char TP_D_AUTHENTICATE[]="Authenticate";
const char TP_D_LOGOUT[]="Logout";
const char TP_D_KEEPALIVE[]="KeepAlive";
const char TP_D_COOKIEKEY[]="JSESSIONID=";
class CSDKInterface;
class CTPCommon
{
public:
	CTPCommon();
	~CTPCommon();

	/*********************************************************************
	* description: 登录
	* input			: userName 用户名， password 密码， ip IP地址， port 端口号
	* output		: N/A
	* return		: 错误码，0：成功  其它：失败
	*********************************************************************/
	int Login(const std::string &userName, const std::string &password);

	/*********************************************************************
	* description: 登出
	* input			: N/A
	* output		: N/A
	* return		: 错误码，0：成功  其它：失败
	*********************************************************************/
	int Logout();


	int KeepAlive();

	/*********************************************************************
	* description: 设置CSDKInterface对象
	* input			: interface CSDKInterface对象指针
	* output		: N/A
	* return		: N/A
	*********************************************************************/
	void SetInterfaceObj(CSDKInterface* interface) {m_Interface = interface;}//lint !e10 !e49 !e26 !e64
	void SetURL(char *baseURL, char *baseMethod);

private:
	int LoginRequest(std::string username, std::string &randomSequence);
	int Authenticate(const std::string sessionID, const std::string randomSequence, const std::string password);

private:
	CSDKInterface* m_Interface;
	char m_strURL[TP_D_URI_LEN+1];
	std::string m_sessionId;
};

#endif //_TP_COMMON_H_
