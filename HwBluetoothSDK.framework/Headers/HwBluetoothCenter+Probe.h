//
//  HwBluetoothCenter+Probe.h
//  HwBluetoothSDK
//

#import "HwBluetoothCenter.h"

NS_ASSUME_NONNULL_BEGIN

@interface HwBluetoothCenter (Probe)

/// 设置心跳包周期（通用设置 0x63 / 0x71 / 0x16）。
/// 内容为 4 字节，单位分钟。0 表示关闭。
- (HwBluetoothTask *)setProbeInterval:(NSInteger)minutes callback:(HwBoolCallback)callback;

@end

NS_ASSUME_NONNULL_END
