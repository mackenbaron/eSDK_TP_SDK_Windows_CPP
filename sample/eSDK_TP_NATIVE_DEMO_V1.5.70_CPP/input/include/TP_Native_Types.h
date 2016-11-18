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
 * @file  TP_Native_Types.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief TP Native Types
 * @details declare data struct, enum value and  macro define
 * @author p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 
****************************************************/

#ifndef _TP_NATIVE_TYPES_H_
#define _TP_NATIVE_TYPES_H_

#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

const int TP_D_NAME_LEN = 64;
const int TP_D_URI_LEN = 128;
const int TP_D_PWD_LEN = 32;
const int TP_D_IP_LEN = 64;
const int TP_D_INTERFACE_LEN = 64;
const int TP_D_KEY_LEN = 64;
const int TP_D_VALUE_LEN = 128;
const int TP_D_SOAPACTION_LEN = 256;
const int TP_D_COOKIE_LEN = 256;
const int TP_D_CONTENTTYPE_LEN = 128;



const int MINFreeBusyState = 0;
const int MAXFreeBusyState = 2;

const int MAX_SWITCHGATE_VALUE=100;
const int MIN_SWITCHGATE_VALUE=0;

const int MIN_PRESENCE_MODE_VALUE=0;
const int MAX_PRESENCE_MODE_VALUE=49;


template <class T>struct  TPSDKResponseEx
{
	int resultCode;
	T result;
};



#define DealPointUnusedWarn(unusedPoint) \
	if(unusedPoint!=NULL){}


// ��������
#define PROTOCOL_VERSION						0x0100				// Э��汾����ǰ�汾��Ϊ0x0100
#define INVALID_MSG_TYPE						(UINT16)(-1)		// ��Ϣ���ͣ��Ƿ�����
#define XML_CONTEXT_TYPE						0x0001				// �ֶ����Ͷ��壬��0x0001��Ϊxml�ı��ֶ�

#define BUFFER_SIZE								1024				// SSL_readһ������ȡ�ֽ���

#define RSP_MSG_FLAG							0xF000				// respond��Ϣ��־

#define SESSIONID_LENGTH						32					// sessionid����

#define KEEPALIVE_TIME							6					// ����ʱ��  ��λ����
#define MAX_TIMEOUT_COUNT						5					// ���ʱ����
//////////////////////////////////////////////////////////////////////////


//SDK������
typedef enum tagTP_E_RET_CODE
{
	TP_E_RET_CODE_SUCCESS=0,
	TP_E_RET_CODE_FAIL=1,
	TP_E_RET_CODE_INVALID_PARA=2,
	TP_E_RET_CODE_URL_EMPTY=3,
	TP_E_RET_CODE_LOST_PARA=4,
	TP_E_RET_CODE_SEND_REQUEST_FAILED=5,
	TP_E_RET_CODE_INVALID_RESPONSE=6,
	TP_SDK_ERR_SUCCESS = 0,					// �ɹ�
	TP_SDK_ERR_GENERAL=2130000020,          //native�����쳣
	// 2135102001 - 2135102100 ��ͨ����
	TP_SDK_ERR_FAILED = 2135102001,			// ͨ��ʧ��
	TP_SDK_ERR_INVALID_PARAM,					// �Ƿ����
	TP_SDK_ERR_NULL_POINTER,					// ��ָ�����
	TP_SDK_ERR_CREATE_OBJECT,                 // ��������ʧ��
	TP_SDK_ERR_CREATE_DIRECTORY,              // ����Ŀ¼ʧ��
	TP_SDK_ERR_LOG_INIT,                      // ��־ģ���ʼ��ʧ��
	TP_SDK_ERR_SDL_INIT,                      // SDL��ʼ��ʧ��

	// 2135102101 - 2135102200 �������
	TP_SDK_ERR_WSA_START_UP = 2135102101,     // ��ʼ���׽��ֶ�̬��ʧ��
	TP_SDK_ERR_CONNECT_SERVER,                // ���ӷ�����ʧ��
	TP_SDK_ERR_SSL_CONNECT,                   // SSL����ʧ��
	TP_SDK_ERR_SEND_MSG,                      // ��������ʧ��
	TP_SDK_ERR_WAIT_TIME_OUT,                 // �ȴ���ʱ
	TP_SDK_ERR_SERVER_NOT_RUNNING,            // ����δ����

	// 2135102201 - 2135102300 �ļ���������
	TP_SDK_ERR_CONFIG_FILE_LOAD = 2135102201,	// ����ini�����ļ�ʧ��
	TP_SDK_ERR_CONFIG_FILE_READ,				// ��ȡini�����ļ�ʧ��
	TP_SDK_ERR_CONFIG_FILE_WRITE,				// д��ini�����ļ�ʧ��

	//2135102301 - 2135102400 XML��������
	TP_SDK_ERR_XML_CONSTRUCT = 2135102301,	// ����XML�ַ���ʧ��
	TP_SDK_ERR_XML_PARSE,						// ����XML�ַ���ʧ��
	TP_SDK_ERR_XML_FIND_ELEM,					// ����XML�ڵ�ʧ��
	TP_SDK_ERR_XML_GET_ELEM_VALUE,		    // ��ȡXML�ڵ�ʧ��


	TP_SDK_ERR_SERVICE_EXPIRE	= 2135103009   // ������ڣ��ͻ�����Ҫ��������
}TP_E_RET_CODE;

