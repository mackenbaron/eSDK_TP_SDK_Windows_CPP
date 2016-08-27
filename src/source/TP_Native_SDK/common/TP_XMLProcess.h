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
 * @file   TP_XMLProcess.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   XML入参解析，XML出参赋值
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init  TP_XMLProcess.h
****************************************************/
#ifndef __TP_NATIVE_XML_PROCESS_H__
#define __TP_NATIVE_XML_PROCESS_H__

#include <string>
#include <map>
#include "TP_Native_Xml.h"
#include "TP_Native_Types.h"

// XML节点解析
#define GET_XML_ELEM_VALUE_CHAR(xml, elem, srcValue, retValue, maxLen)			\
	if (!xml.FindElem(elem))													\
	{																			\
		TP_LOG_ERROR("FindElem %s failed.", elem);								\
		return TP_SDK_ERR_XML_FIND_ELEM;											\
	}																			\
	srcValue = xml.GetElemValue();												\
	if (NULL == srcValue)														\
	{																			\
		TP_LOG_ERROR("GetElemValue %s failed.", elem);							\
		return TP_SDK_ERR_XML_GET_ELEM_VALUE;										\
	}																			\
	maxLen = (strlen(srcValue) < (maxLen)) ? strlen(srcValue) : ((maxLen)-1);	\
	memcpy(retValue, srcValue, maxLen)


// XML节点解析
#define GET_XML_ATTR_VALUE_CHAR(xml, attr, srcValue, retValue, maxLen)			\
	if (!xml.FindAttr(elem))													\
	{																			\
	TP_LOG_ERROR("FindElem %s failed.", elem);								\
	return TP_SDK_ERR_XML_FIND_ELEM;											\
	}																			\
	srcValue = xml.GetElemValue();												\
	if (NULL == srcValue)														\
	{																			\
	TP_LOG_ERROR("GetElemValue %s failed.", elem);							\
	return TP_SDK_ERR_XML_GET_ELEM_VALUE;										\
	}																			\
	maxLen = (strlen(srcValue) < (maxLen)) ? strlen(srcValue) : ((maxLen)-1);	\
	memcpy(retValue, srcValue, maxLen)

struct VIDEO_PARAM
{
	std::string VideoFormat;
	std::string CameraType;
	std::string UserConfirmType;
	std::string MuteType;
};

#define TP_CONFIG_ATTR_KEY				"key"
#define TP_CONFIG_ATTR_VALUE			"value"
#define TP_CONFIG_APPSETTINGS_ELEM		"appSettings"
#define TP_CONFIG_URL					"url"
#define TP_CONFIG_COMMON				"tpCommon"
#define TP_CONFIG_CONFCTRL				"tpProfessionalConfCtrl"
#define TP_CONFIG_CONFMGR				"tpProfessionalConfMgr"
#define TP_CONFIG_SITEMGR				"tpProfessionalSiteMgr"
#define TP_CONFIG_MCUMGR				"tpProfessionalMCUMgr"
#define TP_CONFIG_ORGAMGR				"tpProfessionalOrgaMgr"
#define TP_CONFIG_TERM_CONFCTR			"tpProfessionalTerminalConfCtr"
#define TP_CONFIG_PLATFORMKEYMGR		"platformKeyMgr"
#define TP_CONFIG_SUBSCRIBE_SERVICEMGR	"tpProfessionalScribMgr"



//////////////////////////////////////////////////////////////////////////
class XMLProcess
{
	// DisplayManager/GISReportManager 回调消息xml构造
public:
	static int SetXml_LoginRequest(const std::string &userName, std::string& xmlStr);
	static int SetXml_Authenticate(const std::string &encryptPassword, std::string& xmlStr);
	static int SetXml_Logout(std::string& xmlStr);
	static int SetXml_KeepAlive(std::string& xmlStr);

