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
 * @file   tpProfessionalScribMgr.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   ∂©‘ƒ”ÎÕ∆ÀÕ¿‡
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2016-04-12 Init tpProfessionalScribMgr.h
****************************************************/


#ifndef _TP_PROFESSIONAL_SCRIBMGR_H_
#define _TP_PROFESSIONAL_SCRIBMGR_H_

#include "Common.h"
#include "string.h"
#include "TP_Native_Types.h"
#include <list>


const char TP_D_SUBSCRIBEEX[]="subscribeEx";
const char TP_D_ENABLEPUSHEX[]="enablePushEx";
const char TP_D_QUERY_NOTIFICATION[]="queryNotificationEx";

class CSDKInterface;
class CTPScribMgr
{
public:
	CTPScribMgr();
	~CTPScribMgr();

	int subscribeEx(const list<SubscribeInfoEx *> &subscribeInfos);
	int enablePushEx(int pushMode, const std::string &extendParameter);
	TPSDKResponseEx<list<NotificationEx *>> queryNotificationEx();

	void SetInterfaceObj(CSDKInterface* interface) {m_Interface = interface;}//lint !e10 !e49 !e26 !e64
	void SetURL(char *baseURL, char *baseMethod);

private:
	CSDKInterface* m_Interface;
	char m_strURL[TP_D_URI_LEN+1];
};






#endif