const int TP_D_CONFID_MAX_LEN = 128;
const int TP_D_CONF_NAME_MAX_LEN = 256;
const int TP_D_TIME_MAX_LEN	= 32;
const int TP_D_ACCESSCODE_MAX_LEN = 8;
const int TP_D_RATE_MAX_LEN = 10;
const int TP_D_SITE_URI_MAX_LEN = 256;
const int TP_D_BILLCODE_MAX_LEN = 32;
const int TP_D_EMAIL_MAX_LEN = 256;
const int TP_D_CONTENT_MAX_LEN = 512;
const int TP_D_SITES_NUM = 64;
const int TP_D_TIMEZONE_MAX_LEN = 32;

const int TP_D_ELEM_OPTIONAL_FLAG = 0;
const int TP_D_ELEM_MUST_FLAG = 1;

const int TP_D_CIRCUIT_TYPE_MAX_VALUE=11;
const int TP_D_CIRCUIT_TYPE_MIN_VALUE=0;

const int TP_D_CAMERA_ACTION_MAX_VALUE=23;
const int TP_D_CAMERA_ACTION_MIN_VALUE=0;

const int TP_D_HD_MIN_VALUE=0;
const int TP_D_HD_MAX_VALUE=6;

const int TP_D_VIDEO_SRC_MIN_VALUE=0;
const int TP_D_VIDEO_SRC_MAX_VALUE=3;

const int TP_D_SCHEDULED_CONF_SUBSCRIBE_TYPE=0;
const int TP_D_ONGOING_CONF_SUBSCRIBE_TYPE=1;

const int TP_D_OVERFLOW_NOTIFICATION_TYPE=0;
const int TP_D_SCHEDULED_CONF_NOTIFICATION_TYPE=1;
const int TP_D_ONGOING_CONF_NOTIFICATION_TYPE=2;

const int TP_D_CONFERENCE_STATUS_TYPE=0;
const int TP_D_SITE_STATUS_TYPE = 1;

typedef struct tagTP_S_CONFERENCE_NOTICEEX
{
	std::string email;
	std::string content;
	std::string telephone;

}ConferenceNoticeEx;

//�᳡��Ϣ
typedef struct tagTP_S_SITE_INFOEX
{
	std::string name;										//�᳡����
	std::string uri;										//�᳡��ʶ
	int type;												//�᳡����
	int from;												//�᳡��Դ
	int dialingMode;										//���з�ʽ
	std::string rate;										//����
	int videoFormat;										//��Ƶ��ʽ
	int videoProtocol;										//��ƵЭ��
	int isLockVideoSource;									//�Ƿ������᳡��ƵԴ
	int participantType;									//�������
	int status;												//�᳡״̬
	std::string dtmf;										//���β�����Ϣ
	tagTP_S_SITE_INFOEX()
	{
		type = 0;
		from = 0;
		dialingMode = 0;
		videoFormat = 0;
		videoProtocol = 0;
		isLockVideoSource = 0;
		participantType = 0;
		status = 0;
		dtmf = "0";
	}
}SiteInfoEx;

//��ͨ������Ϣ
typedef struct tagTP_S_CONFERENCE_INFOEX 
{
	std::string confId;										//���� ID����ϵͳ�Զ����䡣
	std::string name;										//��������
	SYSTEMTIME beginTime;									//���鿪ʼʱ�䡣
	std::string duration;									//����ʱ�����磺P0Y0M0DT1H0M0.000S����PT1H����ʾ1Сʱ��
	std::string accessCode;									//��������롣����Ϊ���ָ�ʽ���ַ������磺075560166��
	std::string password;									//����������롣ֻ֧��0��9�����֡�����Ϊ6λ���ֵ����롣
	int mediaEncryptType;									//ý�������ܷ�ʽ��
	int auxVideoFormat;										//������Ƶ��ʽ��
	int auxVideoProtocol;									//������ƵЭ�飬ȡֵ˵���μ���Native-C++��VideoProtocol����ƵЭ�飩��
	int cpResouce;											//�໭����Դ����
	std::string rate;										//���ʡ���ʽΪ������ֵk/M�����硰1920k��
	int isRecording;										//�����Ƿ�֧��¼�ƹ��ܣ�������Ĭ�ϲ�֧��
	std::string recorderAddr;								//ֱ����ַ
	int isLiveBroadcast;									//¼�������Ƿ�֧��ֱ�����ܣ�������Ĭ�ϲ�֧��
	int presentation;										//��ʾ��ʽ
	std::string chairmanPassword;							//��ϯ���������������롣ֻ֧��0��9�����֡�����Ϊ6λ���֡�
	int status;												//����״̬
	std::string billCode;									//�Ʒ��루��ѡ��
	std::string mainSiteUri;								//�������᳡����ѡ��
	ConferenceNoticeEx conferenceNotice;					//����֪ͨ��Ϣ����ѡ��
	vector<SiteInfoEx> sites;								//�᳡��Ϣ�б�
	int maxSitesCount;	                                    //���������᷽��
	tagTP_S_CONFERENCE_INFOEX()
	{
		beginTime.wDay=1;
		beginTime.wDayOfWeek = 0;
		beginTime.wHour = 0;
		beginTime.wMilliseconds = 0;
		beginTime.wMinute = 0;
		beginTime.wMonth = 1;
		beginTime.wSecond = 0;
		beginTime.wYear = 1;

		mediaEncryptType = 0;
		auxVideoFormat = 0;
		auxVideoProtocol = 0;
		cpResouce = 0;
		isRecording = 0;
		isLiveBroadcast = 0;
		presentation = 0;
		status = 0;
		maxSitesCount = 0;
	}

}ConferenceInfoEx;