	static int GetXml_Config(const char* xmlStr, std::map<std::string,std::string> *MapKeyValue);
	static int GetRSPXML_ResultCode(const char *xmlStr, char *RSP_Method_ELEM);
	static int GetRSPXml_LoginRequest(const char *xmlStr, std::string &randomSequence);
	
	static int SetXml_scheduleConfEx(const ConferenceInfoEx *conferenceInfo, std::string& xmlStr);
	static int GetRSPXml_scheduleConfEx(const char *xmlStr, ConferenceInfoEx *conferenceInfo);
	static int SetXml_scheduleRecurrenceConferenceEx(const RecurrenceConfInfoEx *recuConfInfo, std::string& xmlStr);
	static int GetRSPXml_scheduleRecurrenceConferenceEx(const char *xmlStr, RecurrenceConfInfoEx *recuConfInfo);

	static int SetXml_editScheduledConfEx(const ConferenceInfoEx *conferenceInfo, std::string& xmlStr);
	static int GetRSPXml_editScheduleConfEx(const char *xmlStr, ConferenceInfoEx *conferenceInfo);

	static int SetXml_editScheduleRecurrenceConferenceEx(const RecurrenceConfInfoEx *recuConfInfo,  const SYSTEMTIME &beginDateTime, std::string& xmlStr);
	static int GetRSPXml_editScheduleRecurrenceConferenceEx(const char *xmlStr, RecurrenceConfInfoEx *recuConfInfo);

	static int SetXml_querySitesEx(std::string& xmlStr);
	static int GetRSPXml_querySitesEx(const char *xmlStr,list<SiteInfoEx> *listSites);

