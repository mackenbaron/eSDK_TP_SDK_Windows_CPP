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
 * @file  TP_Tool.h 
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief  ���������ӿ��࣬��Ҫ��һЩ������������ͳһ��װ(����˺Ϳͻ��˹����ļ�)
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init TP_Tool.h
****************************************************/

#ifndef __TP_Tool_H__
#define __TP_Tool_H__

#include <string>


class TP_Tool
{
private:
	TP_Tool();
	~TP_Tool();

	// ·������
public:
	static std::string GetServicePath();
	static std::string GetServicePathEx();
	static std::string GetDllPath(const std::string& strDllName);
	static void RelativePathToAbsolute(std::string& strPath);
	static BOOL CreateMultipleDirectory(const std::string& path);

	// ����ת��
public:
	// int ת��Ϊ std::string
	static std::string Int2String(int iVar);
	// unsigned int ת��Ϊ std::string
	static std::string UInt2String(unsigned int iVar);
	// double װ��Ϊ std::string
	static std::string Double2String(double dVar);
	// std::string ת��Ϊ int
	static int String2Int(const std::string& str);
	// std::string ת��Ϊ unsigned int
	static unsigned int String2UInt(const std::string& str);
	// std::wstring ת��Ϊ int
	static int WString2Int(const std::wstring& wstr);
	// std::wstring ת��Ϊ unsigned int
	static unsigned int WString2UInt(const std::wstring& wstr);

	// ����ת��
public:	
	static std::string UnicodeToANSI(const std::wstring& str);
	static std::string UnicodeToUTF8(const std::wstring& str);
	static std::wstring ANSIToUnicode(const std::string& str);
	static std::wstring UTF8ToUnicode(const std::string& str);
	static std::string UTF8ToANSI(const std::string& str);
	static std::string ANSIToUTF8(const std::string& str);

	// IP����
public:
	static std::string GetIPByUIntValue(unsigned long ulIP);
	static std::string GetLocalTimeZone();

	// ���봦��
public:
	static std::string GetEncryptPassword(const std::string& strPath);
public:
	static void Str2HexStr(char* _ucDst, unsigned char* _ucSrc, int len);
	static void Sha_256(unsigned char* _ucDst, unsigned char* _ucSrc, int len);
	static void EncryptPassword(unsigned char* _strRadomKey,int len, std::string _strPassword, unsigned char *encryptValue, int encryptLen);

	// ������ܴ���
private:
	static int Sha256AndBase64Encrypt(const char* pInBuf, unsigned char* pOutBuf, int& iOutLen);
};

#endif
