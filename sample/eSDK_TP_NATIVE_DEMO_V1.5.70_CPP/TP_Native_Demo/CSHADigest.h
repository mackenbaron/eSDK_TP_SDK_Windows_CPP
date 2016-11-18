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
 * @file   CSHADigest.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   SHA digest encryption function
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init  CSHADigest.h
****************************************************/
#ifndef __CSHADIGEST_H__
#define __CSHADIGEST_H__
typedef unsigned long uInt32;
typedef unsigned short uInt16;
typedef unsigned char uByte;

class CSHADigest
{

public:

	CSHADigest();
	virtual ~CSHADigest();

	//CString str;


	void Start();
	int  ComputeInputBuffer(const uByte* buffer, uInt32 bufferSize);
	void Stop();


	const uByte* GetByteResult();
	void GetByteResult(uByte* ubyteResult);
	
	const char* GetHexResult();
	void GetHexResult(char* chexResult);


	static void ConvertByteResultToHexResult(const uByte* ubyteResult, char* chexResult);

protected:

	struct SSHAContext
	{
	    uInt32 intermediateHash[8];
	    uInt32 lengthLow;
	    uInt32 lengthHigh;

	    uInt16 messageBlockIndex;
	    uByte messageBlock[64];

		
	};
	SSHAContext SHAContext;


	void PadMessage();
	void ProcessMessageBlock();
	

	uByte byteResult[32];
	char hexResult[65];
};

#endif
