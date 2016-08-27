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
#include "CSHADigest.h"
#include <fstream>
#include <stdio.h>
using namespace std;

#define Ch(a,b,c)\
	((a & b)^((~a) & c))
#define Maj(a,b,c)\
	((a & b)^(a & c)^(b & c))
#define ROTR(n,x) \
	(((x) >> (n)) | ((x) << (32-(n))))
#define SHR(n,x) \
	((x) >> (n))
#define Sigam0(y) \
	(ROTR(2,y)^ROTR(13,y)^ROTR(22,y))
#define Sigam1(y) \
	(ROTR(6,y)^ROTR(11,y)^ROTR(25,y))
#define sigam0(y) \
	(ROTR(7,y)^ROTR(18,y)^SHR(3,y))
#define sigam1(y) \
	(ROTR(17,y)^ROTR(19,y)^SHR(10,y))


CSHADigest::CSHADigest()
{
	SHAContext.lengthLow = 0;
	SHAContext.lengthHigh = 0;
	SHAContext.messageBlockIndex = 0;

	SHAContext.intermediateHash[0] = 0x6a09e667;
	SHAContext.intermediateHash[1] = 0xbb67ae85;
	SHAContext.intermediateHash[2] = 0x3c6ef372;
	SHAContext.intermediateHash[3] = 0xa54ff53a;
	SHAContext.intermediateHash[4] = 0x510e527f;
	SHAContext.intermediateHash[5] = 0x9b05688c;
	SHAContext.intermediateHash[6] = 0x1f83d9ab;
	SHAContext.intermediateHash[7] = 0x5be0cd19;
	

	uInt32 i;

	for(i = 0 ; i < 64 ; i++)
		SHAContext.messageBlock[i] = 0;

	for(i = 0 ; i < 32 ; i++)
		byteResult[i] = 0;

	for(i = 0 ; i < 65 ; i++)
		hexResult[i] = 0;
}

CSHADigest::~CSHADigest()
{

}



void CSHADigest::Start()
{
	SHAContext.lengthLow = 0;
	SHAContext.lengthHigh = 0;
	SHAContext.messageBlockIndex = 0;

	SHAContext.intermediateHash[0] = 0x6a09e667;
	SHAContext.intermediateHash[1] = 0xbb67ae85;
	SHAContext.intermediateHash[2] = 0x3c6ef372;
	SHAContext.intermediateHash[3] = 0xa54ff53a;
	SHAContext.intermediateHash[4] = 0x510e527f;
	SHAContext.intermediateHash[5] = 0x9b05688c;
	SHAContext.intermediateHash[6] = 0x1f83d9ab;
	SHAContext.intermediateHash[7] = 0x5be0cd19;

	uInt32 i;

	for(i = 0 ; i < 32 ; i++)
	byteResult[i] = 0;

	for(i = 0 ; i < 65 ; i++)
	hexResult[i] = 0;
}

int CSHADigest::ComputeInputBuffer(const uByte* buffer, uInt32 bufferSize)
{
    if (!bufferSize)
    return 0;                                                                             

    while(bufferSize--)
    {
		if (SHAContext.messageBlockIndex == 64)
		{
			break;
		}
		SHAContext.messageBlock[SHAContext.messageBlockIndex++] = (*buffer & 0xFF);

		SHAContext.lengthLow += 8;
		
		if(SHAContext.lengthLow == 0)                                                    
			SHAContext.lengthHigh++;

		if(SHAContext.messageBlockIndex == 64)
			ProcessMessageBlock();
 
		buffer++;
    }

    return 1;
}


void CSHADigest::Stop()
{
    PadMessage();

	uInt32 i;

    for(i = 0 ; i < 64 ; i++)
    SHAContext.messageBlock[i] = 0;

    SHAContext.lengthLow = 0;
    SHAContext.lengthHigh = 0;

    for(i = 0 ; i < 32 ; i++)
    byteResult[i] = (uByte) (SHAContext.intermediateHash[i >> 2] >> (8 * (3 - (i & 0x03))));       //////////!!!!!

    ConvertByteResultToHexResult(byteResult, hexResult);
}



const uByte* CSHADigest::GetByteResult()
{
	return byteResult;
}
void CSHADigest::GetByteResult(uByte* ubyteResult)
{
	for(uInt32 i = 0 ; i < 32 ; i++)
	ubyteResult[i] = this->byteResult[i];
}