//�᳡������Ϣ
typedef struct tagTP_S_SITE_ACCESS_INFOEX
{
	std::string uri;										//�᳡��ʶ
	std::string confAccessCode;								//��������
	std::string name;										//�᳡����
	SYSTEMTIME beginTime;									//���鿪ʼʱ��
	std::string mcuUri;										//�᳡���� MCU �� Uri����û�� GK �� SIP ������������ֱ�Ӻ��� MCU �ĳ���
	tagTP_S_SITE_ACCESS_INFOEX()
	{
		beginTime.wDay=1;
		beginTime.wDayOfWeek = 0;
		beginTime.wHour = 0;
		beginTime.wMilliseconds = 0;
		beginTime.wMinute = 0;
		beginTime.wMonth = 1;
		beginTime.wSecond = 0;
		beginTime.wYear = 1;
	}

}SiteAccessInfoEx;

//�����Ի�����Ϣ
typedef struct tagTP_S_RECURRENCE_CONF_INFOEX
{
	ConferenceInfoEx base_info;								//��ͨ������Ϣ
	int frequency;											//���ڻ�����������
	int interval;											//��������ڻ��� interval �������0���磺�ò���Ϊ1��frequency Ϊ0ʱ����ÿ�춼�ٿ�һ��
	list<int> weekDays;											//ʹ�� Weekly ��������ʱ���洢�����ա��������ı�ǡ���Ŵ�0��6����ʾ�����ա����������� Monthly ��������ʱ�����ڱ�ʾ�ڼ������ڵ����ڼ����� Daily��������ʱ�������Ϊ�ò�����ֵ��ֵΪnull��������sizeΪ0����ÿһ�춼�����ٿ����飬����ֻ�ڹ������ٿ����飨���������ղ��ٿ����ڻ��飩
	int weekDay;											//ʹMonthlyʱ����ʾ�ڼ�������
	int monthDay;											//ÿ���µĵڼ��죬�� frequency Ϊ Monthly ��������ʱ��Ч
	int count;												//�ظ�����
	SYSTEMTIME endDate;									//��������
	std::string timeZone;									//���ڻ��鱾��ʱ����ʱ���ִ���ʾ����ο�ʱ���б�
	vector<SiteAccessInfoEx> siteAccessInfos;				//�᳡������Ϣ
	tagTP_S_RECURRENCE_CONF_INFOEX()
	{
		frequency = 0;
		interval = 0;
		weekDay = 0;
		monthDay = 0;
		count = 0;
		endDate.wDay=1;
		endDate.wDayOfWeek = 0;
		endDate.wHour = 0;
		endDate.wMilliseconds = 0;
		endDate.wMinute = 0;
		endDate.wMonth = 1;
		endDate.wSecond = 0;
		endDate.wYear = 1;
	}

}RecurrenceConfInfoEx;

//�᳡æ��״̬
typedef struct tagTP_S_FREE_BUSY_STATEEX
{
	SYSTEMTIME startTime;									//��ʼʱ��
	std::string span;										//ʱ���ȡ��磺P0Y0M0DT1H0M0.000S
	int state;												//æ��״̬�����״̬Ϊ���С����Ұ����л��� ID�����ʾ��ʱ��λ��鱻ɾ������᳡�Ѿ����ڸû�����
	std::string confId;										//���� ID
	std::string confName;									//��������
	tagTP_S_FREE_BUSY_STATEEX()
	{
		startTime.wDay=1;
		startTime.wDayOfWeek = 0;
		startTime.wHour = 0;
		startTime.wMilliseconds = 0;
		startTime.wMinute = 0;
		startTime.wMonth = 1;
		startTime.wSecond = 0;
		startTime.wYear = 1;

		state = 0;
	}
}FreeBusyStateEx;

typedef struct tagTP_S_RECORD_STATUSEX
{
	int isSupportLiving;									//�Ƿ�֧��ֱ��
	int isSupportRecording;									//�Ƿ�֧��¼��
	int status;												//״̬
	int isAutoRecordingVideoSource;							//�Ƿ��Զ�¼����ƵԴ
	std::string videoSource;								//��ƵԴ

	tagTP_S_RECORD_STATUSEX()
	{
		isSupportLiving = 0;
		isSupportRecording = 0;
		status = 0;
		isAutoRecordingVideoSource = 0;
	}

}RecordStatusEx;

typedef struct tagTP_S_NOTIFICATION_STATUSEX
{
	int structtype;
}NotificationStatusEx;

