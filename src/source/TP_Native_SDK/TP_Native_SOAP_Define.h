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
 * @file  TP_Native_SOAP_Define.h   
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief TP Native SOAP Key Name
 * @details
 * @author p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init TP Native SOAP Key Name
****************************************************/

#ifndef _CESDK_TPNATIVE_SOAP_DEFINE_H_
#define _CESDK_TPNATIVE_SOAP_DEFINE_H_

//config xml
const char TP_D_CONFIG_ELEM[]="config";
const char TP_D_APPSETTINGS_ELEM[]="appSettings";
const char TP_D_ADD_ATTR_URL[]="url";
const char TP_D_ADD_ATTR_COMMON[]="tpCommon";
const char TP_D_ADD_ATTR_CONFCTRL[]="tpProfessionalConfCtrl";
const char TP_D_ADD_ATTR_CONFMGR[]="tpProfessionalConfMgr";
const char TP_D_ADD_ATTR_SITEMGR[]="tpProfessionalSiteMgr";
const char TP_D_ADD_ATTR_MCUMGR[]="tpProfessionalMCUMgr";
const char TP_D_ADD_ATTR_ORGAMGR[]="tpProfessionalOrgaMgr";
const char TP_D_ADD_ATTR_TERMCONFCTR[]="tpProfessionalTerminalConfCtr";
const char TP_D_ADD_ATTR_KEYMGR[]="platformKeyMgr";
//const char TP_D_SOAP_URL[]="http://smc.huawei.com/";

const char TP_D_HTTP_HEADER_COOKIE[]="Cookie: JSESSIONID";
const char TP_D_HTTP_HEADER_JSESSIONID[]="JSESSIONID";
const char TP_D_HTTP_HEADER_SOAPACTION[]="SOAPAction";
const char TP_D_HTTP_HEADER_CONTENT_TYPE[]="Content-Type: text/xml; charset=utf-8";



const char TP_D_SOAP_ENVELOPE_ELEM[]="soapenv:Envelope";
const char TP_D_SOAP_ENVELOPE_ATTR_SOAPENV[]="xmlns:soapenv";
const char TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI[]="xmlns:xsi";
const char TP_D_SOAP_FILTERS_ATTR_XMLNS_XSI_VALUE[]="http://www.w3.org/2001/XMLSchema-instance";
const char TP_D_SOAP_FILTERS_ATTR_XSI_TYPE[]="xsi:type";
const char TP_D_SOAP_FILTERS_ATTR_XSI_TYPE_VALUE[]="smc:StringFilterEx";

const char TP_D_SOAP_ENVELOPE_ATTR_SMC[]="xmlns:smc";
const char TP_D_SOAP_HEADER_ELEM[]="soapenv:Header";
const char TP_D_SOAP_BODY_ELEM[]="soapenv:Body";
const char TP_D_SOAP_ENVELOPE_ATTR_SOAPENV_VALUE[]="http://schemas.xmlsoap.org/soap/envelope/";
const char TP_D_SOAP_ENVELOPE_ATTR_SMC_VALUE[]="http://smc.huawei.com/";

//login reuqest
const char TP_D_SOAP_SMC_LOGINREQ_ELEM[]="smc:LoginRequest";
const char TP_D_SOAP_SMC_USRNAME[]="userName";
const char TP_D_SOAP_SMC_CLIENTTYPE[]="clientType";
const char TP_D_SOAP_SMC_CLIENTTYPE_VALUE[]="API";
const char TP_D_SOAP_SMC_VERSION[]="version";
const int  TP_D_SOAP_SMC_VERSION_VALUE = 5;

//Authenticate
const char TP_D_SOAP_SMC_AUTHENTICATE[]="smc:Authenticate";
const char TP_D_SOAP_ENCRYPTPASSWORD[]="encryptPassword";


//Logout
const char TP_D_SOAP_SMC_LOGOUT[]="smc:Logout";


//KeepAlive
const char TP_D_SOAP_SMC_KEEPALIVE[]="smc:KeepAlive";