const char* CSHADigest::GetHexResult()
{
	return hexResult;
}


void CSHADigest::GetHexResult(char* chexResult)
{
	for(uInt32 i = 0 ; i < 64 ; i++)                              
	chexResult[i] = this->hexResult[i];
}

void CSHADigest::ConvertByteResultToHexResult(const uByte* ubyteResult, char* chexResult)
{
	char* tempHexResult=chexResult;
	chexResult[0] = 0;
	for(uInt32 i = 0 ; i < 32 ; i++)
		 (void)sprintf_s(chexResult, strlen(tempHexResult)+4,"%s%02X", tempHexResult, ubyteResult[i]);   
    //sprintf(chexResult, "%s%02X", tempHexResult, ubyteResult[i]); 
	
}




void CSHADigest::ProcessMessageBlock()
{
	const uInt32 K[] = 
	{
		0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
		0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
		0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
		0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
		0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
		0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
	};

	uInt32 t;
    uInt32 W[64];
    uInt32 A, B, C, D, E, F, G, H, T1, T2;

    for(t = 0; t < 16; t++)
    {
        W[t] =  SHAContext.messageBlock[t * 4] << 24;
        W[t] |= SHAContext.messageBlock[t * 4 + 1] << 16;
        W[t] |= SHAContext.messageBlock[t * 4 + 2] << 8;
        W[t] |= SHAContext.messageBlock[t * 4 + 3];
    }

    for(t = 16 ; t < 64 ; t++)
		W[t] = sigam1(W[t-2])+W[t-7]+sigam0(W[t-15])+W[t-16];

    A = SHAContext.intermediateHash[0];
    B = SHAContext.intermediateHash[1];
    C = SHAContext.intermediateHash[2];
    D = SHAContext.intermediateHash[3];
    E = SHAContext.intermediateHash[4];
	F = SHAContext.intermediateHash[5];
	G = SHAContext.intermediateHash[6];
	H = SHAContext.intermediateHash[7];
	for(t = 0 ; t < 64 ; t ++)
	{


		T1 = H+Sigam1(E)+Ch(E,F,G)+K[t]+W[t];
		T2 = Sigam0(A)+Maj(A,B,C);
		H = G;
		G = F;
		F = E;
		E = D+T1;
		D = C;
		C = B;
		B = A;
		A = T1+T2;
	}


    SHAContext.intermediateHash[0] += A;
    SHAContext.intermediateHash[1] += B;
    SHAContext.intermediateHash[2] += C;
    SHAContext.intermediateHash[3] += D;
    SHAContext.intermediateHash[4] += E;
	SHAContext.intermediateHash[5] += F;
	SHAContext.intermediateHash[6] += G;
	SHAContext.intermediateHash[7] += H;

    SHAContext.messageBlockIndex = 0;
}

void CSHADigest::PadMessage()
{
    if (SHAContext.messageBlockIndex > 55)
    {
        SHAContext.messageBlock[SHAContext.messageBlockIndex++] = 0x80;

        while(SHAContext.messageBlockIndex < 64)
        SHAContext.messageBlock[SHAContext.messageBlockIndex++] = 0;

        ProcessMessageBlock();

        while(SHAContext.messageBlockIndex < 56)
        SHAContext.messageBlock[SHAContext.messageBlockIndex++] = 0;               
    }
    else
    {
        SHAContext.messageBlock[SHAContext.messageBlockIndex++] = 0x80;

        while(SHAContext.messageBlockIndex < 56)
        SHAContext.messageBlock[SHAContext.messageBlockIndex++] = 0;
    }

	SHAContext.messageBlock[56] = (uByte) (SHAContext.lengthHigh >> 24);            
    SHAContext.messageBlock[57] = (uByte) (SHAContext.lengthHigh >> 16);
    SHAContext.messageBlock[58] = (uByte) (SHAContext.lengthHigh >> 8);
    SHAContext.messageBlock[59] = (uByte) (SHAContext.lengthHigh);
    SHAContext.messageBlock[60] = (uByte) (SHAContext.lengthLow >> 24);
    SHAContext.messageBlock[61] = (uByte) (SHAContext.lengthLow >> 16);
    SHAContext.messageBlock[62] = (uByte) (SHAContext.lengthLow >> 8);
    SHAContext.messageBlock[63] = (uByte) (SHAContext.lengthLow);

    ProcessMessageBlock();
}
