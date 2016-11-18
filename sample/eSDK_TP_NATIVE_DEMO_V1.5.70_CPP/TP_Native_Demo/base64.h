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
 * @file   base64.h
 * @copyright Copyright (c) 2013-2016 Huawei Tech.Co.,Ltd
 * @brief   base64 encode and decode function
 * @details
 * @author pengyaowen p00327183
 * @version 1.0
 * @date 2015-09-17    
 * @history  v1.1 2015-09-17 Init base64.h
****************************************************/
/** Provide base 64 encoding and decoding as described in rfc822.
 */
#ifndef BASE64_HXX
#define BASE64_HXX

/** Places base 64 encoded input buffer into output buffer.
*/
int base64_encode(unsigned char* outputBuf, unsigned int* outputLen,
                          unsigned char* inputBuf, unsigned int inputLen);


/** Places base 64 decoded input buffer into output buffer.
*/
int base64_decode(unsigned char* outputBuf, unsigned int* outputLen,
                          unsigned char* inputBuf, unsigned int inputLen);
#endif // BASE64_HXX

