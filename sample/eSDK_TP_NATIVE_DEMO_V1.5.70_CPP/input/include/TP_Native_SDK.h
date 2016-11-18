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
 * @file  TP_Native_SDK.h   
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief TP Native SDK Interface
 * @details TP Native SDK Interface:
 * @author p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init TP Native SDK Interface
****************************************************/

#ifndef _CESDK_TPNATIVE_H
#define _CESDK_TPNATIVE_H
#include "TP_Native_Types.h"
#include "stdafx.h"


#ifdef WIN32
#ifdef  TP_NATIVE_SDK_EXPORTS
#define ESDK_TPNATIVE_API __declspec(dllexport)
#else
#define ESDK_TPNATIVE_API __declspec(dllimport)
#endif
#else
#define ESDK_TPNATIVE_API __attribute__((visibility("default")))
#endif

#ifdef WIN32
#define __SDK_CALL __stdcall
#else
#define __SDK_CALL
#endif

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� ESDK_TPNATIVE_H
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// ESDK_TESERVICE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�



/**************************************************
 * @fn         login
 * @brief      ��¼��֤����
 * @param[in]  username    eSDK��¼�û�����ȡֵΪ��װeSDK TP����ӵĵ�¼eSDK�û�ID
 * @param[in]  password    eSDK��¼���롣
 * @return     �ɹ�����0��ʧ�ܷ��ش�����
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL login(const std::string &username, const std::string &password);

/**************************************************
 * @fn         logout
 * @brief      �û��ǳ�
 * @return     �ɹ�����0��ʧ�ܷ��ش�����
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL logout();

/**************************************************
 * @fn         keepAlive
 * @brief      ��������
 * @return     �ɹ�����0��ʧ�ܷ��ش�����
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL keepAlive();


/**************************************************
 * @fn         scheduleConfEx
 * @brief      �ټ���ԤԼ�������Ի���
 * @param[in]  scheduleConf 		׼��ԤԼ�Ļ�������������᳡�б�Ͳ���, ԤԼʱ ConferenceInfoEx �������������
 *									name����������
 *									beginTime�����鿪ʼʱ��
 *									rate������
 *									duration������ʱ��
 *									sites���᳡��Ϣ�б�
 *									���л᳡�б�����е� SiteInfoEx �������Ϊ��
 *									uri �᳡��ʶ���� uri Ϊ��ʱ��ԤԼ��������
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result����ԤԼ�ɹ�����������Ϣ������ϵͳ����Ļ��� ID������Ľ��������Ϣ��
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<ConferenceInfoEx> __SDK_CALL scheduleConfEx(const ConferenceInfoEx& scheduleConf);

/**************************************************
 * @fn         scheduleRecurrenceConferenceEx
 * @brief     �ټ���ԤԼ�����Ի���
 * @param[in]  scheduleConf 		׼��ԤԼ�Ļ�������������᳡�б�ͻ᳡�Ĳ�����ԤԼʱ ConferenceInfoEx �������������
 *									name����������
 *									beginTime�����鿪ʼʱ��
 *									duration������ʱ��
 *									rate������
 *									sites���᳡��Ϣ�б�
 *									frequency�����ڻ�����������
 *									interval�����ڻ�������ڼ��
 *									count���ظ���������endTime��countͬʱ��ֵʱ������ϵͳ������������ٵ�����Ϊ׼����countΪ3��endTimeΪ5���frequencyΪÿ�죬��������ڻ����ٿ�3�Σ������������
 *									weekDays��weekDay��monthDay������������������Ҫ��дһ������
 *									���л᳡�б�����е� SiteInfoEx �������Ϊ��
 *									uri �᳡��ʶ���� uri Ϊ��ʱ��ԤԼ��������
 *									name���᳡����
 *									type���᳡����
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result����ԤԼ�ɹ�����������Ϣ������ϵͳ����Ļ��� ID������Ľ��������Ϣ��
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<RecurrenceConfInfoEx> __SDK_CALL scheduleRecurrenceConferenceEx(const RecurrenceConfInfoEx& scheduleConf);


/**************************************************
 * @fn         editScheduledConfEx
 * @brief      �༭��ԤԼ����ͨ����
 * @param[in]  editConf 			�Ѿ�ԤԼ��δ�ٿ��Ļ�����Ϣ��ConferenceInfoEx �������������
 *									confId������ID
 *									name����������
 *									beginTime�����鿪ʼʱ��
 *									rate������
 *									duration������ʱ��
 *									sites���᳡��Ϣ�б�
 *									���л᳡�б�����е� SiteInfoEx �������Ϊ��
 *									uri �᳡��ʶ��
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	 �����ɹ��� response.result���ػ����޸ĳɹ�������Ļ��顢�᳡��Ϣ��
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<ConferenceInfoEx> __SDK_CALL editScheduledConfEx(const ConferenceInfoEx& scheduleConf);



/**************************************************
 * @fn         editRecurrenceConferenceEx
 * @brief     �ټ���ԤԼ�����Ի���
 * @param[in]  scheduleConf 		�Ѿ�ԤԼ��δ�ٿ��Ļ�����Ϣ��ConferenceInfoEx ����������£�
 *									confId������ ID
 *									name����������
 *									beginTime�����鿪ʼʱ��
 *									rate������
 *									frequency�����ڻ�����������
 *									interval�����ڻ�������ڼ��
 *									count���ظ�����������ʼʱ�䣨beginTime��Ϊ��ȥ��ĳ��ʱ�䣬��ϵͳ��Ĭ�Ͻ���ʼʱ������Ϊ��ǰʱ�䡣weekDays��weekDay��monthDay������������������Ҫ��дһ����
 *									���л᳡�б�����е� SiteInfoEx �������Ϊ��
 *									uri �᳡��ʶ���� uri Ϊ��ʱ��ԤԼ��������
 *									name���᳡����
 *									type���᳡����
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result���ػ����޸ĳɹ�������Ļ��顢�᳡��Ϣ��
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<RecurrenceConfInfoEx> __SDK_CALL editRecurrenceConferenceEx(const RecurrenceConfInfoEx& scheduleConf,const SYSTEMTIME &beginDateTime);


/**************************************************
 * @fn         querySitesEx
 * @brief     ��ѯ���л᳡�б�
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result�������л᳡�б�
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<SiteInfoEx>> __SDK_CALL querySitesEx();


/**************************************************
 * @fn         prolongScheduledConfEx
 * @brief     �ӳ���ԤԼ����ʱ��
 * @param[in]  confId 				���� ID��
 * @param[in]  beginDateTime 		���鿪ʼʱ�䡣����˵�����£�
 *									�����ڻ����еĵ�����������ӳ���
 *									�������ͨ���飬���߶����ڻ�������л�������ӳ�������Բ������롣
 * @param[in]  prolongTime			׼���ӳ���ʱ�䡣ÿ���ӳ�ʱ������ SMC ��̨���õġ���С�ӳ�����ʱ�����͡�����ӳ�����ʱ����֮�䡣�ӳ��������ʱ���������ơ�
 *									����SMC ���ӳ�����ʱ����������ο�SMC ��������ĵ���
 * @return      resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL prolongScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginDateTime, const std::string &prolongTime);

/**************************************************
 * @fn         querySiteStatusEx
 * @brief     ��ѯָ���᳡��ָ��ʱ�䷶Χ�ڵ�æ��״̬
 * @param[in]  siteUris 			��Ҫ��ѯæ��״̬�Ļ᳡ URI �б�������H.323�ĺ��룬�� SIP �� URI����绰����ȡ�
 * @param[in]  beginDateTime 		��ѯ��ʼʱ�䡣
 * @param[in]  duration				��ѯʱ�䷶Χ��
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result����ָ���᳡��ѯʱ��η�Χ�ڵ�æ��״̬��
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<map<std::string, list<FreeBusyStateEx>>> __SDK_CALL querySiteStatusEx(const list<std::string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration);


/**************************************************
 * @fn         queryConferencesStatusEx
 * @brief     ��ѯ�ѵ��Ȼ����״̬
 * @param[in]  confIds 				����ID�б�
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result���ػ���״̬�б�
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<ConferenceStatusEx>> __SDK_CALL queryConferencesStatusEx(const list<std::string> &confIds);




/**************************************************
 * @fn        queryScheduleConferencesEx
 * @brief     ��ѯ���еĵ��Ȼ���״̬��֧�ֹ��ˡ���ҳ
 * @param[in]   queryConfig 		��������
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result���ػ���״̬��Ϣ��
 *				response.pagesInfo	ҳ����Ϣ
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseWithPageEx<list<ConferenceStatusEx>> queryScheduleConferencesEx(const QueryConfigEx &queryConfig);


/**************************************************
 * @fn        addAdhocConfTemplateEx
 * @brief     ���Adhoc����ģ��
 * @param[in]   orgId 				����ģ����ӵ�����֯
 * @param[in]   adhocConfTemplate 	Adhoc����ģ�����
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	���Adhoc����ģ��ɹ����ģ��ID��������
 *				response.pagesInfo	ҳ����Ϣ
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<std::string> addAdhocConfTemplateEx(const std::string &orgId, const AdhocConfTemplateParamEx &adhocConfTemplate);



/**************************************************
 * @fn        editAdhocConfTemplateEx
 * @brief     �޸�Adhoc����ģ��
 * @param[in]   adhocConfTemplate 	Adhoc����ģ�����
 * @return      resultCode 		�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int editAdhocConfTemplateEx(const AdhocConfTemplateParamEx &adhocConfTemplate);


/**************************************************
 * @fn        delAdhocConfTemplateEx
 * @brief     ɾ��Adhoc����ģ��
 * @param[in]   adhocConfTemplateId 	Adhoc����ģ��ID
 * @return      resultCode 		�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int delAdhocConfTemplateEx(const std::string &adhocConfTemplateId);


/**************************************************
 * @fn			queryAdhocConfTemplateListEx
 * @brief		��ѯAd hoc����
 * @param[in]   queryConfig 	��ѯAd hoc����ʱʹ�õĹ��ˡ����򡢷�ҳ����
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	������ϲ�ѯ������Ad hoc�����б�
 *				response.pagesInfo	ҳ����Ϣ
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseWithPageEx<list<AdhocConfTemplateParamEx>> queryAdhocConfTemplateListEx(const QueryConfigEx &queryConfig);


/**************************************************
 * @fn         queryConfSitesStatusEx
 * @brief     ��ѯָ�������еĻ᳡״̬
 * @param[in]  confIds 				����ID�б�
 * @param[in]  siteUris 			׼����ѯ�Ļ᳡�б������ѯ�б�Ϊ�գ����ʾ��ѯ���������У��к���� URI �ģ��᳡��״̬��
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result����ָ���᳡״̬��
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<SiteStatusEx>> __SDK_CALL queryConfSitesStatusEx(const std::string &confId, const list<std::string> &siteUris);


/**************************************************
 * @fn         synchSiteStatusEx
 * @brief     ָ���᳡æ��״̬ͬ��
 * @param[in]  siteUris 			��Ҫͬ��æ��״̬�Ļ᳡ URI �б�������H.323�ĺ��룬�� SIP �� URI����绰����ȡ�
 * @param[in]  beginTime 			��ѯ���ݷ����仯�Ŀ�ʼʱ�䡣
 * @param[in]  duration				��ѯ���ݷ����仯��ʱ�䷶Χ��
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result����ָ���᳡ͬ������᳡��æ��״̬������˵�����£�
 *										ÿ���᳡æ��״̬����æ���б�ͬʱ�����û᳡�Ļ�����Ϣ�����������Ϣ���£�
 *											���������
 *											���鿪ʼʱ��
 *											�������ʱ��
 *										�����״̬�ǡ��С�����ͬʱ�л��� Id�����ʾ�û����Ѿ���ɾ������������᳡������������С�
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<map<string, list<FreeBusyStateEx>>> __SDK_CALL synchSiteStatusEx(const list<string> &siteUris, const SYSTEMTIME &beginTime, const std::string &duration);


/**************************************************
 * @fn         addSiteToConfEx
 * @brief     �������ӻ᳡
 * @param[in]  confId 				���� ID��
 * @param[in]  siteInfo 			׼����ӵ�����Ļ᳡��Ϣ��
 * @param[in]  beginTime			���鿪ʼʱ�䡣����˵�����£�
 *										���ֻ�����ڻ����еĵ���������ӻ᳡������Ҫ�ṩ���ڻ��� ID �͵�������Ŀ�ʼʱ�䡣
 *										�������ͨ���飬���߶����ڻ�������л�����ӻ᳡������������鿪ʼʱ�䡣
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result����»᳡���뵽����Ľ������Ϣ��
 *									��Ϊ���ڻ����е��ӻ������ſ��ܲ�ͬ�����Կ��ܴ��ڶ������ŵ������ÿ���������Ϣ�ڶ��ж�Ӧ�Ļ��鿪ʼʱ�䡣
 *									��ʽ�磺2013-05-07T22:46:31.235+08:00������2013-05-07T22:46:31.235Ϊ��������ʱ�䣨GMTʱ�䣩��+08:00Ϊ�й���½��GMT��ʱ�
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<SiteAccessInfoEx>> __SDK_CALL addSiteToConfEx(const std::string &confId, const SiteInfoEx &siteInfo, const SYSTEMTIME &beginTime);


/**************************************************
 * @fn         delSiteFromConfEx
 * @brief     ɾ�������еĻ᳡
 * @param[in]  confId 				���� ID��
 * @param[in]  siteUri 				�᳡ URI��
 * @param[in]  beginTime			���鿪ʼʱ�䡣����˵�����£�
 *										ֻɾ�����ڻ����еĵ����������Ϣ������Ҫ�ṩ���ڻ��� Id�͵�������Ŀ�ʼʱ�䡣
 *										ɾ����ͨ������Ϣ�����߶����ڻ�������л�������޸ģ�����Բ������롣
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ��� response.result����»᳡���뵽����Ľ������Ϣ��
 *									��Ϊ���ڻ����е��ӻ������ſ��ܲ�ͬ�����Կ��ܴ��ڶ������ŵ������ÿ���������Ϣ�ڶ��ж�Ӧ�Ļ��鿪ʼʱ�䡣
 *									��ʽ�磺2013-05-07T22:46:31.235+08:00������2013-05-07T22:46:31.235Ϊ��������ʱ�䣨GMTʱ�䣩��+08:00Ϊ�й���½��GMT��ʱ�
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL delSiteFromConfEx(const std::string &confId, const std::string &siteUri, const SYSTEMTIME &beginTime);


/**************************************************
 * @fn         connectSitesEx
 * @brief     ����һ�������᳡
 * @param[in]  confId 				���� ID
 * @param[in]  siteUris 			׼�����еĻ᳡�б�
 * @return      resultCode			�������������˵�����£�
 *										ָ���Ĳ��ֻ᳡�����ڣ����᷵�ش����롣
 *										ָ���᳡ȫ�������ڣ��򷵻ػ᳡�����ڵĴ����롣
 *										ָ���Ļ᳡�Ѿ������Ѿ����ں���״̬���򲻽��к��в�����
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL connectSitesEx(const std::string &confId, const list<std::string> &siteUris);


/**************************************************
 * @fn         disconnectSitesEx
 * @brief     �Ͽ�ָ�������һ�������᳡
 * @param[in]  confId 				���� ID
 * @param[in]  siteUris 			׼���Ͽ��Ļ���URI�б�
 * @return      resultCode			�������������˵�����£�
 *										ָ���Ĳ��ֻ᳡�����ڣ����᷵�ش����롣
 *										ָ���᳡ȫ�������ڣ��򷵻ػ᳡�����ڵĴ����롣
 *										ָ���Ļ᳡�Ѿ��뿪���飬�򲻽��жϿ�������
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL disconnectSitesEx(const std::string &confId, const list<std::string> &siteUris);

/**************************************************
 * @fn         delScheduledConfEx
 * @brief     ɾ��ԤԼ����&��������
 * @param[in]  confId 				���� ID
 * @param[in]  beginTime 			���鿪ʼʱ�䡣����˵�����£�
 *										�������ڻ����еĵ������飬����Ҫ�ṩ��������Ŀ�ʼʱ�䡣
 *										ɾ��������ͨ���飬�����������ڻ��飬����Բ������롣
 * @return      resultCode			�������������˵�����£�
 *										�÷�����δ�ٿ����Ѿ��ٿ��Ļ��鶼��Ч��
 *										�Ѿ��ٿ��Ļ���ִ�и÷����󣬻��齫��������
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL delScheduledConfEx(const std::string &confId, const SYSTEMTIME &beginTime);

/**************************************************
 * @fn         queryMultiPointCDREx
 * @brief     ��ѯ���CDR����
 * @param[in]  queryConfig 			���CDR������ѯ����
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ���cdr����ѯ�Ķ��CDR�������ݣ�pageInfo�������ѯ����ķ�ҳ��Ϣ
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<QueryMultiPointCDRExResponse> __SDK_CALL queryMultiPointCDREx(const MultiPointCDRQueryConfigEx &queryConfig);

/**************************************************
 * @fn         queryPointToPointCDREx
 * @brief     ��ѯ��Ե�CDR����
 * @param[in]  queryConfig 			��Ե�CDR������ѯ����
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ���cdr����ѯ�ĵ�Ե�CDR�������ݣ�pageInfo�������ѯ����ķ�ҳ��Ϣ
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<QueryPointToPointCDRExResponse> __SDK_CALL queryPointToPointCDREx(const PointToPointCDRQueryConfigEx &queryConfig);


/**************************************************
 * @fn         queryAdhocConfFreeBusyEx
 * @brief     ��ѯAdhoc����æ��״̬
 * @param[in]  confAccessCodes 		Ad hoc���������б�����ͬʱ��ѯ���Ad hoc��æ��״̬
 * @param[in]  beginTime 			��ѯ��ʼʱ�䡣��ʽ�磺2013-05-07T22:46:31.235+08:00
 *									2013-05-07T22:46:31.235Ϊ��������ʱ�䣨GMTʱ�䣩��+08:00Ϊ�й���½��GMT��ʱ��
 * @param[in]  duration 			��ѯ���ʱ�����磺P0Y0M0DT1H0M0.000S����PT1H����ʾ1Сʱ������PTΪ��־λ��YMDHMS�ֱ����������ʱ����
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ������Ad hoc�����æ��״̬��Ϣ�����ָ����Ad hoc���鲻���ڣ����Ӧ��Ad hoc����û��æ��״̬
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> __SDK_CALL queryAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration);


/**************************************************
 * @fn         synchAdhocConfFreeBusyEx
 * @brief     ��ѯAdhoc����æ��״̬�仯������
 * @param[in]  confAccessCodes 		Ad hoc���������б�����ͬʱ��ѯ���Ad hoc��æ��״̬
 * @param[in]  beginTime 			��ѯ��ʼʱ�䡣��ʽ�磺2013-05-07T22:46:31.235+08:00
 *									2013-05-07T22:46:31.235Ϊ��������ʱ�䣨GMTʱ�䣩��+08:00Ϊ�й���½��GMT��ʱ��
 * @param[in]  duration 			��ѯ���ʱ�����磺P0Y0M0DT1H0M0.000S����PT1H����ʾ1Сʱ������PTΪ��־λ��YMDHMS�ֱ����������ʱ����
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	������������Ad hoc�����æ��״̬��Ϣ�����ָ����Ad hoc���鲻���ڣ����Ӧ��Ad hoc����û��æ��״̬
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<AdhocConfFreeBusyStateEx>> __SDK_CALL synchAdhocConfFreeBusyEx(const list<std::string> &confAccessCodes, const SYSTEMTIME &beginTime, const std::string &duration);


/**************************************************
 * @fn         queryAdhocConferencesEx
 * @brief     ��ѯAdhoc���͵Ļ���ģ���б�
 * @param[in]  queryConfig 			��ѯAd hoc����ʱʹ�õĹ��ˡ����򡢷�ҳ�������������ʹ�õ��ֶΡ��������ͣ����˷�ʽ
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ���adhocConferences��������ϲ�ѯ������Ad hoc�����б�pageInfo�������ѯ����ķ�ҳ��Ϣ
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<QueryAdhocConferenceExResponse> __SDK_CALL queryAdhocConferencesEx(const QueryConfigEx &queryConfig);

/**************************************************
 * @fn         	queryConfSiteMCUEx
 * @brief     	��ѯָ�������еĻ᳡����MCU
 * @param[in]  	confId 				���� ID
 * @param[in]  	siteUris 			׼����ѯ�Ļ᳡�б������ѯ�б�Ϊ�գ����ʾ��ѯ���������У��к����Uri�ģ��᳡��MCU
 * @param[in]  	beginTime 			��ѡ�����鿪ʼʱ�䡣���ڲ�ѯ���ڻ����еĵ������顣�����ڻ��鲻����ʱ�䣬�򷵻����ڻ����е�һ������Ļ᳡����MCU��Ϣ��
 *									�������ͨ���飬������ÿա�
 *									��ʽ�磺2013-05-07T22:46:31.235+08:00��2013-05-07T22:46:31.235Ϊ��������ʱ�䣨GMTʱ�䣩��+08:00Ϊ�й���½��GMT��ʱ�
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	������������ػ᳡����MCU��Ϣ��
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<SiteMCUEx>> __SDK_CALL queryConfSiteMCUEx(const std::string &confId, const list<std::string> &siteUris, const SYSTEMTIME &beginTime);

/**************************************************
 * @fn         	getContinuousPresenceInfoEx
 * @brief     	��ѯ�໭��ģʽ��Դ��
 * @param[in]  	confId 				���� ID
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	���������targets���������֧�ֵĶ໭�����ͣ������ʽ��ο������ö໭��������ӿ��е�target������
 *									cpResource���������໭����Դ������ֵ����ͬʱ�ж��ٸ���ͬ���ӻ������
 *									supportCPModes�������ǰ������֧�ֵĶ໭��ģʽ�б�
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<GetContinuousPresenceInfoResponseEx> __SDK_CALL getContinuousPresenceInfoEx(const std::string &confId);

/**************************************************
 * @fn         	getContinuousPresenceParamEx
 * @brief     	��ȡָ������Ķ໭�����
 * @param[in]  	confId 				���� ID
 * @param[in]  	target 				��ȡ�Ķ໭�����ͣ������ʽ��ο����ö໭������ӿ��е�target�����������ȡ�Ļ��鲻֧��ָ�������ͣ�������ʧ����ʾ
 * @return     	response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	���������presenceMode���໭��ģʽ��
 *									subPics���ӻ���᳡��ʶ˳���б�
 * @attention  ��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<GetContinuousPresenceParamResponseEx> __SDK_CALL getContinuousPresenceParamEx(const std::string &confId, const std::string &target);

/**************************************************
 * @fn         	setVideoSourceEx
 * @brief     	����ָ���᳡����ƵԴ
 * @param[in]  	confId 				���� ID
 * @param[in]  	siteUri 			�᳡��ʶ
 * @param[in]  	videoSourceUri 		��ƵԴ���ڻ᳡��ʶ
 * @param[in]  	isLock		 		�Ƿ�������ƵԴ(�ֶ��ݲ�֧��)
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setVideoSourceEx(const std::string &confId, const std::string &siteUri, const std::string &videoSourceUri, int isLock);

/**************************************************
 * @fn         	setAudioSwitchEx
 * @brief     	���û���������л�
 * @param[in]  	confId 				���� ID
 * @param[in]  	switchGate 			�����л�����ֵ��ȡֵ��ΧΪ0��100��
 *									������������л�ʱ����Ϊ0����ʾ����Ĭ��ֵ��ǰ�������ʷ���ã�������ǿ�ȴﵽ���úõ���ֵʱ���᳡ͼ�񽫱��㲥��
 *									�ر������л�ʱ���ò����ɲ����롣
 * @param[in]  	isSwitch 			�Ƿ����������л�������˵�����£�
 *										1�����������л�
 *										0���ر������л�
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setAudioSwitchEx(const std::string &confId, int switchGate, int isSwitch);

/**************************************************
 * @fn         	setBroadcastSiteEx
 * @brief     	���ù㲥�᳡
 * @param[in]  	confId 				���� ID
 * @param[in]  	siteUri 			�᳡��ʶ
 * @param[in]  	isBroadcast 		ȡֵ˵�����£�
 *										0����ʼ�㲥�᳡
 *										1��ֹͣ�㲥�᳡
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setBroadcastSiteEx(const std::string &confId, const std::string &siteUri, int isBroadcast);


/**************************************************
 * @fn         	setBroadcastContinuousPresenceEx
 * @brief     	���ù㲥�໭��
 * @param[in]  	confId 				���� ID
 * @param[in]  	isBroadcast 		ȡֵ˵�����£�
 *										0����ʼ�㲥�᳡
 *										1��ֹͣ�㲥�᳡
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setBroadcastContinuousPresenceEx(const std::string &confId, int isBroadcast);

/**************************************************
 * @fn         	setSitesMuteEx
 * @brief     	ָ���᳡����
 * @param[in]  	confId 				���� ID
 * @param[in]  	siteUris 			�᳡ URI �б�
 * @param[in]  	isMute 				�Ƿ������ȡֵ˵�����£�
 *										0������
 *										1��������
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setSitesMuteEx(const std::string &confId, const list<std::string> &siteUris, int isMute);

/**************************************************
 * @fn         	setSitesQuietEx
 * @brief     	ָ���᳡����
 * @param[in]  	confId 				���� ID
 * @param[in]  	siteUris 			�᳡ URI �б�
 * @param[in]  	isQuiet 			�Ƿ�����ȡֵ˵�����£�
 *										0������
 *										1��������
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setSitesQuietEx(const std::string &confId, const list<std::string> &siteUris, int isQuiet);


/**************************************************
 * @fn         	setContinuousPresenceEx
 * @brief     	���ö໭�����
 * @param[in]  	confId 				���� ID
 * @param[in]  	target 				�໭���ʶ��ȡֵ˵�����£�
 *										�մ�������໭��
 *										0����һ���Ĭ�ϵ�����໭��
 *										N����N��໭�棨�ݲ�֧�֣�
 *										(siteUri)����(01010086)��(sip:test@huawei.com)��ÿ�˿ڶ໭��(ͬһ��������ÿ���᳡���Թۿ���ͬ�Ķ໭��
 *									˵�������ȡֵ��siteUri����Ҫ�������¸�ʽ��(siteUri)�����Ժ͵�N��໭�����֡�ͬʱ��Ҫע��ֻ��9ϵ�е�MCU֧��ÿ�˿ڶ໭�档
 * @param[in]  	presenceMode 		�໭��ģʽ
 * @param[in]  	subPics 			�ӻ���᳡��ʶ˳���б�
 *									˵�������ֶ����������ӻ����ڶ໭���е�����˳������໭��ģʽΪ2��subPicsΪ{��01010086��,��01010010��}�����ʾ�����ҵĻ���Ϊ�᳡01010086�ͻ᳡01010010��
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setContinuousPresenceEx(const std::string &confId, const std::string &target, int presenceMode, const list<std::string> &subPics);

/**************************************************
 * @fn         	requestConfChairEx
 * @brief     	������ϯ
 * @param[in]  	confId 				���� ID
 * @param[in]  	chairmanUri 		��ϯ�᳡��ʶ��
 *									˵���� 
 *										��������������᳡��ֻ����������Ϊ��ϯ��
 *										��ϯ�᳡�ɽ��е������ԵȲ�����
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL requestConfChairEx(const std::string &confId, const std::string &chairmanUri);

/**************************************************
 * @fn         	releaseConfChairEx
 * @brief     	�ͷ���ϯ
 * @param[in]  	confId 				���� ID
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL releaseConfChairEx(const std::string &confId);

/**************************************************
 * @fn         	setFloorEx
 * @brief     	ָ���᳡���ԣ��������ԣ�
 * @param[in]  	confId 				���� ID
 * @param[in]  	siteUri 			��ָ�����ԵĻ᳡URI
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setFloorEx(const std::string &confId, const std::string &siteUri);

/**************************************************
 * @fn         	setConfSiteVolumeEx
 * @brief     	���û᳡����ֵ
 * @param[in]  	confId 				���� ID
 * @param[in]  	siteVolumes 		���û᳡������ֵ
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setConfSiteVolumeEx(const std::string &confId, const list<SiteVolumeEx> &siteVolumes);

/**************************************************
 * @fn         	displayConfSiteLocalVideoEx
 * @brief     	�򿪻����л᳡����Ƶ
 * @param[in]  	confId 				���� ID
 * @param[in]  	siteUris	 		����Ƶ�᳡��URI�б�
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL displayConfSiteLocalVideoEx(const std::string &confId, const list<std::string> &siteUris);


/**************************************************
 * @fn         	hideConfSiteLocalVideoEx
 * @brief     	�رջ����л᳡����Ƶ
 * @param[in]  	confId 				���� ID
 * @param[in]  	siteUris	 		�ر���Ƶ�᳡��URI�б�
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL hideConfSiteLocalVideoEx(const std::string &confId, const list<std::string> &siteUris);

/**************************************************
 * @fn         	lockPresentationEx
 * @brief     	������ʾ������
 * @param[in]  	confId 				���� ID
 * @param[in]  	siteUri		 		�����������ƵĻ᳡URI
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL lockPresentationEx(const std::string &confId, const std::string &siteUri);


/**************************************************
 * @fn         	unlockPresentationEx
 * @brief     	������ʾ������
 * @param[in]  	confId 				���� ID
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL unlockPresentationEx(const std::string &confId);


/**************************************************
 * @fn         	addSiteInfoEx
 * @brief     	��ӻ᳡��Ϣ
 * @param[in]  	orgId				׼�����᳡��ӵ�����֯�ڵ��ID
 * @param[in]  	siteInfo			׼����ӵĻ᳡����
 *									˵�������汾ֻ֧����ӵĻ᳡����Ϊ��H323��SIP���֣��Ҷ�������᳡��URI���ͱ���һ�£��������3������᳡����3��URI����ȫ�Ǻ��룬����ȫ��IP������ȫ��URI��
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL addSiteInfoEx(const std::string &orgId, const TerminalInfoEx& siteInfo);

/**************************************************
 * @fn         	editSiteInfoEx
 * @brief     	�༭�᳡��Ϣ
 * @param[in]  	siteInfo			׼���޸ĵĻ᳡����
 *									˵�������汾ֻ֧����ӵĻ᳡����Ϊ��H323��SIP���֣��Ҷ�������᳡��URI���ͱ���һ�£��������3������᳡����3��URI����ȫ�Ǻ��룬����ȫ��IP������ȫ��URI��
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL editSiteInfoEx(const TerminalInfoEx& siteInfo);


/**************************************************
 * @fn         	deleteSiteInfoEx
 * @brief     	ɾ���᳡��Ϣ
 * @param[in]  	siteUris			׼��ɾ���᳡��URI��
 *									��������������᳡��ֻ��Ҫ��д������ʶ���ɡ�
 * @return     	resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL deleteSiteInfoEx(const list<std::string> &siteUris);


/**************************************************
 * @fn         	querySitesInfoEx
 * @brief     	��ѯ�᳡��Ϣ
 * @param[in]  	queryConfig			��ѯԤ����᳡ʱʹ�õĹ��ˡ����򡢷�ҳ����
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ���sites������ݲ�ѯ���������ز�ѯ�Ļ᳡��Ϣ�б�pageInfo�������ѯ����ķ�ҳ��Ϣ
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<QuerySitesInfoExResponse> __SDK_CALL querySitesInfoEx(const QueryConfigEx &queryConfig);

/**************************************************
 * @fn         	queryMCUInfoEx
 * @brief     	��ѯMCU��Ϣ�б�
 * @param[in]  	queryConfig			��ѯMCU��Ϣʱʹ�õĹ��ˡ����򡢷�ҳ����
 *									�������ʹ�õ��ֶΡ��������ͣ����˷�ʽ�ο�ǰ���������
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ���mcus��������ϲ�ѯ������MCU�б�pageInfo�������ѯ����ķ�ҳ��Ϣ
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<QueryMCUInfoExResponse> __SDK_CALL queryMCUInfoEx(const QueryConfigEx &queryConfig);

/**************************************************
 * @fn         	queryMCUFutureResourceEx
 * @brief     	��ѯδ��ʱ��MCU����Դռ�����
 * @param[in]  	mcus				����ѯ��Դ��MCU ID�б�
 * @param[in]  	beginTime			��ѯ��ʼʱ�䡣��ʽ�磺2013-05-07T22:46:31.235+08:00
 *									2013-05-07T22:46:31.235Ϊ��������ʱ�䣨GMTʱ�䣩��+08:00Ϊ�й���½��GMT��ʱ�
 * @param[in]  	duration			��ѯ���ʱ�����磺P0Y0M0DT1H0M0.000S����PT1H����ʾ1Сʱ������PTΪ��־λ��YMDHMS�ֱ����������ʱ���롣
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ���MCUδ��ʱ����Դռ������
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<MCUResourceEx>> __SDK_CALL queryMCUFutureResourceEx(const list<int> &mcus, const SYSTEMTIME &beginTime, const std::string &duration);

/**************************************************
 * @fn         	queryOrganizationEx
 * @brief     	��ѯϵͳ����֯�ڵ�
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	���ϵͳ��������֯�ڵ���Ϣ
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<OrganizationItemEx>>  __SDK_CALL queryOrganizationEx();

/**************************************************
 * @fn         	requestChairEx
 * @brief     	������ϯ
 * @param[in]  	siteUri				�᳡��ʶ
 * @return     	resultCode			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL requestChairEx(const std::string &siteUri);

/**************************************************
 * @fn         	releaseChairEx
 * @brief     	�ͷ���ϯ
 * @param[in]  	siteUri				�᳡��ʶ
 * @return     	resultCode			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL releaseChairEx(const std::string &siteUri);


/**************************************************
 * @fn         	queryConfCtrlPwdEx
 * @brief     	��ѯ�᳡���ڻ����Ƿ��������
 * @param[in]  	siteUri				�᳡��ʶ
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	���ػ����Ƿ�������롣ȡֵ˵�����£�0�������ڣ�1������
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<int> __SDK_CALL queryConfCtrlPwdEx(const std::string &siteUri);

/**************************************************
 * @fn         	queryBroadInfoEx
 * @brief     	��ѯָ���᳡���ڻ�����¼����ֱ������Ϣ
 * @param[in]  	siteUri				�᳡��ʶ
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ�����ֱ��״̬��¼��״̬
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<BroadInfoEx> __SDK_CALL queryBroadInfoEx(const std::string &siteUri);

/**************************************************
 * @fn         	setRecordBroadEx
 * @brief     	����������ֹͣ¼��
 * @param[in]  	siteUri				�᳡��ʶ
 * @param[in]  	action				ȡֵ˵�����£�0����startRecord������ʼ¼������1����stopRecord����ֹͣ¼����
 * @return      resultCode			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setRecordBroadEx(const std::string &siteUri, int action);

/**************************************************
 * @fn         	setDirectBroadEx
 * @brief     	����������ֱֹͣ��
 * @param[in]  	siteUri				�᳡��ʶ
 * @param[in]  	action				ȡֵ˵�����£�0����startDirect������ʼֱ������1����stopDirect����ֱֹͣ����
 * @return      resultCode			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setDirectBroadEx(const std::string &siteUri, int action);


/**************************************************
 * @fn         	isConnectAuxSourceEx
 * @brief     	��ѯ�Ƿ���븨������Դ
 * @param[in]  	siteUri				�᳡��ʶ
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ������Ƿ���븨������Դ��ȡֵ˵�����£�0��δ���룻1������
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<int> __SDK_CALL isConnectAuxSourceEx(const std::string &siteUri);

/**************************************************
 * @fn         	isSendAuxStreamEx
 * @brief     	��ѯ��ǰ�Ƿ����ڷ��͸���
 * @param[in]  	siteUri				�᳡��ʶ
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ������Ƿ����ڷ��͸�����ȡֵ˵�����£�0��û�з��͸�����1�����ڷ��͸���
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<int> __SDK_CALL isSendAuxStreamEx(const std::string &siteUri);

/**************************************************
 * @fn         	isReceiveRemAuxStrmEx
 * @brief     	��ѯָ���᳡�Ƿ����ڽ���Զ�˸���
 * @param[in]  	siteUri				�᳡��ʶ
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ������Ƿ����ڽ���Զ�˸�����ȡֵ˵�����£�0��δ�ڽ���Զ�˸�����1�����ڽ���Զ�˸���
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<int> __SDK_CALL isReceiveRemAuxStrmEx(const std::string &siteUri);


/**************************************************
 * @fn         	setAuxStreamEx
 * @brief     	���ÿ�ʼ��ֹͣ���͸���
 * @param[in]  	siteUri				�᳡��ʶ
 * @param[in]  	controlCode			������ʼ���ͼ�ֹͣ���ͷ�ʽ��ȡֵ˵�����£�0����ʼ���ͣ�1��ֹͣ����
 * @return      resultCode			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setAuxStreamEx(const std::string &siteUri, int controlCode);

/**************************************************
 * @fn         	queryAuxStreamSourcesEx
 * @brief     	��ȡ������ƵԴ�б�
 * @param[in]  	siteUri				�᳡��ʶ
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ����ظ�����ƵԴ�б�
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<AuxStreamInfoEx>> __SDK_CALL queryAuxStreamSourcesEx(const std::string &siteUri);


/**************************************************
 * @fn         	queryVideoOutSrcStateEx
 * @brief     	��ѯ��Ƶ����ڽ�����ƵԴ״̬
 * @param[in]  	siteUri				�᳡��ʶ
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ�������Ƶ����ڽ�����ƵԴ��Ϣ
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<VideoSourcesInfoEx>> __SDK_CALL queryVideoOutSrcStateEx(const std::string &siteUri);

/**************************************************
 * @fn         	ctrlCameraEx
 * @brief     	��������Ʋ���
 * @param[in]  	siteUri				�᳡��ʶ
 * @param[in]  	cameraControl		����ͷ���Ʋ������������˵�����£�camState�������λ�ã�camAction������������camPos�������Ԥ��λ�úţ�camSrc������� id
 * @return      resultCode			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL ctrlCameraEx(const std::string &siteUri, const CameraControlEx &cameraControl);

/**************************************************
 * @fn         	setMainAuxStreamSourcesEx
 * @brief     	����������ƵԴ��������ƵԴ
 * @param[in]  	siteUri				�᳡��ʶ
 * @param[in]  	localMainSrcs		����������ƵԴ
 * @param[in]  	localAuxSrc			���˸�����ƵԴ
 * @return      resultCode			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setMainAuxStreamSourcesEx(const std::string &siteUri, const list<int> &localMainSrcs, int localAuxSrc);

/**************************************************
 * @fn         	queryMainStreamSourcesEx
 * @brief     	��ȡ������ƵԴ�������б������
 * @param[in]  	siteUri				�᳡��ʶ
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	�����ɹ����ظ�����ƵԴ�б�
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<AuxStreamInfoEx>> __SDK_CALL queryMainStreamSourcesEx(const std::string &siteUri);

/**************************************************
 * @fn         	setVideoOutSrcEx
 * @brief     	�����������ʾ����
 * @param[in]  	siteUri				�᳡��ʶ
 * @param[in]  	hdOut				������ƵԴ����� ID��0��HD1��1��HD2��2��HD3��3��HD4��4��HD5��5��SD1��6��SD2
 * @param[in]  	videoSrc			ȡֵ˵�����£�0����local_main����������������1����local_aux�������ظ�������2����remote_main����Զ����������3����remote_aux����Զ�˸�����
 * @return      resultCode			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL setVideoOutSrcEx(const std::string &siteUri, int hdOut, int videoSrc);


/**************************************************
 * @fn         	querySiteVersionInfoEx
 * @brief     	��ѯ��ȡ�ն��ͺ�/�汾��Ϣ
 * @param[in]  	siteUri				�᳡��ʶ
 * @return      response.code 		�ɹ�����0��ʧ�ܷ��ش�����
 *				response.result 	��������ɹ������ն��ͺ�/�汾��Ϣ
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<SiteDeviceVersionInfoEx> __SDK_CALL querySiteVersionInfoEx(const std::string &siteUri);

/**************************************************
 * @fn         	enablePushEx
 * @brief     	�������͹���
 * @param[in]  	pushMode			���ͻ���:0: NONE 1: PULL 2: CALLBACK
 * @param[in]  	extendParameter		None��Pullģʽ�£����á� Pushģʽ�£��ṩSMC 2.0�ص���URI��ַ
 * @return      resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL enablePushEx(int pushMode, const std::string &extendParameter);

/**************************************************
 * @fn         	subscribeEx
 * @brief     	�������͹���
 * @param[in]  	subscribeInfos		���Ļ�ȡ��������Ϣ���б�
 * @return      resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL subscribeEx(list<SubscribeInfoEx *> subscribeInfos);


/**************************************************
 * @fn         	queryNotificationEx
 * @brief     	��ȡ֪ͨ��Ϣ
 * @param[in]  	��
 * @return      resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API TPSDKResponseEx<list<NotificationEx *>> __SDK_CALL queryNotificationEx();

/**************************************************
 * @fn         	releasequeryNotificationMemery
 * @brief     	�ͷŽӿ�queryNotificationEx������ڴ�
 * @param[in]  	listNotificationEx  ��Ϣ��ָ���б�
 * @return      resultCode 			�ɹ�����0��ʧ�ܷ��ش�����
 * @attention  	��
 * @par ʾ��
 * @code
 * @endcode
****************************************************/
ESDK_TPNATIVE_API int __SDK_CALL releasequeryNotificationMemery(list<NotificationEx *> &listNotificationEx);

#endif