//ScheduleConfEx
const char TP_D_SOAP_SMC_SCHEDULECONFEX[]="smc:scheduleConfEx";
const char TP_D_SOAP_SCHEDULECONF[] = "scheduleConf";
const char TP_D_SOAP_CONFID[] = "confId";
const char TP_D_SOAP_NAME[] = "name";
const char TP_D_SOAP_BEGINTIME[] = "beginTime";
const char TP_D_SOAP_DURATION[] = "duration";
const char TP_D_SOAP_ACCESS_CODE[] = "accessCode";
const char TP_D_SOAP_PASSWORD[] = "password";
const char TP_D_SOAP_MEDIA_ENCRYPT_TYPE[] = "mediaEncryptType";
const char TP_D_SOAP_AUX_VIDEO_FORMAT[] ="auxVideoFormat";
const char TP_D_SOAP_AUX_VIDEO_PROTOCOL[] = "auxVideoProtocol";
const char TP_D_SOAP_CP_RESOURCE[] = "cpResouce";
const char TP_D_SOAP_RATE[] = "rate";
const char TP_D_SOAP_ISRECORDING[] = "isRecording";
const char TP_D_SOAP_RECORDER_ADDR[] = "recorderAddr";
const char TP_D_SOAP_IS_LIVE_BROADCAST[] = "isLiveBroadcast";
const char TP_D_SOAP_PRESENTATION[] = "presentation";
const char TP_D_SOAP_CHAIRMAN_PASSWORD[] = "chairmanPassword";
const char TP_D_SOAP_STATUS[] = "status";
const char TP_D_SOAP_BILL_CODE[] = "billCode";
const char TP_D_SOAP_MAIN_SITE_URI[] = "mainSiteUri";
const char TP_D_SOAP_CONFERENCE_NOTICE[] = "conferenceNotice";
const char TP_D_SOAP_SITES[] = "sites";
const char TP_D_SOAP_EMAIL[] = "email";
const char TP_D_SOAP_CONTENT[] = "content";
//const char TP_D_SOAP_SITES[] = "sites";
const char TP_D_SOAP_URI[] = "uri";
const char TP_D_SOAP_TYPE[] = "type";
const char TP_D_SOAP_FROM[] = "from";
const char TP_D_SOAP_DIALINGMODE[] = "dialingMode";
//const char TP_D_SOAP_RATE[] = "rate";
const char TP_D_SOAP_VIDEO_FORMAT[]="videoFormat";
const char TP_D_SOAP_VIDEO_PROTOCOL[]="videoProtocol";
const char TP_D_SOAP_IS_LOCK_VIDEO_SOURCE[]="isLockVideoSource";
const char TP_D_SOAP_PARTICIPANT_TYPE[] = "participantType"; 
//const char TP_D_SOAP_STATUS[] = "status";
const char TP_D_SOAP_FREQUENCY[] = "frequency";
const char TP_D_SOAP_INTERVAL[] = "interval";
const char TP_D_SOAP_WEEKDAYS[] = "weekDays";
const char TP_D_SOAP_WEEKDAY[] = "weekDay";
const char TP_D_SOAP_MONTHDAY[] = "monthDay";
const char TP_D_SOAP_COUNT[] = "count";
const char TP_D_SOAP_ENDDATE[]  = "endDate";
const char TP_D_SOAP_TIMEZONE[] = "timeZone";
const char TP_D_SOAP_SITEACCESSINFOS[] = "siteAccessInfos";
const char TP_D_SOAP_CONFACCESSCODE[] = "confAccessCode";
const char TP_D_SOAP_CONFINFO[] = "conferenceInfo";
const char TP_D_SOAP_RECURRENCECONFINFO[] = "recurrenceConfInfo";

//schedule Recurrence ConferenceEx
const char TP_D_SOAP_SCHEDULE_RECURRENCE_CONFEX[] = "smc:scheduleRecurrenceConferenceEx";
const char TP_D_SOAP_RECURRENCE_CONF_INFO[]="recurrenceConfInfo";

//edit ScheduledConfEx 
const char TP_D_SOAP_SMC_EDIT_SCHEDULECONFEX[] = "smc:editScheduledConfEx";
const char TP_D_SOAP_EDITCONF[] = "editConf";


//edit Recurrence ConferenceEx
const char TP_D_SOAP_SMC_EDIT_RECURRENCE_CONFEX[] = "smc:editRecurrenceConferenceEx";

//query sites Ex
const char TP_D_SOAP_SMC_QUERY_SITESEX[]="smc:querySitesEx";
const char TP_D_SOAP_SITEINFOS[]="siteInfos";


//prolongScheduledConfEx
const char TP_D_SOAP_SMC_PROLONG_SCHEDULED_CONFEX[]="smc:prolongScheduledConfEx";
const char TP_D_SOAP_BEGINDATE[] = "beginDate";
const char TP_D_SOAP_PROLONGTIME[] = "prolongTime";

//query site status
const char TP_D_SOAP_SMC_QUERY_SITE_STATUSEX[]="smc:querySiteStatusEx";
const char TP_D_SOAP_SITE_FREE_BUSY_STATES[]="siteFreeBusyStates";
const char TP_D_SOAP_STATES[]="states";
const char TP_D_SOAP_STATE[]="state";
const char TP_D_SOAP_STARTTIME[]="startTime";
const char TP_D_SOAP_SPAN[]="span";
const char TP_D_SOAP_CONFNAME[]="confName";
const char TP_D_SOAP_SITEURIS[]="siteUris";

//query conference status
const char TP_D_SOAP_SMC_QUERY_CONFERENCES_STATUSEX[]="smc:queryConferencesStatusEx";
const char TP_D_SOAP_CONFIDS[]="confIds";
const char TP_D_SOAP_CONFSTATUS[]="conferenceStatuses";
const char TP_D_SOAP_ID[]="id";
const char TP_D_SOAP_CHAIR[]="chair";
const char TP_D_SOAP_BROADCAST[]="broadcast";
const char TP_D_SOAP_SPEAKING[]="speaking";
const char TP_D_SOAP_ISLOCK[]="isLock";
const char TP_D_SOAP_ISAUDIOSWITCH[]="isAudioSwitch";
const char TP_D_SOAP_SWITCHGATE[]="switchGate";
const char TP_D_SOAP_ENDTIME[]="endTime";

