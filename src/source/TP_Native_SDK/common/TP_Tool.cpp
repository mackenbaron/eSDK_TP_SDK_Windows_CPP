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

#include "stdafx.h"
#include <Shlwapi.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>

#include <algorithm>
#include "TP_Tool.h"
#include "TP_Error.h"
#include "TP_Native_Types.h"
//#include "eLTE_Message.h"
//#include "eLTE_Log.h"
//#include "crypto/crypto_api.h"
#include "base64.h"
#include "CSHADigest.h"


#pragma comment(lib, "Shlwapi.lib")


#define STR_LENGTH_SIZE     20
#define INT_FORMAT_D	    10
#define DOUBLE_STR_SIZE	    64
#define DOUBLE_FORMAT	    "%g"
#define UINT_FORMAT		    "%u"

#define SECTION_SERVER_INFO			"ServerInfo"
#define KEY_NEED_ENCRYPT            "NeedEncrypt"
#define KEY_PASSWORD                "Password"
#define SPECIAL_STRING "①≠②"

// 配置文件读取返回值检测
#define CHECK_READ_CONFIG_FILE(x)			\
	if(0 == x)								\
	{										\
	return "";	\
	}

TP_Tool::TP_Tool()
{

}

TP_Tool::~TP_Tool()
{

}

std::string TP_Tool::GetServicePath()
{
	char path[MAX_PATH] = {0};
	GetModuleFileName(NULL,path, MAX_PATH);
	std::string strPath(path);
	strPath = strPath.substr(0, strPath.rfind("\\")+1);
	return strPath;
}

std::string TP_Tool::GetServicePathEx()
{
	char path[MAX_PATH] = {0};
	GetModuleFileName(NULL, path, MAX_PATH);
	std::string strPath(path);
	return strPath;
}

std::string TP_Tool::GetDllPath(const std::string& strDllName)
{
	HMODULE hModule = GetModuleHandle(strDllName.c_str());
	if(NULL == hModule)
	{
		return "";
	}
	char dllpath[MAX_PATH];
	memset(dllpath, 0, sizeof(dllpath));
	::GetModuleFileName(hModule, dllpath, MAX_PATH);
	std::string strPath(dllpath);
	strPath = strPath.substr(0, strPath.rfind("\\")+1);
	return strPath;
}

void TP_Tool::RelativePathToAbsolute(std::string& strPath)
{
	if (PathIsRelative(strPath.c_str()))
	{
		std::string strSvc = GetServicePath();
		strSvc.append(strPath);
		strPath = strSvc;
	}
}

BOOL TP_Tool::CreateMultipleDirectory(const std::string& path)
{
	std::string strPath(path);

	// 判断空
	if (strPath.empty())
	{
		return FALSE;
	}
	// 如果已经存在返回成功
	if (PathFileExists(strPath.c_str()))
	{
		return TRUE;
	}
	else
	{
		// 除去结尾的"\\"
		while ('\\' == strPath.back())
		{
			strPath = strPath.substr(0, strPath.rfind("\\"));
		}

		// 获取上级目录
		std::string prePath = strPath.substr(0, strPath.rfind("\\"));

		// 不存在的目录
		if (prePath == strPath)
		{
			return FALSE;
		}

		if (PathFileExists(prePath.c_str()))
		{
			return CreateDirectoryA(strPath.c_str(), NULL);
		}
		else
		{
			// 如果前面的目录不存在，则先创建前面的目录
			if (CreateMultipleDirectory(prePath))
			{
				// 前面目录创建好了以后，则再创建后面的目录
				return CreateMultipleDirectory(strPath);
			}
			return FALSE;
		}
	}
}

// int 转换为 std::string
std::string TP_Tool::Int2String(int iVar)
{
	char buf[STR_LENGTH_SIZE] = {0};
	(void)_itoa_s(iVar, buf, INT_FORMAT_D);
	return std::string(buf);
}