//����״̬
typedef struct tagTP_S_CONFERENCE_STATUSEX:NotificationStatusEx
{
	std::string id;											//���� ID
	std::string name;										//��������
	int status;												//����״̬
	std::string chair;										//��ϯ�᳡
	std::string broadcast;									//�㲥�᳡
	std::string speaking;									//���ڷ��ԵĻ᳡���������Ļ᳡��
	std::string presentation;								//���ڷ��͸����Ļ᳡
	int isLock;												//�����Ƿ�����
	int isAudioSwitch;										//�����Ƿ��������л�����
	int switchGate;											//�����л�����ֵ��ȡֵ��ΧΪ0��100
	SYSTEMTIME beginTime;									//���鿪ʼʱ��
	SYSTEMTIME endTime;										//�������ʱ��
	int isLockPresentation;									//�����Ƿ���������������״̬
	std::string lockPresentation;							//�����������ƵĻ᳡
	RecordStatusEx recording;								//��¼״̬
	int conferenceMode;										//����ģʽ��ȡֵ˵�� 0��AUTO 1��CONVERGENT
	tagTP_S_CONFERENCE_STATUSEX()
	{
		structtype = TP_D_CONFERENCE_STATUS_TYPE;

		status = 0;
		isLock = 0;
		isAudioSwitch = 0;
		switchGate = 0;

		beginTime.wDay=1;
		beginTime.wDayOfWeek = 0;
		beginTime.wHour = 0;
		beginTime.wMilliseconds = 0;
		beginTime.wMinute = 0;
		beginTime.wMonth = 1;
		beginTime.wSecond = 0;
		beginTime.wYear = 1;

		endTime.wDay=1;
		endTime.wDayOfWeek = 0;
		endTime.wHour = 0;
		endTime.wMilliseconds = 0;
		endTime.wMinute = 0;
		endTime.wMonth = 1;
		endTime.wSecond = 0;
		endTime.wYear = 1;
		isLockPresentation = 0;
		conferenceMode = 0;
	}
}ConferenceStatusEx;


//��ϸ������Ϣ
typedef struct tagTP_S_ERROR_INFOEX
{
	int errCode;											//������
	std::string description;								//������Ϣ����

	tagTP_S_ERROR_INFOEX()
	{
		errCode = 0;
	}

}ErrorInfoEx;

//�᳡״̬
typedef struct tagTP_S_SITE_STATUSEX:NotificationStatusEx
{
	std::string uri;										//�᳡��ʶ
	std::string name;										//�᳡����
	int status;												//�᳡״̬
	int volume;												//�᳡����ֵ
	std::string videoSource;								//�᳡����ƵԴ
	int isMute;												//�Ƿ����
	int isQuiet;											//�Ƿ���
	int type;												//�᳡����
	ErrorInfoEx callFailedReason;							//����ʧ��ԭ��
	int isLocalVideoOpen;									//�᳡������Ƶ�Ƿ�򿪣��˲����������ʾ��Ƶ���ڴ�״̬
	int participantType;									//������ͣ��ò����ÿձ�ʾ�ն˻᳡����ѡ��
	int screens;											//�᳡�ж���������1��ʱ����ʾ�᳡���������᳡������1����Ϊ�����᳡ʱ���˲����ÿգ���ѡ��

	tagTP_S_SITE_STATUSEX()
	{
		structtype = TP_D_SITE_STATUS_TYPE;
		status = 0;
		volume = 0;
		isMute = 0;
		isQuiet = 0;
		type = 0;
		isLocalVideoOpen = 0;
		participantType = 0;
		screens = 0;
	}

}SiteStatusEx;



//��������Ʋ���
typedef struct tagTP_S_CAMERA_CONTROLEX
{
	int camState;											//���������
	int camAction;											//�������������
	int camPos;												//Ԥ��λ�úţ���camAction����ȡֵ��Ϊ18��19��20ʱ��Ԥ��λ�ſɹ̶�Ϊ255
	int camSrc;												//�����id�����ն�������

	tagTP_S_CAMERA_CONTROLEX()
	{
		camState = 0;
		camAction = 0;
		camPos = 0;
		camSrc = 0;
	}
}CameraControlEx;

//¼��ֱ����Ϣ
typedef struct tagTP_S_BROAD_INFOEX
{
	int directBroad;										//�Ƿ�֧��ֱ��
	int recordBroad;										//�Ƿ�֧��¼��
	int directBroadStatus;									//ֱ��״̬
	int recordBroadStatus;									//¼��״̬

	tagTP_S_BROAD_INFOEX()
	{
		directBroad = 0;
		recordBroad = 0;
		directBroadStatus = 0;
		recordBroadStatus = 0;
	}

}BroadInfoEx;

//��ƵԴ��Ϣ
typedef struct tagTP_S_VideoSourcesInfoEX
{
	int sourcesId;											//��ƵԴ����ֵ
	int sourcesState;										//��Ӧ������Ƿ������ƵԴ
	std::string sourcesName;								//��ƵԴ����

	tagTP_S_VideoSourcesInfoEX()
	{
		sourcesId = 0;
		sourcesState = 0;
	}
}VideoSourcesInfoEx;

//�᳡ָ��ʱ����æ��״̬
typedef struct tagTP_S_SITE_FREE_BUSY_STATEEX
{
	int uri;												//�᳡ URI
	FreeBusyStateEx state;									//�᳡״̬

	tagTP_S_SITE_FREE_BUSY_STATEEX()
	{
		uri = 0;
	}

}SiteFreeBusyStateEx;