//query schedule conferences
const char TP_D_SOAP_SMC_QUERY_SCHEDULE_CONFERENCESEX[] = "smc:queryScheduleConferencesEx";
const char TP_D_SOAP_CONFS[] = "confs";
const char TP_D_SOAP_ISLOCKPRESENTATION[] = "isLockPresentation";
const char TP_D_SOAP_LOCKPRESENTATION[] = "lockPresentation";
const char TP_D_SOAP_RECORDING[] = "recording";
const char TP_D_SOAP_CONFERENCEMODE[] = "conferenceMode";
const char TP_D_SOAP_ISSUPPORTLIVING[] = "isSupportLiving";
const char TP_D_SOAP_ISSUPPORTRECORDING[] = "isSupportRecording";
//const char TP_D_SOAP_STATUS[] = "status";
const char TP_D_SOAP_ISAUTORECORDINGVIDEOSOURCE[] = "isAutoRecordingVideoSource";
const char TP_D_SOAP_VIDEOSOURCE[] = "videoSource";
const char TP_D_SOAP_QUERY_SCHEDULE_CONFERENCESEX[]="queryScheduleConferencesEx";


//add Adhoc Conf TemplateEx
const char TP_D_SOAP_SMC_ADD_ADHOC_CONF_TEMPLATEEX[] = "smc:addAdhocConfTemplateEx";
const char TP_D_SOAP_ADHOC_CONF_TEMPLATE[] = "adhocConfTemplate";
const char TP_D_SOAP_ADHOC_CONF_TEMPLATE_ID[] = "adhocConfTemplateId";
const char TP_D_SOAP_PRESENTATION_VIDEO[] = "presentationVideo";
const char TP_D_SOAP_PROTOCOL[] = "protocol";
const char TP_D_SOAP_FORMAT[] = "format";
const char TP_D_SOAP_NOTICE[] = "notice";
const char TP_D_SOAP_SEMAIL[] = "email";
const char TP_D_SOAP_SCONTENT[] = "content";
const char TP_D_SOAP_TELEPHONE[] = "telephone";
const char TP_D_SOAP_MAX_SITES_COUNT[] = "maxSitesCount";
const char TP_D_SOAP_RESERVED_CSD_PORTS[] = "reservedCsdPorts";
const char TP_D_SOAP_DTMF[] = "dtmf";


//edit Adhoc Conf TemplateEx
const char TP_D_SOAP_SMC_EDIT_ADHOC_CONF_TEMPLATEEX[] = "smc:editAdhocConfTemplateEx";

//del Adhoc Conf TemplateEx
const char TP_D_SOAP_SMC_DEL_ADHOC_CONF_TEMPLATEEX[] = "smc:delAdhocConfTemplateEx";

//query Adhoc Conf TemplateEx
const char TP_D_SOAP_SMC_QUERY_ADHOC_CONF_TEMPLATE_LISTEX[] = "smc:queryAdhocConfTemplateListEx";

//query conf site status
const char TP_D_SOAP_SMC_CONF_SITE_STATUS[]="smc:queryConfSitesStatusEx";
const char TP_D_SOAP_SITE_STATUS[]="siteStatuses";
const char TP_D_SOAP_VOLUME[]="volume";
const char TP_D_SOAP_VIDEO_SOURCE[]="videoSource";
const char TP_D_SOAP_ISMUTE[]="isMute";
const char TP_D_SOAP_ISQUIET[]="isQuiet";
const char TP_D_SOAP_CALL_FAILED_REASON[]="callFailedReason";
const char TP_D_SOAP_ERRCODE[]="errCode";
const char TP_D_SOAP_DESCRIPTION[]="discription";
const char TP_D_SOAP_ISLOCALVIDEOOPEN[]="isLocalVideoOpen";
const char TP_D_SOAP_PARTICIPANTTYPE[]="participantType";
const char TP_D_SOAP_TOTAL_PAGES[]="totalPages";
const char TP_D_SOAP_CURRENT_PAGE[]="currentPage";
const char TP_D_SOAP_TOTAL_RECORDS[]="totalRecords";


//subscribe
const char TP_D_SOAP_SMC_SUBSCRIBE[]="smc:subscribeEx";
const char TP_D_SOAP_SUBSCRIBE_INFOS[]="subscribeInfos";
const char TP_D_SOAP_SMC_ONGOING_CONF_SUBSCRIBE[]="smc:OngoingConfSubscribeEx";
const char TP_D_SOAP_SMC_SCHEDULED_CONF_SUBSCIRBE[]="smc:ScheduledConfSubscribeEx";
const char TP_D_SOAP_IS_SUBSCRIBE[]="isSubscribe";

//enable push
const char TP_D_SOAP_SMC_ENABLE_PUSH[]="smc:enablePushEx";
const char TP_D_SOAP_PUSH_MODE[]="pushMode";
const char TP_D_SOAP_EXTEND_PARAMETER[]="extendParameter";