// unsigned int 转换为 std::string
std::string TP_Tool::UInt2String(unsigned int iVar)
{
	char _Buf[STR_LENGTH_SIZE];
	(void)sprintf_s(_Buf, sizeof(_Buf), UINT_FORMAT, iVar);
	return std::string(_Buf);
}

// double 装换为 std::string
std::string TP_Tool::Double2String(double dVar)
{
	char _Buf[DOUBLE_STR_SIZE];
	(void)sprintf_s(_Buf, sizeof(_Buf), DOUBLE_FORMAT, dVar);
	return std::string(_Buf);
}

// std::string 转换为 int
int TP_Tool::String2Int(const std::string& str)
{
	int iRet = 0;

	try
	{
		iRet=atoi(str.c_str());
		//iRet = std::stoi(str);
	}
	catch (...)
	{
		iRet = 0;
	}

	return iRet;
}

// std::string 转换为 unsigned int
unsigned int TP_Tool::String2UInt(const std::string& str)
{
	unsigned int uiRet = 0;

	try
	{
		uiRet = std::stoul(str);
	}
	catch (...)
	{
		uiRet = 0;
	}

	return uiRet;
}

// std::wstring 转换为 int
int TP_Tool::WString2Int(const std::wstring& wstr)
{
	int iRet = 0;

	try
	{
		iRet=_wtoi(wstr.c_str());
		//iRet = std::stoi(wstr);
	}
	catch (...)
	{
		iRet = 0;
	}

	return iRet;
}

// std::wstring 转换为 unsigned int
unsigned int TP_Tool::WString2UInt(const std::wstring& wstr)
{
	unsigned int uiRet = 0;

	try
	{
		uiRet = std::stoul(wstr);
	}
	catch (...)
	{
		uiRet = 0;
	}

	return uiRet;
}

std::string TP_Tool::UnicodeToANSI(const std::wstring& str)
{
	std::string strResult("");

	int textlen = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	if (0 >= textlen)
	{
		// WideCharToMultiByte failed.
		return strResult;
	}

	size_t bufsize = (size_t)(textlen+1);
	char* pBuf = new char[bufsize];
	memset(pBuf, 0, sizeof(char)*bufsize);
	WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, pBuf, textlen, NULL, NULL);//lint !e713

	strResult = pBuf;
	delete[] pBuf;	
	
	
	return strResult;
}

std::string TP_Tool::UnicodeToUTF8(const std::wstring& str)
{
	std::string strResult("");

	int textlen = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	if (0 >= textlen)
	{
		// WideCharToMultiByte failed.
		return strResult;
	}

	size_t bufsize = (size_t)(textlen+1);
	char* pBuf = new char[bufsize];
	memset(pBuf, 0, sizeof(char)*bufsize);
	WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, pBuf, textlen, NULL, NULL);//lint !e713

	strResult = pBuf;
	delete[] pBuf;

	return strResult;
}

std::wstring TP_Tool::ANSIToUnicode(const std::string& str)
{
	std::wstring strResult(L"");

	int textlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	if (0 >= textlen)
	{
		// MultiByteToWideChar failed.
		return strResult;
	}

	size_t bufsize = (size_t)(textlen+1);
	wchar_t* pBuf = new wchar_t[bufsize];
	memset(pBuf, 0, sizeof(wchar_t)*bufsize);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (LPWSTR)pBuf, textlen);//lint !e713

	strResult = pBuf;
	delete[] pBuf;

	return strResult;
}

std::wstring TP_Tool::UTF8ToUnicode(const std::string& str)
{
	std::wstring strResult(L"");
	int textlen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	if (0 >= textlen)
	{
		// MultiByteToWideChar failed.
		return strResult;
	}

	size_t bufsize = (size_t)(textlen+1);
	wchar_t* pBuf = new wchar_t[bufsize];
	memset(pBuf, 0, sizeof(wchar_t)*bufsize);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, (LPWSTR)pBuf, textlen);//lint !e713

	strResult = pBuf;
	delete[] pBuf;	

	return strResult;
}