	static int SetXml_prolongScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginDateTime, const std::string &prolongTime, std::string& xmlStr);
	static int GetRSPXml_prolongScheduledConfEx(const char *xmlStr, int &resCode);


	static int SetXml_querySiteStatusEx(const list<string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration, std::string& xmlStr);
	static int GetRSPXml_querySiteStatusEx(const char *xmlStr, map<std::string, list<FreeBusyStateEx>> *map_SiteStatus);


	static int SetXml_queryConferencesStatusEx(const list<string> &confIds, std::string& xmlStr);
	static int GetRSPXml_queryConferencesStatusEx(const char *xmlStr, list<ConferenceStatusEx> *list_ConferenceStatus);


	static int SetXml_queryScheduleConferencesEx(const QueryConfigEx &queryConfig, std::string& xmlStr);
	static int GetRSPXml_queryScheduleConferencesEx(const char *xmlStr, list<ConferenceStatusEx> *list_ConferenceStatus, PagesInfoEx &pagesInfo);

	static int SetXml_queryConfSitesStatusEx(const std::string &confId, const list<std::string> &siteUris, std::string& xmlStr);
	static int GetRSPXml_queryConfSitesStatusEx(const char *xmlStr, list<SiteStatusEx> *list_SiteStatus);

	static int SetXml_synchSiteStatusEx(const list<string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration, std::string& xmlStr);
	static int GetRSPXml_synchSiteStatusEx(const char *xmlStr, map<string, list<FreeBusyStateEx>> *map_SiteStatus);

	static int SetXml_addSiteToConfEx(const std::string &confId, const SiteInfoEx &siteInfo, const SYSTEMTIME &beginTime, std::string& xmlStr);
	static int GetRSPXml_addSiteToConfEx(const char *xmlStr, list<SiteAccessInfoEx> *siteAccessInfo);

	static int SetXml_delSiteFromConfEx(const std::string &confId, const std::string &siteUri, const SYSTEMTIME &beginTime, std::string& xmlStr);

	static int SetXml_connectSitesEx(const std::string &confId, const list<std::string> &siteUris, std::string& xmlStr);
	
	static int SetXml_disconnectSitesEx(const std::string &confId, const list<std::string> &siteUris, std::string& xmlStr);
	
	static int SetXml_delScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginTime, std::string& xmlStr);

	static int SetXml_queryMultiPointCDREx(const MultiPointCDRQueryConfigEx &queryConfig, std::string& xmlStr);
	static int GetRSPXml_queryMultiPointCDREx(const char *xmlStr, QueryMultiPointCDRExResponse *queryMultiPointCDR);

	
	static int SetXml_queryPointToPointCDREx(const PointToPointCDRQueryConfigEx &queryConfig, std::string& xmlStr);
	static int GetRSPXml_queryPointToPointCDREx(const char *xmlStr, QueryPointToPointCDRExResponse *queryPointToPointCDR);

	
	static int SetXml_queryAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration, std::string& xmlStr);
	static int GetRSPXml_queryAdhocConfFreeBusyEx(const char *xmlStr, list<AdhocConfFreeBusyStateEx> *adhocConfFreeBusyState);

	static int SetXml_synchAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration, std::string& xmlStr);
	static int GetRSPXml_synchAdhocConfFreeBusyEx(const char *xmlStr, list<AdhocConfFreeBusyStateEx> *adhocConfFreeBusyState);

	static int SetXml_queryAdhocConferencesEx(const QueryConfigEx &queryConfig, std::string& xmlStr);
	static int GetRSPXml_queryAdhocConferencesEx(const char *xmlStr, QueryAdhocConferenceExResponse *queryAdhocConfExResponse);

	static int SetXml_queryConfSiteMCUEx(const std::string &confId, const list<std::string> &siteUris, const SYSTEMTIME &beginTime, std::string& xmlStr);
	static int GetRSPXml_queryConfSiteMCUEx(const char *xmlStr, list<SiteMCUEx> *list_siteMcu);


	static int SetXml_getContinuousPresenceInfoEx(const std::string &confId, std::string &xmlStr);
	static int GetRSPXml_getContinuousPresenceInfoEx(const char *xmlStr, GetContinuousPresenceInfoResponseEx *getContinPresenceInfoResponse);

	static int SetXml_getContinuousPresenceParamEx(const std::string &confId, const std::string &target, std::string& xmlStr);
	static int GetRSPXml_getContinuousPresenceParamEx(const char *xmlStr, GetContinuousPresenceParamResponseEx *getContinPresenceParamResponse);

	static int SetXml_addAdhocConfTemplateEx(const std::string &orgId, const AdhocConfTemplateParamEx &adhocConfTemplate, std::string &xmlStr);
	static int GetRSPXml_addAdhocConfTemplateEx(const char *xmlStr, std::string &adhocConfTemplateId);

	static int SetXml_editAdhocConfTemplateEx(const AdhocConfTemplateParamEx &adhocConfTemplate, std::string &xmlStr);
	static int GetRSPXml_editAdhocConfTemplateEx(const char *xmlStr);

	static int SetXml_delAdhocConfTemplateEx(const std::string &adhocConfTemplateId, std::string &xmlStr);
	static int GetRSPXml_delAdhocConfTemplateEx(const char *xmlStr);

	static int SetXml_queryAdhocConfTemplateListEx(const QueryConfigEx &queryConfig, std::string &xmlStr);
	static int GetRSPXml_queryAdhocConfTemplateListEx(const char *xmlStr, list<AdhocConfTemplateParamEx> *list_AdhocConfTemplateParam, PagesInfoEx &pagesInfo);

	static int SetXml_subscribeEx(const list<SubscribeInfoEx *> &subscribeInfos, std::string &xmlStr);
	static int GetRSPXml_subscribeEx(const char *xmlStr);

	static int SetXml_enablePushEx(int pushMode,const std::string &extendParameter, std::string &xmlStr);
	static int GetRSPXml_enablePushEx(const char *xmlStr);

	static int SetXml_queryNotificationEx(std::string &xmlStr);
	static int GetRSPXml_queryNotificationEx(const char *xmlStr, list<NotificationEx *> &list_Notification);

	static int SetXml_setVideoSourceEx(const std::string &confId, const std::string &siteUri, const std::string &videoSourceUri, int isLock, std::string& xmlStr);
	static int SetXml_setAudioSwitchEx(const std::string &confId, int switchGate, int isSwitch, std::string& xmlStr);
	static int SetXml_setBroadcastSiteEx(const std::string &confId, const std::string &siteUri, int isBroadcast, std::string& xmlStr);
	static int SetXml_setBroadcastContinuousPresenceEx(const std::string &confId, int isBroadcast, std::string& xmlStr);
	static int SetXml_setSitesMuteEx(const std::string &confId, const list<std::string> &siteUris, int isMute, std::string &xmlStr);
	static int SetXml_setSitesQuietEx(const std::string &confId, const list<std::string> &siteUris, int isQuiet, std::string &xmlStr);
	static int SetXml_setContinuousPresenceEx(const std::string &confId, const std::string &target, int presenceMode, const list<std::string> &subPics, std::string &xmlStr);
	static int SetXml_requestConfChairEx(const std::string &confId, const std::string &chairmanUri, std::string &xmlStr);
	static int SetXml_releaseConfChairEx(const std::string &confId, std::string& xmlStr);
	static int SetXml_setFloorEx(const std::string &confId, const std::string &siteUri, std::string& xmlStr);
	static int SetXml_setConfSiteVolumeEx(const std::string &confId, const list<SiteVolumeEx> &siteVolumes, std::string& xmlStr);
	static int SetXml_displayConfSiteLocalVideoEx(const std::string &confId, const list<std::string> &siteUris, std::string& xmlStr);
	static int SetXml_hideConfSiteLocalVideoEx(const std::string &confId,const  list<std::string> &siteUris, std::string& xmlStr);
	static int SetXml_lockPresentationEx(const std::string &confId, const std::string &siteUri, std::string& xmlStr);
	static int SetXml_unlockPresentationEx(const std::string &confId, std::string& xmlStr);

	static int SetXml_addSiteInfoEx(const std::string &orgId, const TerminalInfoEx &siteInfo, std::string& xmlStr);
	static int SetXml_editSiteInfoEx(const TerminalInfoEx& siteInfo, std::string& xmlStr);
	static int SetXml_deleteSiteInfoEx(const list<std::string>& siteUris, std::string& xmlStr);
	static int SetXml_querySitesInfoEx(const QueryConfigEx &queryConfig, std::string& xmlStr);
	static int GetXml_querySitesInfoEx(const char *xmlStr, QuerySitesInfoExResponse *querySitesInfoExResponse);

	static int SetXml_queryMCUInfoEx(const QueryConfigEx &queryConfig, std::string& xmlStr);
	static int GetXml_queryMCUInfoEx(const char *xmlStr, QueryMCUInfoExResponse *queryMCUInfoExResponse);
	static int SetXml_queryMCUFutureResourceEx(const list<int> &mcus, const SYSTEMTIME &beginTime, const std::string &duration, std::string& xmlStr);
	static int GetXml_queryMCUFutureResourceEx(const char *xmlStr, list<MCUResourceEx> *MCUResouce);

	static int SetXml_queryOrganizationEx(std::string& xmlStr);
	static int GetXml_queryOrganizationEx(const char *xmlStr, list<OrganizationItemEx> *list_orgItem);


	static int SetXml_requestChairEx(const std::string &siteUri,std::string& xmlStr);
	static int SetXml_releaseChairEx(const std::string &siteUri,std::string& xmlStr);
	static int SetXml_queryConfCtrlPwdEx(const std::string &siteUri,std::string& xmlStr);
	static int GetXml_queryConfCtrlPwdEx(const char *xmlStr, int &result);
	static int SetXml_queryBroadInfoEx(const std::string &siteUri,std::string& xmlStr);
	static int GetXml_queryBroadInfoEx(const char *xmlStr, BroadInfoEx *broadInfo);
	static int SetXml_setRecordBroadEx(const std::string &siteUri, int action,std::string& xmlStr);
	static int SetXml_setDirectBroadEx(const std::string &siteUri, int action,std::string& xmlStr);


	static int SetXml_isConnectAuxSourceEx(const std::string &siteUri,std::string& xmlStr);
	static int GetXml_isConnectAuxSourceEx(const char *xmlStr, int &result);
	static int SetXml_isSendAuxStreamEx(const std::string &siteUri,std::string& xmlStr);
	static int GetXml_isSendAuxStreamEx(const char *xmlStr, int &result);
	static int SetXml_isReceiveRemAuxStrmEx(const std::string &siteUri,std::string& xmlStr);
	static int GetXml_isReceiveRemAuxStrmEx(const char *xmlStr, int &result);
	static int SetXml_setAuxStreamEx(const std::string &siteUri, int controlCode,std::string& xmlStr);
	static int SetXml_queryAuxStreamSourcesEx(const std::string &siteUri,std::string& xmlStr);
	static int GetXml_queryAuxStreamSourcesEx(const char *xmlStr, list<AuxStreamInfoEx> *list_auxStreamInfo);

	static int SetXml_queryVideoOutSrcStateEx(const std::string &siteUri,std::string& xmlStr);
	static int GetXml_queryVideoOutSrcStateEx(const char *xmlStr, list<VideoSourcesInfoEx> *list_VideoSourcesInfo);
	static int SetXml_ctrlCameraEx(const std::string &siteUri, const CameraControlEx &cameraControl,std::string& xmlStr);
	static int SetXml_setMainAuxStreamSourcesEx(const std::string &siteUri, const list<int>& localMainSrcs, int localAuxSrc,std::string& xmlStr);
	static int SetXml_queryMainStreamSourcesEx(const std::string &siteUri,std::string& xmlStr);
	static int GetXml_queryMainStreamSourcesEx(const char *xmlStr, list<AuxStreamInfoEx> *list_auxStreamInfo);
	static int SetXml_setVideoOutSrcEx(const std::string &siteUri, int hdOut, int videoSrc,std::string& xmlStr);

	static int SetXml_querySiteVersionInfoEx(const std::string &siteUri,std::string& xmlStr);
	static int GetXml_querySiteVersionInfoEx(const char *xmlStr, SiteDeviceVersionInfoEx *siteDeviceVersionInfo);
	