//query notification
const char TP_D_SOAP_SMC_QUERY_NOTIFICATION[]="smc:queryNotificationEx";
const char TP_D_SOAP_NOTIFICATIONS[]="notifications";
const char TP_D_SOAP_RSP_ONGOING_CONF_NOTIFICATION[]="ns2:OngoingConfNotificationEx";
const char TP_D_SOAP_RSP_SCHEDULED_CONF_NOTIFICATION[]="ns2:ScheduledConfNotificationEx";
const char TP_D_SOAP_RSP_OVERFLOW_NOTIFICATION[]="ns2:OverflowNotificationEx";
const char TP_D_SOAP_EVENT[]="event";
const char TP_D_SOAP_CHANGES[]="changes";
const char TP_D_SOAP_RSP_STIE_STATUS[]="ns2:SiteStatusEx";
const char TP_D_SOAP_RSP_CONFERENCE_STATUS[]="ns2:ConferenceStatusEx";

//sysnc site status
const char TP_D_SOAP_SMC_SYNC_SITE_STATUS[]="smc:synchSiteStatusEx";





//add site to conf
const char TP_D_SOAP_SMC_ADD_SITE_TO_CONF[]="smc:addSiteToConfEx";
const char TP_D_SOAP_SITEINFO[]="siteInfo";

//del site from conf
const char TP_D_SOAP_SMC_DEL_SITE_FROM_CONF[]="smc:delSiteFromConfEx";
const char TP_D_SOAP_SITEURI[]="siteUri";

//connect site
const char TP_D_SOAP_SMC_CONNECT_SITE[]="smc:connectSitesEx";

//disconnect site
const char TP_D_SOAP_SMC_DISCONNECT_SITE[]="smc:disconnectSitesEx";

//del schedule conf
const char TP_D_SOAP_SMC_DEL_SCHEDULED_CONF[]="smc:delScheduledConfEx";

//query multi point cdr
const char TP_D_SOAP_SMC_QUERY_MULTI_POINT_CDR[]="smc:queryMultiPointCDREx";
const char TP_D_SOAP_QUERY_CONFIG[]="queryConfig";
const char TP_D_SOAP_PAGEPARAM[]="pageParam";
const char TP_D_SOAP_NUMBERPERPAGE[]="numberPerPage";
const char TP_D_SOAP_CURRENTPAGE[]="currentPage";
const char TP_D_SOAP_SITENAME[]="siteName";
const char TP_D_SOAP_SITETYPE[]="siteType";
const char TP_D_SOAP_CONFERENCE_NAME[]="conferenceName";
const char TP_D_SOAP_CONFERENCE_ID[]="conferenceId";
const char TP_D_SOAP_CONFERENCE_CREATER[]="conferenceCreater";
const char TP_D_SOAP_CDR[]="cdr";
const char TP_D_SOAP_PAGE_INFO[]="pageInfo";


//query point to point CDR
const char TP_D_SOAP_CALLING_URI[]="callingUri";
const char TP_D_SOAP_CALLING_PROTOCOL[]="callingProtocol";
const char TP_D_SOAP_CALLED_URI[]="calledUri";
const char TP_D_SOAP_CALLED_PROTOCOL[]="calledProtocol";
const char TP_D_SOAP_SMC_QUERY_POINT_TO_POINT_CDR[]="smc:queryPointToPointCDREx";
const char TP_D_SOAP_ENDPOINT[]="endPoint";

//query adhoc conf free busy
const char TP_D_SOAP_SMC_QUERY_ADHOC_CONF_FREE_BUSY[]="smc:queryAdhocConfFreeBusyEx";


//sync adhoc conf free busy
const char TP_D_SOAP_SMC_SYNC_ADHOC_CONF_FREE_BUSY[]="smc:synchAdhocConfFreeBusyEx";
const char TP_D_SOAP_CONF_ACCESS_CODES[]="confAccessCodes";
const char TP_D_SOAP_FREEBUSY[]="freebusy";
const char TP_D_SOAP_FREEBUSYS[]="freebusys";


//query adhoc conf
const char TP_D_SOAP_SMC_QUERY_ADHOC_CONFERENCESEX[]="smc:queryAdhocConferencesEx";
const char TP_D_SOAP_SORT_ITEMS[]="sortItems";
const char TP_D_SOAP_SORT[]="sort";
const char TP_D_SOAP_ITEM_INDEX[]="itemIndex";
const char TP_D_SOAP_FILTERS[]="filters";
const char TP_D_SOAP_COLUMN_INDEX[]="columnIndex";
const char TP_D_SOAP_VALUE[]="value";
const char TP_D_SOAP_ADHOCCONFERENCES[]="adhocConferences";
const char TP_D_SOAP_FOCUSITEM[]="focusItem";

//query conf site MCU
const char TP_D_SOAP_SMC_QUERY_CONF_SITE_MCUEX[]="smc:queryConfSiteMCUEx";
const char TP_D_SOAP_MCUS[]="mcus";
const char TP_D_SOAP_MCUID[]="mcuId";
const char TP_D_SOAP_TARGETS[]="targets";
const char TP_D_SOAP_CPRESOURCE[]="cpResource";
const char TP_D_SOAP_SUPPORTCPMODES[]="supportCPModes";

