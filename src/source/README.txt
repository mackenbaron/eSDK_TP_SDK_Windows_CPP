TP Native SDK

TP Native PC 开放的SDK接口，开放会议调度、会议控制、会场管理、终端管理等能力。
v1.5.70B117
1、修改问题
   1. 问题单号：DTS2016080104036，激活Ad hoc会议模板会失败，提示213000020（native处理异常）
   
v1.5.70B115
1、修改问题
   1. 问题单号：DTS2016062705494,新增会议模板，当模板名称中包含中文时，提示213000020（native处理异常）
   2. 查询Adhoc会议模板接口，当XML中presentationVideo节点为空时，presentationVideo节点之后的信息解析发生异常
   3. 问题单号：DTS2016070401001，添加Adhoc会议模板，videoFormat字段与设置不一致
   4. 查询Adhoc会议模板接口，不能正确的获得pagesinfo

v1.5.70B111
1、修改问题
   1. 问题单号: DTS2016052604661,订阅接口，接口文档中说明，当入参confIds为空时，订阅所有，实际当confIds为空时，接口报错。
   2. 问题单号: DTS2016052604575,调用订阅接口，订阅信息列表为两条，订阅失败，接口返回213000020 native处理异常
   3. 问题单号: DTS2016052408516,synchAdhocConfFreeBusyEx接口，接口返回成功，但是无法查询出信息
   4. 问题单号: DTS2016052408237,查询会场信息，信息中含有中文的时候，会出现乱码

v1.5.70B108
1、修改问题
   1. 查询点对点话单（queryPointToPointCDREx），即使有话单，查询依然为空
   2. 查询多点话单（queryMultiPointCDREx），响应超时
   3. 结构体FilterBaseEx中删除std::string value; 结构体QueryConfigEx中list<FilterBaseEx> filters改list<StringFilterEx> filters; ConferenceInfoEx中新增int maxSitesCount; 相应代码一并做了修改
2、更新eSDKLogAPI.dll
3、更新eSDKHTTPClient.dll，libcurl.dll的openssl库为1.0.1t

v1.5.70B104
1.和B102相比，更新了libcurl.dll依赖的openssl版本为1.0.1s，其他地方未变更

v1.5.70B102
1、增加了9个新的接口.如下所示：
  1. addAdhocConfTemplateEx
  2. editAdhocConfTemplateEx
  3. delAdhocConfTemplateEx
  4. queryAdhocConfTemplateListEx
  5. queryScheduleConferencesEx
  6. enablePushEx
  7. subscribeEx
  8. queryNotificationEx
  9. releasequeryNotificationMemery

V1.5.50B102
1、修改问题:C_queryMCUFutureResourceEx (查询未来时间MCU的资源占用情况) 查询时长为空，其他参数正确时，查询MCU资源失败，应该返回错误码 570462210，实际返回 2130000010 异常
2、完善日志功能.