std::string TP_Tool::UTF8ToANSI(const std::string& str)
{
	std::wstring strUnicode = UTF8ToUnicode(str);
	std::string strAnsi = UnicodeToANSI(strUnicode);
	return strAnsi;
}

std::string TP_Tool::ANSIToUTF8(const std::string& str)
{
	std::wstring strUnicode = ANSIToUnicode(str);
	std::string strUtf8 = UnicodeToUTF8(strUnicode);
	return strUtf8;
}

std::string TP_Tool::GetIPByUIntValue(unsigned long ulIP)
{
	int val1 = (ulIP & 0xFF000000) >> 24;
	int val2 = (ulIP & 0x00FF0000) >> 16;
	int val3 = (ulIP & 0x0000FF00) >> 8;
	int val4 = (ulIP & 0x000000FF);

	std::string str = ".";
	std::string strIP
		= Int2String(val1)
		+ str
		+ Int2String(val2)
		+ str
		+ Int2String(val3)
		+ str
		+ Int2String(val4);

	return strIP;
}
#if 0
std::string TP_Tool::GetEncryptPassword(const std::string& strPath)
{
	const int LENGTH = 256;
	char val[LENGTH] = {0};
	std::string strPassword = "";

	memset(val, 0, sizeof(char)*LENGTH);
	unsigned long dwRet = GetPrivateProfileString(SECTION_SERVER_INFO, KEY_NEED_ENCRYPT, "", val, LENGTH, strPath.c_str());
	CHECK_READ_CONFIG_FILE(dwRet);
	std::string m_strNeedEncrypt = val;

	memset(val, 0, sizeof(char)*LENGTH);
	dwRet = GetPrivateProfileString(SECTION_SERVER_INFO, KEY_PASSWORD, "", val, LENGTH, strPath.c_str());
	CHECK_READ_CONFIG_FILE(dwRet);
	strPassword = val;

	transform(m_strNeedEncrypt.begin(),m_strNeedEncrypt.end(),m_strNeedEncrypt.begin(),tolower);
	if (0 == m_strNeedEncrypt.compare("true"))
	{
		//加密密码
		unsigned char encryptPwd[BUFFER_SIZE] = {0};
		int iEncryptLen = BUFFER_SIZE;
		int iRet = Sha256AndBase64Encrypt(val, encryptPwd, iEncryptLen);
		if(0 != iRet)
		{
			LOG_RUN_ERROR("Encrypt password failed, error code[%d]", iRet);
			return "";
		}
		std::string strNewPassword;
		if(std::string::npos == strPassword.find(SPECIAL_STRING))
		{
			//第一次加密
			strNewPassword = SPECIAL_STRING;
			strNewPassword.append((char*)encryptPwd);
			dwRet = WritePrivateProfileString(SECTION_SERVER_INFO, KEY_PASSWORD, strNewPassword.c_str(), strPath.c_str());
			CHECK_READ_CONFIG_FILE(dwRet);
			//再加一次密
			memset(encryptPwd, 0x00, BUFFER_SIZE);
			iRet = Sha256AndBase64Encrypt(strNewPassword.c_str(), encryptPwd, iEncryptLen);
			if(0 != iRet)
			{
				LOG_RUN_ERROR("Encrypt password failed, error code[%d]", iRet);
				return "";
			}
		}
		strPassword = (char*)encryptPwd;
	}
	return strPassword;
}