//������������Ϣ
typedef struct tagTP_S_AUXSTREAM_INFOEX
{
	int id;													//������������ƵԴ ID
	std::string name;										//������������ƵԴ����

	tagTP_S_AUXSTREAM_INFOEX()
	{
		id = 0;
	}
}AuxStreamInfoEx;

//��˰汾�б�
typedef struct tagTP_S_SITE_MIC_VERSION_MAPEX
{
	std::string micIP;										//Mic IP��ַ
	std::string version;									//Mic �汾��Ϣ
}SiteMicVersionMapEx;

//�᳡����
typedef struct tagTP_S_SITE_VOLUMEEX
{
	std::string siteUri;									//�᳡URI
	int volume;												//����ֵ��С

	tagTP_S_SITE_VOLUMEEX()
	{
		volume = 0;
	}

}SiteVolumeEx;

//�᳡��������
typedef struct tagTP_S_SORT_ITEMEX
{
	int sort;												//����ʽ 0������1������
	int itemIndex;											//��ѯ�����������б�ʶ

	tagTP_S_SORT_ITEMEX()
	{
		sort = 0;
		itemIndex = 0;

	}

}SortItemEx;

//�᳡��������
typedef struct tagTP_S_FILTER_BASEEX
{
	int columnIndex;										//���������������б�ʶ
	//std::string value;										//�������ַ���

	tagTP_S_FILTER_BASEEX()
	{
		columnIndex = 0;
	}

}FilterBaseEx;

typedef struct tagTP_S_STRING_FILTEREX:FilterBaseEx
{
	std::string value;			//�������ַ���
}StringFilterEx;

//ҳ�붨λ����
typedef struct tagTP_S_PAGE_PARAMEX
{
	int numberPerPage;										//ÿҳ�ļ�¼����
	int currentPage;										//��ǰҳ�룬����Ҫ���ص�ҳ��

	tagTP_S_PAGE_PARAMEX()
	{
		numberPerPage = 0;
		currentPage = 0;
	}

}PageParamEx;

//��ҳ��Ϣ
typedef struct tagTP_S_PAGE_INFOEX
{
	int totalPages;											//��ҳ��
	int currentPage;										//��ǰҳ��
	int totalRecords;										//�ܼ�¼��

	tagTP_S_PAGE_INFOEX()
	{
		totalPages = 0;
		currentPage = 0;
		totalRecords = 0;
	}

}PagesInfoEx;


//�᳡��ѯ����
typedef struct tagTP_S_QUERY_CONFIGEX
{

	list<SortItemEx> sortItems;								//����������ϣ�Ŀǰֻ֧�ֵ�������
	list<StringFilterEx> filters;								//����������ϣ�֧�ֶ������������ΪAND��ϵ
	int focusItem;											//��������ID
	PageParamEx pageParam;									//ҳ�붨λ����

	tagTP_S_QUERY_CONFIGEX()
	{
		focusItem = 0;
	}

}QueryConfigEx;

//��ѯ���CDR��������
typedef struct tagTP_S_MULTI_POINT_CDR_QUERY_CONFIGEX
{
	SYSTEMTIME beginTime;									//��ѯ��ʼʱ�䡣��ʽ�磺2013-05-07T22:46:31.235+08:00
	std::string duration;									//��ѯʱ����
	std::string siteUri;									//�᳡URI�����ڲ�ѯָ���᳡�Ķ�㻰������ѡ��
	PageParamEx pageParam;									//ҳ�붨λ��������ָ�����ز�ѯ����ĵڼ�ҳ

	tagTP_S_MULTI_POINT_CDR_QUERY_CONFIGEX()
	{
		beginTime.wDay=1;
		beginTime.wDayOfWeek = 0;
		beginTime.wHour = 0;
		beginTime.wMilliseconds = 0;
		beginTime.wMinute = 0;
		beginTime.wMonth = 1;
		beginTime.wSecond = 0;
		beginTime.wYear = 1;
	}

}MultiPointCDRQueryConfigEx;


//ָ���᳡
typedef struct tagTP_S_CALL_END_POINTEX
{
	int type;												//��������
	std::string siteUri;									//�᳡��ʶ

	tagTP_S_CALL_END_POINTEX()
	{
		type = 0;
	}
}CallEndPointEx;

//��ѯ����CDR��������
typedef struct tagTP_S_POINTTOPOINT_CDR_QUERY_CONFIGEX
{
	SYSTEMTIME beginTime;									//���鿪ʼʱ�䡣��ʽ�磺2013-05-07T22:46:31.235+08:00
	std::string duration;									//ʱ����
	CallEndPointEx endPoint;								//��ѯָ���᳡����ѡ��
	PageParamEx pageParam;									//ҳ�붨λ��������ָ�����ز�ѯ����ĵڼ�ҳ

	tagTP_S_POINTTOPOINT_CDR_QUERY_CONFIGEX()
	{
		beginTime.wDay=1;
		beginTime.wDayOfWeek = 0;
		beginTime.wHour = 0;
		beginTime.wMilliseconds = 0;
		beginTime.wMinute = 0;
		beginTime.wMonth = 1;
		beginTime.wSecond = 0;
		beginTime.wYear = 1;
	}

}PointToPointCDRQueryConfigEx;

