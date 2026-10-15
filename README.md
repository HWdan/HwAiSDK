# AiSDK

支持 iOS 12.0 及以上版本，使用 arm64 真机运行。

1.在 Podfile 添加：

```ruby
source 'http://gitlab.hanshuang.ltd/oa/v2/ios-podspecs.git'
source 'https://cdn.cocoapods.org/'

platform :ios, '12.0'
use_frameworks!

# 添加到 App 的 target 中
pod 'AiSDK', :git => 'https://github.com/HWdan/HwAiSDK.git', :branch => 'main'
pod 'WatchfaceSDK', :git => 'https://github.com/HWdan/WatchfaceSDK.git', :branch => 'main'
```

执行 `pod install` 安装依赖。
  

2.初始化- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions：

    [[SifliWatchfaceSDK getInstance] initSDK];
    [HwAIManager sharedInstance] initSDK];

//可以自己创建一个类管理HwAIManager
- (void) initSDK
{
    // 需要实现代理方法
    [[AiSDK sharedInstance] setLogger:self];
    [[AiSDK sharedInstance] setAiErrorMessageProvider:self];
    // 需要实现代理方法
    [AiSDK sharedInstance].callback = self;
    // 开始工作
    [[AiSDK sharedInstance] startWorking];
}

//绑定后、连接设备或者切换设备语言更新AiSDK设备信息：
- (void)updateDeviceInfo {
    
    NSInteger width = [Watch current].width;
    NSInteger height = [Watch current].height;
    NSInteger cornerRadius = [Watch current].radius;
    NSInteger thumbnailWidth = [Watch current].thumbnailSize.width;
    NSInteger thumbnailHeight = [Watch current].thumbnailSize.height;
    NSInteger thumbnailCornerRadius = [Watch current].thumbnailRadius;
    
    self.deviceInfo = [[AiDeviceInfo alloc] init];
    self.deviceInfo.Id = [Watch current].Id;
    self.deviceInfo.mac = [Watch current].mac;
    self.deviceInfo.name = [Watch current].name;
    self.deviceInfo.width = (width > 0) ? width : 480;
    self.deviceInfo.height = (height > 0) ? height : 480;
    self.deviceInfo.cornerRadius = (cornerRadius > 0) ? cornerRadius : 240;
    self.deviceInfo.thumbnailWidth = (thumbnailWidth > 0) ? thumbnailWidth : 264;
    self.deviceInfo.thumbnailHeight = (thumbnailHeight > 0) ? thumbnailHeight : 264;
    self.deviceInfo.thumbnailCornerRadius = (thumbnailCornerRadius > 0) ? thumbnailCornerRadius : 132;
    
    //方屏ai表盘缩略图需要加白色边框
    if (![Watch current].isCircle && [Watch current].isSifli) {
        self.deviceInfo.needPreviewBorder = YES;
        self.deviceInfo.previewBorderWidth = 1;
        self.deviceInfo.previewBorderColor = Theme.whiteColor;
    }
    
    //不是跟随系统，需要获取本地保存的语言设置
    HwLogWarn(@"[Watch current].deviceLanguage == %@",[Watch current].deviceLanguage);
    if ([Watch current].deviceLanguage.integerValue != -1 && [Watch current].deviceLanguage != nil) {
        NSString *currentLocale = [HwLanguageUtil getLocaleWithLanguage:[Watch current].deviceLanguage.integerValue];
        self.deviceInfo.currentLocale = currentLocale;
    } else {
        NSString *userLanguage = [[NSLocale preferredLanguages] firstObject];
        if (!userLanguage) {
            HwLogWarn(@"userLanguage == nil,设置默认英文");
            userLanguage = @"en-US";
        }
        self.deviceInfo.currentLocale = userLanguage;
    }
    HwLogWarn(@"切换语言给AI SDK设置语言：%@",self.deviceInfo.currentLocale);
    
    HwLogWarn(@"AI SDK 语言设置：%@", self.deviceInfo.currentLocale);
    
    [[AiSDK sharedInstance] setDeviceInfo:self.deviceInfo];
}



