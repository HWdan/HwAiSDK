#import <Foundation/Foundation.h>
#import "IHealthAnalysisResultHandler.h"

NS_ASSUME_NONNULL_BEGIN

/// 独立处理健康分析，仅通过 App 回调返回结果，不向设备下发。
@interface AppOnlyHealthAnalysisResultHandler : NSObject<IHealthAnalysisResultHandler>
@end

NS_ASSUME_NONNULL_END
