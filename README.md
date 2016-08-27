## eSDK TP Native SDK ##

**eSDK TP Nativa SDK**是针对华为视频会议（Video Conference，VC）解决方案的业务管理平台（SMC2.0），基于标准C++ API，为合作伙伴提供统一账号管理、视频会议调度、会议控制等业务能力。

### 版本更新 ###
最新版本v1.5.70B117  修改如下

- 激活Ad hoc会议模板会失败，提示213000020（native处理异常）


### 开发环境 ###

- 操作系统： Windows7专业版
- Microsoft Visual Studio：Visual Studio 2010专业版


### 文件指引 ###

- src文件夹：包含eSDK TP Nativa SDK源码
- sample文件夹：包含如何使用eSDK TPNative SDK的样例
- doc：包含eSDK TP Native SDK的接口参考，开发指南
- third-party:包含eSDK TP Native SDK中的第三方库


### 入门指导 ###

- 编译eSDK TP Native SDK：在src文件夹中找到TP\_Native\_SDK.sln，并使用VS2010打开它。在VS2010中，菜单>Build>Build Solution。注意区分Debug和Realse版本。
- 在sample中包含上一步编译的SDK，并将TP\_Native_SDK.dll拷贝到sample的运行目录
- 把third-party中的所有文件拷贝到sample的运行目录。注意区分Debug和Realse版本。
- 在sample运行目录下找到esdk\_tp\_native\_professional_cs.dll.config文件，修改其中的url为你自己的TP server。
- 详细的开发指南请参考doc中的开发指南


### 获取帮助 ###

在开发过程中，您有任何问题均可以至[DevCenter](https://devcenter.huawei.com)中提单跟踪。也可以在[华为开发者社区](http://bbs.csdn.net/forums/hwucdeveloper)中查找或提问。另外，华为技术支持热线电话：400-822-9999（转二次开发）