int TP_Tool::Sha256AndBase64Encrypt(const char* pInBuf, unsigned char* pOutBuf, int& iOutLen)
{
	unsigned int iEncryptLen = 0;
	if(0 != SHA256_ENCRYPT((unsigned char*)pInBuf, strlen(pInBuf), pOutBuf, iEncryptLen))//lint !e1773
	{
		LOG_RUN_ERROR("SHA256_ENCRYPT failed");
		return -1;
	}
	unsigned char strBuf[BUFFER_SIZE]={0};
	memcpy(strBuf, pOutBuf, iEncryptLen);
	memset(pOutBuf, 0x00, iEncryptLen);
	iOutLen = BUFFER_SIZE;
	if(TRUE != BASE64_ENCRYPT(BINARY_NO_FORMAT, strBuf, iEncryptLen, pOutBuf, iOutLen))//lint !e1773 !e713
	{
		LOG_RUN_ERROR("BASE64_ENCRYPT failed");
		return -1;
	}

	return 0;
}//lint !e1762

#endif
void TP_Tool::Str2HexStr(char* _ucDst, unsigned char* _ucSrc, int len)
{
	char* tempUcDst=_ucDst;
	for (int i = 0; i < len; ++i)
	{
		//sprintf(_ucDst, "%s%02x", tempUcDst, _ucSrc[i]);
		(void)sprintf_s(_ucDst, strlen(tempUcDst)+4, "%s%02x", tempUcDst, _ucSrc[i]);   
	}
}


std::string TP_Tool::GetLocalTimeZone()
{

	char strbuff[256]={0};
	SYSTEMTIME t1;  
	SYSTEMTIME t2;
	::GetSystemTime(&t2);
	::GetLocalTime(&t1);	
	
	int hour;
	int min;

	min = t1.wMinute - t2.wMinute;
	hour = t1.wHour - t2.wHour;

	if (min<0)
	{
		min = 0 - min;
		if(hour>0)
		{
			hour = hour - 1;
		}
		else
		{
			hour = hour + 1;
		}
		
	}

	(void)sprintf_s(strbuff,255,"+%02d:%02d",hour,min);

	return std::string((char *)strbuff);
}

void TP_Tool::Sha_256(unsigned char* _ucDst, unsigned char* _ucSrc, int len)
{
	CSHADigest sha;
	sha.Start();
	if(sha.ComputeInputBuffer(_ucSrc, len)==0){}else{}
	sha.Stop();
	sha.GetByteResult(_ucDst);
	return;
}
void TP_Tool::EncryptPassword(unsigned char* _strRadomKey,int len, std::string _strPassword, unsigned char *encryptValue, int encryptLen)
{
	//	string str = "AFCGprgpHrTAjkzFAJiYJw==";
	//	memcpy(_strRadomKey, str.c_str(), len);
	//密码加密
	unsigned char ucPass[32] = {0};

	int _strPasswordLen=0;
	if(_strPassword.length() && (_strPasswordLen = _strPassword.length()))
	{
	}

	Sha_256(ucPass, (unsigned char*)_strPassword.c_str(),_strPasswordLen);
	char ucPassHexBuf[128] = {0};
	Str2HexStr(ucPassHexBuf, ucPass, 32);
	unsigned int iLen = (unsigned int)-1;
	//随机码解密，转成16进制
	unsigned char ucBuf[256] = {0};
	if(base64_decode(ucBuf, &iLen, _strRadomKey, len)==len){}else{}
	//	base64_decode(ucBuf, &iLen, (unsigned char*)str.c_str(), len);
	char ucHexBuf[256] = {0};
	Str2HexStr(ucHexBuf, ucBuf, iLen);

	//拼接
	unsigned char ucAppend[512] = {0};
	memcpy(ucAppend, ucPassHexBuf, 64);
	memcpy(ucAppend+64, ucHexBuf, 2*iLen);

	unsigned char ucRet[512] = {0};
	Sha_256(ucRet, ucAppend, 64+2*iLen);

	char uu[128] = {0};
	Str2HexStr(uu, ucRet, 32);
	std::string ret = (char *)ucRet;
	char output[512]={0};
	unsigned int outputlen;
	if(base64_encode((unsigned char *)output,&outputlen,ucRet,strlen((const char *)ucRet))==outputlen){}else{}
	memcpy_s(encryptValue, encryptLen, ucRet, 512);
	return ;
}
