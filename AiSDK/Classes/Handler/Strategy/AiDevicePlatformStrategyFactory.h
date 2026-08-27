//
//  AiDevicePlatformStrategyFactory.h
//  AiSDK
//

#import "AiDevicePlatformStrategy.h"

NS_ASSUME_NONNULL_BEGIN

/// 根据设备平台类型提供无状态、可复用的策略实例。
@interface AiDevicePlatformStrategyFactory : NSObject

/// 未识别的平台类型将回退到 Sifli 策略，保持与默认设备行为一致。
+ (id<AiDevicePlatformStrategy>)strategyForPlatformType:(HWPlatformType)platformType;

@end

NS_ASSUME_NONNULL_END