#pragma mark - ILog 代理
- (void)d:(nonnull NSString *)msg {
    HwLogWarn(@"dddd: %@", msg);
    
}

- (void)e:(nonnull NSString *)msg {
    HwLogWarn(@"eee: %@", msg);
    
}

- (void)i:(nonnull NSString *)msg {
    HwLogWarn(@"iiii: %@", msg);
    
}

- (void)w:(nonnull NSString *)msg {
    HwLogWarn(@"www: %@", msg);
    
}

#pragma mark - AiSDKCallback 代理
- (void) aiMeetingDone:(HwMeeting *_Nullable)meeting
         voiceFilePath:(NSString *_Nullable)voiceFilePath
           meetingTime:(NSDate *_Nullable)meetingTime
                  code:(NSInteger)code
              errorMsg:(NSString *_Nullable)errorMsg {
    if (code == 0) {
        //会议返回成功处理数据
    } else {
        HwLogWarn(@"会议返回失败：errorMsg = %@，code = %ld",errorMsg,code);
    }
}

- (void) aiHealthAnalysisDone:(HwHealthAnalysisResult *_Nullable)result
                         code:(NSInteger)code
                     errorMsg:(NSString *_Nullable)errorMsg {
    
    //加个判断总结内容是空的，不保存数据
    if (code == 0 && result.summary && ![result.summary isEqualToString:@""]) {
        //健康分析数据处理
    } else {
        HwLogWarn(@"健康分析回失败：errorMsg = %@，code = %ld",errorMsg,code);
    }
}

- (void)aiImageDone:(UIImage *)image code:(NSInteger)code errorMsg:(NSString *)errorMsg
{
    
}

- (void)aiPreviewDone:(UIImage *)image code:(NSInteger)code errorMsg:(NSString *)errorMsg
{
    
}

- (void)aiStartSendingPreview {
    
}

- (void) aiStartSendingWatchface
{
    
}

- (void)aiSendingWatchfaceProgressUpdated:(float)progress
{
    NSLog(@"进度：%f",progress);
}

- (void) aiSentWatchface:(SlifiCustomWatchface *)watchface code:(NSInteger)code errorMsg:(NSString *)errorMsg
{
    if (code != 0) {
        NSLog(@"安装AI表盘失败：%@",errorMsg);
      
        
    } else {
        NSLog(@"安装AI表盘成功");
        
    }
        
}

## App 健康报告

支持由 App 主动请求睡眠生物钟、运动洞察和身体状况报告。
使用前申请 OAS 渠道参数，并在调用 `setDeviceInfo:` 前完成配置：

```objc
#import <AiSDK/AiSDK-Swift.h>
#import <AiSDK/AiSDK+HealthAgents.h>

[[AiOASClient shared] configureWithChannelId:channelId
                                    appKey:appKey
                                   appUuid:userId
                                appChannel:appChannel];
```

配置后，按上面的设备信息设置流程调用 `setDeviceInfo:`。

| 功能 | 接口 | 入参类型 |
| --- | --- | --- |
| 睡眠生物钟 | `generateSleepChronotype:completion:` | `AiSleepChronotypeInput` |
| 运动洞察 | `generateExerciseInsight:completion:` | `AiExerciseInsightInput` |
| 身体状况 | `generateBodyStatus:completion:` | `AiBodyStatusInput` |

参数、单位和返回字段见 [AiHealthAgentModel.h](AiSDK/Classes/Handler/Model/AiHealthAgentModel.h)。
结果通过 completion 在主线程返回，同时提供结果对象或 `NSError`。

睡眠报告通过 `period` 指定日（0）、周（1）、月（2），通过 `use12HourClock` 选择时间制式。
入睡和起床时间分别使用 `HH:mm:ss` 或 `hh:mm:ss AM/PM` 格式，缺失日期填字符串 `"0"`。

## 健康分析结果回传

健康分析结果默认回传手表。如仅需在 App 展示，在设置设备信息时配置：

```objc
deviceInfo.healthAnalysisAppOnly = YES;
```

结果通过 `aiHealthAnalysisDone:code:errorMsg:` 回调获取。