private:
	static int Package_BasicSOAP(const char *SMC_ELEM, CXml *xml);
	static int Package_ConferenceInfo(const ConferenceInfoEx *conferenceInfo,CXml *xml);
	static int Package_ConferenceNoticeEx(const ConferenceNoticeEx *conferenceNotice, CXml *xml);
	static int Package_SiteInfoEx(const SiteInfoEx *site, CXml *xml);
	static int Package_RecurrenceConfInfoEx(const RecurrenceConfInfoEx *recuConfInfo,CXml *xml);
	static int Package_MultiPointCDRQueryConfigEx(const MultiPointCDRQueryConfigEx *queryConfig,CXml *xml);
	static int Package_PointToPointCDRQueryConfigEx(const PointToPointCDRQueryConfigEx *queryConfig,CXml *xml);
	static int Package_TerminalInfoEx(const TerminalInfoEx *siteInfo, CXml *xml);
	static int Package_QueryConfigEx(const QueryConfigEx *queryConfig, CXml *xml);
	static int Package_AdhocConfTemplateParamEx(const AdhocConfTemplateParamEx &adhocConfTemplate, CXml *xml);
	static int Package_OngoingConfSubscribeEx(const OngoingConfSubscribeEx &subscribeInfos, CXml *xml);
	static int Package_ScheduledConfSubscribeEx(const ScheduledConfSubscribeEx &subscribeInfos, CXml *xml);
	static int GetXMLElemValue(CXml *xmlParse,  const char *elem, int elem_flag, std::string &strValue);
	static int Parse_siteFreeBusyStates(CXml *xmlParse, SiteStatusEx &SiteStatus);
	static int Parse_FreeBusyStateEx(CXml *xmlParse, FreeBusyStateEx &siteState);
	static int Parse_siteFreeBusyStates(CXml *xmlParse, std::string &uri, list<FreeBusyStateEx> &list_freeBusyState);
	static int Parse_SiteAccessInfoEx(CXml *xmlParse, SiteAccessInfoEx &siteAccessInfo);
	static int Parse_MultiPointCDREx(CXml *xmlParse, MultiPointCDREx &multiPointCDR);
	static int Parse_PagesInfoEx(CXml *xmlParse, PagesInfoEx &pageInfo);
	static int Parse_PointToPointCDREx(CXml *xmlParse, PointToPointCDREx &PointToPointCDR);
	static int Parse_AdhocConfFreeBusyStateEx(CXml *xmlParse, AdhocConfFreeBusyStateEx &adhocConfState);
	static int Parse_AdhocConferenceEx(CXml *xmlParse, AdhocConferenceEx &AdhocConf);
	static int Parse_SiteMCUEx(CXml *xmlParse, SiteMCUEx &siteMcu);
	static int Parse_MCUInfoEx(CXml *xmlParse, MCUInfoEx &mcuInfo);
	static int Parse_TerminalInfoEx(CXml *xmlParse, TerminalInfoEx &site);
	static int Parse_MCUResourceEx(CXml *xmlParse, MCUResourceEx &mcuResource);
	static int Parse_MCUResourceItemEx(CXml *xmlParse, MCUResourceItemEx &mcuResourceItem);
	static int Parse_ResourceOccupiedStatusEx(CXml *xmlParse, ResourceOccupiedStatusEx &ResourceOccupiedStatus);
	static int Parse_OrganizationItemEx(CXml *xmlParse, OrganizationItemEx &orgaItem);
	static int Parse_AuxStreamInfoEx(CXml *xmlParse, AuxStreamInfoEx &auxStreamInfo);
	static int Parse_VideoSourcesInfoEx(CXml *xmlParse, VideoSourcesInfoEx &videoSourcesInfo);
	static int Parse_SiteMicVersionMapEx(CXml *xmlParse, SiteMicVersionMapEx &micVersionMap);
	static int Parse_SiteDeviceVersionInfoEx(CXml *xmlParse, SiteDeviceVersionInfoEx *siteDeviceVersionInfo);
	static int Parse_ConferenceStatusEx(CXml *xmlParse, ConferenceStatusEx &conferenceStatus);
	static int Parse_ConferenceNoticeEx(CXml *xmlParse, ConferenceNoticeEx &conferenceNotice);
	static int Parse_RecordStatusEx(CXml *xmlParse, RecordStatusEx &recordStatus);
	static int Parse_AdhocConfTemplateParamEx(CXml *xmlParse, AdhocConfTemplateParamEx &adhocConfTemplateParam);
	static int Parse_VideoParamEx(CXml *xmlParse, VideoParamEx &videoParam);
	static int Parse_SiteInfoEx(CXml *xmlParse, SiteInfoEx &siteInfo);
	static int Parse_OngoingConfNotificationEx(CXml *xmlParse, OngoingConfNotificationEx *notification);
	static int Parse_ScheduledConfNotificationEx(CXml *xmlParse, ScheduledConfNotificationEx *notification);
	static int Parse_OverflowNotificationEx(CXml *xmlParse, OverflowNotificationEx *notification);
	static int StringTimeFormatTOSystemtime(const std::string &strTime,SYSTEMTIME &sysTime);
	
private:
	XMLProcess(void);
	~XMLProcess(void);

};

#endif