//get Continuous Presence InfoEx
const char TP_D_SOAP_SMC_GET_CONTINUOUS_PRESENCE_INFOEX[]="smc:getContinuousPresenceInfoEx";


//get continuous presence param
const char TP_D_SOAP_SMC_GET_CONTINUOUS_PRESENCE_PARAMEXP[]="smc:getContinuousPresenceParamEx";
const char TP_D_SOAP_TARGET[]="target";
const char TP_D_SOAP_PRESENCE_MODE[]="presenceMode";
const char TP_D_SOAP_SUBPICS[]="subPics";

//confctrl
//set video source
const char TP_D_SOAP_SMC_SET_VIDEO_SOURCE[]="smc:setVideoSourceEx";
const char TP_D_SOAP_VIDEO_SOURCE_URI[]="videoSourceUri";

//set audio switch
const char TP_D_SOAP_SMC_SET_AUDIO_SWITCH[]="smc:setAudioSwitchEx";
const char TP_D_SOAP_ISSWITCH[]="isSwitch";

//set broadcast site
const char TP_D_SOAP_SMC_SET_BROADCAST_SITE[]="smc:setBroadcastSiteEx";
const char TP_D_SOAP_ISBROADCAST[]="isBroadcast";

//set broadcast continuours presence
const char TP_D_SOAP_SMC_SET_BROADCAST_CONTINUOURS_PRESENCE[]="smc:setBroadcastContinuousPresenceEx";

//set sites mute
const char TP_D_SOAP_SMC_SET_SITES_MUTE[]="smc:setSitesMuteEx";

//set sites quiet
const char TP_D_SOAP_SMC_SET_SITES_QUIET[]="smc:setSitesQuietEx";

//set continuours presence
const char TP_D_SOAP_SMC_SET_CONTINUOURS_PRESENCE[]="smc:setContinuousPresenceEx";

//request conf chair
const char TP_D_SOAP_SMC_REQUEST_CONF_CHAIR[]="smc:requestConfChairEx";
const char TP_D_SOAP_CHAIRMAN_URI[]="chairmanUri";

//release conf chair
const char TP_D_SOAP_SMC_RELEASE_CONF_CHAIR[]="smc:releaseConfChairEx";

//set floor
const char TP_D_SOAP_SMC_SET_FLOOR[]="smc:setFloorEx";

//set conf site volume
const char TP_D_SOAP_SMC_SET_CONF_SITE_VOLUME[]="smc:setConfSiteVolumeEx";
const char TP_D_SOAP_SITE_VOLUMES[]="siteVolumes";

//display conf site local video
const char TP_D_SOAP_SMC_DISPLAY_CONF_SITE_LOCAL_VIDEO[]="smc:displayConfSiteLocalVideoEx";

//hide conf site local video
const char TP_D_SOAP_SMC_HIDE_CONF_SITE_LOCAL_VIDEO[]="smc:hideConfSiteLocalVideoEx";

//lock presentation 
const char TP_D_SOAP_SMC_LOCK_PRESENTATION[]="smc:lockPresentationEx";

//unlock presentation
const char TP_D_SOAP_SMC_UNLOCK_PRESENTATION[]="smc:unlockPresentationEx";

//site mgr
//add site info
const char TP_D_SOAP_SMC_ADD_SITE_INFOEX[]="smc:addSiteInfoEx";
const char TP_D_SOAP_ORGID[]="orgId";
const char TP_D_SOAP_VIDEO_CAPBILITY[]="videoCapbility";
const char TP_D_SOAP_REGUSER[]="regUser";
const char TP_D_SOAP_REGPASSWORD[]="regPassword";

//edit site info
const char TP_D_SOAP_SMC_EDIT_SITE_INFOEX[]="smc:editSiteInfoEx"; 


//delete site info
const char TP_D_SOAP_SMC_DELETE_SITE_INFOEX[]="smc:deleteSiteInfoEx";


//query site info
const char TP_D_SOAP_SMC_QUERY_SITES_INFO[]="smc:querySitesInfoEx";
//query MCU info
const char TP_D_SOAP_SMC_QUERY_MCU_INFOEX[]="smc:queryMCUInfoEx";
const char TP_D_SOAP_IP1[]="ip1";
const char TP_D_SOAP_PORT1[]="port1";
const char TP_D_SOAP_IP2[]="ip2";
const char TP_D_SOAP_PORT2[]="port2";
const char TP_D_SOAP_DOMAIN_NAME[]="domainName";
const char TP_D_SOAP_STUTAS[]="stutas";

//query MCU future resource
const char TP_D_SOAP_SMC_QUERY_MCU_FUTURE_RESOURCEEX[]="smc:queryMCUFutureResourceEx";
const char TP_D_SOAP_RESOURCE_LIST[]="resourceList";
const char TP_D_SOAP_MCURES_LIST[]="mcuResList";
const char TP_D_SOAP_RESOURCE_TYPE[]="resourceType";
const char TP_D_SOAP_RESOURCE_STATUS[]="resourceStatus";
const char TP_D_SOAP_FREE_COUNT[]="freeCount";
const char TP_D_SOAP_TOTAL_COUNT[]="totalCount";