//���CDR��������
typedef struct tagTP_S_MULTI_POINT_CDREX
{
	std::string siteName;									//�᳡����
	std::string siteUri;									//�᳡��ʶ
	int siteType;											//�᳡����
	int participantType;									//�᳡�������
	std::string rate;										//����
	SYSTEMTIME startTime;									//���п�ʼʱ�䡣��ʽ�磺2013-05-07T22:46:31.235+08:00
	SYSTEMTIME endTime;										//���н���ʱ�䡣��ʽ�磺2013-05-07T22:46:31.235+08:00
	std::string conferenceName;								//��������
	std::string conferenceId;								//����ID
	std::string conferenceCreater;							//���鴴����
	std::string billCode;									//����Ʒ���

	tagTP_S_MULTI_POINT_CDREX()
	{
		siteType = 0;
		participantType = 0;

		startTime.wDay=1;
		startTime.wDayOfWeek = 0;
		startTime.wHour = 0;
		startTime.wMilliseconds = 0;
		startTime.wMinute = 0;
		startTime.wMonth = 1;
		startTime.wSecond = 0;
		startTime.wYear = 1;

		endTime.wDay=1;
		endTime.wDayOfWeek = 0;
		endTime.wHour = 0;
		endTime.wMilliseconds = 0;
		endTime.wMinute = 0;
		endTime.wMonth = 1;
		endTime.wSecond = 0;
		endTime.wYear = 1;
	}

}MultiPointCDREx;

//��Ե�CDR��������
typedef struct tagTP_S_POINTTOPOINT_CDREX
{
	std::string callingUri;									//���б�ʶ
	int callingProtocol;									//����Э������ 0��H.323Э�飻1��SIPЭ��
	std::string calledUri;									//���б�ʶ
	int calledProtocol;										//����Э������ 0��H.323Э�飻1��SIPЭ��
	std::string rate;										//���д�����λ��kbit/s��Mbit/s
	SYSTEMTIME startTime;									//���п�ʼʱ�䡣��ʽ�磺2013-05-07T22:46:31.235+08:00
	SYSTEMTIME endTime;										//���н���ʱ�䡣��ʽ�磺2013-05-07T22:46:31.235+08:00

	tagTP_S_POINTTOPOINT_CDREX()
	{
		callingProtocol = 0;
		calledProtocol = 0;

		startTime.wDay=1;
		startTime.wDayOfWeek = 0;
		startTime.wHour = 0;
		startTime.wMilliseconds = 0;
		startTime.wMinute = 0;
		startTime.wMonth = 1;
		startTime.wSecond = 0;
		startTime.wYear = 1;

		endTime.wDay=1;
		endTime.wDayOfWeek = 0;
		endTime.wHour = 0;
		endTime.wMilliseconds = 0;
		endTime.wMinute = 0;
		endTime.wMonth = 1;
		endTime.wSecond = 0;
		endTime.wYear = 1;
	}

}PointToPointCDREx;

//Adhoc�������
typedef struct tagTP_S_ADHOC_CONFERENCEEX
{
	std::string name;										//Ad hoc��������
	std::string confAccessCode;								//Ad hoc��������

}AdhocConferenceEx;

//Adhoc����æ��״̬����
typedef struct tagTP_S_ADHOC_CONF_FREE_BUSY_STATEEX
{
	std::string confAccessCode;								//Ad hoc��������
	list<FreeBusyStateEx> freebusys;						//æ��״̬�б�

}AdhocConfFreeBusyStateEx;

//�᳡������MCU
typedef struct tagTP_S_SITE_MCUEX
{
	std::string siteUri;									//�᳡��ʶ
	int mcuId;												//�᳡������MCU ID

	tagTP_S_SITE_MCUEX()
	{
		mcuId = 0;
	}
}SiteMCUEx;

//MCU��Դռ�����
typedef struct tagTP_S_RESOURCE_OCCUPIED_STATUSEX
{
	int freeCount;											//������Դ��
	int totalcount;											//��Դ����
	SYSTEMTIME beginTime;									//��ѯ��ʼʱ�䡣��ʽ�磺2013-05-07T22:46:31.235+08:00
	std::string duration;									//��ѯʱ�䷶Χ

	tagTP_S_RESOURCE_OCCUPIED_STATUSEX()
	{
		freeCount = 0;
		totalcount = 0;

		beginTime.wDay=1;
		beginTime.wDayOfWeek = 0;
		beginTime.wHour = 0;
		beginTime.wMilliseconds = 0;
		beginTime.wMinute = 0;
		beginTime.wMonth = 1;
		beginTime.wSecond = 0;
		beginTime.wYear = 1;
	}

}ResourceOccupiedStatusEx;

//MCU��Դ����
typedef struct tagTP_S_MCU_RESOURCE_ITEMEX
{
	int resourceType;										//MCU����Դ����
	list<ResourceOccupiedStatusEx> resourceStatus;			//��Դռ�����

	tagTP_S_MCU_RESOURCE_ITEMEX()
	{
		resourceType = 0;
	}

}MCUResourceItemEx;

//MCU��Դ����
typedef struct tagTP_S_MCU_RESOURCEEX
{
	int mcuId;												//MCU ID
	list<MCUResourceItemEx> resourceList;					//MCU����Դ�б�

	tagTP_S_MCU_RESOURCEEX()
	{
		mcuId = 0;
	}

}MCUResourceEx;

