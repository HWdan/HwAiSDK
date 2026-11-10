# AiSDK

支持 iOS 12.0 及以上版本，使用 arm64 真机运行。

1.在 Podfile 添加：

```ruby
source 'https://cdn.cocoapods.org/'

platform :ios, '12.0'
use_frameworks!

# 添加到 App 的 target 中
pod 'AiSDK', :git => 'https://github.com/HWdan/HwAiSDK.git', :branch => 'main'
pod 'WatchfaceSDK', :git => 'https://github.com/HWdan/WatchfaceSDK.git', :branch => 'main'
```

执行 `pod install` 安装依赖。

`use_frameworks!` 不要加 `:linkage => :static`。AiSDK 是动态框架，HwBluetoothSDK 和 NativeLib 只链接进这一份。只在 App target 里 `pod 'AiSDK'`，并由 App Embed 一次。Hawofit.framework、TitanBandLibrary 不要再把 AiSDK、HwBluetoothSDK、NativeLib 链进去或再 Embed 一份，否则 `HwBluetoothDevice` 会注册多次，Swift 桥接扫描结果数组时会崩溃。其它 framework 需要调用时，只链接 App 里的那一份动态 AiSDK，不要再链接这两个静态库。

支持杰里表盘的 App 需要自行加入 `JLBmpConvertKit.xcframework` 1.2.0（Embed & Sign，iOS 10+），并在启动杰里预览或表盘传输前注册转换器：

```objc
#import <AiSDK/AiSDK+BmpConverter.h>
#import <JLBmpConvertKit/JLBmpConvertKit.h>

[[AiSDK sharedInstance] setJLBmpDataConverter:^NSData * _Nullable(NSData *imageData) {
    JLBmpConvertOption *option = [[JLBmpConvertOption alloc] init];
    option.convertType = JLBmpConvertType707N_ARGB;
    option.pixelformat = JLBmpPixelformat_Auto;
    JLImageConvertResult *result = [JLBmpConvert convert:option ImageData:imageData];
    return result.outFileData;
}];
```

未注册转换器或转换返回 `nil` 时，杰里表盘生成会失败。

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

## 健康分析结果回传

健康分析结果默认回传手表。如仅需在 App 展示，在设置设备信息时配置：

```objc
deviceInfo.healthAnalysisAppOnly = YES;
```

结果通过 `aiHealthAnalysisDone:code:errorMsg:` 回调获取。
