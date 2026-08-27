//
//  AiDevicePlatformStrategy.h
//  AiSDK
//

#import <Foundation/Foundation.h>
#import "AiDeviceInfo.h"

NS_ASSUME_NONNULL_BEGIN

@class AiDeviceInfo;
@class AiSDK;
@class UIImage;
@protocol IImageToWatchfaceHandler;

typedef void (^AiDeviceRecordDataCallback)(NSData *_Nullable data, NSError *_Nullable error);

/**
 * 将不同设备平台的行为差异集中在策略中。
 *
 * 新增平台时，实现该平台并在 AiDevicePlatformStrategyFactory 中注册，
 * 调用端无需根据平台类型编写条件分支。
 */
@protocol AiDevicePlatformStrategy <NSObject>

/// 创建与当前平台匹配的表盘发送处理器。
- (id<IImageToWatchfaceHandler>)createWatchfaceHandlerWithImage:(UIImage *)image
                                                      deviceInfo:(AiDeviceInfo *)deviceInfo;
/// 从设备读取当前平台格式的录音数据。
- (void)requestRecordDataWithCallback:(AiDeviceRecordDataCallback)callback;
/// 将文生图结果分发给当前平台对应的预览处理流程。
- (void)completeTextToImageWithSDK:(AiSDK *)sdk
                              image:(UIImage *_Nullable)image
                               code:(NSInteger)code
                           errorMsg:(NSString *_Nullable)errorMsg;

@end

NS_ASSUME_NONNULL_END