//query organization 
const char TP_D_SOAP_SMC_QUERY_ORGANIZATIONEX[]="smc:queryOrganizationEx";
const char TP_D_SOAP_ORGS[]="orgs";


//request chair
const char TP_D_SOAP_SMC_REQUEST_CHAIREX[]="smc:requestChairEx";

//release chair
const char TP_D_SOAP_SMC_RELEASE_CHAIREX[]="smc:releaseChairEx";

//query conf ctrl pwd
const char TP_D_SOAP_SMC_QUERY_CONF_CTRL_PWDEX[]="smc:queryConfCtrlPwdEx";
const char TP_D_SOAP_RESULT[]="result";

//query broad info
const char TP_D_SOAP_SMC_QUERY_BROAD_INFOEX[]="smc:queryBroadInfoEx";
const char TP_D_SOAP_BROAD_INFO[]="broadInfo";
const char TP_D_SOAP_DIRECT_BROAD[]="directBroad";
const char TP_D_SOAP_RECORD_BROAD[]="recordBroad";
const char TP_D_SOAP_DIRECT_BROAD_STATUS[]="directBroadStatus";
const char TP_D_SOAP_RECORD_BROAD_STATUS[]="recordBroadStatus";

//set record broad
const char TP_D_SOAP_SMC_RECORD_BROADEX[]="smc:setRecordBroadEx";
const char TP_D_SOAP_ACTION[]="action";

//set direct broad
const char TP_D_SOAP_SMC_DIRECT_BROADEX[]="smc:setDirectBroadEx";

//is Connect Aux Source
const char TP_D_SOAP_SMC_IS_CONNECT_AUX_SOURCEEX[]="smc:isConnectAuxSourceEx";

//is Send Aux Stream
const char TP_D_SOAP_SMC_IS_SEND_AUX_STREAMEX[]="smc:isSendAuxStreamEx";


//is Receive Rem Aux StrmEx
const char TP_D_SOAP_SMC_IS_RECEIVE_REM_AUX_STRMEX[]="smc:isReceiveRemAuxStrmEx";

//set Aux stream
const char TP_D_SOAP_SMC_SET_AUX_STREAMEX[]="smc:setAuxStreamEx";
const char TP_D_SOAP_CONTROL_CODE[]="controlCode";

//query aux stream source
const char TP_D_SOAP_SMC_QUERY_AUX_STREAM_SOURCEEX[]="smc:queryAuxStreamSourcesEx";
const char TP_D_SOAP_AUXSTREAMS[]="auxStreams";


//query video out src state 
const char TP_D_SOAP_SMC_QUERY_VIDEO_OUT_SRC_STATEEX[]="smc:queryVideoOutSrcStateEx";
const char TP_D_SOAP_SOURCE_ID[]="sourcesId";
const char TP_D_SOAP_SOURCES_STATE[]="sourcesState";
const char TP_D_SOAP_SOURCES_NAME[]="sourcesName";
const char TP_D_SOAP_VIDEO_SOURCES_INFOS[]="videoSourcesInfos";

//ctrl camera
const char TP_D_SOAP_SMC_CTRL_CAMERAEX[]="smc:ctrlCameraEx";
const char TP_D_SOAP_CAMERA_CONTROL[]="cameraControl";
const char TP_D_SOAP_CAM_STATE[]="camState";
const char TP_D_SOAP_CAM_ACTION[]="camAction";
const char TP_D_SOAP_CAM_POS[]="camPos";
const char TP_D_SOAP_CAM_SRC[]="camSrc";


//set main aux stream sources 
const char TP_D_SOAP_SMC_SET_MAIN_AUX_STREAM_SOURCESEX[]="smc:setMainAuxStreamSourcesEx";
const char TP_D_SOAP_LOCAL_MAIN_SRCS[]="localMainSrcs";
const char TP_D_SOAP_LOCAL_AUX_SRC[]="localAuxSrc";

//query main stream sources
const char TP_D_SOAP_SMC_QUERY_MAIN_STREAM_SOURCESEX[]="smc:queryMainStreamSourcesEx";


//set video out src
const char TP_D_SOAP_SMC_SET_VIDEO_OUT_SRCEX[]="smc:setVideoOutSrcEx";
const char TP_D_SOAP_HDOUT[]="hdOut";
const char TP_D_SOAP_VIDEO_SRC[]="videoSrc";

//query site version info
const char TP_D_SOAP_SMC_QUERY_SITE_VERSION_INFOEX[]="smc:querySiteVersionInfoEx";
const char TP_D_SOAP_MODEL[]="model";
const char TP_D_SOAP_LICENSE[]="license";
const char TP_D_SOAP_SOFT_VERSION[]="softVersion";
const char TP_D_SOAP_HARD_VERSION[]="hardVersion";
const char TP_D_SOAP_LOGIC_VERSION[]="logicVersion";
const char TP_D_SOAP_MIC_VERSIONS[]="micVersions";
const char TP_D_SOAP_MANUFACTURER[]="manufacturer";
const char TP_D_SOAP_MICIP[]="micIP";
const char TP_D_SOAP_VERSION[]="version";
const char TP_D_SOAP_SITE_DEVICE_VERSION_INFO[]="siteDeviceVersionInfo";

