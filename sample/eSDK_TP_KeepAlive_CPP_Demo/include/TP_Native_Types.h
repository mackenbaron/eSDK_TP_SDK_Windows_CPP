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


// 常量定义
#define PROTOCOL_VERSION						0x0100				// 协议版本，当前版本号为0x0100
#define INVALID_MSG_TYPE						(UINT16)(-1)		// 消息类型，非法类型
#define XML_CONTEXT_TYPE						0x0001				// 字段类型定义，“0x0001”为xml文本字段

#define BUFFER_SIZE								1024				// SSL_read一次最多读取字节数

#define RSP_MSG_FLAG							0xF000				// respond消息标志

#define SESSIONID_LENGTH						32					// sessionid长度

#define KEEPALIVE_TIME							6					// 保活时间  单位：秒
#define MAX_TIMEOUT_COUNT						5					// 最大超时次数
//////////////////////////////////////////////////////////////////////////


//SDK错误码
typedef enum tagTP_E_RET_CODE
{
	TP_E_RET_CODE_SUCCESS=0,
	TP_E_RET_CODE_FAIL=1,
	TP_E_RET_CODE_INVALID_PARA=2,
	TP_E_RET_CODE_URL_EMPTY=3,
	TP_E_RET_CODE_LOST_PARA=4,
	TP_E_RET_CODE_SEND_REQUEST_FAILED=5,
	TP_E_RET_CODE_INVALID_RESPONSE=6,
	TP_SDK_ERR_SUCCESS = 0,					// 成功
	TP_SDK_ERR_GENERAL=2130000020,          //native处理异常
	// 2135102001 - 2135102100 普通错误
	TP_SDK_ERR_FAILED = 2135102001,			// 通用失败
	TP_SDK_ERR_INVALID_PARAM,					// 非法入参
	TP_SDK_ERR_NULL_POINTER,					// 空指针错误
	TP_SDK_ERR_CREATE_OBJECT,                 // 创建对象失败
	TP_SDK_ERR_CREATE_DIRECTORY,              // 创建目录失败
	TP_SDK_ERR_LOG_INIT,                      // 日志模块初始化失败
	TP_SDK_ERR_SDL_INIT,                      // SDL初始化失败

	// 2135102101 - 2135102200 网络错误
	TP_SDK_ERR_WSA_START_UP = 2135102101,     // 初始化套结字动态库失败
	TP_SDK_ERR_CONNECT_SERVER,                // 连接服务器失败
	TP_SDK_ERR_SSL_CONNECT,                   // SSL连接失败
	TP_SDK_ERR_SEND_MSG,                      // 发送数据失败
	TP_SDK_ERR_WAIT_TIME_OUT,                 // 等待超时
	TP_SDK_ERR_SERVER_NOT_RUNNING,            // 服务未运行

	// 2135102201 - 2135102300 文件操作错误
	TP_SDK_ERR_CONFIG_FILE_LOAD = 2135102201,	// 加载ini配置文件失败
	TP_SDK_ERR_CONFIG_FILE_READ,				// 读取ini配置文件失败
	TP_SDK_ERR_CONFIG_FILE_WRITE,				// 写入ini配置文件失败

	//2135102301 - 2135102400 XML操作错误
	TP_SDK_ERR_XML_CONSTRUCT = 2135102301,	// 构造XML字符串失败
	TP_SDK_ERR_XML_PARSE,						// 解析XML字符串失败
	TP_SDK_ERR_XML_FIND_ELEM,					// 查找XML节点失败
	TP_SDK_ERR_XML_GET_ELEM_VALUE,		    // 获取XML节点失败


	TP_SDK_ERR_SERVICE_EXPIRE	= 2135103009   // 服务过期，客户端需要重启服务
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

//会场信息
typedef struct tagTP_S_SITE_INFOEX
{
	std::string name;										//会场名称
	std::string uri;										//会场标识
	int type;												//会场类型
	int from;												//会场来源
	int dialingMode;										//呼叫方式
	std::string rate;										//速率
	int videoFormat;										//视频格式
	int videoProtocol;										//视频协议
	int isLockVideoSource;									//是否锁定会场视频源
	int participantType;									//与会类型
	int status;												//会场状态
	std::string dtmf;										//二次拨号信息
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

//普通会议信息
typedef struct tagTP_S_CONFERENCE_INFOEX 
{
	std::string confId;										//会议 ID，由系统自动分配。
	std::string name;										//会议名称
	SYSTEMTIME beginTime;									//会议开始时间。
	std::string duration;									//会议时长，如：P0Y0M0DT1H0M0.000S或者PT1H：表示1小时。
	std::string accessCode;									//会议接入码。必须为数字格式的字符串。如：075560166。
	std::string password;									//会议接入密码。只支持0～9的数字。长度为6位数字的密码。
	int mediaEncryptType;									//媒体流加密方式。
	int auxVideoFormat;										//辅流视频格式。
	int auxVideoProtocol;									//辅流视频协议，取值说明参见【Native-C++】VideoProtocol（视频协议）。
	int cpResouce;											//多画面资源数。
	std::string rate;										//速率。格式为“速率值k/M”，如“1920k”
	int isRecording;										//会议是否支持录制功能，不填则默认不支持
	std::string recorderAddr;								//直播地址
	int isLiveBroadcast;									//录播会议是否支持直播功能，不填则默认不支持
	int presentation;										//演示方式
	std::string chairmanPassword;							//主席密码或会议启动密码。只支持0～9的数字。长度为6位数字。
	int status;												//会议状态
	std::string billCode;									//计费码（可选）
	std::string mainSiteUri;								//会议主会场（可选）
	ConferenceNoticeEx conferenceNotice;					//会议通知信息（可选）
	vector<SiteInfoEx> sites;								//会场信息列表
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

	}

}ConferenceInfoEx;

//会场接入信息
typedef struct tagTP_S_SITE_ACCESS_INFOEX
{
	std::string uri;										//会场标识
	std::string confAccessCode;								//会议接入号
	std::string name;										//会场名称
	SYSTEMTIME beginTime;									//会议开始时间
	std::string mcuUri;										//会场接入 MCU 的 Uri。在没有 GK 或 SIP 服务器环境下直接呼叫 MCU 的场景
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

//周期性会议信息
typedef struct tagTP_S_RECURRENCE_CONF_INFOEX
{
	ConferenceInfoEx base_info;								//普通会议信息
	int frequency;											//周期会议周期类型
	int interval;											//间隔。周期会议 interval 必须大于0。如：该参数为1，frequency 为0时，即每天都召开一次
	list<int> weekDays;											//使用 Weekly 周期类型时，存储星期日～星期六的标记。序号从0～6，表示星期日～星期六；在 Monthly 周期类型时，用于表示第几个星期的星期几；在 Daily周期类型时，如果不为该参数设值（值为null或者数组size为0），每一天都允许召开会议，否则只在工作日召开会议（周六、周日不召开周期会议）
	int weekDay;											//使Monthly时，表示第几个星期
	int monthDay;											//每个月的第几天，当 frequency 为 Monthly 周期类型时有效
	int count;												//重复次数
	SYSTEMTIME endDate;									//结束日期
	std::string timeZone;									//周期会议本地时区。时区字串表示，请参考时区列表
	vector<SiteAccessInfoEx> siteAccessInfos;				//会场接入信息
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

//会场忙闲状态
typedef struct tagTP_S_FREE_BUSY_STATEEX
{
	SYSTEMTIME startTime;									//起始时间
	std::string span;										//时间跨度。如：P0Y0M0DT1H0M0.000S
	int state;												//忙闲状态。如果状态为“闲”，且包含有会议 ID，则表示该时间段会议被删除，或会场已经不在该会议中
	std::string confId;										//会议 ID
	std::string confName;									//会议名称
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
	int isSupportLiving;									//是否支持直播
	int isSupportRecording;									//是否支持录播
	int status;												//状态
	int isAutoRecordingVideoSource;							//是否自动录制视频源
	std::string videoSource;								//视频源

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

//会议状态
typedef struct tagTP_S_CONFERENCE_STATUSEX:NotificationStatusEx
{
	std::string id;											//会议 ID
	std::string name;										//会议名称
	int status;												//会议状态
	std::string chair;										//主席会场
	std::string broadcast;									//广播会场
	std::string speaking;									//正在发言的会场（音量最大的会场）
	std::string presentation;								//正在发送辅流的会场
	int isLock;												//会议是否锁定
	int isAudioSwitch;										//会议是否开启声控切换功能
	int switchGate;											//声控切换门限值。取值范围为0～100
	SYSTEMTIME beginTime;									//会议开始时间
	SYSTEMTIME endTime;										//会议结束时间
	int isLockPresentation;									//会议是否处于锁定辅流令牌状态
	std::string lockPresentation;							//锁定辅流令牌的会场
	RecordStatusEx recording;								//记录状态
	int conferenceMode;										//会议模式，取值说明 0：AUTO 1：CONVERGENT
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


//详细错误信息
typedef struct tagTP_S_ERROR_INFOEX
{
	int errCode;											//错误码
	std::string description;								//错误信息描述

	tagTP_S_ERROR_INFOEX()
	{
		errCode = 0;
	}

}ErrorInfoEx;

//会场状态
typedef struct tagTP_S_SITE_STATUSEX:NotificationStatusEx
{
	std::string uri;										//会场标识
	std::string name;										//会场名称
	int status;												//会场状态
	int volume;												//会场音量值
	std::string videoSource;								//会场的视频源
	int isMute;												//是否闭音
	int isQuiet;											//是否静音
	int type;												//会场类型
	ErrorInfoEx callFailedReason;							//呼叫失败原因
	int isLocalVideoOpen;									//会场本地视频是否打开，此参数若空则表示视频处于打开状态
	int participantType;									//与会类型，该参数置空表示终端会场（可选）
	int screens;											//会场有多屏（屏数1）时，表示会场的屏数。会场屏数是1或者为语音会场时，此参数置空（可选）

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



//摄像机控制参数
typedef struct tagTP_S_CAMERA_CONTROLEX
{
	int camState;											//摄像机类型
	int camAction;											//摄像机操作命令
	int camPos;												//预置位置号，在camAction参数取值不为18、19、20时，预置位号可固定为255
	int camSrc;												//输入口id，在终端中配置

	tagTP_S_CAMERA_CONTROLEX()
	{
		camState = 0;
		camAction = 0;
		camPos = 0;
		camSrc = 0;
	}
}CameraControlEx;

//录播直播信息
typedef struct tagTP_S_BROAD_INFOEX
{
	int directBroad;										//是否支持直播
	int recordBroad;										//是否支持录播
	int directBroadStatus;									//直播状态
	int recordBroadStatus;									//录播状态

	tagTP_S_BROAD_INFOEX()
	{
		directBroad = 0;
		recordBroad = 0;
		directBroadStatus = 0;
		recordBroadStatus = 0;
	}

}BroadInfoEx;

//视频源信息
typedef struct tagTP_S_VideoSourcesInfoEX
{
	int sourcesId;											//视频源索引值
	int sourcesState;										//对应输入口是否接入视频源
	std::string sourcesName;								//视频源名称

	tagTP_S_VideoSourcesInfoEX()
	{
		sourcesId = 0;
		sourcesState = 0;
	}
}VideoSourcesInfoEx;

//会场指定时间内忙闲状态
typedef struct tagTP_S_SITE_FREE_BUSY_STATEEX
{
	int uri;												//会场 URI
	FreeBusyStateEx state;									//会场状态

	tagTP_S_SITE_FREE_BUSY_STATEEX()
	{
		uri = 0;
	}

}SiteFreeBusyStateEx;

//主流、辅流信息
typedef struct tagTP_S_AUXSTREAM_INFOEX
{
	int id;													//主流、辅流视频源 ID
	std::string name;										//主流、辅流视频源名称

	tagTP_S_AUXSTREAM_INFOEX()
	{
		id = 0;
	}
}AuxStreamInfoEx;

//麦克版本列表
typedef struct tagTP_S_SITE_MIC_VERSION_MAPEX
{
	std::string micIP;										//Mic IP地址
	std::string version;									//Mic 版本信息
}SiteMicVersionMapEx;

//会场音量
typedef struct tagTP_S_SITE_VOLUMEEX
{
	std::string siteUri;									//会场URI
	int volume;												//音量值大小

	tagTP_S_SITE_VOLUMEEX()
	{
		volume = 0;
	}

}SiteVolumeEx;

//会场排序条件
typedef struct tagTP_S_SORT_ITEMEX
{
	int sort;												//排序方式 0：升序；1：降序
	int itemIndex;											//查询条件的数据列标识

	tagTP_S_SORT_ITEMEX()
	{
		sort = 0;
		itemIndex = 0;

	}

}SortItemEx;

//会场过滤条件
typedef struct tagTP_S_FILTER_BASEEX
{
	int columnIndex;										//过滤条件的数据列标识
	std::string value;										//包含的字符串

	tagTP_S_FILTER_BASEEX()
	{
		columnIndex = 0;
	}

}FilterBaseEx;

typedef struct tagTP_S_STRING_FILTEREX:FilterBaseEx
{
	std::string value;
}StringFilterEx;

//页码定位参数
typedef struct tagTP_S_PAGE_PARAMEX
{
	int numberPerPage;										//每页的记录条数
	int currentPage;										//当前页码，或需要返回的页码

	tagTP_S_PAGE_PARAMEX()
	{
		numberPerPage = 0;
		currentPage = 0;
	}

}PageParamEx;

//分页信息
typedef struct tagTP_S_PAGE_INFOEX
{
	int totalPages;											//总页数
	int currentPage;										//当前页码
	int totalRecords;										//总记录数

	tagTP_S_PAGE_INFOEX()
	{
		totalPages = 0;
		currentPage = 0;
		totalRecords = 0;
	}

}PagesInfoEx;


//会场查询条件
typedef struct tagTP_S_QUERY_CONFIGEX
{

	list<SortItemEx> sortItems;								//排序条件组合，目前只支持单列排序
	list<FilterBaseEx> filters;								//过滤条件组合，支持多个过滤条件，为AND关系
	int focusItem;											//焦点数据ID
	PageParamEx pageParam;									//页码定位参数

	tagTP_S_QUERY_CONFIGEX()
	{
		focusItem = 0;
	}

}QueryConfigEx;

//查询多点CDR话单条件
typedef struct tagTP_S_MULTI_POINT_CDR_QUERY_CONFIGEX
{
	SYSTEMTIME beginTime;									//查询开始时间。格式如：2013-05-07T22:46:31.235+08:00
	std::string duration;									//查询时间跨度
	std::string siteUri;									//会场URI，用于查询指定会场的多点话单（可选）
	PageParamEx pageParam;									//页码定位参数，即指定返回查询结果的第几页

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


//指定会场
typedef struct tagTP_S_CALL_END_POINTEX
{
	int type;												//呼叫类型
	std::string siteUri;									//会场标识

	tagTP_S_CALL_END_POINTEX()
	{
		type = 0;
	}
}CallEndPointEx;

//查询单点CDR话单条件
typedef struct tagTP_S_POINTTOPOINT_CDR_QUERY_CONFIGEX
{
	SYSTEMTIME beginTime;									//会议开始时间。格式如：2013-05-07T22:46:31.235+08:00
	std::string duration;									//时间跨度
	CallEndPointEx endPoint;								//查询指定会场（可选）
	PageParamEx pageParam;									//页码定位参数，即指定返回查询结果的第几页

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

//多点CDR话单数据
typedef struct tagTP_S_MULTI_POINT_CDREX
{
	std::string siteName;									//会场名称
	std::string siteUri;									//会场标识
	int siteType;											//会场类型
	int participantType;									//会场与会类型
	std::string rate;										//速率
	SYSTEMTIME startTime;									//呼叫开始时间。格式如：2013-05-07T22:46:31.235+08:00
	SYSTEMTIME endTime;										//呼叫结束时间。格式如：2013-05-07T22:46:31.235+08:00
	std::string conferenceName;								//会议名称
	std::string conferenceId;								//会议ID
	std::string conferenceCreater;							//会议创建者
	std::string billCode;									//会议计费码

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

//点对点CDR话单数据
typedef struct tagTP_S_POINTTOPOINT_CDREX
{
	std::string callingUri;									//主叫标识
	int callingProtocol;									//主叫协议类型 0：H.323协议；1：SIP协议
	std::string calledUri;									//被叫标识
	int calledProtocol;										//被叫协议类型 0：H.323协议；1：SIP协议
	std::string rate;										//呼叫带宽。单位：kbit/s、Mbit/s
	SYSTEMTIME startTime;									//呼叫开始时间。格式如：2013-05-07T22:46:31.235+08:00
	SYSTEMTIME endTime;										//呼叫结束时间。格式如：2013-05-07T22:46:31.235+08:00

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

//Adhoc会议参数
typedef struct tagTP_S_ADHOC_CONFERENCEEX
{
	std::string name;										//Ad hoc会议名称
	std::string confAccessCode;								//Ad hoc会议接入号

}AdhocConferenceEx;

//Adhoc会议忙闲状态数据
typedef struct tagTP_S_ADHOC_CONF_FREE_BUSY_STATEEX
{
	std::string confAccessCode;								//Ad hoc会议接入号
	list<FreeBusyStateEx> freebusys;						//忙闲状态列表

}AdhocConfFreeBusyStateEx;

//会场所属的MCU
typedef struct tagTP_S_SITE_MCUEX
{
	std::string siteUri;									//会场标识
	int mcuId;												//会场所属的MCU ID

	tagTP_S_SITE_MCUEX()
	{
		mcuId = 0;
	}
}SiteMCUEx;

//MCU资源占用情况
typedef struct tagTP_S_RESOURCE_OCCUPIED_STATUSEX
{
	int freeCount;											//空闲资源数
	int totalcount;											//资源总数
	SYSTEMTIME beginTime;									//查询开始时间。格式如：2013-05-07T22:46:31.235+08:00
	std::string duration;									//查询时间范围

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

//MCU资源数据
typedef struct tagTP_S_MCU_RESOURCE_ITEMEX
{
	int resourceType;										//MCU的资源类型
	list<ResourceOccupiedStatusEx> resourceStatus;			//资源占用情况

	tagTP_S_MCU_RESOURCE_ITEMEX()
	{
		resourceType = 0;
	}

}MCUResourceItemEx;

//MCU资源数据
typedef struct tagTP_S_MCU_RESOURCEEX
{
	int mcuId;												//MCU ID
	list<MCUResourceItemEx> resourceList;					//MCU的资源列表

	tagTP_S_MCU_RESOURCEEX()
	{
		mcuId = 0;
	}

}MCUResourceEx;

//MCU的信息
typedef struct tagTP_S_MCU_INFOEX
{
	int id;													//MCU ID
	std::string name;										//MCU的名称
	int type;												//MCU的类型
	std::string ip1;										//MCU 的主控板IP地址1。IP地址1与IP地址2不可同时置空（可选）
	int port1;												//MCU 的主控板端口1。端口1是与IP地址1对应（可选）
	std::string ip2;										//MCU 的主控板IP地址2（可选）
	int port2;												//MCU 的主控板端口2（可选）
	std::string domainName;									//MCU域名
	int stutas;												//MCU的状态情况
	tagTP_S_MCU_INFOEX()
	{
		id = 0;
		type = 0;
		port1 = 0;
		port2 = 0;
		stutas = 0;
	}
}MCUInfoEx;

//组织节点信息
typedef struct tagTP_S_ORGANIZATION_ITEMEX
{
	std::string id;											//组织节点ID
	std::string name;										//组织节点名称
}OrganizationItemEx;

//查询多点CDR话单
typedef struct tagTP_S_QUERY_MULTI_POINT_CDREX
{
	list<MultiPointCDREx> cdr;								//查询的多点CDR话单数据
	PagesInfoEx PageInfo;									//输出查询结果的翻页信息

}QueryMultiPointCDRExResponse;

//查询点对点CDR话单
typedef struct tagTP_S_QUERY_POINT_TO_POINT_CDREX
{
	list<PointToPointCDREx> cdr;							//查询的点对点CDR话单数据
	PagesInfoEx PageInfo;									//输出查询结果的翻页信息

}QueryPointToPointCDRExResponse; 

//查询Ad hoc类型的会议模板列表结果
typedef struct tagTP_S_RSP_QUERY_ADHOC_CONFEX
{
	list<AdhocConferenceEx> adhocConferences;				//输出符合查询条件的Ad hoc会议列表
	PagesInfoEx PageInfo;									//输出查询结果的翻页信息
}QueryAdhocConferenceExResponse;

//查询多画面模式资源数结果
typedef struct tagTP_S_RSP_GET_CONTINUOUS_PRESENCE_INFOEX
{
	list<std::string> targets;								//输出会议支持的多画面类型，具体格式请参考“设置多画面参数”接口中的target描述
	int cpResource;											//输出会议多画面资源数，该值决定同时有多少个不同的子画面存在
	list<int> supportCPModes;								//输出当前会议能支持的多画面模式列表

	tagTP_S_RSP_GET_CONTINUOUS_PRESENCE_INFOEX()
	{
		cpResource = 0;
	}


}GetContinuousPresenceInfoResponseEx;

//读取指定会议的多画面参数结果
typedef struct tagTP_S_RSP_GET_CONTINUOUS_PRESENCE_PARAMEX
{
	int presenceMode;										//多画面模式
	list<std::string> subPics;								//子画面会场标识顺序列表

	tagTP_S_RSP_GET_CONTINUOUS_PRESENCE_PARAMEX()
	{
		presenceMode = 0;
	}


}GetContinuousPresenceParamResponseEx;

//视频能力参数
typedef struct tagTP_S_VIDEO_CAPBILITY_ITEMEX
{
	int videoProtocol;										//视频协议
	list<int> videoFormat;									//视频协议对应的视频格式列表
	tagTP_S_VIDEO_CAPBILITY_ITEMEX()
	{
		videoProtocol = 0;
	}

}VideoCapbilityItemEx;

//终端基本信息
typedef struct tagTP_S_TERMINAL_INFOEX
{
	std::string name;										//会场名称
	std::string uri;										//会场标识
	int type;												//会场类型
	std::string rate;										//速率
	list<VideoCapbilityItemEx> videoCapbility;				//终端支持的视频能力参数列表。如果不填，与SMC的默认配置策略保持一致（可选）
	std::string regUser;									//H.323、SIP协议会场注册SC的用户名（可选）
	std::string regPassword;								//H.323、SIP协议会场注册SC的密码（可选）

	tagTP_S_TERMINAL_INFOEX()
	{
		type = 0;
	}
}TerminalInfoEx;

//查询会场信息结果
typedef struct tagTP_S_QUERY_SITES_INFOEX
{
	list<TerminalInfoEx> sites;								//查询的会场信息列表
	PagesInfoEx pageInfo;									//输出查询结果的翻页信息

}QuerySitesInfoExResponse;

//查询MCU信息列表结果
typedef struct tagTP_S_QUERY_MCU_INFOEX
{
	list<MCUInfoEx> mcus;									//符合查询条件的MCU列表
	PagesInfoEx pageInfo;									//查询结果的翻页信息

}QueryMCUInfoExResponse;


//会场终端版本信息
typedef struct tagTP_S_SITE_DEVICE_VERSION_INFOEX
{
	std::string model;										//设备型号
	std::string license;									//软件license(终端序列号)
	std::string softVersion;								//软件版本
	std::string hardVersion;								//硬件版本
	std::string logicVersion;								//逻辑版本
	list<SiteMicVersionMapEx> micVersions;					//麦克版本列表
	std::string manufacturer;								//厂家信息，默认返回“HUAWEI”

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
	PagesInfoEx pagesInfo;									//页码信息
};
#endif