//MCU����Ϣ
typedef struct tagTP_S_MCU_INFOEX
{
	int id;													//MCU ID
	std::string name;										//MCU������
	int type;												//MCU������
	std::string ip1;										//MCU �����ذ�IP��ַ1��IP��ַ1��IP��ַ2����ͬʱ�ÿգ���ѡ��
	int port1;												//MCU �����ذ�˿�1���˿�1����IP��ַ1��Ӧ����ѡ��
	std::string ip2;										//MCU �����ذ�IP��ַ2����ѡ��
	int port2;												//MCU �����ذ�˿�2����ѡ��
	std::string domainName;									//MCU����
	int stutas;												//MCU��״̬���
	tagTP_S_MCU_INFOEX()
	{
		id = 0;
		type = 0;
		port1 = 0;
		port2 = 0;
		stutas = 0;
	}
}MCUInfoEx;

//��֯�ڵ���Ϣ
typedef struct tagTP_S_ORGANIZATION_ITEMEX
{
	std::string id;											//��֯�ڵ�ID
	std::string name;										//��֯�ڵ�����
}OrganizationItemEx;

//��ѯ���CDR����
typedef struct tagTP_S_QUERY_MULTI_POINT_CDREX
{
	list<MultiPointCDREx> cdr;								//��ѯ�Ķ��CDR��������
	PagesInfoEx PageInfo;									//�����ѯ����ķ�ҳ��Ϣ

}QueryMultiPointCDRExResponse;

//��ѯ��Ե�CDR����
typedef struct tagTP_S_QUERY_POINT_TO_POINT_CDREX
{
	list<PointToPointCDREx> cdr;							//��ѯ�ĵ�Ե�CDR��������
	PagesInfoEx PageInfo;									//�����ѯ����ķ�ҳ��Ϣ

}QueryPointToPointCDRExResponse; 

//��ѯAd hoc���͵Ļ���ģ���б���
typedef struct tagTP_S_RSP_QUERY_ADHOC_CONFEX
{
	list<AdhocConferenceEx> adhocConferences;				//������ϲ�ѯ������Ad hoc�����б�
	PagesInfoEx PageInfo;									//�����ѯ����ķ�ҳ��Ϣ
}QueryAdhocConferenceExResponse;

//��ѯ�໭��ģʽ��Դ�����
typedef struct tagTP_S_RSP_GET_CONTINUOUS_PRESENCE_INFOEX
{
	list<std::string> targets;								//�������֧�ֵĶ໭�����ͣ������ʽ��ο������ö໭��������ӿ��е�target����
	int cpResource;											//�������໭����Դ������ֵ����ͬʱ�ж��ٸ���ͬ���ӻ������
	list<int> supportCPModes;								//�����ǰ������֧�ֵĶ໭��ģʽ�б�

	tagTP_S_RSP_GET_CONTINUOUS_PRESENCE_INFOEX()
	{
		cpResource = 0;
	}


}GetContinuousPresenceInfoResponseEx;

//��ȡָ������Ķ໭��������
typedef struct tagTP_S_RSP_GET_CONTINUOUS_PRESENCE_PARAMEX
{
	int presenceMode;										//�໭��ģʽ
	list<std::string> subPics;								//�ӻ���᳡��ʶ˳���б�

	tagTP_S_RSP_GET_CONTINUOUS_PRESENCE_PARAMEX()
	{
		presenceMode = 0;
	}


}GetContinuousPresenceParamResponseEx;

//��Ƶ��������
typedef struct tagTP_S_VIDEO_CAPBILITY_ITEMEX
{
	int videoProtocol;										//��ƵЭ��
	list<int> videoFormat;									//��ƵЭ���Ӧ����Ƶ��ʽ�б�
	tagTP_S_VIDEO_CAPBILITY_ITEMEX()
	{
		videoProtocol = 0;
	}

}VideoCapbilityItemEx;

//�ն˻�����Ϣ
typedef struct tagTP_S_TERMINAL_INFOEX
{
	std::string name;										//�᳡����
	std::string uri;										//�᳡��ʶ
	int type;												//�᳡����
	std::string rate;										//����
	list<VideoCapbilityItemEx> videoCapbility;				//�ն�֧�ֵ���Ƶ���������б���������SMC��Ĭ�����ò��Ա���һ�£���ѡ��
	std::string regUser;									//H.323��SIPЭ��᳡ע��SC���û�������ѡ��
	std::string regPassword;								//H.323��SIPЭ��᳡ע��SC�����루��ѡ��

	tagTP_S_TERMINAL_INFOEX()
	{
		type = 0;
	}
}TerminalInfoEx;

//��ѯ�᳡��Ϣ���
typedef struct tagTP_S_QUERY_SITES_INFOEX
{
	list<TerminalInfoEx> sites;								//��ѯ�Ļ᳡��Ϣ�б�
	PagesInfoEx pageInfo;									//�����ѯ����ķ�ҳ��Ϣ

}QuerySitesInfoExResponse;

