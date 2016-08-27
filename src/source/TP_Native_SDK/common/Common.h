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
 * @file   Common.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   ANSI UTF8 Unicode transfer function
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init  Common.h
****************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#include "esdk_http_client.h"
#include "Log.h"

#define TIMEOUT_2S (2*1000)//ms
#define TIMEOUT_5S (5*1000)//ms
#define TIMEOUT_30S (30*1000)//ms

//×ªÂë£ºANSI¡¢UTF8¡¢Unicode
static wchar_t* ANSIToUnicode(const char* str);
static wchar_t* UTF8ToUnicode(const char* str);
static char* UnicodeToANSI( const wchar_t* str);
static char* UnicodeToUTF8(const wchar_t* str);
static char* UTF8ToANSI(const char* str);
static char* ANSIToUTF8(const char* str);

//lint -e1775 -e438
static wchar_t* ANSIToUnicode(const char* str)
{
	wchar_t * result = NULL;
	unsigned int textlen = static_cast<unsigned int>(MultiByteToWideChar( CP_ACP, 0, str,-1, NULL,0 ));
	try
	{
		result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t));
		if (NULL == result)
		{
			return NULL;
		}
	}
	catch (...)
	{
		return NULL;
	}

	memset(result,0,(textlen+1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0,str,-1,(LPWSTR)result,textlen );//lint !e713
	return result;
}

static wchar_t* UTF8ToUnicode( const char* str )
{
	wchar_t * result = NULL;
	unsigned int textlen = static_cast<unsigned int>(MultiByteToWideChar( CP_UTF8, 0, str,-1, NULL,0 ));
	try
	{
		result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t));
		if (NULL == result)
		{
			return NULL;
		}
	}
	catch (...)
	{
		return NULL;
	}

	memset(result,0,(textlen+1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0,str,-1,(LPWSTR)result,textlen );//lint !e713
	return result;
}

static char* UnicodeToANSI( const wchar_t* str )
{
	char* result = NULL;
	unsigned int textlen = static_cast<unsigned int>(WideCharToMultiByte( CP_ACP, 0, str, -1, NULL, 0, NULL, NULL ));
	try
	{
		result =(char *)malloc((textlen+1)*sizeof(char));
		if (NULL == result)
		{
			return NULL;
		}
	}
	catch (...)
	{
		return NULL;
	}

	memset( result, 0, sizeof(char) * ( textlen + 1 ) );
	WideCharToMultiByte( CP_ACP, 0, str, -1, result, textlen, NULL, NULL );//lint !e713
	return result;
}

static char* UnicodeToUTF8( const wchar_t* str )
{
	char* result = NULL;
	unsigned int textlen = static_cast<unsigned int>(WideCharToMultiByte( CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL ));
	try
	{
		result =(char *)malloc((textlen+1)*sizeof(char));
		if (NULL == result)
		{
			return NULL;
		}
	}
	catch (...)
	{
		return NULL;
	}

	memset(result, 0, sizeof(char) * ( textlen + 1 ) );
	WideCharToMultiByte( CP_UTF8, 0, str, -1, result, textlen, NULL, NULL );//lint !e713
	return result;
}

static char* UTF8ToANSI(const char* str)
{
	wchar_t* unicode = UTF8ToUnicode(str);
	if (NULL == unicode)
	{
		return NULL;
	}
	char* ansi = UnicodeToANSI(unicode);
	free(unicode);
	unicode = NULL;
	return ansi;
}

static char* ANSIToUTF8(const char* str)
{
	wchar_t* unicode = ANSIToUnicode(str);
	if (NULL == unicode)
	{
		return NULL;
	}
	char* utf8 = UnicodeToUTF8(unicode);
	free(unicode);
	unicode = NULL;
	return utf8;
}
//lint +e1775 +e438

#endif //_COMMON_H_
