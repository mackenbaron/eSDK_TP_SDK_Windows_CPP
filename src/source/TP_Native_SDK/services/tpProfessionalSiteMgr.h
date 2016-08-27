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
 * @file   tpProfessionalSiteMgr.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   会场管理类
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init tpProfessionalSiteMgr.h
****************************************************/

#ifndef _TP_PROFESSIONAL_SITEMGR_H_
#define _TP_PROFESSIONAL_SITEMGR_H_

#include "Common.h"
#include "string.h"
#include "TP_Native_Types.h"
#include <list>


const char TP_D_ADD_SITE_INFOEX[]="addSiteInfoEx";
const char TP_D_EDIT_SITE_INFOEX[]="editSiteInfoEx";
const char TP_D_DELETE_SITE_INFOEX[]="deleteSiteInfoEx";
const char TP_D_QUERY_SITE_INFOEX[]="querySitesInfoEx";

const char TP_D_IS_CONNECT_AUX_SOURCEEX[]="isConnectAuxSourceEx";
const char TP_D_IS_SEND_AUX_STREAMEX[]="isSendAuxStreamEx";
const char TP_D_IS_RECEIVE_REM_AUX_STRMEX[]="isReceiveRemAuxStrmEx";
const char TP_D_SET_AUX_STREAMEX[]="setAuxStreamEx";
const char TP_D_QUERY_AUX_STREAM_SOURCESEX[]="queryAuxStreamSourcesEx";

const char TP_D_QUERY_VIDEO_OUT_SRC_STATEEX[]="queryVideoOutSrcStateEx";
const char TP_D_CTRL_CAMERAEX[]="ctrlCameraEx";
const char TP_D_SET_MAIN_AUX_STREAM_SOURCESEX[]="setMainAuxStreamSourcesEx";
const char TP_D_QUERY_MAIN_STREAM_SOURCESEX[]="queryMainStreamSourcesEx";
const char TP_D_SET_VIDEO_OUT_SRCEX[]="setVideoOutSrcEx";

const char TP_D_QUERY_SITE_VERSION_INFOEX[]="querySiteVersionInfoEx";



class CSDKInterface;
class CTPSiteMgr
{
public:
	CTPSiteMgr();
	~CTPSiteMgr();
	int addSiteInfoEx(const std::string &orgId, const TerminalInfoEx& siteInfo);
	int editSiteInfoEx(const TerminalInfoEx& siteInfo);
	int deleteSiteInfoEx(const list<std::string>&  siteUris);
	TPSDKResponseEx<QuerySitesInfoExResponse> querySitesInfoEx(const QueryConfigEx &queryConfig);

	TPSDKResponseEx<int> isConnectAuxSourceEx(const std::string &siteUri);
	TPSDKResponseEx<int> isSendAuxStreamEx(const std::string &siteUri);
	TPSDKResponseEx<int> isReceiveRemAuxStrmEx(const std::string &siteUri);
	int setAuxStreamEx(const std::string &siteUri, int controlCode);
	TPSDKResponseEx<list<AuxStreamInfoEx>> queryAuxStreamSourcesEx(const std::string &siteUri);

	TPSDKResponseEx<list<VideoSourcesInfoEx>> queryVideoOutSrcStateEx(const std::string &siteUri);
	int ctrlCameraEx(const std::string &siteUri, const CameraControlEx &cameraControl);
	int setMainAuxStreamSourcesEx(const std::string &siteUri, const list<int> &localMainSrcs, int localAuxSrc);
	TPSDKResponseEx<list<AuxStreamInfoEx>> queryMainStreamSourcesEx(const std::string &siteUri);
	int setVideoOutSrcEx(const std::string &siteUri, int hdOut, int videoSrc);

	TPSDKResponseEx<SiteDeviceVersionInfoEx> querySiteVersionInfoEx(const std::string &siteUri);


	void SetInterfaceObj(CSDKInterface* interface) {m_Interface = interface;}//lint !e10 !e49 !e26 !e64
	void SetURL(char *baseURL, char *baseMethod);



private:
	CSDKInterface* m_Interface;
	char m_strURL[TP_D_URI_LEN+1];
};

#endif //_TP_PROFESSIONAL_SITEMGR_H_