//��ѯMCU��Ϣ�б���
typedef struct tagTP_S_QUERY_MCU_INFOEX
{
	list<MCUInfoEx> mcus;									//���ϲ�ѯ������MCU�б�
	PagesInfoEx pageInfo;									//��ѯ����ķ�ҳ��Ϣ

}QueryMCUInfoExResponse;


//�᳡�ն˰汾��Ϣ
typedef struct tagTP_S_SITE_DEVICE_VERSION_INFOEX
{
	std::string model;										//�豸�ͺ�
	std::string license;									//���license(�ն����к�)
	std::string softVersion;								//����汾
	std::string hardVersion;								//Ӳ���汾
	std::string logicVersion;								//�߼��汾
	list<SiteMicVersionMapEx> micVersions;					//��˰汾�б�
	std::string manufacturer;								//������Ϣ��Ĭ�Ϸ��ء�HUAWEI��

}SiteDeviceVersionInfoEx;

typedef struct tagTP_S_VIDEO_PRARMEX
{
	int videoFormat;
	int videoProtocol;

	tagTP_S_VIDEO_PRARMEX()
	{
		videoFormat = 0;
		videoProtocol = 0;
	}

}VideoParamEx;


typedef struct tagTP_S_ADHOC_CONF_TEMPLATE_PARAMEX
{
	std::string adhocConfTemplateId;
	std::string name;
	std::string accessCode;
	std::string duration;
	std::string billCode;
	std::string password;
	int cpResouce;
	std::string rate;
	int mediaEncryptType;
	int isLiveBroadcast;
	int isRecording;
	int presentation;
	std::string chairmanPassword;
	VideoParamEx presentationVideo;
	std::string mainSiteUri;
	ConferenceNoticeEx notice;
	int maxSitesCount;
	int state;
	list<SiteInfoEx> sites;
	int reservedCsdPorts;

	tagTP_S_ADHOC_CONF_TEMPLATE_PARAMEX()
	{
		cpResouce = 0;
		mediaEncryptType = 0;
		isLiveBroadcast = 0;
		isRecording = 0;
		presentation = 0;
		maxSitesCount = 0;
		state = 0;
		reservedCsdPorts = 0;
	}

}AdhocConfTemplateParamEx;

typedef struct tagTP_S_SUBSCRIBE_INFOEX
{
	int isSubscribe;
	int type;
	tagTP_S_SUBSCRIBE_INFOEX()
	{
		isSubscribe =0;
		type = 0;
	}

}SubscribeInfoEx;


typedef struct tagTP_S_NOTIFICATIONEX
{
	int type;
}NotificationEx;

typedef struct tagTP_S_OVERFLOW_NOTIFICATIONEX:NotificationEx
{
	tagTP_S_OVERFLOW_NOTIFICATIONEX()
	{
		type = TP_D_OVERFLOW_NOTIFICATION_TYPE;
	}
}OverflowNotificationEx;

typedef struct tagTP_S_SCHEDULED_CONF_NOTIFICATIONEX:NotificationEx
{
	int event;
	std::string confId;
	SYSTEMTIME beginTime;
	tagTP_S_SCHEDULED_CONF_NOTIFICATIONEX()
	{
		type = TP_D_SCHEDULED_CONF_NOTIFICATION_TYPE;
		beginTime.wYear = 0;
		beginTime.wMonth = 0;
		beginTime.wDay = 0;
		beginTime.wDayOfWeek = 0;
		beginTime.wHour = 0;
		beginTime.wMinute = 0;
		beginTime.wSecond = 0;
		beginTime.wMilliseconds =0;
		event = 0;
	}

}ScheduledConfNotificationEx;



typedef struct tagTP_S_ONGOING_CONF_NOTIFICATIONEX:NotificationEx
{
	int event;
	std::string confId;
	SYSTEMTIME beginTime;
	std::string siteUri;
	list<NotificationStatusEx *> changes;
	tagTP_S_ONGOING_CONF_NOTIFICATIONEX()
	{
		type = TP_D_ONGOING_CONF_NOTIFICATION_TYPE;
		beginTime.wYear = 0;
		beginTime.wMonth = 0;
		beginTime.wDay = 0;
		beginTime.wDayOfWeek = 0;
		beginTime.wHour = 0;
		beginTime.wMinute = 0;
		beginTime.wSecond = 0;
		beginTime.wMilliseconds =0;
		event = 0;
	}

}OngoingConfNotificationEx;



typedef struct tagTP_S_SCHEDULED_CONF_SUBSCRIBEEX:SubscribeInfoEx
{
	//list<std::string> confIds;
	std::string confIds;
	tagTP_S_SCHEDULED_CONF_SUBSCRIBEEX()
	{
		type = TP_D_SCHEDULED_CONF_SUBSCRIBE_TYPE;
	}
}ScheduledConfSubscribeEx;

typedef struct tagTP_S_ONGOING_CONF_SUBSCRIBEEX:SubscribeInfoEx
{
	//list<std::string> confIds;
	std::string confIds;
	tagTP_S_ONGOING_CONF_SUBSCRIBEEX()
	{
		type = TP_D_ONGOING_CONF_SUBSCRIBE_TYPE;
	}
}OngoingConfSubscribeEx;


template <class T>struct TPSDKResponseWithPageEx:TPSDKResponseEx<T>
{
	PagesInfoEx pagesInfo;									//ҳ����Ϣ
};
#endif