const char TP_D_SOAP_RSP_ENVELOP_ELEM[]="soap:Envelope";
const char TP_D_SOAP_RSP_BODY_ELEM[]="soap:Body";
#define	TP_D_SOAP_RSP_LOGINREQ_ELEM					"ns2:LoginRequestResponse"
#define TP_D_SOAP_RSP_AUTH_ELEM						"ns2:AuthenticateResponse"
#define TP_D_SOAP_RSP_LOGOUT						"ns2:LogoutResponse"
#define TP_D_SOAP_RSP_KEEPALIVE						"ns2:KeepAliveResponse"
#define TP_D_SOAP_RSP_SCHEDULECONF					"ns2:scheduleConfExResponse"
#define TP_D_SOAP_RSP_SCHEDULERECURRENCECONF		"ns2:scheduleRecurrenceConferenceExResponse"
#define TP_D_SOAP_RSP_EDITSCHEDULECONF				"ns2:editScheduledConfExResponse"
#define TP_D_SOAP_RSP_EDITSCHEDULERECURRENCECONF	"ns2:editRecurrenceConferenceExResponse"
#define TP_D_SOAP_RSP_QUERYSITESEX					"ns2:querySitesExResponse"
#define TP_D_SOAP_RSP_PROLONGSCHEDULECONF			"ns2:prolongScheduledConfExResponse"
#define TP_D_SOAP_RSP_QUERYSITESSTATUSEX			"ns2:querySiteStatusExResponse"
#define TP_D_SOAP_RSP_QUERYCONFERENCESTATUSEX		"ns2:queryConferencesStatusExResponse"
#define TP_D_SOAP_RSP_ADDADHOCCONFTEMPLATEEX		"ns2:addAdhocConfTemplateExResponse"
#define TP_D_SOAP_RSP_EDITADHOCCONFTEMPLATEEX		"ns2:editAdhocConfTemplateExResponse"
#define TP_D_SOAP_RSP_DELADHOCCONFTEMPLATEEX		"ns2:delAdhocConfTemplateExResponse"
#define TP_D_SOAP_RSP_QUERYADHOCCONFTEMPLATELISTEX	"ns2:queryAdhocConfTemplateListExResponse"
#define TP_D_SOAP_RSP_QUERYSCHEDULECONFERENCESEX	"ns2:queryScheduleConferencesExResponse"
#define TP_D_SOAP_RSP_QUERYCONFSITESSTATUSEX		"ns2:queryConfSitesStatusExResponse"
#define TP_D_SOAP_RSP_SYNCSITESTATUSEX				"ns2:synchSiteStatusExResponse"
#define TP_D_SOAP_RSP_ADDSITETOCONFEX				"ns2:addSiteToConfExResponse"
#define TP_D_SOAP_RSP_DELSITEFROMCONFEX				"ns2:delSiteFromConfExResponse"
#define TP_D_SOAP_RSP_CONNECTSITEEX					"ns2:connectSitesExResponse"
#define TP_D_SOAP_RSP_DISCONNECTSITEEX				"ns2:disconnectSitesExResponse"
#define TP_D_SOAP_RSP_DELSCHEDULECONFEX				"ns2:delScheduledConfExResponse"
#define TP_D_SOAP_RSP_QUERYMULTIPOINTCDREX			"ns2:queryMultiPointCDRExResponse"
#define TP_D_SOAP_RSP_QUERYPOINTTOPOINTCDREX		"ns2:queryPointToPointCDRExResponse"
#define TP_D_SOAP_RSP_SYNCADHOCCONFFREEBUSYEX		"ns2:synchAdhocConfFreeBusyExResponse"
#define TP_D_SOAP_RSP_QUERYADHOCCONFFREEBUSYEX		"ns2:queryAdhocConfFreeBusyExResponse"
#define TP_D_SOAP_RSP_QUERYADHOCCONFERENCESEX		"ns2:queryAdhocConferencesExResponse"
#define TP_D_SOAP_RSP_QUERYCONFSITEMCUEX			"ns2:queryConfSiteMCUExResponse"
#define TP_D_SOAP_RSP_GETCONTINPRESENCEINFO			"ns2:getContinuousPresenceInfoExResponse"
#define TP_D_SOAP_RSP_GETCONTINPRESENCEPARAM		"ns2:getContinuousPresenceParamExResponse"

