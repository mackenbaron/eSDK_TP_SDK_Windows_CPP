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
 * @file   tpProfessionalConfMgr.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   会议调度类
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init tpProfessionalConfMgr.h
****************************************************/

#ifndef _TP_PROFESSIONAL_CONFMGR_H_
#define _TP_PROFESSIONAL_CONFMGR_H_

#include "Common.h"
#include "string.h"
#include "TP_Native_Types.h"
#include <list>
const char TP_D_SCHE_CONFEX[]="scheduleConfEx";
const char TP_D_SCHE_RECURRENCE_CONFEX[]="scheduleRecurrenceConferenceEx";
const char TP_D_EDIT_SCHE_CONFEX[]="editScheduledConfEx";
const char TP_D_EDIT_RECURRENCE_CONFEX[]="editRecurrenceConferenceEx";
const char TP_D_QUERY_SITESEX[]="querySitesEx";
const char TP_D_PROLONG_SCHE_CONFEX[]="prolongScheduledConfEx";
const char TP_D_QUERY_SITE_STATUSEX[]="querySiteStatusEx";
const char TP_D_QUERY_CONF_STATUSEX[]="queryConferencesStatusEx";
const char TP_D_QUERY_CONF_SITES_STATUSEX[]="queryConfSitesStatusEx";
const char TP_D_SYNC_SITE_STATUSEX[]="synchSiteStatusEx";
const char TP_D_ADD_SITE_TO_CONFEX[]="addSiteToConfEx";
const char TP_D_DEL_SITE_FROM_CONFEX[]="delSiteFromConfEx";
const char TP_D_CONNECT_SITESEX[]="connectSitesEx";
const char TP_D_DISCONNECT_SITESEX[]="disconnectSitesEx";
const char TP_D_DEL_SCHE_CONFEX[]="delScheduledConfEx";
const char TP_D_QUERY_MULTI_POINT_CDREX[]="queryMultiPointCDREx";
const char TP_D_QUERY_POINTTOPOINT_CDREX[]="queryPointToPointCDREx";
const char TP_D_QUERY_ADHOC_CONF_FREE_BUSY[]="queryAdhocConfFreeBusyEx";
const char TP_D_SYNC_ADHOC_CONF_FREE_BUSY[]="synchAdhocConfFreeBusyEx";
const char TP_D_QUERY_ADHOC_CONFERENCESEX[]="queryAdhocConferencesEx";
const char TP_D_QUERY_CONF_SITE_MCUEX[]="queryConfSiteMCUEx";
const char TP_D_GET_CONTI_PRESENCE_INFOEX[]="getContinuousPresenceInfoEx";
const char TP_D_GET_CONTI_PRESENCE_PARAMEX[]="getContinuousPresenceParamEx";
const char TP_D_ADD_ADHOC_CONF_TEMPLATEEX[]="addAdhocConfTemplateEx";
const char TP_D_EDIT_ADHOC_CONF_TEMPLATEEX[]="editAdhocConfTemplateEx";
const char TP_D_DEL_ADHOC_CONF_TEMPLATEEX[]="delAdhocConfTemplateEx";
const char TP_D_QUERY_ADHOC_CONF_TEMPLATE_LISTEX[]="queryAdhocConfTemplateListEx";

class CSDKInterface;
class CTPConfMgr
{
public:
	CTPConfMgr();
	~CTPConfMgr();


	TPSDKResponseEx<ConferenceInfoEx> scheduleConfEx(const ConferenceInfoEx *conferenceInfo);
	TPSDKResponseEx<RecurrenceConfInfoEx> scheduleRecurrenceConferenceEx(const RecurrenceConfInfoEx *recuConfInfo);
	TPSDKResponseEx<ConferenceInfoEx> editScheduledConfEx(const ConferenceInfoEx *conferenceInfo);
	TPSDKResponseEx<RecurrenceConfInfoEx> editRecurrenceConferenceEx(const RecurrenceConfInfoEx *recuConfInfo, const SYSTEMTIME &beginDateTime);
	TPSDKResponseEx<list<SiteInfoEx>> querySitesEx();
	int prolongScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginDateTime, const std::string &prolongTime);
	TPSDKResponseEx<map<std::string, list<FreeBusyStateEx>>> querySiteStatusEx(const list<string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration);
	TPSDKResponseEx<list<ConferenceStatusEx>> queryConferencesStatusEx(const list<string> &confIds);
	TPSDKResponseWithPageEx<list<ConferenceStatusEx>> queryScheduleConferencesEx(const QueryConfigEx &queryConfig);
	TPSDKResponseEx<list<SiteStatusEx>> queryConfSitesStatusEx(const std::string &confId, const list<std::string> &siteUris);
	TPSDKResponseEx<map<string, list<FreeBusyStateEx>>> synchSiteStatusEx(const list<string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration);
	TPSDKResponseEx<list<SiteAccessInfoEx>> addSiteToConfEx(const std::string &confId, const SiteInfoEx &siteInfo, const SYSTEMTIME &beginTime);
	int delSiteFromConfEx(const std::string &confId, const std::string &siteUri, const SYSTEMTIME &beginTime);
	int connectSitesEx(const std::string &confId, const list<std::string> &siteUris);
	int disconnectSitesEx(const std::string &confId, const list<std::string> &siteUris);
	int delScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginTime);
	TPSDKResponseEx<QueryMultiPointCDRExResponse> queryMultiPointCDREx(const MultiPointCDRQueryConfigEx &queryConfig);
	TPSDKResponseEx<QueryPointToPointCDRExResponse> queryPointToPointCDREx(const PointToPointCDRQueryConfigEx &queryConfig);
	
	TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> queryAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration);
	TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> synchAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration);

	TPSDKResponseEx<QueryAdhocConferenceExResponse> queryAdhocConferencesEx(const QueryConfigEx &queryConfig);
	TPSDKResponseEx<list<SiteMCUEx>> queryConfSiteMCUEx(const std::string &confId, const list<std::string>& siteUris, const SYSTEMTIME &beginTime);
	TPSDKResponseEx<GetContinuousPresenceInfoResponseEx> getContinuousPresenceInfoEx(const std::string &confId);
	TPSDKResponseEx<GetContinuousPresenceParamResponseEx> getContinuousPresenceParamEx(const std::string &confId, const std::string &target);

	TPSDKResponseEx<std::string> addAdhocConfTemplateEx(const std::string &orgId, const AdhocConfTemplateParamEx &adhocConfTemplate);
	int editAdhocConfTemplateEx(const AdhocConfTemplateParamEx &adhocConfTemplate);
	int delAdhocConfTemplateEx(const std::string &adhocConfTemplateId);
	TPSDKResponseWithPageEx<list<AdhocConfTemplateParamEx>> queryAdhocConfTemplateListEx(const QueryConfigEx &queryConfig);

	void SetInterfaceObj(CSDKInterface* interface) {m_Interface = interface;}//lint !e10 !e49 !e26 !e64
	void SetURL(char *baseURL, char *baseMethod);



private:
	CSDKInterface* m_Interface;
	char m_strURL[TP_D_URI_LEN+1];
};

#endif //_TP_PROFESSIONAL_CONFMGR_H_