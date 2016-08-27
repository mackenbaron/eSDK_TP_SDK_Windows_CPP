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
#include <string.h>
#include "base64.h"


static char basis_64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


static char index_64[128] =
{
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
    -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1
};


#define char64(c)  (((c) > 127) ? -1 : index_64[(c)])


int base64_encode(unsigned char* outputBuf, unsigned int* outputLen,
                   unsigned char* inputBuf, unsigned int inputLen)
{
    unsigned char c1, c2, c3;
    unsigned char *pOutputBuf = outputBuf;

    unsigned int count = 0;//, charsPerLine = 0;


    c1 = 0x00;
    c2 = 0x00;
    c3 = 0x00;

    while (count < inputLen)
    {
        c1 = inputBuf[count++];
        if (count == inputLen)
        {
            c2 = 0x00;
            *pOutputBuf++ = basis_64[c1 >> 2];
            *pOutputBuf++ = basis_64[(((c1 & 0x3) << 4) | ((c2 & 0xF0) >> 4))];
            *pOutputBuf++ = '=';
            *pOutputBuf++ = '=';
        }
        else	// count < inputLen
        {
            c2 = inputBuf[count++];
            if (count == inputLen)
            {
                c3 = 0x00;
                *pOutputBuf++ = basis_64[c1 >> 2];
                *pOutputBuf++ = basis_64[(((c1 & 0x03) << 4) | ((c2 & 0xF0) >> 4))];
                *pOutputBuf++ = basis_64[(((c2 & 0x0F) << 2) | ((c3 & 0xC0) >> 6))];
                *pOutputBuf++ = '=';
            }
            else // count  < inputLen
            {
                c3 = inputBuf[count++];
                *pOutputBuf++ = basis_64[c1 >> 2];
                *pOutputBuf++ = basis_64[(((c1 & 0x03) << 4) | ((c2 & 0xF0) >> 4))];
                *pOutputBuf++ = basis_64[(((c2 & 0x0F) << 2) | ((c3 & 0xC0) >> 6))];
                *pOutputBuf++ = basis_64[(c3 & 0x3F)];
            }
        }

        //charsPerLine += 4;

    } //end while

    *pOutputBuf++ = '\0';

    *outputLen = strlen((char*)outputBuf);

    return *outputLen;
}

// std::string base64_encode(){
// 	int iLen = 0;
// 	bool l_bFlag;
// 	int l_iGroup;
// 	char[] l_szData;
// 	byte[] l_btTmp;
// 
// 	int ii;
// 	int jj;
// 	int kk;
// 
// 	string l_stEncoding = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
// 
// 	if (btData == null)
// 	{
// 		return null;
// 	}
// 
// 	if ((iLen <= 0) || (iLen > btData.Length))
// 	{
// 		iLen = btData.Length;
// 	}
// 
// 	l_bFlag = ((iLen % 3) == 0);
// 
// 	l_iGroup = iLen / 3;
// 
// 	ii = l_iGroup;
// 
// 	if (!l_bFlag)
// 	{
// 		ii++;
// 	}
// 
// 	l_szData = new char[4 * ii];
// 	l_btTmp = new byte[3];
// 
// 	for (ii = 0, jj = 0, kk = 0; ii < l_iGroup; ii++)
// 	{
// 		l_btTmp[0] = btData[kk++];
// 		l_btTmp[1] = btData[kk++];
// 		l_btTmp[2] = btData[kk++];
// 
// 		l_szData[jj++] = l_stEncoding.ElementAt((l_btTmp[0] >> 2) & 0x3F);
// 		l_szData[jj++] = l_stEncoding.ElementAt(((l_btTmp[0] & 0x03) << 4)
// 			| ((l_btTmp[1] >> 4) & 0x0F));
// 		l_szData[jj++] = l_stEncoding.ElementAt(((l_btTmp[1] & 0x0F) << 2)
// 			| ((l_btTmp[2] >> 6) & 0x03));
// 		l_szData[jj++] = l_stEncoding.ElementAt(l_btTmp[2] & 0x3F);
// 	}
// 
// 	if (!l_bFlag)
// 	{
// 		l_btTmp[0] = btData[kk++];
// 
// 		l_szData[jj++] = l_stEncoding.ElementAt((l_btTmp[0] >> 2) & 0x3F);
// 		l_szData[jj + 1] = '=';
// 		l_szData[jj + 2] = '=';
// 
// 		if ((iLen % 3) == 1)
// 		{
// 			l_szData[jj] = l_stEncoding.ElementAt((l_btTmp[0] & 0x03) << 4);
// 		}
// 		else
// 			// if ((iLen % 3) == 2)
// 		{
// 			l_btTmp[1] = btData[kk];
// 
// 			l_szData[jj++] = l_stEncoding.ElementAt(((l_btTmp[0] & 0x03) << 4)
// 				| ((l_btTmp[1] >> 4) & 0x0F));
// 			l_szData[jj] = l_stEncoding.ElementAt((l_btTmp[1] & 0x0F) << 2);
// 		}
// 	}
// 
// 	return new string(l_szData);
// }


int base64_decode(unsigned char* outputBuf, unsigned int* outputLen,
                   unsigned char* inputBuf, unsigned int inputLen)
{
    unsigned char c1, c2, c3, c4;
    unsigned int count = 0;
	if (inputLen % 4 != 0)
	{
		int iLen = 4 - (inputLen % 4);
		for (int i = 0; i < iLen; ++i)
		{
			*(inputBuf + inputLen + i) = '=';
		}
		*(inputBuf + inputLen + iLen) = '\0';
	}
    c1 = *inputBuf++;
    while (c1 != '\0')
    {
        c2 = *inputBuf++;
        c3 = *inputBuf++;
        c4 = *inputBuf++;

        c1 = char64(c1);
        c2 = char64(c2);

        outputBuf[count++] = ((c1 << 2) | ((c2 & 0x30) >> 4));

        if (c3 != '=')
        {
            c3 = char64(c3);
            outputBuf[count++] = (((c2 & 0XF) << 4) | ((c3 & 0x3C) >> 2));

            if (c4 != '=')
            {
                c4 = char64(c4);
                outputBuf[count++] = (((c3 & 0x03) << 6) | c4);
            }
        }

        c1 = *inputBuf++;
        if (c1 == '\r')
        {
            c1 = *inputBuf++;
            if (c1 == '\n')
                c1 = *inputBuf++;
        }
    }// while c1 != 0
    
    outputBuf[count] = '\0';//xumm add 
    *outputLen = count;



    return count;
}