#define TP_D_SOAP_RSP_SETVIDEOSOURCEEX					"ns2:setVideoSourceExResponse"
#define TP_D_SOAP_RSP_SETAUDIOSWITCHEX					"ns2:setAudioSwitchExResponse"
#define TP_D_SOAP_RSP_SETBROADCASTSITEEX				"ns2:setBroadcastSiteExResponse"
#define TP_D_SOAP_RSP_SETBROADCASTCONTINUOUSPRESENCEEX	"ns2:setBroadcastContinuousPresenceExResponse"
#define TP_D_SOAP_RSP_SETSITESMUTEEX					"ns2:setSitesMuteExResponse"
#define TP_D_SOAP_RSP_SETSITESQUIETEX					"ns2:setSitesQuietExResponse"
#define TP_D_SOAP_RSP_SETCONTINUOUSPRESENCEEX			"ns2:setContinuousPresenceExResponse"
#define TP_D_SOAP_RSP_REQUESTCONFCHAIREX				"ns2:requestConfChairExResponse"
#define TP_D_SOAP_RSP_RELEASECONFCHAIREX				"ns2:releaseConfChairExResponse"
#define TP_D_SOAP_RSP_SETFLOOREX						"ns2:setFloorExResponse"
#define TP_D_SOAP_RSP_SETCONFSITEVOLUMEEX				"ns2:setConfSiteVolumeExResponse"
#define TP_D_SOAP_RSP_DISPLAYCONFSITELOCALVIDEOEX		"ns2:displayConfSiteLocalVideoExResponse"
#define TP_D_SOAP_RSP_HIDECONFSITELOCALVIDEOEX			"ns2:hideConfSiteLocalVideoExResponse"
#define TP_D_SOAP_RSP_LOCKPRESENTATIONEX				"ns2:lockPresentationExResponse"
#define TP_D_SOAP_RSP_UNLOCKPRESENTATIONEX				"ns2:unlockPresentationExResponse"

#define TP_D_SOAP_RSP_ADDSITEINFOEX						"ns2:addSiteInfoExResponse"
#define TP_D_SOAP_RSP_EDITSITEINFOEX					"ns2:editSiteInfoExResponse"
#define TP_D_SOAP_RSP_DELETESITEINFOEX					"ns2:deleteSiteInfoExResponse"
#define TP_D_SOAP_RSP_QUERYSITESINFOEX					"ns2:querySitesInfoExResponse"

#define TP_D_SOAP_RSP_QUERYMCUINFOEX					"ns2:queryMCUInfoExResponse"
#define TP_D_SOAP_RSP_QUERYMCUFUTURERESOURCEEX			"ns2:queryMCUFutureResourceExResponse"

#define TP_D_SOAP_RSP_QUERYORGANIZATIONEX				"ns2:queryOrganizationExResponse"

#define TP_D_SOAP_RSP_REQUESTCHAIREX					"ns2:requestChairExResponse"
#define TP_D_SOAP_RSP_RELEASECHAIREX					"ns2:releaseChairExResponse"
#define TP_D_SOAP_RSP_QUERYCONFCTRLPWDEX				"ns2:queryConfCtrlPwdExResponse"
#define TP_D_SOAP_RSP_QUERYBROADINFOEX					"ns2:queryBroadInfoExResponse"
#define TP_D_SOAP_RSP_SETRECORDBROADEX					"ns2:setRecordBroadExResponse"
#define TP_D_SOAP_RSP_SETDIRECTBROADEX					"ns2:setDirectBroadExResponse"


#define TP_D_SOAP_RSP_ISCONNECTAUXSOURCEEX				"ns2:isConnectAuxSourceExResponse"
#define TP_D_SOAP_RSP_ISSENDAUXSTREAMEX					"ns2:isSendAuxStreamExResponse"
#define TP_D_SOAP_RSP_ISRECEIVEREMAUXSTRMEX				"ns2:isReceiveRemAuxStrmExResponse"
#define TP_D_SOAP_RSP_SETAUXSTREAMEX					"ns2:setAuxStreamExResponse"
#define TP_D_SOAP_RSP_QUERYAUXSTREAMSOURCESEX			"ns2:queryAuxStreamSourcesExResponse"


#define TP_D_SOAP_RSP_QUERYVIDEOOUTSRCSTATEEX			"ns2:queryVideoOutSrcStateExResponse"
#define TP_D_SOAP_RSP_CTRLCAMERAEX						"ns2:ctrlCameraExResponse"
#define TP_D_SOAP_RSP_SETMAINAUXSTREAMSOURCESEX			"ns2:setMainAuxStreamSourcesExResponse"
#define TP_D_SOAP_RSP_QUERYMAINSTREAMSOURCESEX			"ns2:queryMainStreamSourcesExResponse"
#define TP_D_SOAP_RSP_SETVIDEOOUTSRCEX					"ns2:setVideoOutSrcExResponse"

#define TP_D_SOAP_RSP_QUERYSITEVERSIONINFOEX			"ns2:querySiteVersionInfoExResponse"


#define TP_D_SOAP_RSP_SUBSCRIBEEX						"ns2:subscribeExResponse"
#define TP_D_SOAP_RSP_ENABLEPUSHEX						"ns2:enablePushResponse"
#define TP_D_SOAP_RSP_ENABLEDPUSHEX                     "ns2:enablePushExResponse"
#define TP_D_SOAP_RSP_QUERY_NOTIFICATIONEX				"ns2:queryNotificationExResponse"

const char TP_D_SOAP_RSP_LOGINREQUEST_RANDOMSEQ_ELEM[]="randomSequence";
const char TP_D_SOAP_RSP_RESULTCODE_ELEM[]="resultCode";

#endif