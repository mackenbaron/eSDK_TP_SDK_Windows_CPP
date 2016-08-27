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
 * @file   tpProfessionalConfCtrl.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   会议控制类
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init tpProfessionalConfCtrl.h
****************************************************/

#ifndef _TP_PROFESSIONAL_CONFCTRL_H_
#define _TP_PROFESSIONAL_CONFCTRL_H_

#include "Common.h"
#include "string.h"
#include "TP_Native_Types.h"
#include <list>

const char TP_D_SET_VIDEO_SOURCEEX[]="setVideoSourceEx";
const char TP_D_SET_AUDIO_SWITCHEX[]="setAudioSwitchEx";
const char TP_D_SET_BROADCAST_SITEEX[]="setBroadcastSiteEx";
const char TP_D_SET_BROADCAST_CONTINUOUS_PRESENCEEX[]="setBroadcastContinuousPresenceEx";
const char TP_D_SET_SITES_MUTEEX[]="setSitesMuteEx";
const char TP_D_SET_SITES_QUIETEX[]="setSitesQuietEx";
const char TP_D_SET_CONTINUOUS_PRESENCEEX[]="setContinuousPresenceEx";
const char TP_D_REQUEST_CONF_CHAIREX[]="requestConfChairEx";
const char TP_D_RELEASE_CONF_CHAIREX[]="releaseConfChairEx";
const char TP_D_SET_FLOOREX[]="setFloorEx";
const char TP_D_SET_CONF_SITE_VOLUMEEX[]="setConfSiteVolumeEx";
const char TP_D_DISPLAY_CONF_SITE_LOCAL_VIDEOEX[]="displayConfSiteLocalVideoEx";
const char TP_D_HIDE_CONF_SITE_LOCAL_VIDEOEX[]="hideConfSiteLocalVideoEx";
const char TP_D_LOCK_PRESENTATIONEX[]="lockPresentationEx";
const char TP_D_UNLOCK_PRESENTATIONEX[]="unlockPresentationEx";



class CSDKInterface;
class CTPConfCtrl
{
public:
	CTPConfCtrl();
	~CTPConfCtrl();

	int setVideoSourceEx(const std::string &confId, const std::string &siteUri, const std::string &videoSourceUri, int isLock);
	int setAudioSwitchEx(const std::string &confId, int switchGate, int isSwitch);
	int setBroadcastSiteEx(const std::string &confId, const std::string &siteUri, int isBroadcast);
	int setBroadcastContinuousPresenceEx(const std::string &confId, int isBroadcast);
	int setSitesMuteEx(const std::string &confId, const list<std::string> &siteUris, int isMute);
	int setSitesQuietEx(const std::string &confId,const list<std::string> &siteUris, int isQuiet);
	int setContinuousPresenceEx(const std::string &confId,const std::string &target, int presenceMode, const list<std::string> &subPics);
	int requestConfChairEx(const std::string &confId, const std::string &chairmanUri);
	int releaseConfChairEx(const std::string &confId);
	int setFloorEx(const std::string &confId, const std::string &siteUri);
	int setConfSiteVolumeEx(const std::string &confId, const list<SiteVolumeEx> &siteVolumes);
	int displayConfSiteLocalVideoEx(const std::string &confId, const list<std::string> &siteUris);
	int hideConfSiteLocalVideoEx(const std::string &confId, const list<std::string> &siteUris);
	int lockPresentationEx(const std::string &confId, const std::string &siteUri);
	int unlockPresentationEx(const std::string &confId);


	void SetInterfaceObj(CSDKInterface* interface) {m_Interface = interface;}//lint !e10 !e49 !e26 !e64
	void SetURL(char *baseURL, char *baseMethod);



private:
	CSDKInterface* m_Interface;
	char m_strURL[TP_D_URI_LEN+1];
};

#endif //_TP_PROFESSIONAL_CONFCTRL_H_